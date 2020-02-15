#pragma once

#include <stdlib.h>

#include "modified_dataframe.h"

#define SEED 102102

bool initalized = false;

void init() {
    if(initalized) return;
    srand(SEED);
    initalized = true;
}

int generate_int(){
    return rand() % 10000 * (rand() % 2 == 1 ? 1 : -1);
}

bool generate_bool(){
    return rand() % 2;
}

float generate_float(){
    return generate_int() * 1.0 / ((rand() % 5) * 1.0);
}

String *generate_string(){
    char buffer[11];
    size_t length = rand() % 10;
    StrBuff sb;
    size_t i = 0;
    while(i < length) {
        bool upper = rand() % 2;
        buffer[i] = (rand() % 26) + (upper ? 65 : 97);
        ++i;
    }
    buffer[i] = '\0'; 
    return sb.c(buffer).get();
}

bool generate_large_dataframe(DataFrame& df, size_t nrows, StringArray *arr){
    if(!initalized) init();
    Schema& scm = df.get_schema();

    for(size_t i = 0; i < nrows; ++i){
        Row r(scm);
        r.set_index(i);
        for(size_t j = 0; j < r.width(); ++j){
            switch(scm.col_type(j)) {
                case 'I':
                    {
                        r.set(j, generate_int());
                        break;
                    } 
                case 'F':
                    {
                        r.set(j, generate_float());
                        break;
                    }
                case 'B':
                    {
                        r.set(j, generate_bool());
                        break;
                    }
                case 'S':
                    {
                        String *s = generate_string();
                        r.set(j, s);
                        if(arr)
                            arr->push(s);
                        break;
                    }
                default:
                    return false;
            }
        }
        df.add_row(r);
    }
    return true;
}
