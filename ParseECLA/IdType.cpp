#include "IdType.h"
#include "IdGroup.h" // Include the header for IdGroup class

#include <stdexcept>
#include <sstream>
#include <iomanip>

bool IdType::checkIdPattern(int id, IdGroup* group) {
    // Check if the masked bits (bits which are needed for the device counter) are 0 in the id mask.
    return group == nullptr || group->getCount() == 1 || ((id & group->getDeviceNumberMask()) == 0);
}

bool IdType::checkIdPattern() const {
    return checkIdPattern(idPattern, group);
}

bool IdType::checkNamePattern(const std::string& name, IdGroup* group) {
    return group == nullptr || group->getCount() == 1 || name.find("_X_") != std::string::npos;
}

IdType::IdType(int id, IdGroup* group) : group(group) {
    if (!checkIdPattern(id, group)) {
        throw std::invalid_argument("The masked bits for the device number have to be 0 in the ID pattern. (ID: 0x" + std::to_string(id) + ")");
    }
    idPattern = id; // not property but direct variable since validation is already done.
    factor = 1;
    name = toString();
    description = "unknown";
}

void IdType::setIdPattern(int value) {
    if (!checkIdPattern(value, group)) {
        throw std::invalid_argument("The masked bits for the device number have to be 0 in the ID pattern. (ID: 0x" + std::to_string(value) + ")");
    }
    idPattern = value;
}

void IdType::setNamePattern(const std::string& value) {
    if (!checkNamePattern(value, group)) {
        throw std::invalid_argument("The name has to contain an \"_X_\", since there has to be a placeholder for the device number (ID: " + value + ")");
    }
    name = value;
}

void IdType::setUnit(const std::string& value) {
    unit = value;
}

void IdType::setFactor(double value) {
    factor = value;
}

void IdType::setCanInterval(int value) {
    canInterval = value;
}

void IdType::setSdInterval(int value) {
    sdInterval = value;
}

void IdType::setCanThreshold(int value) {
    canThreshold = value;
}

void IdType::setSdThreshold(int value) {
    sdThreshold = value;
}

void IdType::setMin(uint32_t value) {
    min = value;
}

void IdType::setMax(uint32_t value) {
    max = value;
}

void IdType::setDescription(const std::string& value) {
    description = value;
}

std::string IdType::toString() const {
    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << idPattern;
    return "0x" + ss.str();
}