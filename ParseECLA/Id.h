#pragma once
#include <string>

class IdType;

class Id {
private:
    int idValue;
    std::string name;
    IdType* type;

    int extractDeviceNumber() const;

public:
    Id(IdType* type, int devNumber);
    Id(IdType* type);

    int getIdValue() const { return idValue; }
    void setIdValue(int value) { idValue = value; }

    std::string getName() const { return name; }
    void setName(const std::string& value) { name = value; }

    IdType* getType() const { return type; }
    void setType(IdType* value) { type = value; }

    std::string toString() const;
};