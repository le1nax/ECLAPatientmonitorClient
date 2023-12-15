#include "../include/DisplayApplication.h"
#include "PCANBasic.h"
#include <iostream>

#include "../include/definitions.h"

//PCANModule includes
#include "../PCANModule/DataManager.h"
#include "../PCANModule/DataPoint.h"
#include "../include/DisplayManager.h"
#include "../include/SocketClient.h"

#include <thread>

#include <vector>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#define LOCALIP "134.61.68.44"
#define LOCALPORT 12345


DisplayApplication::DisplayApplication() 
{
    
//     setCallback(std::bind(&DisplayManager::onPressureChanged, dispManager, std::placeholders::_1));
}

void DisplayApplication::run()
{
    try
    {
        std::unique_ptr<WSASession> Session = std::make_unique<WSASession>();
        DisplayManager dispManager;

        const std::string s_remoteIP = LOCALIP;
        const unsigned short remotePort = LOCALPORT;
        std::unique_ptr<SocketClient> client = std::make_unique<SocketClient>(s_remoteIP, remotePort);

        client->establishLanConnection();
        if(configModeDebug) {
             std::cout << "sent" << std::endl;
        }
        // std::cin.get();// Wait for user input before exiting
        dispManager.initWindow();
        char* buffer;
        if(configModeDebug) { 
            std::cout << "begin receive" << std::endl;
        }

        while(true)
        {
            buffer = client->Receive(buffer, size_encoded);
            //swapEndianness(buffer, size_encoded);
            DataPointEncoded encoded;
            int32_t valDebug;
            memcpy(&encoded, buffer, size_encoded);
            // if(configModeDebug) { std::cout << "canID extracted: " << int(encoded.canID) << std::endl;
            // if(configModeDebug) { std::cout << "timestamp extracted: " << int(encoded.timestamp) << std::endl;   
            // if(configModeDebug) { std::cout << "value extracted: " << int(encoded.value) << std::endl;
            if(configModeDebug) { 
                std::cout << "pcantime extracted: " << std::to_string(encoded.pcanTimestamp) << std::endl;  
            }
            // if(configModeDebug) { std::cout << "value extracted: " << valDebug << std::endl;
            dispManager.onPressureChanged(encoded);
        }
    }
    catch (std::exception &ex) //catch any occurring system errors
    {
        if(configModeDebug) { 
            std::cout << ex.what();  //print error message
        }
    }
	if(configModeDebug) { 
        std::cout << "return to main end" << std::endl;
    }
}
