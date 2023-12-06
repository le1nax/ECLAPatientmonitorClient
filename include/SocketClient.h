#pragma once
/// SocketClient is the Client class
///
/// It processes the protocol dialog between Monitor and Client
#include "Socket.h"
#include <thread>


#define RECEIVEINTERVAL 500 // koennen den receive thread nicht komplett durchlaufen lassen weil wir keinen echten Parallelismus haben

class SocketClient : public UDPSocket {

    public:

        SocketClient(std::string remoteIPtarget, const unsigned short remotePortTarget);
        ~SocketClient() = default;
        
        
        void establishLanConnection();

        SOCKET getSocket();

        void initReceive();
        
        sockaddr_in m_sa_remoteIPtarget;
        char* Receive(char* buffer, size_t buffersize = maxbuffersize, int flags = 0);

        std::vector<std::byte> init_msg;
    private:
        void sendBytes(std::vector<std::byte> bytes);
        void ProcessPacket(char* buffer);

        char* m_lastMsg;
        size_t lastMsgSize = 0;

        std::string m_remoteIPtarget = "";
        std::string m_strTimestamp = "";
        std::string m_DeviceID= "";
        std::string m_idlabelstring = "";
        const unsigned short m_port = 0;

        void onThreadReceive();
        std::unique_ptr<std::thread> m_receiveThread {nullptr};

        unsigned char ConvertToByte(int value);

        bool IsLittleEndian();

        private:

        void CALLBACK ReceiveCallback(DWORD errorCode, DWORD numBytesReceived, LPWSAOVERLAPPED overlapped, DWORD flags = 0);

        bool stopThreadKeepConnectionAlive = false;
        bool stopThreadReceive = false;
        int m_receiveInterval = RECEIVEINTERVAL;
};

///current state of the client for the asynchronous receiving of data
class Receive_State 
{
    public:
        Receive_State() = default;
        ~Receive_State() = default;

        WSAOVERLAPPED overlapped; ///nötig um auf hEvent und overlap operation params zuzugreifen
        WSABUF wsaBuf;
        sockaddr_in state_ip;
        long unsigned int numBytesReceived;
        long unsigned int numBytesTransferred;
};
