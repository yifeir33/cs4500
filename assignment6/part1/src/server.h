#pragma once

#include <mutex>
#include <atomic>

#include "object.h"
#include "array.h"
#include "packet.h"
#include "socket_addr.h"

class Server : public Object {
public:
    sockaddr_in _self;
    int _server_fd;
    std::mutex _client_mutex;
    ObjectArray _clients;
    std::mutex _connections_mutex;
    ObjectArray _connections;
    std::atomic<size_t> _passed_update;
    std::atomic<size_t> _expected_update;
    std::atomic<bool> _new_update;

    Server(const char *ip, size_t port);

    ~Server();

    void server_listen();

    void _cleanup_closed();

    void update_and_alert(SockAddrWrapper *saw);

    Packet* get_clients();

    void remove_client(SockAddrWrapper* client);

    bool new_client_update();
}; // SERVER

