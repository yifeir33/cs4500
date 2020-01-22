#include <iostream>
#include "CwCAPI.h"
void readFile(){

}

int main(int argh, char** argv) {
    //missing value, BOOL, INTEGER, FLOAT, or STRING.
    char* filename;
    int from;
    int len;
    int col_type;
    int first_arg_col;
    int second_offset;
    int miss_col;
    int miss_row;
    CwCAPI* = api;

    for (int i = 0; i < argh; i++) {
        if (i == 1 || strcmp(argv[1],  "-f") != 0) {
            std::cout << "Invalid 1st argument" << std::endl;
            exit(1);
        } else if (i == 2) { // path to SoR file to be read
            filename = argv[2];
        } else {
            if (argv[i] == "-from"){
                i++;
                if(i< argh) {
                    from = atoi(argv[i]);
                }else{
                    std::cout << "there is no argument after -from" << std::endl;
                    exit(1);
                }

            } else if (argv[i] == "-len"){
                i++;
                if(i< argh) {
                    len = atoi(argv[i]);
                }else{
                    std::cout << "there is no argument after -len" << std::endl;
                    exit(1);
                }


            } else if (argv[i] == "-print_col_type"){
                i++;
                if(i< argh) {
                    col_type = atoi(argv[i]);
                }else{
                    std::cout << "there is no argument after -print_col_type" << std::endl;
                    exit(1);
                }

            } else if (argv[i] == "-print_col_idx") {
                i++;
                if(i< argh) {
                    first_arg_col = atoi(argv[i]);
                    i++;
                    if(i<argh){
                        second_offset = atoi(argv[i]);
                    } else{
                        std::cout << "there is no 2nd argument after -print_col_idx" << std::endl;
                        exit(1);
                    }
                }else{
                    std::cout << "there is no 1st argument after -print_col_idx" << std::endl;
                    exit(1);
                }

            } else if (argv[i] == "-is_missing_idx"){
                i++;
                if(i< argh) {
                    miss_col = atoi(argv[i]);
                    i++;
                    if(i<argh){
                        miss_row = atoi(argv[i]);
                    } else{
                        std::cout << "there is no 2nd argument after -is_missing_idx" << std::endl;
                        exit(1);
                    }
                }else{
                    std::cout << "there is no 1st argument after -is_missing_idx" << std::endl;
                    exit(1);
                }
            }
        }
    }



    return 0;
};
