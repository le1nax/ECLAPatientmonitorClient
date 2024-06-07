#pragma once
#include <unordered_map>
#include <list>

template<typename Key, typename Value>
class LRUCache {
public:
    LRUCache(size_t capacity);
    Value* get(const Key& key);
    void put(const Key& key, const Value& value);
    void setCapacity(uint8_t cap){capacity = cap;};

private:
    size_t capacity;
    std::list<std::pair<Key, Value>> cacheList;
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> cacheMap;
};

// Include implementation in the header file
template<typename Key, typename Value>
LRUCache<Key, Value>::LRUCache(size_t capacity) : capacity(capacity) {}

template<typename Key, typename Value>
Value* LRUCache<Key, Value>::get(const Key& key) {
    auto it = cacheMap.find(key);
    if (it == cacheMap.end()) {
        return nullptr;
    } else {
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        return &it->second->second;
    }
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::put(const Key& key, const Value& value) {
    auto it = cacheMap.find(key);
    if (it != cacheMap.end()) {
        cacheList.erase(it->second);
        cacheMap.erase(it);
    }

    cacheList.emplace_front(key, value);
    cacheMap[key] = cacheList.begin();

    if (cacheMap.size() > capacity) {
        auto last = cacheList.end();
        last--;
        cacheMap.erase(last->first);
        cacheList.pop_back();
    }
}

