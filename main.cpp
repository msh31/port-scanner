#include <iostream>
#include <winsock2.h> //enables network programming 
#include <ws2tcpip.h> //for inet_pton(), enebles modern IP address conversion
#include <string>
#include <vector>

#include "Ascii.h"

sockaddr_in service;
std::string ipAddress = "";
std::vector<int> portList = {
    21, 22, 23, 25, 53, 80, 81, 110, 135, 143, 443, 445, 993, 995, 2375, 2376, 3096, 3097, 3389, 5357
};

void getIpAddress() {
    bool finished = false;

    do {
        std::cout << "Enter target IP (or 'quit' / 'q' to exit): ";
        std::getline(std::cin, ipAddress);

        if (ipAddress == "quit" || ipAddress == "q") {
            std::cout << "Exiting...\n";
            exit(0);
        }

        // ip validation 
        struct in_addr addr_buf;
        if (inet_pton(AF_INET, ipAddress.c_str(), &addr_buf) != 1) { 
            std::cout << "Invalid IP address format. Please enter a valid IPv4 address.\n"; 
            continue; 
        }

        finished = true;
    } while (!finished);
}

void quickScan() {
    service.sin_family = AF_INET; 
    inet_pton(AF_INET, ipAddress.c_str(), &service.sin_addr);

    std::cout << "\n[Quick Scan] Scanning common ports...\n";
    
    for (const auto &ports : portList)
    {
        SOCKET clientSocket;
        clientSocket = INVALID_SOCKET;
        clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //create TCP socket for outbound connections

        service.sin_port = htons(ports);
        int connectResult = connect(clientSocket, (SOCKADDR *)&service, sizeof(service));

        if (connectResult != SOCKET_ERROR) {
            std::cout << "Port " << ports << " : OPEN" << "\n";
        } else {
            std::cout << "Port " << ports << " : CLOSED\n"; 
        }

        closesocket(clientSocket);
    }
}

void customPortRange() {
    int startPort, endPort;

    std::cout << "\n[Custom Port Range] Enter start port: ";
    std::cin >> startPort;
    std::cout << "Enter end port: ";
    std::cin >> endPort;
    std::cout << "Scanning from port " << startPort << " to " << endPort << "...\n";


}

int main() 
{
    int choice;
    ascii::Ascii font(ascii::FontName::small);
    font.print("Port Scanner");

    WSADATA wsaData; //initialize windows socket
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (iResult != 0) { 
        std::cerr << "WSAStartup failed: " << iResult << "\n"; 
        return 1; 
    }

    getIpAddress();

    do {
        std::cout << "[1] Quick Scan\n";
        std::cout << "[2] Custom Port Range\n";
        std::cout << "[3] Exit\n\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: quickScan(); break;
            case 2: customPortRange(); break;
            case 3: std::cout << "Exiting...\n"; WSACleanup(); return 0; break;
            default: std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);
    
    WSACleanup();
    return 0;
}