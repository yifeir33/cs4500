#pragma once

#include <atomic>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "thread.h"
#include "packet.h"
#include "socket_addr.h"
#include "util.h"

#define BUFFER_SIZE (5 * PACKET_MAX_SIZE)

class Connection : public Thread {
public:
    int _conn_fd;
    SockAddrWrapper* _conn_other;
    std::atomic<bool> _finished;
    size_t _r_buf_pos;
    uint8_t _r_buffer[BUFFER_SIZE];

    Connection(int cfd, SockAddrWrapper *c) : Thread(), _conn_fd(cfd), _conn_other(c), _finished(false) {
        p("New Connection!\n");
        make_non_blocking(_conn_fd);
    }

    virtual ~Connection() {
        if(_conn_fd > 0){
            close(_conn_fd);
        }
        if(_conn_other){
            delete _conn_other;
        }
    }

    bool _send_packet(Packet *packet) {
        p("_send_packet\n");
        uint8_t w_buffer[PACKET_MAX_SIZE];
        int p_size = packet->pack(w_buffer, PACKET_MAX_SIZE);
        if(p_size < -1) return false;
        int attempt = 0;

        while(attempt < 5){
            if(send(_conn_fd, w_buffer, p_size, 0) < 0){
                if(errno != EWOULDBLOCK && errno != EAGAIN) {
                    perror("Error sending packet: ");
                    return false;
                }
            } else {
                return true;
            }
            sleep(100); // sleep 100 milliseconds
            ++attempt;
        }
        return false;
    }

    SockAddrWrapper *get_conn_other() {
        if(!_conn_other) return nullptr;
        return new SockAddrWrapper(_conn_other);
    }

    int _check_for_socket_errors() {
        int opt = 0;
        socklen_t optlen = sizeof(opt);
        if(getsockopt(_conn_fd, SOL_SOCKET, SO_ERROR, &opt, &optlen) < 0){
            perror("Error checking socket: ");
            exit(1);
        }
        return opt;
    }

    int receive_data() {
        Packet p;
        int received = 0;
        int attempt = 0;

        while (attempt < 5) {
            if((received = recv(_conn_fd, _r_buffer + _r_buf_pos, BUFFER_SIZE - _r_buf_pos, 0)) < 0) {
                if(errno != EWOULDBLOCK && errno != EAGAIN) {
                    perror("Error receiving data: ");
                    return received;
                }
            } else {
                _r_buf_pos += received;
            }
            ++attempt;
        } // while
        return -1;
    }

    bool unpack(Packet& packet){
        int parsed_pos = 0;
        if((parsed_pos = packet.unpack(_r_buffer, BUFFER_SIZE)) < 0){
            return false;
        } else {
            memmove(_r_buffer, _r_buffer + parsed_pos, BUFFER_SIZE - parsed_pos);
            _r_buf_pos -= parsed_pos;
            memset(_r_buffer + _r_buf_pos, 0, BUFFER_SIZE - _r_buf_pos); // 0 out rest of buffer
            return true;
        }
    }

    virtual ParseResult _parse_data(Packet& packet){
        p("_parse_data\n");
        std::cout.flush();

        switch(packet.type){
            /*
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
                            char addr_str[INET_ADDRSTRLEN];
                            inet_ntop(AF_INET,
                                      &(saw->addr.sin_addr),
                                      addr_str,
                                      INET_ADDRSTRLEN);
                            p(addr_str).p(":").p(ntohs(saw->addr.sin_port)).p('\n');
                        } else {
                            delete saw;
                        }
                    }
                break;
            }*/
            case REGISTER:
                break;
            case CHAR_MSG:
            case ERROR_MSG:
                {
                    if(packet.type == CHAR_MSG)
                        p("Message Received:\n");
                    else 
                        p("Error Received:\n");

                    char msg[packet.length + 1];
                    memcpy(msg, &packet.value, packet.length);
                    msg[packet.length] = '\0';
                    p(msg).p('\n');
                    p("Sender:\n");
                    char addr_str[INET_ADDRSTRLEN];
                    p(inet_ntop(AF_INET, &(_conn_other->addr.sin_addr), addr_str, INET_ADDRSTRLEN));
                    p(":").p(ntohs((_conn_other->addr.sin_port)));
                    p("\n");
                    std::cout.flush();
                    break;
                }
            default:
                p("Unrecognized Type: ").p(packet.type).p('\n');
                std::cout.flush();
                return ParseResult::ParseError;
        }
        return ParseResult::Success;
    }

    bool receive_and_parse() {
        if(this->receive_data() < 0) {
            return false;
        }

        Packet packet;
        while(_r_buf_pos > 0){
            if(!this->unpack(packet)){
                break;
            }

            switch(this->_parse_data(packet)){
                case Success:
                    return true;
                case Response:
                    // TODO
                    break;
                case ParseError:
                        return false;
                default:
                    return false;
            }
        }
        return true;
    }

    void connect_to_target(sockaddr_in target){
        if(connect(_conn_fd, reinterpret_cast<sockaddr*>(&target), sizeof(target)) < 0) {
            // Needed cause the socket is non-blocking
            if(errno == EINPROGRESS){
                fd_set fdset{0};
                FD_SET(_conn_fd, &fdset);
                if(select(_conn_fd + 1, nullptr, &fdset, nullptr, nullptr) < 0){ 
                    perror("Error on select: ");
                    exit(1);
                }
                if(FD_ISSET(_conn_fd, &fdset)){
                    if(this->_check_for_socket_errors()){
                        perror("Error in socket: ");
                        exit(1);
                    }
                }
            } else {
                perror("Failed to connect to target: ");
                exit(1);
            }
        }
    }

    void ask_to_finish(){
        this->_finished = true;
    }

    bool is_finished(){
        return _finished;
    }
};
