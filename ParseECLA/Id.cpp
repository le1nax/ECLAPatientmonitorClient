#include "Id.h"
#include "IdType.h" 
#include "IdGroup.h"

#include <stdexcept>
#include <sstream>
#include <iomanip>

Id::Id(IdType* type, int devNumber) : type(type) {
    // Check if type is null
    if (type == nullptr) {
        throw std::invalid_argument("The type must be defined when using this constructor!");
    }

    // Check devNumber validity
    if (devNumber < 0 || devNumber > type->getGroup()->getCount() - 1) {
        throw std::invalid_argument("devNumber is higher than Count-1!");
    }

    // Derive id
    idValue = (type->getIdPattern() & ~type->getGroup()->getDeviceNumberMask()) | (devNumber << type->getGroup()->getShifter());

    // Derive name
    if (type->getNamePattern().find("_X_") != std::string::npos) {
        std::stringstream ss;
        ss << std::setw(8) << std::setfill('0') << std::hex << idValue;
        name = type->getNamePattern().replace(type->getNamePattern().find("_X_"), 3, "_" + ss.str() + "_");
    } else if (type->getGroup()->getCount() == 1) {
        name = type->getNamePattern();
    } else {
        throw std::invalid_argument("There is no \"_X_\" placeholder in the name pattern of id type " + type->getNamePattern());
    }
}

Id::Id(IdType* type) : type(type) {
    idValue = type->getIdPattern();
    name = type->getNamePattern();
}

int Id::extractDeviceNumber() const {
    if (type->getGroup() == nullptr) {
        return 0; // we have a zero-based device enumeration
    } else {
        int mask = type->getGroup()->getDeviceNumberMask();
        int shifter = type->getGroup()->getShifter();
        return ((idValue & mask) >> shifter);
    }
}

std::string Id::toString() const {
    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << idValue;
    return "0x" + ss.str();
}