#ifndef LED_HPP_
#define LED_HPP_

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class SocketHandler
{
public:
    // Callbacks
    virtual void onConnect() {}
    virtual void onDisconnect() {}
    virtual void onReceive(const char *data) {}

    // Connect to a server
    bool connectToServer(const std::string &serverAddress, int port)
    {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1)
        {
            perror("Socket creation failed");
            return false;
        }

        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);

        if (inet_pton(AF_INET, serverAddress.c_str(), &serverAddr.sin_addr) <= 0)
        {
            perror("Invalid address/ Address not supported");
            return false;
        }

        if (connect(serverSocket, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr)) < 0)
        {
            perror("Connection failed");
            return false;
        }

        onConnect(); // Notify on successful connection
        return true;
    }

    // Send data to the server
    bool send(const char *data)
    {
        if (serverSocket == -1)
        {
            std::cerr << "Socket not connected.\n";
            return false;
        }

        if (write(serverSocket, data, strlen(data)) != strlen(data))
        {
            perror("Write failed");
            return false;
        }

        return true;
    }

    // Receive data from the server

    void receive()
    {
        char buffer[1024] = {0};
        int valread = read(serverSocket, buffer, 1024);
        if (valread == 0)
        {
            onDisconnect(); // Notify on disconnection
            close(serverSocket);
            serverSocket = -1;
            return;
        }
        else if (valread < 0)
        {
            perror("Read failed");
            return;
        }

        onReceive(buffer);
    }

    bool isSocketConnected()
    {
        int error = 0;
        socklen_t len = sizeof(error);
        int retval = getsockopt(serverSocket, SOL_SOCKET, SO_ERROR, &error, &len);

        if (retval != 0)
        {
            // Error in getsockopt
            perror("Error in getsockopt");
            return false;
        }

        if (error != 0)
        {
            // Socket has an error, not connected
            std::cout << "Socket not connected. Error: " << strerror(error) << "\n";
            close(serverSocket);
            serverSocket = -1;
            onDisconnect();
            return false;
        }

        return true;
    }

private:
    int serverSocket = -1;
};

#endif