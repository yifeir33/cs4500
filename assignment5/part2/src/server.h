#pragma once

#include <thread>
#include <mutex>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#include "object.h"
#include "string.h"
#include "array.h"
#include "thread_wrapper.h"

class Server : public Object {
public:
    int _server_fd;
    StringArray _clients;
    ObjectArray _connections;

    Server(const char *ip, size_t port) : _server_fd(-1), _clients(10), _connections(10) {
        if((_server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0) {
            perror("Failed to create socket!");
            exit(1);
        }

        struct sockaddr_in saddr{};
        saddr.sin_family = AF_INET;
        saddr.sin_addr.s_addr = INADDR_ANY;
        saddr.sin_port = htons(port);

        if(bind(_server_fd, reinterpret_cast<sockaddr *>(&saddr), sizeof(saddr)) < 0){
            perror("Failed to bind to address!");
            exit(1);
        }

        if(listen(_server_fd, 10) < 0){
            perror("Failed to listen!");
            exit(1);
        }

        this->wait_for_connection();
    }

    ~Server() {
        while(_clients.length() > 0) {
            delete _clients.pop();
        }

        if(_server_fd > 0) {
            close(_server_fd);
        }

        while(_connections.length() > 0) {
            ThreadWrapper *tw = static_cast<ThreadWrapper*>(_connections.pop());
            if(tw) {
                tw->joindelete();
                delete tw;
            }
        }
    }

    void wait_for_connection() {
        while(true) {
            int new_connection_fd = 0;
            if((new_connection_fd = accept(_server_fd, nullptr, nullptr)) < 0) {
                if(errno != EAGAIN && errno != EWOULDBLOCK) { // Since _server_fd is non-blocking to allow clean_up of threads
                    perror("Failed to Accept Connection");
                    exit(1);
                }
            } else {
                // Found Connection
                ThreadWrapper *tw = new ThreadWrapper();
                std::thread *new_thread = new std::thread(&Server::handle_connection, this, new_connection_fd, tw->finished);
                tw->set_thread(new_thread);
                _connections.push(tw);
            }
            this->_cleanup_closed();
            sleep(1); // sleep for 1 second
        }
    }

    void _cleanup_closed() {
        ObjectArray remove_arr(10);
        for(size_t i = 0; i < _connections.length(); ++i){
            ThreadWrapper *tw = static_cast<ThreadWrapper*>(_connections.get(i));
            if(tw && tw->is_finished()) {
                tw->joindelete();
                remove_arr.push(tw);
            }
        }

        for(size_t i = 0; i < remove_arr.length(); ++i) {
            // delete unneeded thread wrappers
            delete _connections.remove(_connections.index_of(remove_arr.get(i)));
        }
    }

    void handle_connection(int conn_fd, std::atomic<bool>& finished){
        assert(conn_fd > 0); // ensure valid fd
        finished = false;
        while(true){
            // TODO
        }
        close(conn_fd);
        finished = true; // mark thread as finished so it can be joined & destroyed
    }
};
