#pragma once

#include <memory>
#include <functional>

class DataPoint;
class DisplayManager;


class DisplayApplication{

    public:
        DisplayApplication();
        void run();

        //  // Define a callback type using std::function
        // using CallbackType = std::function<void(const DataPointEncoded&)>;

        // // Set the callback function
        // void setCallback(const CallbackType& callback) {
        // callback_ = callback;
        // }

        // // Simulate receiving data and trigger the callback
        // void receiveData(const DataPointEncoded& dataPoint) {
        // if (callback_) {
        //     callback_(dataPoint);
        // }
    // }
    private: 
        // CallbackType callback_;
        // std::unique_ptr<DisplayManager> dispManager;
    
};
