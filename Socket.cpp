//
// Created by Pedro Soares on 03/07/16.
//

#include "Socket.h"

using namespace Tigre;

Socket::Socket(Tigre::String host, int port, SocketType type) {
    if(type == TCP) {
        socket_ = socket(AF_INET, SOCK_STREAM, 6);
        struct hostent *hostname = gethostbyname(host.getValue().c_str());
        if (socket_ < 0) {
            throw SocketException("Erro ao criar servidor socket.");
        }
        config.sin_family = hostname->h_addrtype;
        config.sin_port = htons(port);
        config.sin_addr = *((struct in_addr *) hostname->h_addr);
        bzero(&(config.sin_zero), 8);
        config_len = sizeof(config);
    } else if(type == UDP){
        throw SocketException("Não foi implementado!");
    }
}

Socket::Socket(int socket) {
    this->socket_ = socket;
    conected = true;
}

Socket::~Socket() {
    if(conected)
        shutdown(this->socket_, SHUT_RDWR);
}

void Socket::Bind(int clients) {
    if(bind(this->socket_, (struct sockaddr * )&config, config_len) < 0)
        throw SocketException("Erro ao iniciar servidor socket.");

    if(listen(this->socket_, clients) < 0)
        throw SocketException("Erro ao ouvir porta do socket.");

    conected = true;
}

Socket* Socket::Accept() {
    int client_socket = accept(this->socket_,(struct sockaddr * )&config, &config_len);
    if(client_socket < 0){
        throw new SocketException("Erro ao receber cliente.");
    }
    return new Socket(client_socket);

}

void Socket::Write(String data) {
    if(send(this->socket_, data.getValue().c_str(), data.getValue().size(), 0) < 0){
        throw SocketException("Erro ao escrever no Socket.");
    }
}

void Socket::Write(char *data) {
    if(send(this->socket_, data, sizeof(data), 0) < 0){
        throw SocketException("Erro ao escrever no Socket.");
    }
}

void Socket::Connect() {

}

String Socket::Read(int size) {
    char buffer[size];
    int status = recv(this->socket_,buffer, sizeof(buffer),0);
    if(status < 0){
        throw SocketException("Erro ao ler socket.");
    }else if(status == 0){
        conected = false;
        throw SocketException("Sem conexão com o Socket.");
    } else {
        String msg = buffer;
        return msg;
    }
}

void Socket::Read(void *buffer, int size) {
    int status = recv(this->socket_,buffer, size,0);
    if(status < 0){
        throw SocketException("Erro ao ler socket.");
    }else if(status == 0){
        conected = false;
        throw SocketException("Sem conexão com o Socket.");
    }
}