#include <iostream>
#include <winsock2.h> //enables network programming 
#include <ws2tcpip.h> //for inet_pton(), enebles modern IP address conversion

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

    //configure target
    sockaddr_in service;
    service.sin_family = AF_INET; //IPv4
    inet_pton(AF_INET, "192.168.1.1", &service.sin_addr); //bind to localhost
    service.sin_port = htons(443);

    //attempt connection
    int connectResult = connect(clientSocket, (SOCKADDR *)&service, sizeof(service));

    if (connectResult == SOCKET_ERROR) 
    { 
        std::cout << "Port 443: CLOSED\n"; 
        WSACleanup();
        return 0;
    }

    std::cout << "Port 443: OPEN" << "\n";
    
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}