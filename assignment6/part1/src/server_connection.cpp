#include "server_connection.h"

ServerConnection::ServerConnection(int cfd, SockAddrWrapper* o, Server& s) : Connection(cfd, o), _server(s) {}

ServerConnection::~ServerConnection(){}

void ServerConnection::run() {
    // TODO: add watchdog
    while(!this->is_finished()){
        this->receive_and_parse();
        if(_server._new_update){
            Packet *packet = _server.get_clients();
            if(!this->_send_packet(packet)){
                delete packet;
                break;
            }
            delete packet;
        }
        sleep(500);
    } // while

    close(_conn_fd);
    _conn_fd = 0;
}

ParseResult ServerConnection::_parse_data(Packet& packet) {
    if(packet.type == REGISTER || packet.type == DEREGISTER) {
        if(packet.length != sizeof(sockaddr_in)) {
            return ParseResult::ParseError;
        }
        SockAddrWrapper *saw = new SockAddrWrapper();
        memcpy(&saw->addr, packet.value, packet.length);

        if(packet.type == REGISTER){
            _server.update_and_alert(saw);
        } else {
            _server.remove_client(saw);
            delete saw;
        }
        return ParseResult::Success;
    } else if(packet.type == SHUTDOWN){
        this->ask_to_finish();
        return ParseResult::Success;
    }

    return Connection::_parse_data(packet);
}
