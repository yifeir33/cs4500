#pragma once

#include <assert.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "object.h"
#include "thread.h"
#include "socket_addr.h"
#include "array.h"
#include "packet.h"

#define EXPECTED 1

// TODO: gonna need to multithread
class Client : public Object {
public:
    int _client_fd;
    SockAddrWrapper _self;
    sockaddr_in _server;
    ObjectArray _other_clients;
    size_t _received;
    bool _said_hello;

    Client(const char *ip, size_t port) : _client_fd(-1), _other_clients(10), _received(0), _said_hello(false) {
        if((_client_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0) {
            perror("Failed to create socket!");
            exit(1);
        }
        int opt = 1;
        if(setsockopt(_client_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
            perror("Error setting socket options: ");
            exit(1);
        }

        _server.sin_family = AF_INET;
        if(inet_pton(AF_INET, ip, &(_server.sin_addr)) <= 0){
            perror("Error converting address: ");
            exit(1);
        } // convert to proper format
        _server.sin_port = htons(port);

        _self.addrlen = sizeof(_self.addr);
        _self.addr.sin_family = AF_INET;
        inet_pton(AF_INET, "127.0.0.1", &(_self.addr.sin_addr));
        /* _self.addr.sin_addr.s_addr = INADDR_ANY; */
        _self.addr.sin_port = 0;

        if(bind(_client_fd, reinterpret_cast<sockaddr *>(&_self.addr), _self.addrlen) < 0){
            perror("Failed to bind to address!");
            exit(1);
        }

        if(getsockname(_client_fd, reinterpret_cast<sockaddr *>(&_self.addr), &_self.addrlen) < 0){
            perror("Error getting socket info: ");
            exit(1);
        }
        char locstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(_self.addr.sin_addr), locstr, INET_ADDRSTRLEN);
        p("Bound to: ").p(locstr).p(':').p(ntohs(_self.addr.sin_port)).p('\n');
        std::cout.flush();
    }

    int _check_for_socket_errors(){
        int opt = 0;
        socklen_t optlen = sizeof(opt);
        if(getsockopt(_client_fd, SOL_SOCKET, SO_ERROR, &opt, &optlen) < 0){
            perror("Error checking socket: ");
            exit(1);
        }
        return opt;
    }

    void connect_to_server(){
        if(connect(_client_fd, reinterpret_cast<sockaddr*>(&_server), sizeof(_server)) < 0) {
            // Needed cause the socket is non-blocking
            if(errno == EINPROGRESS){
                fd_set fdset{0};
                FD_SET(_client_fd, &fdset);
                if(select(_client_fd + 1, nullptr, &fdset, nullptr, nullptr) < 0){ 
                    perror("Error on select: ");
                    exit(1);
                }
                if(FD_ISSET(_client_fd, &fdset)){
                    if(this->_check_for_socket_errors()){
                        perror("Error in socket: ");
                        exit(1);
                    }
                }
            } else {
                perror("Failed to connect to server: ");
                exit(1);
            }
        }
        size_t watchdog = 0;
        this->_greet_server();
        size_t pos = 0;
        uint8_t buffer[2 * Packet::MaxSize()];
        int received = 0;
        size_t failed = 0;
        while(this->_check_for_socket_errors() == 0 && watchdog > 1000){
            if((received = recv(_client_fd, buffer + pos, (2 * Packet::MaxSize()) - pos, 0)) < 0){
                if(errno != EWOULDBLOCK && errno != EAGAIN) {
                    perror("Error receiving data: ");
                    break;
                }
            } else if(received > 0) {
                watchdog = 0;
                Packet packet;
                int end_pos = packet.unpack(buffer, received + pos);
                if(end_pos < 0){
                    pos += received;
                    ++failed;
                } else if(received - end_pos > 0){
                    memmove(buffer, buffer + end_pos, received - end_pos);
                    pos = received - end_pos;
                }

                if(end_pos >= 0){
                    if(this->parse_msg(packet) != ParseResult::Success) {
                        p("Error parsing packet!\n");
                        std::cout.flush();
                    }
                }
            }

            if(pos > 0){
                Packet packet;
                int end_pos = 0;
                if((end_pos = packet.unpack(buffer, pos)) < 0){
                    ++failed;
                } else if(pos - end_pos > 0) {
                    memmove(buffer, buffer + end_pos, pos - end_pos);
                    pos -= end_pos;
                }
                if(end_pos > 0)
                    this->parse_msg(packet);
            }

            if(failed > 5) {
                // clear buffer
                memset(buffer, 0, 2 * Packet::MaxSize());
            }

            if(_received >= EXPECTED){
                break;
            }
            ++watchdog;
        }
        close(_client_fd);
    }

    void _greet_server() {
        p("_greet_server\n");
        std::cout.flush();
        String hello("Hello!");
        Packet packet;
        packet.type = CHAR_MSG;
        memcpy(packet.value, hello.c_str(), hello.size());
        packet.vallen = hello.size() + 1;
        this->_send_packet(packet);
    }

    bool _send_packet(Packet& packet){
        p("_send_packet\n");
        std::cout.flush();
        uint8_t *buffer = packet.pack();
        if(send(_client_fd, buffer, packet.get_size(), 0) < 0){
            if(errno != EWOULDBLOCK && errno != EAGAIN) {
                perror("Error sending packet: ");
                delete buffer;
                return false;
            }
        }
        delete buffer;
        return true;
    }

    ParseResult parse_msg(Packet& packet){
        p("parse_msg\n");
        std::cout.flush();
        switch(packet.type){
        case CLIENT_UPDATE:
            {
                p("Client Update!\n");
                std::cout.flush();
                // reset other clients
                while(_other_clients.length() > 0){
                    delete _other_clients.pop();
                }

                size_t i = 0;
                while(i + sizeof(sockaddr_in) < packet.vallen){
                    SockAddrWrapper *saw = new SockAddrWrapper();
                    saw->addrlen = sizeof(sockaddr_in);
                    memcpy(&saw->addr, packet.value + i, saw->addrlen);
                    i += saw->addrlen + 1;
                    if(!_self.equals(saw)){
                        _other_clients.push(saw);
                        char *saw_c_str = saw->c_str();
                        p(saw_c_str).p('\n');
                        delete saw_c_str;
                        std::cout.flush();
                        /* char addr_str[INET_ADDRSTRLEN]; */
                        /* inet_ntop(AF_INET, */
                        /*           &(saw->addr.sin_addr), */
                        /*           addr_str, */
                        /*           INET_ADDRSTRLEN); */
                        /* p(addr_str).p(":").p(ntohs(saw->addr.sin_port)).p('\n'); */
                    } else {
                        delete saw;
                    }
                }
                break;
            }
        case CHAR_MSG:
        case ERROR_MSG:
            {
                if(packet.type == CHAR_MSG)
                    p("Message Received:\n");
                else 
                    p("Error Received:\n");

                char msg[packet.vallen + 1];
                memcpy(msg, &packet.value, packet.vallen);
                msg[packet.vallen] = '\0';
                p(msg).p('\n');
                p("Sender:\n");
                char addr_str[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(_server.sin_addr), addr_str, INET_ADDRSTRLEN);
                p(addr_str).p(":").p(ntohs((_server.sin_port))).p('\n');
                std::cout.flush();
                break;
            }
            default:
                return ParseResult::ParseError;
        }

        p("Message Parsed Sucessfully!\n");
        std::cout.flush();
        return ParseResult::Success;
    }
    
};
