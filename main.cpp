#include <iostream>
#include <string>
#include <vector>

#include "socket_wrapper.h"

sockaddr_in service;
std::string ipAddress;
std::vector portList = {
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
        sockaddr_in sa;
        int result = inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr));
        if (result != 1) {
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

    for (const auto &ports : portList) {
        SocketWrapper clientSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));

        if (clientSocket == INVALID_SOCKET) {
            std::cout << "Port " << ports << " : ERROR (couldn't create socket)\n";
            continue;
        }

        service.sin_port = htons(ports);
        int connectResult = connect(clientSocket, SOCKADDR_CAST &service, sizeof(service));

        if (connectResult != SOCKET_ERROR) {
            std::cout << "Port " << ports << " : OPEN\n";
        } else {
            std::cout << "Port " << ports << " : CLOSED\n";
        }
    }
}

void customPortRange() {
    int startPort, endPort;

    std::cout << "\n[Custom Port Range] Enter start port: ";
    std::cin >> startPort;
    std::cout << "Enter end port: ";
    std::cin >> endPort;

    if (startPort < 1 || endPort > 65535 || startPort > endPort) {
        std::cout << "Invalid port range. Ports must be between 1-65535 and start <= end.\n";
        return;
    }

    std::cout << "Scanning from port " << startPort << " to " << endPort << "...\n";

    service.sin_family = AF_INET;
    inet_pton(AF_INET, ipAddress.c_str(), &service.sin_addr);

    int openPorts = 0;
    for (int port = startPort; port <= endPort; ++port) {
        SocketWrapper clientSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));

        if (clientSocket == INVALID_SOCKET) {
            continue;
        }

        service.sin_port = htons(port);
        int connectResult = connect(clientSocket, SOCKADDR_CAST &service, sizeof(service));

        if (connectResult != SOCKET_ERROR) {
            std::cout << "Port " << port << " : OPEN\n";
            openPorts++;
        }
    }

    std::cout << "Found " << openPorts << " open ports.\n";
}

int main() {
    int choice;

    std::cout << R"(
 ____            _       ____
|  _ \ ___  _ __| |_    / ___|  ___ __ _ _ __  _ __   ___ _ __
| |_) / _ \| '__| __|   \___ \ / __/ _` | '_ \| '_ \ / _ \ '__|
|  __/ (_) | |  | |_     ___) | (_| (_| | | | | | | |  __/ |
|_|   \___/|_|   \__|   |____/ \___\__,_|_| |_|_| |_|\___|_|

)" << "\n";

#ifdef _WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << "\n";
        return 1;
    }
#endif

    getIpAddress();

    do {
        std::cout << "\n[1] Quick Scan\n";
        std::cout << "[2] Custom Port Range\n";
        std::cout << "[3] Exit\n\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                quickScan();
                break;
            case 2:
                customPortRange();
                break;
            case 3:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}