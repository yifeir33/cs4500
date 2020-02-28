#include <iostream>
#include <signal.h>

#include "network.h"

int main(int argc, char** argv) {
    // SIGPIPE is the stupidest thing - nothing like failing silently
    struct sigaction sa{{SIG_IGN}};
    sigaction(SIGPIPE, &sa, NULL);

    // parse args
    char *ip = nullptr;
    in_port_t port = SERVER_PORT;
    int i = 0;
    while(i < argc){
        if(strcmp(argv[i], "-ip") == 0){
            ip = argv[++i];
        } else if(strcmp(argv[i], "-port") == 0){
            port = std::stoi(argv[++i]);
            if(port == 0) {
                std::cout <<"Invalid Port Provided!" <<std::endl;
                return 1;
            }
        }
        ++i;
    }
    if(!ip) {
        std::cout <<"IP not provided!" <<std::endl;
        return 1;
    }
    std::cout <<"Server IP: " <<ip <<std::endl;

    Server serv(ip, SERVER_PORT);
    serv.listen_on_socket(10);
    return 0;
}
