#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#include "server_connection.h"

ServerConnection::ServerConnection(int cfd, SockAddrWrapper* c, Server& s) : Thread(),
    _conn_fd(cfd), _client(c), _server(s), _finished(false) {
        p("New Connection!\n");
        // make socket non-blocking
        if(fcntl(_conn_fd, F_SETFL, fcntl(_conn_fd, F_GETFL, 0) | O_NONBLOCK) < 0){
            perror("Failed to set socket to non-blocking!");
        }
    }

ServerConnection::~ServerConnection() {
    if(_client){
        delete _client;
    }
};

int ServerConnection::_check_for_socket_errors(){
    int opt = 0;
    socklen_t optlen = sizeof(opt);
    if(getsockopt(_conn_fd, SOL_SOCKET, SO_ERROR, &opt, &optlen) < 0){
        perror("Error checking socket: ");
        exit(1);
    }
    return opt;
}

SockAddrWrapper *ServerConnection::get_client() {
    return new SockAddrWrapper(_client);
}

void ServerConnection::run() {
    p("Running\n");
    std::cout.flush();
    assert(_conn_fd > 0); // ensure valid fd
    std::cout.flush();
    _finished = false;
    this->_send_packet(_server.get_clients());
    size_t watchdog = 0;
    std::cout.flush();
    size_t pos = 0;
    uint8_t buffer[2 * Packet::MaxSize()];
    int received = 0;
    std::cout.flush();
    while(this->_check_for_socket_errors() == 0 && !this->_finished && watchdog < 1000){
        if((received = recv(_conn_fd, buffer + pos, (2 * Packet::MaxSize()) - pos, 0)) < 0) {
            if(errno != EWOULDBLOCK && errno != EAGAIN) {
                perror("Error receiving data: ");
                break;
            }
        } else if(received > 0) {
            watchdog = 0;
            std::cout.flush();
            Packet *packet = new Packet();
            int end_pos = packet->unpack(buffer, received + pos);
            if(end_pos < 0){
                pos += received;
            } else if(received - end_pos > 0){
                std::cout.flush();
                memmove(buffer, buffer + end_pos, received + pos - end_pos);
                std::cout.flush();
                pos = 0;
            }
            std::cout.flush();
            if(end_pos >= 0){
                std::cout.flush();
            } else if(this->_parse_data(packet) != ParseResult::Success){
                p("Error parsing data!\n");
                std::cout.flush();
            }
            received = 0;
        }

        if(_server.new_client_update()) {
            Packet *client_update = _server.get_clients();
            if(!_send_packet(client_update)) {
                perror("Failed to send packet: ");
                delete client_update;
                break;
            }
            delete client_update;
        }

        ++watchdog;
    } // While
    close(_conn_fd);
    _server.remove_client(this->_client);
    if(!_finished){
        // otherwise was asked to finish
        _finished = true; // mark thread as finished so it can be joined & destroyed
    }
    p("Thread Finished!\n");
    std::cout.flush();
}

bool ServerConnection::is_finished() {
     return _finished;
}

bool ServerConnection::_send_packet(Packet *packet) {
    p("_send_packet\n");
    std::cout.flush();
    uint8_t *buf = packet->pack();
    if(send(_conn_fd, buf, packet->get_size(), 0) < 0){
        if(errno != EWOULDBLOCK && errno != EAGAIN) {
            perror("Error sending packet: ");
            std::cout.flush();
            delete buf;
            return false;
        }
    }
    std::cout.flush();
    delete buf;
    return true;
}

ParseResult ServerConnection::_parse_data(Packet *packet){
    p("_parse_data\n");
    std::cout.flush();
    if(!packet) return ParseResult::ParseError;
    switch(packet->type){
        case CHAR_MSG:
        case ERROR_MSG:
            {
                if(packet->type == CHAR_MSG)
                    p("Message Received:\n");
                else 
                    p("Error Received:\n");

                char msg[packet->vallen];
                memcpy(msg, &packet->value, packet->vallen);
                msg[packet->vallen - 1] = '\0';
                p(msg).p('\n');
                p("Sender:\n");
                char addr_str[INET_ADDRSTRLEN];
                p(inet_ntop(AF_INET, &(_client->addr.sin_addr), addr_str, INET_ADDRSTRLEN));
                p(":").p(ntohs((_client->addr.sin_port)));
                p("\n");
                std::cout.flush();
                break;
            }
        default:
            p("Unrecognized Type: ").p(packet->type).p('\n');
            std::cout.flush();
            delete packet;
            return ParseResult::ParseError;
    }

    delete packet;
    return ParseResult::Success;
}

void ServerConnection::ask_to_finish(){
    this->_finished = true;
}
