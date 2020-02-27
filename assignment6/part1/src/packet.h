#pragma once

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/ip.h>

#include "object.h"

#define DATA_MAX        256
#define PACKET_MAX_SIZE (1 + 2 + DATA_MAX) // Type + Length + DATA_MAX

// types
#define REGISTER        0x01
#define DEREGISTER      0x02
#define CLIENT_UPDATE   0x03
#define CHAR_MSG        0x04
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
    uint16_t length;
    uint8_t value[DATA_MAX];

    Packet() : type(0), length(0) {
        memset(value, 0, DATA_MAX);
    }

    size_t get_size(){
        return sizeof(type) + sizeof(length) + length;
    }

    int pack(uint8_t *buffer, size_t buflen){
        if(this->get_size() < buflen) return -1;
        size_t pos = 0;

        // type
        memcpy(buffer + pos, &type, sizeof(type));
        pos += sizeof(type);

        // length
        memcpy(buffer + pos, &length, sizeof(length));
        pos += sizeof(length);

        // value
        memcpy(buffer + pos, &value, length);
        pos += length;

        return pos;
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

        // unpack length
        if(pos + sizeof(length) >= buflen){
            p("Too short for length!\n").p("Pos: ").p(pos).p(" BufLen: ").p(buflen).p('\n');
            std::cout.flush();
            goto TOO_SHORT;
        }
        memcpy(&this->length, buffer + pos, sizeof(length));
        pos += sizeof(length);
        
        // unpack value
        if(pos + length >= buflen){
            p("Too short for value!\n").p("Pos: ").p(pos).p(" BufLen: ").p(buflen).p('\n');
            std::cout.flush();
            goto TOO_SHORT;
        }
        memcpy(&this->value, buffer + pos, length);
        pos += length;

        return pos;

        TOO_SHORT:
            this->type = 0;
            this->length = 0;
            memset(&this->value, 0, DATA_MAX);
            return -1;
    }

};
