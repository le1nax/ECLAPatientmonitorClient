#pragma once
#include <string>
#include <cstdint>
class IdGroup;

class IdType {
private:
    int idPattern;
    std::string name;
    std::string unit;
    double factor;
    int canInterval;
    int sdInterval;
    int canThreshold;
    int sdThreshold;
    uint32_t min;
    uint32_t max;
    std::string description;
    IdGroup* group;

    static bool checkIdPattern(int id, IdGroup* group);
    bool checkIdPattern() const;
    static bool checkNamePattern(const std::string& name, IdGroup* group);

public:
    IdType(int id, IdGroup* group);

    int getIdPattern() const { return idPattern; }
    void setIdPattern(int value);

    std::string getNamePattern() const { return name; }
    void setNamePattern(const std::string& value);

    std::string getUnit() const { return unit; }
    void setUnit(const std::string& value);

    double getFactor() const { return factor; }
    void setFactor(double value);

    int getCanInterval() const { return canInterval; }
    void setCanInterval(int value);

    int getSdInterval() const { return sdInterval; }
    void setSdInterval(int value);

    int getCanThreshold() const { return canThreshold; }
    void setCanThreshold(int value);

    int getSdThreshold() const { return sdThreshold; }
    void setSdThreshold(int value);

    uint32_t getMin() const { return min; }
    void setMin(uint32_t value);

    uint32_t getMax() const { return max; }
    void setMax(uint32_t value);

    std::string getDescription() const { return description; }
    void setDescription(const std::string& value);

    IdGroup* getGroup() const { return group; }
    void setGroup(IdGroup* value);

    std::string toString() const;
};