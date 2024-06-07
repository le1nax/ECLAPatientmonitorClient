#pragma once
#include <vector>
#include <string>
#include "IdGroup.h"

class IdGroupList : public std::vector<IdGroup> {
public:
    IdGroup* getOrCreateGroupByName(const std::string& name) {
        IdGroup* res = nullptr;

        // Look for group first
        for (auto& group : *this) {
            if (group.getName() == name) {
                res = &group;
                break;
            }
        }

        // if no group found: create new one and add it
        if (res == nullptr) {
            emplace_back(name);
            res = &back();
        }

        return res;
    }
};