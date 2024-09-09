#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>
#include <cstring> 
#include <boost/asio.hpp>


using namespace std;


int main() {

    //Server syntax

    // socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    //binding
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    //listening
    listen(serverSocket, 5);

    //accepting connection request
    int clientSocket = accept(serverSocket, NULL, NULL);

    //sending
    // const char* msg = "Hi dear client!";

    //receiving
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << "msg from client is: " << buffer << endl;

    //close socket
    close(serverSocket);
    close(clientSocket);

    return 0;
}
