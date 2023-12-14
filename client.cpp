#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"
#include <fstream>

int main()
{
    std::ofstream index("index.html", std::ofstream::trunc);
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Error: Socket creation failed\n";
        return 1;
    }
    // Define server address structure
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;       // IPv4
    server_address.sin_port = htons(80);    // Server's port
    inet_pton(AF_INET, "163.172.250.11", &server_address.sin_addr);  // Server's IP address
    // inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);  // Server's IP address

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error: Connection failed\n";
        return 1;
    }

    std::cout << "Connected to the server\n";
    // const char *request = "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
    const char *request = "GEt / HTTP/1.1\r\nHost: 127.0.0.1:8080\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nsec-ch-ua: Google Chrome;v=119, Chromium;v=119, Not?A_Brand;v=24\r\nsec-ch-ua-mobile: ?0\r\nsec-ch-ua-platform: Linux\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\r\nSec-Fetch-Site: none\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-User: ?1\r\nSec-Fetch-Dest: document\r\nAccept-Encoding: gzip, deflate, br\r\nAccept-Language: ar,en;q=0.9,fr;q=0.8\r\n\r\n";
    // const char *request = "hello\n";
    send(client_socket, request, strlen(request), 0);
    std::cout<<"----------------"<<std::endl;
    char *ptr = NULL;
    while ((ptr = get_next_line(client_socket)))
    {
        index<<ptr;
    }
    close(client_socket);
}