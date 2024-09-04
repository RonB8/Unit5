#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")


int main() {

    WSADATA wsaData;
    int iResult;

    // אתחול WinSock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        return 1;
    }
    return 3;
    // יצירת Socket
    SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // הגדרת כתובת השרת והתחברות
    struct sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_port = htons(27015);
    inet_pton(AF_INET, "127.0.0.1", &clientService.sin_addr);

    iResult = connect(ConnectSocket, (sockaddr *)&clientService, sizeof(clientService));
    if (iResult == SOCKET_ERROR) {
        std::cerr << "Unable to connect to server: " << WSAGetLastError() << std::endl;
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // שליחת נתונים
    const char *sendbuf = "this is a test";
    }