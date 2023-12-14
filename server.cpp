#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "get_next_line.h"
#include <cstring>
#include <fstream>

int main(int c, char **v) {
    // Create a socket
    std::ofstream out("akatfi", std::ofstream::trunc);
    std::fstream index("index1.html");
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Error: Socket creation failed\n";
        return 1;
    }

    // Define server address structure
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;       // IPv4
    server_address.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP
    server_address.sin_port = htons(8080);    // Port to listen on (in network byte order)

    // Bind the socket to the specified address and port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error: Binding failed\n";
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        std::cerr << "Error: Listen failed\n";
        return 1;
    }

    std::cout << "Server is listening on port 8080...\n";

    // Accept incoming connections
    int client_socket;
    sockaddr_in client_address;
    socklen_t client_addr_size = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_addr_size);
    std::cout << "Connection established with a client\n";
    if (client_socket < 0)
    {
        std::cerr << "Error: Accept failed\n";
        return 1;
    }
    ///----------------------
    int google_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (google_socket == -1) {
        std::cerr << "Error: Socket creation failed\n";
        return 1;
    }
    sockaddr_in google_address;
    google_address.sin_family = AF_INET;    // IPv4
    google_address.sin_port = htons(80);    // Server's port
    inet_pton(AF_INET, "163.172.250.11", &google_address.sin_addr);  // Server's IP address

    if (connect(google_socket, (struct sockaddr *)&google_address, sizeof(google_address)) < 0) {
        std::cerr << "Error: Connection failed\n";
        return 1;
    }
    std::cout << "Connected to the server\n";
    const char *request = "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
    send(google_socket, request, strlen(request), 0);
    ///----------------------
    int n = atoi(v[1]);
    char    ptr[n];// = "HTTP/1.1 400 Bad Request\r\n\r\n<!DOCTYPE html>\n<html>\n<body>\n  	Hello World!  \n</body>\n</html>";
    read(google_socket, ptr, n);
    // while ((ptr = get_next_line(google_socket)))
    // {
    //     send(client_socket, ptr, strlen(ptr), 0);
        std::cout<<ptr<<std::endl;
    // }
    std::cout<<"---------"<<std::endl;
    close(client_socket);
    close(server_socket);

    return 0;
}
