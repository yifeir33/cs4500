#include <iostream>
#include <cstring>

#include "sorer.h"

enum operation {
    INVALID,
    COL_TYPE,
    IS_MISSING,
    GET_VALUE
};

std::string col_type_to_str(Sorer::ColType type){
    switch(type){
        case Sorer::ColType::INVALID:
            return "INVALID";
        case Sorer::ColType::BOOL:
            return "BOOL";
        case Sorer::ColType::INTEGER:
            return "INTEGER";
        case Sorer::ColType::FLOAT:
            return "FLOAT";
        case Sorer::ColType::STRING:
            return "STRING";
        default:
            return "UNEXPECTED TYPE";
    }
}

/* void print_val(std::string sval, Sorer::ColType type){ */
/*     if(type == Sorer::ColType::BOOL){ */
/*         bool bval = atoi(sval.c_str()); */
/*         std::cout <<bval <<std::endl; */
/*     } else if(type == Sorer::ColType::INTEGER){ */
/*         int ival = atoi(sval.c_str()); */
/*         std::cout <<ival <<std::endl; */

/*     } else if(type == Sorer::ColType::FLOAT){ */
/*         float fval = atof(sval.c_str()); */
/*         std::cout <<fval <<std::endl; */

/*     } else if(type == Sorer::ColType::STRING){ */
/*         std::cout <<sval <<std::endl; */
/*     } */
/* } */

int main(int argc, char** argv){
    char* filename = nullptr;
    int from = -1;
    int len = -1;
    int col = -1;
    int row = -1;
    operation o = operation::INVALID;
    /* std::cout <<"Argc: " <<argc <<std::endl; */

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i],  "-f") == 0) {
            if(i + 1 < argc) {
                filename = argv[i + 1];
            } else {
                std::cout << "No filename given" << std::endl;
                exit(1);
            }
        } else if (strcmp(argv[i], "-from") == 0){
            if(i + 1 < argc) {
                from = atoi(argv[i + 1]);
            }else{
                std::cout << "there is no argument after -from" << std::endl;
                exit(1);
            }
        } else if (strcmp(argv[i], "-len") == 0){
            if(i + 1 < argc) {
                len = atoi(argv[i + 1]);
            }else{
                std::cout << "there is no argument after -len" << std::endl;
                exit(1);
            }
        } else if (strcmp(argv[i], "-print_col_type") == 0){
            o = operation::COL_TYPE;
            if(i + 1< argc) {
                col = atoi(argv[i + 1]);
            }else{
                std::cout << "there is no argument after -print_ColType" << std::endl;
                exit(1);
            }
        } else if (strcmp(argv[i], "-print_col_idx") == 0){
            o = operation::GET_VALUE;
            if(i + 1 < argc) {
                col = atoi(argv[i + 1]);
                if(i + 2 <argc){
                    row = atoi(argv[i + 2]);
                } else {
                    std::cout << "there is no 2nd argument after -print_col_idx" << std::endl;
                    exit(1);
                }
            }else{
                std::cout << "there is no 1st argument after -print_col_idx" << std::endl;
                exit(1);
            }
        } else if (strcmp(argv[i], "-is_missing_idx") == 0){
            o = operation::IS_MISSING;
            if(i + 1 < argc) {
                col = atoi(argv[i + 1]);
                if(i + 2 <argc){
                    row = atoi(argv[i + 2]);
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

    /* std::cout <<"From: " <<from <<",  To: " <<from+len <<std::endl; */  
    Sorer sorer(filename, from, from + len);
    /* std::cout <<"Sorer Constructed!" <<std::endl; */

    switch(o){
        case operation::COL_TYPE:{
            /* std::cout<<"COl Type" <<std::endl; */
            std::cout <<col_type_to_str(sorer.column_type(col)) <<std::endl;
            break;
        }
        case operation::GET_VALUE:{
            /* Sorer::ColType type = sorer.column_type(col); */
            std::cout <<sorer.get(col, row) <<std::endl;
            /* print_val(val, type); */
            break;
        }
        case operation::IS_MISSING:{
            bool exists = false;
            if((exists = sorer.exists(col, row))){
                std::cout <<sorer.get(col, row) <<std::endl;
            } else {
                std::cout <<exists <<std::endl;
            }
            break;
        }
        default:
            return 1;
    }

    return 0;
}
