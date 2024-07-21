#ifndef HTTP_TCP_SERVER_H
#define HTTP_TCP_SERVER_H

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace http
{

    class TcpServer
    {
    public:
        TcpServer(const std::string &ipAddress, int port);
        ~TcpServer();
        void startListening();

    private:
        std::string ipAddress;
        int port;
        int serverSocket;
        int clientSocket;
        struct sockaddr_in serverAddress;
        unsigned int serverAddressLength;
        std::string serverResponseMessage;

        int initializeServer();
        void shutdownServer();
        void acceptClientConnection(int &clientSocket);
        std::string buildHttpResponse();
        void sendHttpResponse();
    };

}

#endif