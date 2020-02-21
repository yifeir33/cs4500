#include <iostream>

#include "client.h"

#define SERVER_PORT     8080

int main(int argc, char** argv) {
    // parse args
    char *ip = nullptr;
    int i = 0;
    while(i < argc){
        if(strcmp(argv[i], "-ip") == 0){
            ip = argv[++i];
        }
        ++i;
    }
    if(!ip) {
        std::cout <<"IP not provided!" <<std::endl;
        return 1;
    }
    std::cout <<"Server IP: " <<ip <<std::endl;

    Client client(ip, SERVER_PORT);
    client.connect_to_server();
    return 0;
}
