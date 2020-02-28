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

#define WATCHDOG_TIMEOUT  60 // seconds
#define BUFFER_SIZE (2 * PACKET_MAX_SIZE)

class Connection : public Thread {
public:
    int _conn_fd;
    SockAddrWrapper* _conn_other;
    std::atomic<bool> _finished;
    size_t _r_buf_pos;
    uint8_t _r_buffer[BUFFER_SIZE];
    std::chrono::time_point<std::chrono::steady_clock> _watchdog;

    Connection(int cfd, SockAddrWrapper *c) : Thread(), _conn_fd(cfd), _conn_other(c), _finished(false), _r_buf_pos(0), _watchdog(std::chrono::steady_clock::now()) {
        memset(_r_buffer, 0, BUFFER_SIZE);
        /* p("New Connection!\n"); */
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

    void feed_dog(){
        _watchdog = std::chrono::steady_clock::now();
    }

    bool dog_is_alive(){
        bool out =  std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _watchdog).count()
                    < WATCHDOG_TIMEOUT;
        if(!out){
            p("Watchdog Timed Out!").p('\n');
        }
        return out;
    }

    bool _keep_alive() {
        Packet packet;
        packet.type = KEEP_ALIVE;
        packet.length = 0;
        return this->_send_packet(&packet);
    }

    void _send_shutdown() {
        Packet packet;
        packet.type = SHUTDOWN;
        packet.length = 0;
        this->_send_packet(&packet); // regardless we shutdown
        this->_finished = true;
    }

    bool _send_packet(Packet *packet) {
        assert(packet);
        uint8_t w_buffer[PACKET_MAX_SIZE];
        int p_size = packet->pack(w_buffer, PACKET_MAX_SIZE);
        if(p_size < 0) return false;
        int attempt = 0;
        ssize_t sent = 0;

        while(attempt < 5){
            if(this->_check_for_socket_errors() > 0){
                if(errno != EWOULDBLOCK && errno != EAGAIN && errno != 0) {
                    perror("Socket Errors Found: ");
                    p("errno value: ").p(errno).p('\n');
                    return false;
                }
            }
            if((sent = send(_conn_fd, w_buffer, p_size, 0)) < 0){
                if(errno != EWOULDBLOCK && errno != EAGAIN) {
                    perror("Error sending packet: ");
                    return false;
                }
            } else if(sent > 0) {
                /* p("Sent Packet!").p('\n'); */
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
            if(errno != EWOULDBLOCK && errno != EAGAIN && errno != 0) {
                perror("Error checking socket: ");
                p("Errno Value: ").p(errno).p('\n');
                this->_finished = true;
            }
        }
        return opt;
    }

    int receive_data() {
        int received = 0;
        int attempt = 0;

        while (attempt < 5) {
            if((received = recv(_conn_fd, _r_buffer + _r_buf_pos, BUFFER_SIZE - _r_buf_pos, 0)) < 0) {
                if(errno != EWOULDBLOCK && errno != EAGAIN) {
                    perror("Error receiving data: ");
                    return received;
                }
            } else {
                /* p("Received: ").p(received).p('\n'); */
                _r_buf_pos += received;
                return received;
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
        /* p("_parse_data\n"); */
        std::cout.flush();

        switch(packet.type){
            case CLIENT_UPDATE:
                break;
            case REGISTER:
                break;
            case KEEP_ALIVE:
                this->_respond(packet);
                break;
            case ASK_FOR_ID:
                return ParseResult::Response;
            case ID:
                {
                    if(packet.length != sizeof(sockaddr_in)) {
                        return ParseResult::ParseError;
                    }
                    SockAddrWrapper *saw = new SockAddrWrapper();
                    memcpy(&saw->addr, packet.value, packet.length);
                    if(this->_conn_other){
                        delete this->_conn_other;
                    }
                    this->_conn_other = saw;
                    break;
                }
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
                    /* p("Sender:\n"); */
                    /* char addr_str[INET_ADDRSTRLEN]; */
                    /* p(inet_ntop(AF_INET, &(_conn_other->addr.sin_addr), addr_str, INET_ADDRSTRLEN)); */
                    /* p(":").p(ntohs((_conn_other->addr.sin_port))); */
                    /* p("\n"); */
                    break;
                }
            case SHUTDOWN:
                p("Shutdown Received!").p('\n');
                this->_finished = true;
                break;
            default:
                p("Unrecognized Type: ").p(packet.type).p('\n');
                return ParseResult::ParseError;
        }
        return ParseResult::Success;
    }

    virtual int _respond(Packet& msg){ return 0; }

    bool receive_and_parse() {
        if(this->receive_data() < 0) {
            return false;
        }
        /* p("Data Received!").p('\n'); */
        /* this->print_read_buffer(); */

        Packet packet;
        while(_r_buf_pos > 0){
            if(!this->unpack(packet)){
                p("Failed to unpack data!").p('\n');
                break;
            }

            switch(this->_parse_data(packet)){
                case Success:
                    return true;
                case Response:
                    this->_respond(packet);
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
                    this->_finished = true;
                    return;
                }
                if(FD_ISSET(_conn_fd, &fdset)){
                    if(this->_check_for_socket_errors()){
                        perror("Error in socket: ");
                        this->_finished = true;
                        return;
                    }
                }
            } else {
                perror("Failed to connect to target: ");
                this->_finished = true;
                return;
            }
        }
    }


    void ask_to_finish(){
        this->_finished = true;
    }

    bool is_finished(){
        return _finished;
    }

    void print_read_buffer(){
        p("Read Buffer (Length: ").p(_r_buf_pos).p("): ").p('\n');
        for(size_t i = 0; i < _r_buf_pos; ++i){
            p(_r_buffer[i]);
            if(i > 0 && i % 8 == 0) {
                p('\n');
            }else {
                p(' ');
            }
        }
        p('\n');
    }
};
