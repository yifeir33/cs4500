#pragma once

#include <stdint.h>

#define DATA_MAX        512 

// type
#define CLIENT_UPDATE   0x01
#define CHAR_MSG        0x02
#define ERROR_MSG       0xFE
#define SHUTDOWN        0xFF


struct tlv {
    uint8_t type;
    uint16_t length;
    uint8_t value[DATA_MAX];
};
