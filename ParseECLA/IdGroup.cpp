#include "IdGroup.h"
#include "Id.h"

IdGroup::IdGroup(const std::string& groupName) : name(groupName), isAlarmGroup(false), count(1), shifter(0), mask(0x00000000), isLost(false) {
    lastReceivedTime = std::time(nullptr);
    alarmEnabled = false;
}

void IdGroup::computeMask() {
    int count = this->count - 1;
    int mask = 0;
    while (count > 0) {
        count /= 0x10;
        mask = (mask << 4) | 0xF;
    }
    mask = mask << this->shifter;
    this->mask = mask;
}

bool IdGroup::getIsAlarmGroup() const {
    return isAlarmGroup;
}
void IdGroup::setIsAlarmGroup(bool value) {
    isAlarmGroup = value;
}

std::string IdGroup::getName() const {
    return name;
}
void IdGroup::setName(const std::string& value) {
    name = value;
}

int IdGroup::getCount() const {
    return count;
}
void IdGroup::setCount(int value) {
    count = value;
    this->computeMask();
}

int IdGroup::getShifter() const {
    return shifter;
}
void IdGroup::setShifter(int value) {
    shifter = value;
    this->computeMask();
}

std::string IdGroup::getShifterDefine() const {
    return shifterDefine;
}
void IdGroup::setShifterDefine(const std::string& value) {
    shifterDefine = value;
}

bool IdGroup::getIsLost() const {
    return isLost;
}

bool IdGroup::getAlarmEnabled() const {
    return alarmEnabled;
}

time_t IdGroup::getLastReceivedTime() const {
    return lastReceivedTime;
}
void IdGroup::setLastReceivedTime(time_t value) {
    lastReceivedTime = value;
}

std::vector<Id>& IdGroup::getIds() {
    return ids;
}
void IdGroup::setIds(const std::vector<Id>& value) {
    ids = value;
}

int IdGroup::getDeviceNumberMask() const {
    return mask;
}

void IdGroup::alarm() {
    alarmEnabled = false;
    isLost = true;
}

void IdGroup::resetAlarm() {
    if (isAlarmGroup) {
        alarmEnabled = true;
        isLost = false;
    }
}