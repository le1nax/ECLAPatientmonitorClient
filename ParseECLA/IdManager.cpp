#include "IdManager.h"
#include <iostream>
#include <regex>
#include <sstream>
#include <iomanip>

// Define the regular expressions
//const std::string ID_LINE_REGEX = "^\\s*(?<name>CAN_ID_\\w+)\\s*=\\s*0x(?<id>[0-9a-fA-F]+),?\\s*\\/\\/(?<description>[^\\|\\t]+)?\\s*(\\|\\s*(?<factor>\\d((\\.|\\,)\\d*)?)?\\s*(?<unit>[^\\|]*[^\\s\\|])?\\s*(\\|\\s*(?<caninterval>\\d+)?\\s*(?<sdinterval>\\d+)?\\s*(?<canthreshold>\\d+((\\.|\\,)\\d+)?)?\\s*(?<sdthreshold>\\d+((\\.|\\,)\\d+)?)?)?\\s*(\\|\\s*(?<min>\\d+)?\\s*(?<max>\\d+)?\\s*)?)?\\s*$";
const std::string ID_LINE_REGEX = R"(^\s*(CAN_ID_\w+)\s*=\s*0x([0-9a-fA-F]+),?\s*\/\/([^|\t]+)?\s*(\|\s*(\d+(?:[.,]\d*)?)?\s*([^|]*[^|\s])?)?\s*(\|\s*(\d+)?\s*(\d+)?\s*(\d+(?:[.,]\d+)?)?\s*(\d+(?:[.,]\d+)?)?)?\s*(\|\s*(\d+)?\s*(\d+)?)?\s*$)";

    
// specifies the format of a group definition line (if a count is defined, there must be a shifter define as well, even if the count is 1).
// sample: "	// idGroup("Florian's Testarea", 5, CAN_TESTAREA_SHIFT, ALARM)"
//const std::string GROUP_LINE_REGEX = "^\\s*//\\s*idGroup\\(((?<none>none)|(\"(?<name>[^\"]+)\"(\\,\\s?(?<count>\\d{1,4})\\,\\s?(?<shifterDefine>\\w+))?(?<alarm>\\,\\s?ALARM)?))\\)\\s*$";
const std::string GROUP_LINE_REGEX = R"(^\s*//\s*idGroup\((none|\"([^\"]+)\"(\,\s?(\d{1,4})\,\s?(\w+))?(\,\s?ALARM)?)\)\s*$)";

// specifies the format of a numeric define, i.e. a define with a hex or a decimal number as value.
// sample: "#define MY_DEFINE   0x123ABC"
//const std::string NUMERIC_DEFINE_REGEX = "^#define[ \t]+(?<name>\\w+)[ \t]+((0x(?<hexValue>[0-9a-fA-F]+))|(?<decValue>\\d+))[ \t]?(\\/\\/[^\\r\\n]*)?$";
const std::string NUMERIC_DEFINE_REGEX = R"(^#define[ \t]+(\w+)[ \t]+((0x[0-9a-fA-F]+)|(\d+))[ \t]?(\/\/[^\r\n]*)?$)";

// specifies the format of the svn revision which is inserted by the svn revision property.
// sample: "$Rev: 1868 $"
//const std::string REVISION_REGEX = "\\$Rev: (?<revision>\\d+) ?\\$";
const std::string REVISION_REGEX = R"(\$Rev: (\d+) ?\$)";

// specifies the begin of the enum which defines the CAN ids.
const std::string ENUM_BEGIN_REGEX = "^\\s*enum\\s*can_id\\s*\\{(\\s*//.*)?$";

// specifies the end of the enum.
const std::string ENUM_END_REGEX = "^\\s*\\}\\s*;(\\s*//.*)$";

// Define the constants
const short DEFAULT_SHIFTER = 12;

IdManager::IdManager(const std::string& idFileLocation) : idFileLocation(idFileLocation) {
    warnings = std::list<std::string>();
    ReadIdInformation();
}

IdManager::~IdManager() {
    for (auto& pair : idDict) {
        delete pair.second;
    }
    for (auto& type : idTypes) {
        delete type;
    }
}

std::ifstream IdManager::getIdReader() {
    std::ifstream fsr(idFileLocation);
    if (!fsr.is_open()) {
        throw std::runtime_error("Failed to open ID file for reading: " + idFileLocation);
    }
    return fsr;
}

std::unordered_map<std::string, int> IdManager::ReadDefines() {
    std::string currentLine;
    std::regex defineRegex(NUMERIC_DEFINE_REGEX);
    std::unordered_map<std::string, int> res;

    std::ifstream fsr = getIdReader();

    if (!fsr.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return res;
    }

    while (std::getline(fsr, currentLine)) {
        std::smatch m;
        if (std::regex_match(currentLine, m, defineRegex)) {
            std::string name = m[1].str();
            int value = 0;
            if (m[2].str().rfind("0x", 0) == 0) { // if hex value
                value = std::stoi(m[2].str(), nullptr, 16);
            } else {
                value = std::stoi(m[4].str());
            }
            res[name] = value;
        }
    }

    fsr.close();
    return res;
}

void IdManager::ReadIdInformation() {
        std::string currentLine;
        std::string idHex;
        std::string factorStr;
        std::string canIntervalStr;
        std::string sdIntervalStr;
        std::string canThresholdStr;
        std::string sdThresholdStr;
        std::string min;
        std::string max;
        double factor = 0;
        int canInterval = 0;
        int sdInterval = 0;
        double threshold = 0;
        double minmax = 0;
        int lineNumber = 0;
        std::smatch mtIdLine;
        std::smatch mtGroupLine;
        std::regex regexIdLine(ID_LINE_REGEX);
        std::regex regexGroupLine(GROUP_LINE_REGEX);
        std::regex regexDeclarationBegin(ENUM_BEGIN_REGEX);
        std::regex regexRevisionNumber(REVISION_REGEX);
        int idNumber = 0;
        IdGroup* currentGroup = nullptr;
        std::unordered_map<std::string, int> defines = this->ReadDefines();

        idDict.clear();
        idsByName.clear();
        idTypes.clear();
        groups = IdGroupList();

        std::ifstream fsr = getIdReader();

        while (std::getline(fsr, currentLine)) {
            lineNumber++;
            if (std::regex_match(currentLine, regexDeclarationBegin)) {
                break;
            }
            if (std::regex_match(currentLine, mtIdLine, regexRevisionNumber)) {
                this->idFileRevision = std::stoi(mtIdLine[1].str());
            }
        }

        while (std::getline(fsr, currentLine)) {
        lineNumber++;
        std::smatch mtIdLine;
          std::smatch mtGroupLine;
        if (std::regex_match(currentLine, mtIdLine, regexIdLine)) {
            idHex = mtIdLine[2].str();
            idNumber = std::stoi(idHex, nullptr, 16);
            if (idDict.count(idNumber)) {
                warnings.push_back("Duplicate ID " + idHex + " found in Line " + std::to_string(lineNumber) + ". It will be ignored.");
                continue;
            }

            try {
                IdType* idType = new IdType(idNumber, currentGroup);
                idType->setNamePattern(mtIdLine[1].str());
                idType->setUnit(mtIdLine[6].str());
                idType->setDescription(mtIdLine[3].str());
                factorStr = mtIdLine[5].str();
                factor = factorStr.empty() ? 1 : std::stod(factorStr.find(",") != std::string::npos ? factorStr.replace(factorStr.find(","), 1, ".") : factorStr);
                factor = (factor == 0) ? 1 : factor;
                idType->setFactor(factor);

                canIntervalStr = mtIdLine[8].str();
                canInterval = canIntervalStr.empty() ? 0 : std::stoi(canIntervalStr);
                idType->setCanInterval(canInterval);

                sdIntervalStr = mtIdLine[9].str();
                sdInterval = sdIntervalStr.empty() ? 0 : std::stoi(sdIntervalStr);
                idType->setSdInterval(sdInterval);

                canThresholdStr = mtIdLine[10].str();
                threshold = canThresholdStr.empty() ? 0 : std::stod(canThresholdStr.replace(canThresholdStr.find("."), 1, ","));
                idType->setCanThreshold(static_cast<int>(threshold / factor));

                sdThresholdStr = mtIdLine[11].str();
                threshold = sdThresholdStr.empty() ? 0 : std::stod(sdThresholdStr.replace(sdThresholdStr.find("."), 1, ","));
                idType->setSdThreshold(static_cast<int>(threshold / factor));

                min = mtIdLine[13].str();
                minmax = min.empty() ? 0 : std::stod(min.replace(min.find("."), 1, ","));
                idType->setMin(static_cast<unsigned int>(minmax / factor));

                max = mtIdLine[14].str();
                minmax = max.empty() ? factor * 4294967295 : std::stod(max.replace(max.find("."), 1, ","));
                idType->setMax(static_cast<unsigned int>(minmax / factor));

                if (currentGroup) {
                    for (int i = 0; i < currentGroup->getCount(); i++) {
                        Id* newId = new Id(idType, i);
                        idDict[newId->getIdValue()] = newId;
                        idsByName[newId->getName()] = newId;
                        currentGroup->getIds().push_back(*newId);
                    }
                } else {
                    Id* newId = new Id(idType);
                    idDict[newId->getIdValue()] = newId;
                    idsByName[newId->getName()] = newId;
                }
                idTypes.push_back(idType);
                } catch (const std::exception& e) {
                    warnings.push_back(e.what());
                }
            }
            else if (std::regex_match(currentLine, mtGroupLine, regexGroupLine)) {
            if (mtGroupLine[1].str() == "none") {
                currentGroup = nullptr;
            } else {
                std::string name = mtGroupLine[2].str();
                currentGroup = groups.getOrCreateGroupByName(name);
                if (!mtGroupLine[6].str().empty()) {
                    currentGroup->setIsAlarmGroup(true);
                }
                if (!mtGroupLine[4].str().empty()) {
                    currentGroup->setCount(std::max(std::stoi(mtGroupLine[4].str()), currentGroup->getCount()));
                } else {
                    currentGroup->setCount(1);
                }
                if (!mtGroupLine[5].str().empty()) {
                    try {
                        std::string shifterDefine = mtGroupLine[5].str();
                        currentGroup->setShifter(defines.at(shifterDefine));
                        currentGroup->setShifterDefine(shifterDefine);
                    } catch (const std::out_of_range&) {
                        warnings.push_back("The shifter define " + mtGroupLine[5].str() + " is not set!");
                        currentGroup->setShifter(DEFAULT_SHIFTER);
                        currentGroup->setShifterDefine(std::to_string(DEFAULT_SHIFTER));
                    }
                } else {
                    currentGroup->setShifter(DEFAULT_SHIFTER);
                }
            }
        }
        }
        fsr.close();
    }

 bool IdManager::deleteIdType(int id) {
        std::ifstream reader;
        std::ofstream writer;
        std::regex regex(ID_LINE_REGEX);

        // Try to open the output file
        try {
            writer.open(idFileLocation + "__", std::ios::out);
            if (!writer) {
                throw std::runtime_error("Cannot write to temporary file " + idFileLocation + "__");
            }
        } catch (const std::exception& e) {
            this->warnings.push_back(e.what());
            return false;
        }

        try {
            reader = getIdReader();
        } catch (const std::exception& e) {
            this->warnings.push_back(e.what());
            writer.close();
            return false;
        }

        std::string currLine;
        while (std::getline(reader, currLine)) {
            std::smatch match;
            if (!std::regex_match(currLine, match, regex) || id != std::stoi(match[2].str(), nullptr, 16)) {
                writer << currLine << std::endl;
            }
        }

        writer.close();
        reader.close();

        std::remove((idFileLocation + "__").c_str());
        std::rename((idFileLocation + "__").c_str(), idFileLocation.c_str());

        // Finally, read all id information again.
        // This is necessary to get rid of all ID instances that used this IdType before.
        this->ReadIdInformation();

        return true;
    }

bool IdManager::deleteIdType(IdType* id) {
    return deleteIdType(id->getIdPattern());
}

bool IdManager::updateIdType(IdType* id) {
        std::ifstream reader;
        std::ofstream writer;
        std::regex regex(ID_LINE_REGEX);
        std::smatch match;
        std::string currLine;

        // Try to open the output file
        try {
            writer.open(idFileLocation + "__", std::ios::out);
            if (!writer) {
                throw std::runtime_error("Cannot write to temporary file " + idFileLocation + "__");
            }
        } catch (const std::exception& e) {
            this->warnings.push_back(e.what());
            return false;
        }

        try {
            reader = getIdReader();
        } catch (const std::exception& e) {
            this->warnings.push_back(e.what());
            writer.close();
            return false;
        }

        // Prepare the factor string with a decimal dot
        std::ostringstream factorStream;
        factorStream << std::fixed << std::setprecision(1) << id->getFactor();
        std::string factorString = factorStream.str();
        std::replace(factorString.begin(), factorString.end(), ',', '.');

        // Copy Units linewise
        while (std::getline(reader, currLine)) {
            if (std::regex_match(currLine, match, regex)) {
                if (std::stoi(match[2].str(), nullptr, 16) == id->getIdPattern()) {
                    writer << "\t" << id->getNamePattern() << "\t\t\t= " << id->toString()
                           << ", //" << id->getDescription() << "\t| " << factorString << " " << id->getUnit() << "\r\n";
                    continue;
                }
            }
            // Else copy:
            writer << currLine << "\n";
        }

        writer.close();
        reader.close();

        std::rename((idFileLocation + "__").c_str(), idFileLocation.c_str());
        std::remove((idFileLocation + "__").c_str());

        return true;
    }

bool IdManager::idExists(int idValue) {
        return idDict.find(idValue) != idDict.end();
    }

std::string IdManager::getLastWarning() {
    if (warnings.empty()) {
        return "";
        }
    return warnings.back();    
}

std::string IdManager::getAllWarnings(const std::string& separator) {
    if (warnings.empty()) return "";
    std::stringstream res;
    for (const std::string& warning : warnings) {
        res << warning << separator;
    }

    // Remove the last separator
    std::string result = res.str();
    if (!result.empty()) {
        result.erase(result.size() - separator.size());
    }
    return result;
}
IdManager* IdManager::getIdManager(const std::string& idFileLocation) {
    // create instance of IdManager
    IdManager* res = new IdManager(idFileLocation);
    // read ids
    res->ReadIdInformation();
    return res;
}

Id* IdManager::getId(int id, bool generateIfUnknown) {
     auto it = idDict.find(id);
    if (it != idDict.end()) {
        return it->second;
    } else {
        return generateIfUnknown ? new Id(new IdType(id, nullptr)) : nullptr;
    }
}