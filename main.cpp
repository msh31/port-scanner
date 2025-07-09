#include <iostream>
#include <winsock2.h> //enables network programming 
#include <ws2tcpip.h> //for inet_pton(), enebles modern IP address conversion
#include <string>

#define DEFAULT_PORT "22"

int main() {
    WSADATA wsaData; //initialize windows socket
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (iResult != 0) { std::cerr << "WSAStartup failed: " << iResult << "\n"; return 1; }

    std::cout << "WSAStartup success!" << "\n";

    SOCKET clientSocket;
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //create TCP socket for outbound connections

    if (clientSocket == INVALID_SOCKET) 
    {
        std::cout << "Error at socket(): " << WSAGetLastError();
        WSACleanup();
        return 0;
    }

    std::cout << "Socket is OK!" << "\n";

    bool finished = false;
    int port;
    std::string ipAddress, enteredPort;

    while (!finished)
    {
        std::cout << "Enter target IP (or 'quit' / 'q' to exit):";
        std::getline(std::cin, ipAddress);

        if (ipAddress == "quit" || ipAddress == "q")
        {
            std::cout << "Exiting...\n";
            closesocket(clientSocket);
            WSACleanup();
            return 0;
        }

        // ip validation 
        struct in_addr addr_buf;
        if (inet_pton(AF_INET, ipAddress.c_str(), &addr_buf) != 1) { std::cout << "Invalid IP address format. Please enter a valid IPv4 address.\n"; continue; }

        std::cout << "Enter target port: ";
        std::getline(std::cin, enteredPort);

        try
        {
            port = std::stoi(enteredPort);

            if (port < 1 || port > 65535) { std::cout << "Invalid port range. Port must be between 1 and 65535.\n"; continue; }

            finished = true; 
        }
        catch (const std::invalid_argument &) { std::cout << "Invalid input. Please enter a numeric port value.\n"; }
        catch (const std::out_of_range &) { std::cout << "Port number is out of range for an integer.\n"; }
    }

    //configure target
    sockaddr_in service;
    service.sin_family = AF_INET; //IPv4
    inet_pton(AF_INET, ipAddress.c_str(), &service.sin_addr); //bind to localhost
    service.sin_port = htons(port);

    //attempt connection
    int connectResult = connect(clientSocket, (SOCKADDR *)&service, sizeof(service));

    if (connectResult == SOCKET_ERROR) 
    { 
        std::cout << "Port " << port << " : CLOSED\n"; 
        WSACleanup();
        return 0;
    }

    std::cout << "Port " << port << " : OPEN" << "\n";
    
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}