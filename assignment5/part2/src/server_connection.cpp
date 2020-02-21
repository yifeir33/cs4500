#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#include "server_connection.h"

ServerConnection::ServerConnection(int cfd, SockAddrWrapper* c, Server& s) : Thread(),
    _conn_fd(cfd), _client(c), _server(s), _finished(false), _msg_queue() {
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
                if(packet->flags & FORWARD){
                    std::cout.flush();
                    if(!this->forward(packet)){
                        p("Error forwarding packet\n");
                        std::cout.flush();
                        delete packet;
                        break;
                    } 
                } else if(this->_parse_data(packet) != ParseResult::Success){
                    p("Error parsing data!\n");
                    std::cout.flush();
                }
            }
            received = 0;
        }

        if(!this->_check_msg_queue()){
            p("Error sending from queue!\n");
            std::cout.flush();
            break;
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

bool ServerConnection::_check_msg_queue(){
    std::cout.flush();
    this->_msg_queue_mutex.lock();
    while(_msg_queue.len() > 0){
        Packet *packet = dynamic_cast<Packet*>(_msg_queue.pop());
        assert(packet);
        p("Forwarding\n");
        std::cout.flush();
        if(!this->_send_packet(packet)){
            delete packet;
            this->_msg_queue_mutex.unlock();
            return false;
        }
        delete packet;
    }
    this->_msg_queue_mutex.unlock();
    return true;
}

void ServerConnection::enqueue_msg(Packet *packet){
    this->_msg_queue_mutex.lock();
    _msg_queue.push(packet);
    this->_msg_queue_mutex.unlock();
}

bool ServerConnection::is_finished() {
     return _finished;
}

bool ServerConnection::forward(Packet *packet){
    p("_forward").p('\n');
    std::cout.flush();
    if(packet->addrlen <= 0) return false;
    // Set-up wrapper for receipient
    SockAddrWrapper saw;
    saw.addrlen = packet->addrlen;
    saw.addr = packet->addr;
    // switch packet info to sender
    packet->addrlen = _client->addrlen;
    packet->addr = _client->addr;

    if(!_server.forward(packet, saw)){
        Packet error_packet;
        error_packet.type = ERROR_MSG;
        const char *e = "Failed To Forward Message!";
        memcpy(&error_packet.value, e, strlen(e));
        error_packet.vallen = strlen(e) + 1;
        return _send_packet(&error_packet);
    }
    return true;
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
                p(inet_ntop(AF_INET,
                            &(packet->flags & FORWARD && packet->addrlen > 0 ? packet->addr.sin_addr : _client->addr.sin_addr),
                            addr_str,
                            INET_ADDRSTRLEN));
                p(":").p(ntohs((packet->flags & FORWARD && packet->addrlen > 0 ? packet->addr.sin_port : _client->addr.sin_port)));
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
