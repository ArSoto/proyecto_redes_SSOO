#include <sys/socket.h>       /* socket definitions */
#include <sys/types.h>        /* socket types */
#include <arpa/inet.h>        /* inet (3) funtions */

#include <iostream>
using namespace std;

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "Server.h"


// Constructor.
Server::Server(int port) {
    this->port = port;

    this->createListener();
    this->configureStruct();
    this->bindSocket();
    this->callListen();
    this->waitConnections();
}
/**Creacion de socket y conexión de red**/
/**Descriptor de socket -> list_s**/
void Server::createListener() {
    cout << "Creating listening socket ..." << endl;
    if ( (this->list_s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { /**SOCK_STREAM --> Conexion TCP**/
        cout << "Error creating listening socket" << endl;
        exit(EXIT_FAILURE);
    }
}

/*  Set all bytes in socket address structure to
 *  zero, and fill in the relevant data members
 */
void Server::configureStruct() {
    cout << "Configuring socket address structure ..." << endl;
    memset(&this->servaddr, 0, sizeof(this->servaddr));
    this->servaddr.sin_family      = AF_INET; /**Protocolo para la conexion**/
    this->servaddr.sin_addr.s_addr = htonl(INADDR_ANY); /**Estructura de la dirección IP**/
    this->servaddr.sin_port        = htons(this->port); /**Puerto para la conexion**/
}

/**Asocia socket con puerto**/
void Server::bindSocket() {
    cout << "Binding socket ..." << endl;
    if ( bind(this->list_s, (struct sockaddr *) &this->servaddr, sizeof(this->servaddr)) < 0 ) {
        cout << "Error calling bind()" << endl;
        exit(EXIT_FAILURE);
    }
}

/**Espera conexiones entrantes --> accept()**/
void Server::callListen() {
    cout << "Calling listening ..." << endl;
    if ( listen(this->list_s, 1024) < 0 ) {
        cout << "Error calling listen()" << endl;
        exit(EXIT_FAILURE);
    }
}

/**Tras esperar conexión accept() la consigue**/
void Server::waitConnections() {
    cout << "Waiting client request ..." << endl;

    int conn_s; /**Toma la primera solicitud de conexión **/
    socklen_t clilen;
    struct sockaddr_in cli_addr; /**Determina qué nodo se quiere conectar y desde qué puerto**/
    clilen = sizeof(cli_addr); /**Longitud de la estructura**/

    /*  Enter an infinite loop to respond
    *  to client requests and echo input
    */
    while (1) {
        /*  Wait for a connection, then accept() it  */
        if ((conn_s = accept(this->list_s, (struct sockaddr *) &cli_addr, &clilen) ) < 0) {
            cout << "Error calling accept()" << endl;
            exit(EXIT_FAILURE);
        }

        // atiende cliente.
        this->readLine(conn_s, cli_addr, clilen);
    }
    /**En este punto la conexión se estableció**/
}

/*
 * Read a line from a socket.
 */
void Server::readLine(int conn_s, struct sockaddr_in cli_addr, socklen_t clilen) {
    ssize_t n;
    char buffer[MAX_LINE] = {0};

    struct sockaddr_in *sockin = (struct sockaddr_in*) &cli_addr;
    struct in_addr sinaddr = sockin->sin_addr;

    /**Direccion IP host --> String**/
    cout << "Open connection [" << inet_ntoa(sinaddr) << ":" << sockin->sin_port << "]" << endl;

    while(1) {
        n = read(conn_s, buffer, MAX_LINE);

        // convierte varchar en string.
        string line(buffer);

        // elimina los últimos 2 caracteres.
        line.pop_back(); line.pop_back();

        if (line.compare("exit") == 0) {
            cout << "Close connection [" << inet_ntoa(sinaddr) << ":" << sockin->sin_port << "]" << endl;
            close(conn_s);
            break;
        } else {
            cout << "Command Connection [" << inet_ntoa(sinaddr) << ":" << sockin->sin_port << "]: " << line << endl;
        }

        // limpia el buffer.
        memset(buffer, 0, MAX_LINE);
    }
}

/**SOLO SERVIDOR ESCUCHA**/
/** SERVER: socket()->bind()->listen()->accept()->Recibir/Enviar
 * CLIENTE: socket()------conect() -^ --->Recibir/Enviar **/
