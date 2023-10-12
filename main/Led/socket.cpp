#include "custom_scoket.hpp"

// int main()
// {
//     // Example usage
//     class MySocketHandler : public SocketHandler
//     {
//         void onConnect() override
//         {
//             std::cout << "Connected to the server.\n";
//         }

//         void onDisconnect() override
//         {
//             std::cout << "Disconnected from the server.\n";
//         }

//         void onReceive(const char *data) override
//         {
//             std::cout << "Received data: " << data << "\n";
//         }
//     };

//     MySocketHandler socketHandler;
//     if (socketHandler.connectToServer("127.0.0.1", 8080))
//     {
//         socketHandler.send("Hello, server!");
//         socketHandler.receive(); // Receive data from the server
//     }

//     return 0;
// }