#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    return 1;
    int sockfd;
    struct sockaddr_in servaddr;
    const char *sendbuf = "this is a test";

    // יצירת Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error at socket(): " << strerror(errno) << std::endl;
        return 1;
    }

    // הגדרת כתובת השרת והתחברות
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(27015);
    if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        close(sockfd);
        return 1;
    }

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Connection failed: " << strerror(errno) << std::endl;
        close(sockfd);
        return 1;
    }

    // שליחת נתונים
    if (send(sockfd, sendbuf, strlen(sendbuf), 0) < 0) {
        std::cerr << "Send failed: " << strerror(errno) << std::endl;
        close(sockfd);
        return 1;
    }

    // סגירת ה-Socket
    close(sockfd);

    return 0;
}
