//
// Created by 王镱霏 on 1/22/20.
//

#ifndef HW3_CWCAPI_H
#define HW3_CWCAPI_H


#include <iostream>

class CwCAPI {
public:
    char* filename;
    int from;
    int len;
//    HashMap db ;
    CwCAPI(){
    }
    void read_file(char* filename1){
        this->filename = filename1;
        FILE *f;
        int c;
        size_t n = 0;
        f = fopen(this->filename, "r");
        char *data;
        if (f == NULL) {
            std::cout << "Can't open file" << std::endl;
            exit(0); //could not open file
        }
            fseek(f, 0, SEEK_END);
            long f_size = ftell(f);
            fseek(f, 0, SEEK_SET);
            data = (char*) malloc(f_size);
        while ((c = fgetc(f)) != EOF)
        {
            data[n++] = c;
        }
        data[n] = '\0';

        fclose(f);

        }

    void add_from(int from1){
        this->from = from1;
    }
    void add_len(int len1){
        this->len = len1;
    }

    void print_col_ind(int first_arg1, int second_offset1){

    }


    bool check_missing(int miss_col1, int miss_row1){

    }

    char* print_col_type(int col_num){

    }


};


#endif //HW3_CWCAPI_H
