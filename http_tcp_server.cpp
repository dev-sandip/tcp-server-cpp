#include "http_tcp_server.h"

#include <iostream>
#include <sstream>
#include <unistd.h>

namespace
{

    const int BUFFER_SIZE = 30720;

    void logMessage(const std::string &message)
    {
        std::cout << message << std::endl;
    }

    void exitWithError(const std::string &errorMessage)
    {
        logMessage("ERROR: " + errorMessage);
        exit(1);
    }

} // anonymous namespace

namespace http
{

    TcpServer::TcpServer(const std::string &ipAddress, int port)
        : ipAddress(ipAddress), port(port), serverSocket(), clientSocket(),
          serverAddress(), serverAddressLength(sizeof(serverAddress)),
          serverResponseMessage(buildHttpResponse())
    {
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(port);
        serverAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());

        if (initializeServer() != 0)
        {
            std::ostringstream ss;
            ss << "Failed to start server with PORT: " << ntohs(serverAddress.sin_port);
            logMessage(ss.str());
        }
    }

    TcpServer::~TcpServer()
    {
        shutdownServer();
    }

    int TcpServer::initializeServer()
    {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0)
        {
            exitWithError("Cannot create socket");
            return 1;
        }

        if (bind(serverSocket, (sockaddr *)&serverAddress, serverAddressLength) < 0)
        {
            exitWithError("Cannot bind socket to address");
            return 1;
        }

        return 0;
    }

    void TcpServer::shutdownServer()
    {
        close(serverSocket);
        close(clientSocket);
    }

    void TcpServer::startListening()
    {
        if (listen(serverSocket, 20) < 0)
        {
            exitWithError("Socket listen failed");
        }

        std::ostringstream ss;
        ss << "\n*** Listening on ADDRESS: " << inet_ntoa(serverAddress.sin_addr)
           << " PORT: " << ntohs(serverAddress.sin_port) << " ***\n\n";
        logMessage(ss.str());

        int bytesRead;

        while (true)
        {
            logMessage("====== Waiting for a new connection ======\n\n\n");
            acceptClientConnection(clientSocket);

            char buffer[BUFFER_SIZE] = {0};
            bytesRead = read(clientSocket, buffer, BUFFER_SIZE);
            if (bytesRead < 0)
            {
                exitWithError("Failed to read bytes from client socket connection");
            }

            logMessage("------ Received Request from client ------\n\n");

            sendHttpResponse();

            close(clientSocket);
        }
    }

    void TcpServer::acceptClientConnection(int &clientSocket)
    {
        clientSocket = accept(serverSocket, (sockaddr *)&serverAddress, &serverAddressLength);
        if (clientSocket < 0)
        {
            std::ostringstream ss;
            ss << "Server failed to accept incoming connection from ADDRESS: "
               << inet_ntoa(serverAddress.sin_addr) << "; PORT: " << ntohs(serverAddress.sin_port);
            exitWithError(ss.str());
        }
    }

    std::string TcpServer::buildHttpResponse()
    {
        std::string htmlContent = "<!DOCTYPE html><title>Team Members</title></head><body><div><h1>Web Server in C++ from scratch</h1></div><div><h1>Team Members</h1></div><div><div><h2>Sandip Sapkota</h2><p><strong>Roll Number:</strong> PUR079BCT076</p><p><strong>Contact:</strong> 079bct076@ioepc.edu.np</p></div><div><h2>Subhakar Pant</h2><p><strong>Roll Number:</strong> PUR079BCT084</p><p><strong>Contact:</strong> 079bct084@ioepc.edu.np</p></div><div><h2>Raghav Updhayay</h2><p><strong>Roll Number:</strong> PUR079BCT057</p><p><strong>Contact:</strong> 079bct057@ioepc.edu.np</p></div><div><h2>Sulav Poudel</h2><p><strong>Roll Number:</strong> PUR079BCT087</p><p><strong>Contact:</strong> 079bct087@ioepc.edu.np</p></div><div><h2>Samir Gautam</h2><p><strong>Roll Number:</strong> PUR079BCT071</p><p><strong>Contact:</strong> 079bct071@ioepc.edu.np</p></div></div></body></html>";
        std::ostringstream ss;
        ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlContent.size() << "\n\n"
           << htmlContent;

        return ss.str();
    }

    void TcpServer::sendHttpResponse()
    {
        long bytesSent = write(clientSocket, serverResponseMessage.c_str(), serverResponseMessage.size());

        if (bytesSent == serverResponseMessage.size())
        {
            logMessage("------ Server Response sent to client ------\n\n");
        }
        else
        {
            logMessage("Error sending response to client");
        }
    }

} // namespace http
