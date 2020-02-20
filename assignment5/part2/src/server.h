#pragma once

#include <thread>
#include <mutex>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#include "object.h"
#include "string.h"
#include "array.h"
#include "thread_wrapper.h"
#include "type_length_value.h"

class Server : public Object {
public:
    class SockAddrWrapper : public Object {
    public:
        struct sockaddr_in addr;
        socklen_t addrlen;

        bool equals(Object *other){
            SockAddrWrapper *saw = dynamic_cast<SockAddrWrapper*>(other);
            if(saw){
                return this->addrlen == saw->addrlen
                       && this->addr.sin_addr.s_addr == saw->addr.sin_addr.s_addr
                       && this->addr.sin_port == saw->addr.sin_port
                       && this->addr.sin_family == saw->addr.sin_family;
            }
            return false;
        }
    };

    enum ParseResult {
        ParseError = -1,
        Success = 0,
        Response = 1,
    };

    int _server_fd;
    std::mutex _client_mutex;
    ObjectArray _clients;
    ObjectArray _connections;
    std::atomic<size_t> _passed_update;
    std::atomic<size_t> _expected_update;
    std::atomic<bool> _new_update;

    Server(const char *ip, size_t port) : _server_fd(-1), _clients(10), _connections(10), _passed_update(0), _expected_update(0), _new_update(false) {
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

    // MAIN THREAD FUNCTIONS
    void wait_for_connection() {
        SockAddrWrapper *saw = new SockAddrWrapper;
        size_t periodic_update = 0;
        while(true) {
            int new_connection_fd = 0;
            if((new_connection_fd = accept(_server_fd, reinterpret_cast<sockaddr*>(&saw->addr), &saw->addrlen)) < 0) {
                if(errno != EAGAIN && errno != EWOULDBLOCK) { // Since _server_fd is non-blocking to allow clean_up of threads
                    perror("Failed to Accept Connection");
                    exit(1);
                }
            } else {
                SockAddrWrapper *accepted_saw = saw;
                saw = new SockAddrWrapper;
                // Found Connection
                ThreadWrapper *tw = new ThreadWrapper();
                std::thread *new_thread = new std::thread(&Server::handle_connection, this, new_connection_fd, tw->finished);
                tw->set_thread(new_thread);
                _connections.push(tw);
                this->update_and_alert(accepted_saw);
                periodic_update = 0;
            }
            this->_cleanup_closed();
            sleep(1); // sleep for 1 second
            if(++periodic_update >= 25){
                this->_cleanup_closed();
                this->update_and_alert(nullptr);
                periodic_update = 0;
            }
        } // while
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

    void update_and_alert(SockAddrWrapper *saw) {
        if(saw){
            // update
            this->_client_mutex.lock();
            this->_clients.push(saw);
            this->_client_mutex.unlock();
        }
        // clean-up & alert
        this->_cleanup_closed();
        this->_expected_update = this->_connections.length();
        this->_new_update = true;
    }


    // CONNECTION FUNCTIONS
    bool client_update(int conn_fd) {
        this->_client_mutex.lock();
        size_t pos = 0;
        uint8_t buffer[sizeof(TypeLengthValue)];
        TypeLengthValue packet{0};
        packet.type = CLIENT_UPDATE;
        for(size_t i = 0; i < _clients.length(); ++i){
            SockAddrWrapper *saw = dynamic_cast<SockAddrWrapper*>(_clients.get(i));
            assert(saw);
            memcpy(&packet.value[packet.length], &saw->addr, saw->addrlen);
            packet.length += saw->addrlen;
            assert(packet.length + saw->addrlen < DATA_MAX);
        }
        this->_client_mutex.unlock();

        // encode into buffer to avoid packing issues/potential vtable/c++ weirdness
        size_t packet_size = sizeof(packet.type) + sizeof(packet.length) + packet.length;
        // type
        memcpy(buffer + pos, &packet.type, sizeof(packet.type));
        pos += sizeof(packet.type);
        // length
        memcpy(buffer + pos, &packet.length, sizeof(packet.length));
        pos += sizeof(packet.length);
        // value
        memcpy(buffer + pos, &packet.value, packet.length);
        pos += packet.length;

        if(send(conn_fd, &buffer, pos, 0) < 0){
            // TODO: if this becomes non-blocking then i need to check for EAGAIN/EWOULDBLOCK
            perror("Failed to send: ");
            return false;
        }
        if(++this->_passed_update >= _expected_update){
            this->_passed_update = 0;
            this->_new_update = false;
        }
        return true;
    }

    void handle_connection(int conn_fd, SockAddrWrapper& client, std::atomic<bool>& finished){
        assert(conn_fd > 0); // ensure valid fd
        finished = false;
        this->client_update(conn_fd);
        while(true){
            // TODO
            // Should this also not block? To allow for faster client updates?
            if(this->_new_update) {
                if(!client_update(conn_fd)) {
                    break;
                }
            }
        }
        close(conn_fd);
        this->_client_mutex.lock();
        this->_clients.remove(this->_clients.index_of(&client));
        this->_client_mutex.unlock();
        finished = true; // mark thread as finished so it can be joined & destroyed
    }

    ParseResult parse_data(int conn_fd, TypeLengthValue& tlv, sockaddr_in* sender){
        switch(tlv.type){
            case CHAR_MSG:
            case ERROR_MSG:
                {
                    if(tlv.type == CHAR_MSG)
                        p("Message Received:\n");
                    else 
                        p("Error Received:\n");

                    char msg[tlv.length + 1];
                    memcpy(msg, &tlv.value, tlv.length);
                    msg[tlv.length] = '\0';
                    p(msg).p('\n');
                    if(sender){
                        p("Sender:\n");
                        print_addr(sender);
                    }
                    return ParseResult::Success;
                }
            default:
                return ParseResult::ParseError;
        }
    }

    void print_addr(sockaddr_in* info){
        if(!info) return;
        p("Addr"); // TODO
    }
};
