#pragma once

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/ip.h>

#include "object.h"

#define DATA_MAX        256

// flags
#define FORWARD 0x02

// type
#define CLIENT_UPDATE   0x01
#define CHAR_MSG        0x02
#define ERROR_MSG       0xFE
#define SHUTDOWN        0xFF

enum ParseResult {
    ParseError = -1,
    Success = 0,
    Response = 1,
};

class Packet : public Object {
public:
    uint8_t type;
    uint8_t flags; // flag
    uint16_t addrlen; // length of addr
    sockaddr_in addr; // sender/receiver addr on forward, otherwise isn't included
    uint16_t vallen;
    uint8_t value[DATA_MAX];

    Packet() : type(0), flags(0), addrlen(0), vallen(0) {}

    static size_t MaxSize() {
        return sizeof(type) + sizeof(flags) + sizeof(addrlen) + sizeof(addr) + sizeof(vallen) + DATA_MAX + 1;
    }

    size_t get_size(){
        return sizeof(type) + sizeof(flags) + sizeof(addrlen) + addrlen + sizeof(vallen) + vallen + 1;
    }

    uint8_t *pack(){
        size_t pos = 0;
        uint8_t *buffer = new uint8_t[this->get_size()];
        // pack packet
        // type
        memcpy(buffer + pos, &type, sizeof(type));
        pos += sizeof(type);
        // flags
        memcpy(buffer + pos, &flags, sizeof(flags));
        pos += sizeof(flags);
        // addrlen
        memcpy(buffer + pos, &addrlen, sizeof(addrlen));
        pos += sizeof(addrlen);
        // addr
        memcpy(buffer + pos, &addr, addrlen);
        pos += addrlen;
        // length
        memcpy(buffer + pos, &vallen, sizeof(vallen));
        pos += sizeof(vallen);
        // value
        memcpy(buffer + pos, &value, vallen);
        pos += vallen;

        return buffer;
    }

    size_t unpack(uint8_t *buffer, size_t buflen){
        p("unpack, buflen: ").p(buflen).p('\n');
        std::cout.flush();
        size_t pos = 0;
        // unpack type
        if(pos + sizeof(type) >= buflen){
            p("Too short for type!\n").p("Pos: ").p(pos).p(" BufLen: ").p(buflen).p('\n');
            p(sizeof(type)).p('\n');
            std::cout.flush();
            goto TOO_SHORT;
        }
        memcpy(&this->type, buffer + pos, sizeof(type));
        pos += sizeof(type);
        // unpack flags
        if(pos + sizeof(flags) >= buflen){
            p("Too short for flags!\n").p("Pos: ").p(pos).p(" BufLen: ").p(buflen).p('\n');
            std::cout.flush();
            goto TOO_SHORT;
        }
        memcpy(&this->flags, buffer + pos, sizeof(flags));
        pos += sizeof(flags);
        // unpack addrlen
        if(pos + sizeof(addrlen) >= buflen){
            p("Too short for addrlen!\n").p("Pos: ").p(pos).p(" BufLen: ").p(buflen).p('\n');
            std::cout.flush();
            goto TOO_SHORT;
        }
        memcpy(&this->addrlen, buffer + pos, sizeof(addrlen));
        pos += sizeof(addrlen);
        // unpack addr
        if(pos + addrlen >= buflen){
            p("Too short for addr!\n").p("Pos: ").p(pos).p(" BufLen: ").p(buflen).p('\n');
            std::cout.flush();
            goto TOO_SHORT;
        }
        memcpy(&this->addr, buffer + pos, addrlen);
        pos += addrlen;
        // unpack vallen
        if(pos + sizeof(vallen) >= buflen){
            p("Too short for vallen!\n").p("Pos: ").p(pos).p(" BufLen: ").p(buflen).p('\n');
            std::cout.flush();
            goto TOO_SHORT;
        }
        memcpy(&this->vallen, buffer + pos, sizeof(vallen));
        pos += sizeof(vallen);
        // unpack value
        if(pos + vallen >= buflen){
            p("Too short for value!\n").p("Pos: ").p(pos).p(" BufLen: ").p(buflen).p('\n');
            std::cout.flush();
            goto TOO_SHORT;
        }
        memcpy(&this->value, buffer + pos, vallen);
        pos += vallen;

        return pos + 1;

        TOO_SHORT:
            this->type = 0;
            this->flags = 0;
            this->addrlen = 0;
            memset(&this->addr, 0, sizeof(this->addr));
            this->vallen = 0;
            this->vallen = 0;
            memset(&this->value, 0, DATA_MAX);
            return -1;
    }

};
