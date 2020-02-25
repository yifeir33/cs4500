#pragma once

#include <mutex>
#include <atomic>

#include "thread.h"
#include "server.h"
#include "socket_addr.h"
#include "queue.h"


class ServerConnection : public Thread {
public:
    int _conn_fd;
    SockAddrWrapper* _client;
    Server& _server;
    std::atomic<bool> _finished;

    ServerConnection(int cfd, SockAddrWrapper* c, Server& s);

    ~ServerConnection();;

    void run();

    bool is_finished();

    bool _send_packet(Packet *packet);

    ParseResult _parse_data(Packet *packet);

    void _print_client_addr(sockaddr_in addr);
    
    int _check_for_socket_errors();

    void ask_to_finish();

    SockAddrWrapper *get_client();
};
