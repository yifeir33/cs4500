#pragma once

#include "connection.h"
#include "client.h"

class CtSConnection : public Connection {
public:
    Client& _client;

    CtSConnection(int fd, Client& c, SockAddrWrapper *server) : Connection(fd, server), _client(c) {}

    void run() override {
        assert(this->_conn_other);
        this->connect_to_target(this->_conn_other->addr);
        while(!this->is_finished()) {
            sleep(1000);
        }
        this->deregister_and_shutdown();
    }

    void register_with_server() {
        Packet *packet = _client.get_registration_packet();
        if(!this->_send_packet(packet)){
            p("Unable to register!");
            this->_finished = true;
        }
        delete packet;
    }

    void deregister_and_shutdown(){
        Packet *packet = _client.get_registration_packet();
        packet->type = DEREGISTER;
        if(!this->_send_packet(packet)){
            p("Unable to deregister!");
            this->_finished = true;
        }
        delete packet;
    }
};
