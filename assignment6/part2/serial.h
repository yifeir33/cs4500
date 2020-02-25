#pragma once

#include "object.h"
#include "string.h"


// TAGs
#define FIELD_START       "{"
#define FIELD_END         "}"
#define VALUE_START       "["
#define VALUE_END         "]"
#define STRING_TAG        "str"
#define INT_TAG           "int"
#define FLOAT_TAG         "flt"
#define BOOL_TAG          "bool"
// these can be appended to any other tag
/* #define PTR_TAG           "ptr" */
#define ARR_TAG           "arr"

// Lengths - must be 1 byte
#define FIELD_START_LEN   0x01
#define FIELD_END_LEN     0x01
#define VALUE_START_LEN   0x01
#define VALUE_END_LEN     0x01
#define STRING_TAG_LEN    0x03
#define INT_TAG_LEN       0x03
#define FLOAT_TAG_LEN     0x03
#define BOOL_TAG_LEN      0x04
/* #define PTR_TAG_LEN       0x03 */
#define ARR_TAG_LEN       0x03

class SerializedData : public Object {
    int pack(uint8_t *buffer, int buffer_len);

    int unpack(uint8_t *buffer, int buffer_len);
};

class Serial : public Object {
    virtual int serial_size() = 0;
    // return -1 on error, else length of serial data
    virtual int marshal(char *buffer, int buffer_len) = 0;
    static Serial *unmarshal(char *buffer, int buffer_len){
        int pos = 0;
        while(pos < buffer_len){
            if(buffer[pos] == *FIELD_START){
                pos += 1;
                // find value start to parse type
                int s_pos = pos;
                while(buffer[s_pos] != *VALUE_START && s_pos < buffer_len) ++s_pos;
                if(s_pos >= buffer_len) return nullptr;
                int tag_len = s_pos - pos;

                if(STRING_TAG_LEN < tag_len && memcmp(buffer + pos, STRING_TAG, STRING_TAG_LEN) == 0) {
                    if(ARR_TAG_LEN < tag_len - STRING_TAG_LEN && memcmp(buffer + pos + STRING_TAG_LEN, ARR_TAG, ARR_TAG_LEN) == 0){
                        // TODO
                    } else {
                        StrBuff sb;
                        s_pos += 1; // TODO: does this go above?
                        while(buffer[s_pos] != *VALUE_END && s_pos < buffer_len){
                            sb.c(buffer[s_pos++]);
                        }
                        //return sb.get();
                        return nullptr;
                    }
                }
            }
            pos += 1;
        } // while
        return nullptr;
    }

    static String *unmarshal_str(char *buffer, int buffer_len){
        // ????
        return nullptr;
    }
};
