// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#define PORT 8081
using namespace std;

int main(int argc, char const *argv[])
{
    string mensaje;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client la hea loca";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }


        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

        while (1) {

        std::cin >> mensaje;
        char hola[mensaje.size() + 1  ];
        strcpy(hola, mensaje.c_str());

        send(sock, hola, 1024, 0);
        valread = read(sock, buffer, 1024);
        printf("%s\n", buffer);


    }
    return 0;
}
