#include "../include/DisplayApplication.h"
#include "PCANBasic.h"
#include <iostream>

#include "../include/definitions.h"

//PCANModule includes
#include "../PCANModule/DataPoint.h"

#include <thread>

#include <vector>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#define LOCALIP "127.0.0.1"
#define LOCALPORT 12345

DisplayApplication::DisplayApplication() 
{
//     setCallback(std::bind(&DisplayManager::handleDataPoints, m_dispManager, std::placeholders::_1));
}

void DisplayApplication::connect(const std::string& s_remoteIP, unsigned short remotePort)
{
    try
    {
        ///connect with m_client udp
        std::unique_ptr<WSASession> Session = std::make_unique<WSASession>();
        //m_client = std::make_unique<SocketClient>(s_remoteIP, remotePort);
        m_client = std::make_unique<SocketClient>(s_remoteIP, remotePort);
        m_client->establishLanConnection();
        if(configModeDebug) {
             std::cout << "sent association Request" << std::endl;
        }
        ///@todo receive and handle association answer
        startReceive();
        //appReceiveThread = std::make_unique<std::thread>(&DisplayApplication::startReceive, this);
    }
    catch (std::exception &ex) 
    {
        if(configModeDebug) { 
            std::cout << ex.what();  
        }
    }

}

void DisplayApplication::run()
{
    //init Display Manager
    m_dispManager = std::make_unique<DisplayManager>();
    m_dispManager->setAppInstance(this);
    m_dispManager->initWindow();
}

void DisplayApplication::stopReceive()
{
    flagReceiving = false;
}

void DisplayApplication::startReceive()
{
    flagReceiving = true;
    char* buffer;
    while(flagReceiving)
        {
            if(configModeDebug) { 
                std::cout << "begin receive" << std::endl;
            }
            buffer = m_client->Receive(buffer, size_encoded);
            //swapEndianness(buffer, size_encoded);
            DataPointEncoded encoded;
            int32_t valDebug;
            memcpy(&encoded, buffer, size_encoded);
            if(configModeDebug) { 
                std::cout << "pcantime extracted: " << std::to_string(encoded.pcanTimestamp) << std::endl;  
            }
            // if(configModeDebug) { std::cout << "value extracted: " << valDebug << std::endl;
            m_dispManager->handleDataPoints(encoded); /// slot that handles incoming data
        }
}