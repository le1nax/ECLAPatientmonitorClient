// #include "include/DisplayApplication.h"
// #pragma managed
// #include <memory>
// #include <iostream>
// #include <windows.h>
// #include <iostream>
// #include "ParseECLA/IdManager.h"
// #include "ParseECLA/LRUCache.hpp"


// int main() {
//     std::unique_ptr<IdManager> idMan = std::make_unique<IdManager>("../ParseECLA/SmartECLA_IDs.h");
//     auto canHashMap = idMan->getIdDict();
//     auto it = canHashMap.find(0x10040436); //enter can id here
//         if (it != canHashMap.end()) {
//             // Found in canHashMap
    
//             MeasurementVector newMeasurementVector(*it->second); 
//             int a = 1; //set breakpoint here
//         }
//     return 0;
// }