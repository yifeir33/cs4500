#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "object.h"
#include "string.h"

class SockAddrWrapper : public Object {
public:
    struct sockaddr_in addr;
    socklen_t addrlen;

    SockAddrWrapper() : addrlen(sizeof(addr)) {}

    SockAddrWrapper(SockAddrWrapper *other){
        this->addr = other->addr;
        this->addrlen = other->addrlen;
    }

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

    char* c_str(){
        StrBuff sb;
        char addr_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(this->addr.sin_addr), addr_str, INET_ADDRSTRLEN);
        sb.c(addr_str);
        sb.c(":");
        sb.c(ntohs(this->addr.sin_port));

        String *s = sb.get();
        char *c_s = s->steal();
        delete s;
        return c_s;
    }
};
