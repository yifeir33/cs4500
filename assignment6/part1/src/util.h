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

inline void get_socket_info(int fd, SockAddrWrapper& saw){
    if(getsockname(fd, reinterpret_cast<sockaddr *>(&saw.addr), &saw.addrlen) < 0){
        perror("Error getting socket info: ");
        exit(1);
    }
}

inline void make_non_blocking(int fd){
    // set socket to non-blocking
    if(fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) < 0){
        perror("Failed to set socket to non-blocking!");
        exit(1);
    }
}

inline int create_socket(SockAddrWrapper& self, bool non_block){
    int sock_fd;
    // create socket
    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed to create socket!");
        exit(1);
    }

    if(non_block){
        make_non_blocking(sock_fd);
    }

    // let multiple sockets use same ip
    int opt = 1;
    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        perror("Error setting socket options: ");
        exit(1);
    }
    // bind to address
    if(bind(sock_fd, reinterpret_cast<sockaddr *>(&self.addr), self.addrlen) < 0){
        perror("Failed to bind to address!");
        exit(1);
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
            exit(1);
        }
    } else {
        self->addr.sin_addr.s_addr = INADDR_ANY;
    }
    self->addr.sin_port = htons(port);
    self->addrlen = sizeof(self->addr);

    int sock_fd = create_socket(*self, non_block);

    // if we let the operating system set the port, get the info on where it was bound
    if(!ip || port == 0){
        get_socket_info(sock_fd, *self);
    }

    return sock_fd;
}
