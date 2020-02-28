#include <iostream>
#include <signal.h>

#include "network.h"

int main(int argc, char** argv) {
    // SIGPIPE is the stupidest thing - nothing like failing silently
    struct sigaction sa{{SIG_IGN}};
    sigaction(SIGPIPE, &sa, NULL);

    // parse args
    char *sip = nullptr;
    char *cip = CLIENT_DEFAULT_IP_STR;
    in_port_t port = SERVER_PORT;
    int i = 0;
    while(i < argc){
        if(strcmp(argv[i], "-ip") == 0){
            sip = argv[++i];
        } else if(strcmp(argv[i], "-port") == 0){
            port = std::stoi(argv[++i]);
            if(port == 0) {
                std::cout <<"Invalid Port Provided!" <<std::endl;
                return 1;
            }
        } else if(strcmp(argv[i], "-cip") == 0){
            cip = argv[++i];
        }
        ++i;
    }
    if(!sip) {
        std::cout <<"IP not provided!" <<std::endl;
        return 1;
    }
    std::cout <<"Server IP: " <<sip <<std::endl;
    std::cout <<"Client IP: " <<cip <<std::endl;

    Client client(cip, sip, port);
    client.listen_on_socket(10);
    return 0;
}
