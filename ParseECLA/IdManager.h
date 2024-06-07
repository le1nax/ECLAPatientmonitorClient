#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <regex>
#include <fstream>
#include <stdexcept>

#include "Id.h"
#include "IdGroupList.hpp"
#include "IdType.h"
#include "Constants.h"

class IdManager {
private:
    std::string idFileLocation = "";
    std::unordered_map<int, Id*> idDict;
    int idFileRevision = 0;
    std::unordered_map<std::string, Id*> idsByName;
    std::vector<IdType*> idTypes;
    IdGroupList groups;
    std::list<std::string> warnings;

    std::ifstream getIdReader();
    std::unordered_map<std::string, int> ReadDefines();
    void ReadIdInformation();
    bool deleteIdType(int id);
    bool deleteIdType(IdType* id);
    bool updateIdType(IdType* id);
    bool idExists(int idValue);
    std::string getLastWarning();
    std::string getAllWarnings(const std::string& separator);

public:
    IdManager(const std::string& idFileLocation);
    IdManager() = default;

    ~IdManager();

    static IdManager* getIdManager(const std::string& idFileLocation);

    const std::string& getIdFileLocation() const { return idFileLocation; }
    void setIdFileLocation(const std::string& value) { idFileLocation = value; }
    const std::unordered_map<int, Id*>& getIdDict() const { return idDict; }
    const std::vector<IdType*>& getIdTypes() const { return idTypes; }
    const IdGroupList& getGroups() const { return groups; }
    const std::list<std::string>& getWarnings() const { return warnings; }
    int getIdFileRevision() const { return idFileRevision; }


    Id* getId(int id, bool generateIfUnknown);
};
