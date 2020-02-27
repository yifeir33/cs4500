#include "client.h"
#include "cts_connection.h"
#include "ctc_connection.h"

Client::Client(const char *ip, in_port_t port) : NetPort("127.0.0.1", 0), _other_clients(10), _client_update(false), _received(0) {
    _server.addr.sin_family = AF_INET;
    if(inet_pton(AF_INET, ip, &(_server.addr.sin_addr)) <= 0){
        perror("Error converting address: ");
        exit(1);
    } // convert to proper format
    _server.addr.sin_port = htons(port);
}

Client::~Client(){
    if(_server_connection){
        _server_connection->ask_to_finish();
        _server_connection->join();
        delete _server_connection;
    }
}

Packet *Client::get_registration_packet() {
    Packet *packet = new Packet();
    packet->type = REGISTER;
    packet->length = _self.addrlen;
    memcpy(&packet->value, &_self.addr, _self.addrlen);
    return packet;
}

Connection *Client::_new_connection(int new_conn_fd, SockAddrWrapper *other) {
    return new CtCConnection(new_conn_fd, other, *this, false);
}

void Client::_initial() {
    SockAddrWrapper cts_saw(_self);
    cts_saw.addr.sin_port = 0;

    int sock = create_socket(cts_saw, true);

    _server_connection = new CtSConnection(sock, *this, &_server);
    _server_connection->start();
}
