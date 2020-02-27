#pragma once

#include "client.h"
#include "connection.h"

class CtCConnection : public Connection {
public:
    Client& _client
    bool _receiver;

    CtCConnection(int fd, SockAddrWrapper *other, Client& c, bool r) : Connection(fd, other), _client(c), _receiver(r) {}

    void run() override {
        if(_receiver){
            this->_as_receiver();
        } else {
            this->_as_client();
        }
    }

    void _as_client() {
        assert(this->_conn_other);
        this->connect_to_target(this->_conn_other->addr);
        while(!this->is_finished()){
            // TODO
        }
    }

    void _as_receiver(){
        while(!this->is_finished()){
            // TODO
        }
    }

};
