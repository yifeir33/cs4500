#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cassert>

#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "sorer.h"
#include "util.h"


Sorer::Sorer(char *filename, size_t start, size_t end) : _fd(-1), _start(start), _end(end), _fsize(0), _mfile(nullptr), _col_types(nullptr), _col_cnt(0){
    _fd = open(filename, O_RDONLY);
    if(_fd < 0 ){
        perror("Error opening file");
        throw "Failed to open file";
    }
    struct stat sb;
    int rc = fstat(_fd, &sb);
    if(rc != 0){
        perror("Error getting file size");
        throw "Failed to get file size";
    }
    _fsize = sb.st_size;
    if(_end > _fsize){
        _end = _fsize;
    }
    _mfile = (const char *) mmap(NULL, _fsize, PROT_READ, MAP_SHARED, _fd, 0);
    this->_init_start_end();
    this->_init_columns();
    this->_init_col_types();
    this->_init_row_indices();
}

Sorer::~Sorer(){
    if(_col_types) delete[] _col_types;
    if(_mfile) assert(munmap((void *) _mfile, _fsize) == 0);
    if(_fd > 0) close(_fd);
}

std::string Sorer::get(size_t col, size_t row){
    if(col >= _col_cnt || row >= _row_index.size()){
        return "";
    }
    // go to row
    size_t r_start = _row_index[row];
    bool in_col = false;
    bool in_str = false;
    uint16_t col_index = 0;

    std::string output = "";
    while(r_start < _end && col_index <= col){
        if(_mfile[r_start] == '\n'){
            return "";
        } else if(_mfile[r_start] == '<'){
            in_col = true;
        } else if(_mfile[r_start] == '>'){
            in_col = false;
            col_index++;
        } else if(in_col && col_index == col && (in_str || !isspace(_mfile[r_start]))){
            if(_col_types[col] == Sorer::col_type::STRING && _mfile[r_start] == '"') in_str = !in_str;
            output += _mfile[r_start];
        }


        r_start++;
    }
    return output;
}

Sorer::col_type Sorer::column_type(size_t col){
    return _col_types[col];
}

bool Sorer::exists(size_t col, size_t row){
    std::string val = this->get(col, row);
    return !val.empty();
}

void Sorer::_init_start_end(){
    /* std::cout <<"_init_start_end" <<std::endl; */
    if(_end < _fsize){
        size_t index = _end;
        while(index > _start){
            if(_mfile[index] == '\n' && index > _start){
                _end = index - 1;
                break;
            }
            index--;
        }
    }

    if(_start != 0){
        size_t index = _start;
        while(index > _start){
            if(_mfile[index] == '\n' && index > _start){
                _end = index + 1;
                break;
            }
            index++;
        }
    }
}


void Sorer::_init_columns() {
    /* std::cout <<"_init_columns" <<std::endl; */
    // get column count from first 500~ entries
    size_t row_count = 0;
    int col_count = 0;
    int max_cols = -1;
    size_t index = _start;
    while(index < _end && row_count < 500){
        if(_mfile[index] == '<'){
            col_count++;
        } else if(_mfile[index] == '\n'){
            row_count++;
            if(col_count > max_cols){
                max_cols = col_count;
                col_count = 0;
            }
        }

        index++;
    }

    if(col_count > max_cols){
        max_cols = col_count;
        col_count = 0;
    }
    // have number of columns
    _col_cnt = max_cols;
    std::cout <<"Col Count: " << _col_cnt << std::endl;
    _col_types = new Sorer::col_type[_col_cnt];
}

void Sorer::_init_col_types() {
    /* std::cout <<"_init_col_types" <<std::endl; */
    size_t index = _start;
    size_t rows_checked = 0;
    int col_index = 0;
    bool done = false;
    size_t start = 0;
    bool in_col = false;

    while(index < _end && !done) {
        if(_mfile[index] == '<'){
            start = index;
            in_col = true;
        } else if(in_col && _mfile[index] == '>'){
            _col_types[col_index++] = this->_parse_col(start, index);
            in_col = false;
        } else if(_mfile[index] == '\n') {
            rows_checked++;
            col_index = 0;
            done = true;
            for(size_t i = 0; i < _col_cnt; ++i){
                if(_col_types[i] == Sorer::col_type::BOOL && rows_checked < 10){
                    done = false;
                } else if(_col_types[i] == Sorer::col_type::INVALID){
                    done = false;
                }
            }
        }
        index++;
    }
}

Sorer::col_type Sorer::_parse_col(size_t start, size_t end){
    /* std::cout <<"_parse_col" <<std::endl; */
    Sorer::col_type type = Sorer::col_type::STRING;
    bool type_set = false;
    // strip leading and trailing whitespace
    start++; // move off <
    end--; // move off >
    while(std::isspace(_mfile[start])){ start++; }
    while(std::isspace(_mfile[end])) { end--; }

    bool decimal = false;

    for(size_t i = start; i <= end; ++i){
        if(type_set && type != Sorer::col_type::STRING && std::isspace(_mfile[i])){
            return Sorer::col_type::INVALID;
        }else if(i == start && _mfile[i] == '-'){
            type = Sorer::col_type::FLOAT;
            type_set = true;
        } else if(_mfile[i] == '"') {
            type = Sorer::col_type::STRING;
        } else if(isdigit(_mfile[i])){
            if((_mfile[i] == '0' || _mfile[i] == '1') && !type_set){
                type = Sorer::col_type::BOOL;
                type_set = true;
            } else if(type != Sorer::col_type::FLOAT){
                type = Sorer::col_type::INTEGER;
                type_set = true;
            }
        } else if(!decimal && (type == Sorer::col_type::FLOAT || type == Sorer::col_type::INTEGER || type == Sorer::col_type::BOOL) && _mfile[i] == '.'){
            decimal = true;
            type = Sorer::col_type::FLOAT;
            type_set = true;
        } else if(decimal && type == Sorer::col_type::FLOAT && _mfile[i] == '.'){
            type = Sorer::col_type::STRING;
        }
    }

    return type;
}


void Sorer::_init_row_indices(){
    /* std::cout <<"_init_row_indices" <<std::endl; */
    _row_index.push_back(_start);

    for(size_t i = _start; i < _end; ++i){
        if(_mfile[i] == '\n' && i + 1 < _end){
            _row_index.push_back(i + 1);
        }
    }
}

