#pragma once

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "object.h"
#include "array.h"
#include "socket_addr.h"
#include "connection.h"
#include "util.h"

class NetPort : public Object {
public:
    int _sock_fd;
    SockAddrWrapper _self;
    std::mutex _connections_mutex;
    ObjectArray _connections;
    std::atomic<bool> _running;

    NetPort(const char *ip, in_port_t port) : _sock_fd(0), _connections(10), _running(true) {
        _sock_fd = create_socket(ip, port, &_self, true);
        char *sock_info = _self.c_str();
        p("Server bound to: ").p(sock_info).p('\n');
        std::cout.flush();
        delete[] sock_info;
    }

    virtual ~NetPort(){
        if(_sock_fd > 0){
            close(_sock_fd);
        }
    }

    void listen_on_socket(int conn_count){
        // TODO: watchdog
        if(listen(_sock_fd, conn_count) < 0){
            perror("Error listening on socket: ");
            exit(1);
        }
        this->_running = true;
        this->_initial();

        while(this->_running){
            if(this->_accept_connection()){
                this->_on_new_connection();
            }
            this->_clean_up_closed();
            this->_main_loop_work();
        }
        close(_sock_fd);
    }

    bool _accept_connection(){
        int new_connection_fd = 0;
        SockAddrWrapper *saw = new SockAddrWrapper();
        if((new_connection_fd = accept(_sock_fd, reinterpret_cast<sockaddr*>(&saw->addr), &saw->addrlen)) < 0){
            if(errno != EAGAIN && errno != EWOULDBLOCK) { // Since _server_fd is non-blocking to allow clean_up of threads
                perror("Failed to Accept Connection");
                exit(1);
            }
            delete saw;
            return false;
        } else {
            Connection *c = _new_connection(new_connection_fd, saw);
            c->start();
            _connections_mutex.lock();
            _connections.push(c);
            _connections_mutex.unlock();
            return true;
        }
    }

    void _clean_up_closed() {
        ObjectArray remove_arr(10);
        _connections_mutex.lock();
        for(size_t i = 0; i < _connections.length(); ++i){
            Connection *c = dynamic_cast<Connection*>(_connections.get(i));
            assert(c);
            if(c && c->is_finished()) {
                p("Cleaning up thread!\n");
                std::cout.flush();
                c->join();
                remove_arr.push(c);
            }
        }

        for(size_t i = 0; i < remove_arr.length(); ++i) {
            // delete unneeded thread wrappers
            delete _connections.remove(_connections.index_of(remove_arr.get(i)));
        }
        _connections_mutex.unlock();
    }

    virtual void _initial(){}

    virtual void _main_loop_work(){}

    virtual void _on_new_connection() {}

    virtual Connection *_new_connection(int new_conn_fd, SockAddrWrapper* other) = 0;
};
