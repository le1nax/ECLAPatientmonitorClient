#pragma once

#include <memory>
#include <functional>
#include "DisplayManager.h"
#include "SocketClient.h"


class DataPoint;



class DisplayApplication{

    public:
        DisplayApplication();
        void run();
        void connect(const std::string& s_remoteIP, unsigned short remotePort); 

        void stopReceive();

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
        std::unique_ptr<DisplayManager> m_dispManager{};
        std::unique_ptr<SocketClient> m_client{};
        std::unique_ptr<std::thread> appReceiveThread {nullptr};
        bool flagReceiving = true;
        void startReceive();  

};
