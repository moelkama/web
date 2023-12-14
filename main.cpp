#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080); // Use the desired port

    if (bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return -1;
    }

    // Get the local address and port after binding
    struct sockaddr_in localAddress;
    socklen_t addrLen = sizeof(localAddress);

    if (getsockname(sockfd, (struct sockaddr *)&localAddress, &addrLen) == -1) {
        std::cerr << "Getsockname failed" << std::endl;
        return -1;
    }

    char localIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(localAddress.sin_addr), localIP, INET_ADDRSTRLEN);

    std::cout << "Local IP: " << localIP << std::endl;
    std::cout << "Local Port: " << ntohs(localAddress.sin_port) << std::endl;

    close(sockfd);

    return 0;
}
