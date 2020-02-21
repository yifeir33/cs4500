#include <thread>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "server.h"
#include "server_connection.h"


Server::Server(const char *ip, size_t port) :
    _server_fd(-1), _clients(10), _connections(10),
    _passed_update(0), _expected_update(0), _new_update(false) {
    if((_server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0) {
        perror("Failed to create socket!");
        exit(1);
    }
    int opt = 1;
    if(setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        perror("Error setting socket options: ");
        exit(1);
    }

    _self.sin_family = AF_INET;
    int rc = inet_pton(AF_INET, ip, &(_self.sin_addr));
    if( rc <= 0){ // convert to proper format
        perror("Error converting address: ");
        exit(1);
    }
    _self.sin_port = htons(port);

    if(bind(_server_fd, reinterpret_cast<sockaddr *>(&_self), sizeof(_self)) < 0){
        perror("Failed to bind to address!");
        exit(1);
    }
    p("Server bound to: ").p(ip).p('\n');
    std::cout.flush();
}

Server::~Server() {
    if(_server_fd > 0) {
        close(_server_fd);
    }

    _connections_mutex.lock();
    while(_connections.length() > 0) {
        ServerConnection *sc = dynamic_cast<ServerConnection*>(_connections.pop());
        if(sc) {
            sc->ask_to_finish();
            sc->join();
            delete sc;
        }
    }
    _connections_mutex.unlock();
    while(_clients.length() > 0) {
        delete _clients.pop();
    }
}

void Server::server_listen() {
    if(listen(_server_fd, 10) < 0){
        perror("Failed to listen!");
        exit(1);
    }

    SockAddrWrapper *saw = new SockAddrWrapper;
    saw->addrlen = sizeof(saw->addr);
    size_t periodic_update = 0;
    while(true) {
        int new_connection_fd = 0;
        if((new_connection_fd = accept(_server_fd, reinterpret_cast<sockaddr*>(&saw->addr), &saw->addrlen)) < 0) {
            if(errno != EAGAIN && errno != EWOULDBLOCK) { // Since _server_fd is non-blocking to allow clean_up of threads
                perror("Failed to Accept Connection");
                exit(1);
            }
        } else {
            p("Accepted Connection:\n");
            char *saw_c_str = saw->c_str();
            p(saw_c_str).p('\n');
            delete saw_c_str;
            std::cout.flush();

            SockAddrWrapper *accepted_saw = saw;
            saw = new SockAddrWrapper;
            saw->addrlen = sizeof(saw->addr);
            // Found Connection
            ServerConnection *sc = new ServerConnection(new_connection_fd, accepted_saw, *this);
            std::cout.flush();
            sc->start();
            _connections_mutex.lock();
            _connections.push(sc);
            _connections_mutex.unlock();
            this->update_and_alert(accepted_saw);
            periodic_update = 0;
        }
        this->_cleanup_closed();
        sleep(1); // sleep for 1 second
        if(++periodic_update >= 25){
            this->_cleanup_closed();
            /* this->update_and_alert(nullptr); */
            /* periodic_update = 0; */
            break;
        }
    } // while
    close(_server_fd);
    p("Server shut down\n");
}

void Server::_cleanup_closed() {
    ObjectArray remove_arr(10);
    _connections_mutex.lock();
    for(size_t i = 0; i < _connections.length(); ++i){
        ServerConnection *sc = dynamic_cast<ServerConnection*>(_connections.get(i));
        if(sc && sc->is_finished()) {
            p("Cleaning up thread!\n");
            std::cout.flush();
            sc->join();
            remove_arr.push(sc);
        }
    }

    for(size_t i = 0; i < remove_arr.length(); ++i) {
        // delete unneeded thread wrappers
        delete _connections.remove(_connections.index_of(remove_arr.get(i)));
    }
    _connections_mutex.unlock();
}

void Server::update_and_alert(SockAddrWrapper *saw) {
    if(saw){
        // update
        this->_client_mutex.lock();
        this->_clients.push(saw);
        this->_client_mutex.unlock();
    }
    // clean-up & alert
    this->_cleanup_closed();
    _connections_mutex.lock();
    this->_expected_update = this->_connections.length();
    _connections_mutex.unlock();
    this->_new_update = true;
}

Packet* Server::get_clients(){
    this->_client_mutex.lock();
    Packet *packet = new Packet();
    packet->type = CLIENT_UPDATE;
    p("Clients:\n");
    for(size_t i = 0; i < _clients.length(); ++i){
        SockAddrWrapper *saw = dynamic_cast<SockAddrWrapper*>(_clients.get(i));
        assert(saw);
        char *saw_c_str = saw->c_str();
        p(saw_c_str).p('\n');
        delete saw_c_str;
        memcpy(packet->value + packet->vallen, &saw->addr, saw->addrlen);
        packet->vallen += saw->addrlen;
        assert(packet->vallen + saw->addrlen < DATA_MAX);
    }
    std::cout.flush();
    packet->vallen += 1;
    this->_client_mutex.unlock();
    if(++this->_passed_update >= _expected_update){
        this->_passed_update = 0;
        this->_new_update = false;
    }
    return packet;
}

void Server::remove_client(SockAddrWrapper* client) {
    this->_client_mutex.lock();
    this->_clients.remove(this->_clients.index_of(client));
    this->_client_mutex.unlock();
}

bool Server::new_client_update() {
    return _new_update;
}

bool Server::forward(Packet *packet, SockAddrWrapper saw){
    _connections_mutex.lock();
    for(size_t i = 0; i < _connections.length(); ++i){
        ServerConnection *sc = dynamic_cast<ServerConnection*>(_connections.get(i));
        assert(sc);
        SockAddrWrapper *conn_client = sc->get_client();
        if(saw.equals(conn_client)){
            sc->enqueue_msg(packet);
            delete conn_client;
            _connections_mutex.unlock();
            return true;
        }
        delete conn_client;
    }
    _connections_mutex.unlock();
    return false;
}
