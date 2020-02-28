#pragma once

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <chrono>

#include "object.h"
#include "array.h"
#include "socket_addr.h"
#include "connection.h"
#include "util.h"

#define WATCHDOG_TIMEOUT  60 // seconds

class NetPort : public Object {
public:
    int _sock_fd;
    SockAddrWrapper _self;
    std::mutex _connections_mutex;
    ObjectArray _connections;
    std::atomic<bool> _running;
    std::atomic<std::chrono::time_point<std::chrono::steady_clock>> _watchdog;

    NetPort(const char *ip, in_port_t port) : _sock_fd(0), _connections(10), _running(true), _watchdog(std::chrono::steady_clock::now()){
        if((_sock_fd = create_socket(ip, port, &_self, true)) < 0){
            assert(false);
        }
        char *sock_info = _self.c_str();
        p("NetPort bound to: ").p(sock_info).p('\n');
        std::cout.flush();
        delete[] sock_info;
    }

    virtual ~NetPort(){
        this->close_all();
        if(_sock_fd > 0){
            close(_sock_fd);
        }
    }

    void feed_dog(){
        _watchdog = std::chrono::steady_clock::now();
    }

    bool dog_is_alive(){
        std::chrono::time_point<std::chrono::steady_clock> wd = _watchdog;

        bool out =  std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - wd).count()
                    < WATCHDOG_TIMEOUT;
        if(!out){
            p("Watchdog Timed Out!").p('\n');
        }
        return out;
    }

    void close_all(){
        _connections_mutex.lock();
        while(_connections.length() > 0){
            Connection *c = dynamic_cast<Connection*>(_connections.pop());
            assert(c);
            c->ask_to_finish();
            c->join();
            delete c;
        }
        _connections_mutex.unlock();
    }

    void listen_on_socket(int conn_count){
        if(listen(_sock_fd, conn_count) < 0){
            perror("Error listening on socket: ");
            this->_running = false;
        }
        this->_running = true;
        this->_initial();

        while(this->_running && this->dog_is_alive()){
            if(this->_accept_connection()){
                this->_on_new_connection();
                this->feed_dog();
            }
            this->_clean_up_closed();
            this->_main_loop_work();
        }
        p("Exiting").p('\n');
        close(_sock_fd);
        this->_running = false;
    }

    bool _accept_connection(){
        int new_connection_fd = 0;
        SockAddrWrapper *saw = new SockAddrWrapper();
        if((new_connection_fd = accept(_sock_fd, reinterpret_cast<sockaddr*>(&saw->addr), &saw->addrlen)) < 0){
            if(errno != EAGAIN && errno != EWOULDBLOCK) { // Since _server_fd is non-blocking to allow clean_up of threads
                perror("Failed to Accept Connection");
                this->_running = false;
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
            if(c->is_finished()) {
                p("Cleaning up thread!").p('\n');
                c->join();
                remove_arr.push(c);
                this->_on_clean_up(c);
            }
        }

        for(size_t i = 0; i < remove_arr.length(); ++i) {
            // delete unneeded thread wrappers
            delete _connections.remove(_connections.index_of(remove_arr.get(i)));
        }
        _connections_mutex.unlock();
    }

    virtual void _on_clean_up(Connection *c){}

    virtual void _initial(){}

    virtual void _main_loop_work(){}

    virtual void _on_new_connection() {}

    virtual Connection *_new_connection(int new_conn_fd, SockAddrWrapper* other) = 0;
};
