#pragma once
#include <string>
#include <vector>
#include <ctime>

class Id;

class IdGroup {
private:
    bool isAlarmGroup;
    std::string name;
    int count;
    int shifter;
    std::string shifterDefine;
    bool isLost;
    bool alarmEnabled;
    time_t lastReceivedTime;
    std::vector<Id> ids;
    int mask;

    void computeMask();

public:
    IdGroup(const std::string& groupName);

    bool getIsAlarmGroup() const;
    void setIsAlarmGroup(bool value);

    std::string getName() const;
    void setName(const std::string& value);

    int getCount() const;
    void setCount(int value);

    int getShifter() const;
    void setShifter(int value);

    std::string getShifterDefine() const;
    void setShifterDefine(const std::string& value);

    bool getIsLost() const;

    bool getAlarmEnabled() const;

    time_t getLastReceivedTime() const;
    void setLastReceivedTime(time_t value);

    std::vector<Id>& getIds();
    void setIds(const std::vector<Id>& value);

    int getDeviceNumberMask() const;

    void alarm();

    void resetAlarm();
};