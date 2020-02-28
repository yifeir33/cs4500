#pragma once

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "socket_addr.h"

inline bool get_socket_info(int fd, SockAddrWrapper& saw){
    if(getsockname(fd, reinterpret_cast<sockaddr *>(&saw.addr), &saw.addrlen) < 0){
        perror("Error getting socket info: ");
        return false;
    }
    return true;
}

inline bool make_non_blocking(int fd){
    // set socket to non-blocking
    if(fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) < 0){
        perror("Failed to set socket to non-blocking!");
        return false;
    }
    return true;
}

inline int create_socket(SockAddrWrapper& self, bool non_block){
    int sock_fd;
    // create socket
    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed to create socket!");
        return -1;
    }

    if(non_block){
        if(!make_non_blocking(sock_fd)){
            std::cerr <<"Failed to make socket non-blocking!" <<std::endl;
            return -1;
        }
    }

    // let multiple sockets use same ip
    int opt = 1;
    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        perror("Error setting socket options: ");
        return -1;
    }
    // bind to address
    if(bind(sock_fd, reinterpret_cast<sockaddr *>(&self.addr), self.addrlen) < 0){
        perror("Failed to bind to address!");
        return -1;
    }


    return sock_fd;
}

inline int create_socket(const char *ip, in_port_t port, SockAddrWrapper *self, bool non_block){
    // set up address to bind to
    SockAddrWrapper saw;
    if(!self){
        self = &saw;
    }

    self->addr.sin_family = AF_INET;
    if(ip){
        if(inet_pton(AF_INET, ip, &(self->addr.sin_addr)) <= 0){ // convert to proper format
            perror("Error converting address: ");
            return -1;
        }
    } else {
        self->addr.sin_addr.s_addr = INADDR_ANY;
    }
    self->addr.sin_port = htons(port);
    self->addrlen = sizeof(self->addr);

    int sock_fd = create_socket(*self, non_block);

    // if we let the operating system set the port, get the info on where it was bound
    if(!ip || port == 0){
        if(!get_socket_info(sock_fd, *self)){
            std::cerr <<"Failed to get socket info!" <<std::endl;
            return -1;
        }
    }

    return sock_fd;
}
