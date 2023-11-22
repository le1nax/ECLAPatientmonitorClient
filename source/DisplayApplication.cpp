#include "../include/DisplayApplication.h"
#include "PCANBasic.h"
#include <iostream>

#include "../include/definitions.h"

//PCANModule includes
#include "../PCANModule/DataManager.h"
#include "../PCANModule/DataPoint.h"
#include "../PCANModule/CanAdapter.h"

#include "../include/DisplayManager.h"
#include "../include/SocketClient.h"

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
 
}

void DisplayApplication::run()
{
    try
    {
        std::unique_ptr<WSASession> Session = std::make_unique<WSASession>();

        const std::string s_remoteIP = LOCALIP;
        const unsigned short remotePort = LOCALPORT;
        std::unique_ptr<SocketClient> client = std::make_unique<SocketClient>(s_remoteIP, remotePort);

        client->establishLanConnection();
        std::cout << "sent" << std::endl;
        // std::cin.get();// Wait for user input before exiting
        char buffer[maxbuffersize];
        std::cout << "begin receive" << std::endl;
        client->Receive(buffer);
    }
    catch (std::exception &ex) //catch any occurring system errors
    {
        std::cout << ex.what();  //print error message
    }
	std::cout << "return to main end" << std::endl;
}
