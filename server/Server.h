/*
 * Declaración de la clase Server.
 * Los métodos están implementados en Server.cpp
 */

// Previene la inclusión múltiple de los headers.
#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <unistd.h>                   /* for ssize_t data type */

#define MAX_LINE           (1024)

class Server {
public:
    // Constructor
    Server(int);

private:
    int list_s;                       /* listening socket */
    struct sockaddr_in servaddr;      /* socket address structure */
    int port;                         /* número de puerto */

    void createListener();
    void configureStruct();
    void bindSocket();
    void callListen();
    void waitConnections();
    void readLine(int conn_s, struct sockaddr_in cli_addr, socklen_t clilen);
};

#endif