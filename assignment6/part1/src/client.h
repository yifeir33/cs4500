#pragma once

#include <assert.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <arpa/inet.h>

#include "netport.h"
#include "socket_addr.h"
#include "array.h"
#include "packet.h"

class CtSConnection;

class Client : public NetPort {
public:
    SockAddrWrapper _server;
    CtSConnection *_server_connection;
    std::mutex _oclient_mutex;
    ObjectArray _other_clients;
    std::atomic<bool> _client_update; 
    size_t _received;

    Client(const char *ip, in_port_t port);

    ~Client();

    Packet *get_registration_packet();

    Connection* _new_connection(int new_conn_fd, SockAddrWrapper *other) override;

    void _initial() override;
};
