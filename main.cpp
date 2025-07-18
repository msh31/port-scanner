#include <iostream>
#include <winsock2.h> //enables network programming 
#include <ws2tcpip.h> //for inet_pton(), enebles modern IP address conversion
#include <string>
#include <vector>

int main() {
    std::vector<int> portList = {
        21, 22, 23, 25, 53, 80, 81, 110, 135, 143, 443, 445, 993, 995, 2375, 2376, 3096, 3097, 3389, 5357
    };

    bool finished = false;
    int port;
    std::string ipAddress, enteredPort;

    while (!finished)
    {
        std::cout << "Enter target IP (or 'quit' / 'q' to exit): ";
        std::getline(std::cin, ipAddress);

        if (ipAddress == "quit" || ipAddress == "q") {
            std::cout << "Exiting...\n";
            return 0;
        }

        // ip validation 
        struct in_addr addr_buf;
        if (inet_pton(AF_INET, ipAddress.c_str(), &addr_buf) != 1) { 
            std::cout << "Invalid IP address format. Please enter a valid IPv4 address.\n"; 
            continue; 
        }

        finished = true;
    }

    WSADATA wsaData; //initialize windows socket
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (iResult != 0) { 
        std::cerr << "WSAStartup failed: " << iResult << "\n"; 
        return 1; 
    }

    // configure target
    sockaddr_in service;
    service.sin_family = AF_INET; // IPv4
    inet_pton(AF_INET, ipAddress.c_str(), &service.sin_addr);

    std::cout << "Scanning " << ipAddress << "...\n";

    for (const auto &ports : portList)
    {
        SOCKET clientSocket;
        clientSocket = INVALID_SOCKET;
        clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //create TCP socket for outbound connections

        service.sin_port = htons(ports);

        // attempt connection
        int connectResult = connect(clientSocket, (SOCKADDR *)&service, sizeof(service));

        if (connectResult != SOCKET_ERROR) {
            std::cout << "Port " << ports << " : OPEN" << "\n";
        } else {
            std::cout << "Port " << ports << " : CLOSED\n"; 
        }

        closesocket(clientSocket);
    }
    
    WSACleanup();
    return 0;
}