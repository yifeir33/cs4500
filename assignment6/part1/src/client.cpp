#include "client.h"
#include "cts_connection.h"
#include "ctc_connection.h"

Client::Client(const char *client_ip, const char *server_ip, in_port_t port)
    : NetPort(client_ip, 0), _other_clients(10), _client_update(false),
    _greeted_clients(10), _received(0) {
    _server.addr.sin_family = AF_INET;
    if(inet_pton(AF_INET, server_ip, &(_server.addr.sin_addr)) <= 0){
        perror("Error converting address: ");
        exit(1);
    } // convert to proper format
    _server.addr.sin_port = htons(port);
}

Client::~Client(){
    p("Shutdown").p('\n');
    if(_server_connection){
        _server_connection->ask_to_finish();
        _server_connection->join();
        delete _server_connection;
    }
    _oclient_mutex.lock();
    for(size_t i = 0; i < _other_clients.length(); ++i){
        delete _other_clients.pop();
    }
    _oclient_mutex.unlock();

    _greeted_mutex.lock();
    for(size_t i = 0; i < _greeted_clients.length(); ++i){
        delete _greeted_clients.pop();
    }
    _greeted_mutex.unlock();
}

Packet *Client::get_registration_packet() {
    Packet *packet = new Packet();
    packet->type = REGISTER;
    packet->length = _self.addrlen;
    memcpy(&packet->value, &_self.addr, _self.addrlen);
    return packet;
}

Connection *Client::_new_connection(int new_conn_fd, SockAddrWrapper *other) {
    return new CtCConnection(new_conn_fd, other, *this, true);
}

void Client::_initial() {
    SockAddrWrapper cts_saw(_self);
    cts_saw.addr.sin_port = 0;

    int sock = create_socket(cts_saw, true);
    if(sock < 0){
        this->_running = false;
        return;
    }

    _server_connection = new CtSConnection(sock, *this, new SockAddrWrapper(_server));
    _server_connection->start();
}

void Client::_main_loop_work() {
    this->_check_done();
    this->_look_to_greet();
}

void Client::_look_to_greet(){
    _oclient_mutex.lock();
    _greeted_mutex.lock();

    for(size_t i = 0; i < _other_clients.length(); ++i){
        SockAddrWrapper *osaw = dynamic_cast<SockAddrWrapper*>(_other_clients.get(i)); 
        assert(osaw);
        if(_greeted_clients.index_of(osaw) < 0){
            bool c_exists = false;

            this->_connections_mutex.lock();

            for(size_t j = 0; j < _connections.length(); ++j){
                CtCConnection *ctcc = dynamic_cast<CtCConnection*>(_connections.get(j));
                assert(ctcc);
                if(ctcc->_conn_other->equals(osaw)){
                    c_exists = true;
                    break;
                }
            } // connection for

            this->_connections_mutex.unlock(); // this must be released before say hello

            if(!c_exists){
                this->_say_hello(new SockAddrWrapper(osaw));
            }
        }
    } // other clients for

    _greeted_mutex.unlock();
    _oclient_mutex.unlock();
}

void Client::_say_hello(SockAddrWrapper *osaw){
    char *addr = osaw->c_str();
    p("Saying Hello to: ").p(addr).p('\n');
    delete addr;

    SockAddrWrapper new_self(this->_self);
    new_self.addr.sin_port = 0;
    int new_fd = create_socket(new_self, true);
    if(new_fd < 0){
        this->_running = false;
        return;
    }
    CtCConnection *ctcc = new CtCConnection(new_fd, osaw, *this, false);
    ctcc->start();
    _connections_mutex.lock();
    _connections.push(ctcc);
    _connections_mutex.unlock();
}

void Client::_check_done() {
    _oclient_mutex.lock();
    _greeted_mutex.lock();

    if(_other_clients.length() > 0 && _other_clients.length() <= _greeted_clients.length() &&_other_clients.length() <= _received){
        p("Finished - Shutting Down!").p('\n');
        this->_running = false;
        this->close_all();
        this->_server_connection->ask_to_finish();
        this->_server_connection->join();
        delete _server_connection;
        _server_connection = nullptr;
    }

    _greeted_mutex.unlock();
    _oclient_mutex.unlock();
}
