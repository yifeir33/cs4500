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


/**
 * Constructs the Sorer object.
 *
 * @param filename - The name/path of the file to open.
 * @param start - The offset in the file to start at.
 * @param end - The end index of the file to read to.
 *
 * This will throw exceptions if it cannot open the file,
 * get the file size, or mmap the file.
 */
Sorer::Sorer(char *filename, size_t start, size_t end) : _fd(-1), _start(start), _end(end),
    _fsize(0), _mfile(nullptr), _ColTypes(nullptr), _col_cnt(0){
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
    off_t offset = 0;
    if(_start > 0){
        // offset has to be a multiple of pagesize for mmap
        // this checks if start is large enough to open the file
        // with an offset.
        long page_size = sysconf(_SC_PAGE_SIZE);
        long page_offset = start / page_size;
        if(page_offset > 0){
            offset = page_offset * page_size;
            if(offset >= _start) {
                offset = 0;
            }
            _start -= offset;
            _end -= offset;
        }
    }
    _mfile = (const char *) mmap(NULL, _end, PROT_READ, MAP_SHARED | MAP_NORESERVE, _fd, offset);
    if(_mfile == MAP_FAILED){
        perror("Error mapping file: ");
        throw "Failed to map the file to memory";
    }
    this->_init_start_end();
    this->_init_columns();
    this->_init_col_types();
    this->_init_row_indices();
}

/**
 * Destructor.
 *
 * This deletes the heap allocated memory used to store the column types,
 * and unmaps and closes the file.
 */
Sorer::~Sorer(){
    if(_ColTypes) delete[] _ColTypes;
    if(_mfile) assert(munmap((void *) _mfile, _end) == 0);
    if(_fd > 0) close(_fd);
}

/**
 * Returns the type of the given column.
 *
 * @param col - The column whose type you wanna get. If it
 * is an invalid column, Sorer::ColType::INVALID is returned.
 *
 * @return The type of the column, or INVALID if the column index is invalid.
 */
Sorer::ColType Sorer::column_type(size_t col){
    if(col >= _col_cnt) return Sorer::ColType::INVALID;
    return _ColTypes[col];
}

/**
 * Returns the value at <col> <row> in the file as a string.
 *
 * @param col - The column of the value to get.
 * @param row - The row of the value to get.
 *
 * @return the string representation of the value at <col> <row>. If
 * the value doesn't exist or one of the indices is invalid, returns 
 * an empty string.
 */
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
            if(in_col) return "";
            in_col = true;
        } else if(_mfile[r_start] == '>'){
            if(!in_col) return "";
            in_col = false;
            col_index++;
        } else if(in_col && col_index == col && (in_str || !isspace(_mfile[r_start]))){
            if(_ColTypes[col] == Sorer::ColType::STRING && _mfile[r_start] == '"') in_str = !in_str;
            output += _mfile[r_start];
        }


        r_start++;
    }
    return output;
}

/**
 * Returns if the value at <col> <row> exists.
 *
 * @param col - The column of the value.
 * @param row - The row of the value.
 *
 * @return true if the row is valid and the value exists, false otherwise.
 */
bool Sorer::exists(size_t col, size_t row){
    std::string val = this->get(col, row);
    return !val.empty();
}

/**
 * Private function to initialize the start and end values. To avoid incomplete data,
 * if non-zero offset is given all data before the first newline is dropped, and all data
 * after the last newline before end is dropped. This readjusts the _start and _end values to 
 * reflect that.
 */
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

    size_t index = _start;
    while(index > _start){
        if(_mfile[index] == '\n' && index > _start){
            _end = index + 1;
            break;
        }
        index++;
    }
}

/**
 * Private function to initialize the column count. It parses
 * the file and figures out how many columns are in the schema and
 * stores it in the appropriate member variables.
 */
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
    /* std::cout <<"Col Count: " << _col_cnt << std::endl; */
    _ColTypes = new Sorer::ColType[_col_cnt];
}

/**
 * Private function to initialize column types. It must run after _init_columns.
 * It parses the columns to figure out what type each column is.
 */
void Sorer::_init_col_types() {
    /* std::cout <<"_init_ColTypes" <<std::endl; */
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
            _ColTypes[col_index++] = this->_parse_type(start, index);
            in_col = false;
        } else if(_mfile[index] == '\n') {
            rows_checked++;
            col_index = 0;
            done = true;
            for(size_t i = 0; i < _col_cnt; ++i){
                if(_ColTypes[i] == Sorer::ColType::BOOL && rows_checked < 10){
                    done = false;
                } else if(_ColTypes[i] == Sorer::ColType::INVALID){
                    done = false;
                }
            }
        }
        index++;
    }
}

/**
 * A helper function for _init_ColTypes that parses the value between start and end
 * and returns what type it thinks it is.
 *
 * @param start - The start index of the value.
 * @param end - The end index of the value.
 *
 * @return - The type that it thinks that value is.
 */
Sorer::ColType Sorer::_parse_type(size_t start, size_t end){
    /* std::cout <<"_parse_type" <<std::endl; */
    Sorer::ColType type = Sorer::ColType::STRING;
    bool type_set = false;
    // strip leading and trailing whitespace
    start++; // move off <
    end--; // move off >
    while(std::isspace(_mfile[start])){ start++; }
    while(std::isspace(_mfile[end])) { end--; }

    bool decimal = false;

    for(size_t i = start; i <= end; ++i){
        if(type_set && type != Sorer::ColType::STRING && std::isspace(_mfile[i])){
            return Sorer::ColType::INVALID;
        }else if(i == start && _mfile[i] == '-'){
            type = Sorer::ColType::FLOAT;
            type_set = true;
        } else if(_mfile[i] == '"') {
            type = Sorer::ColType::STRING;
        } else if(isdigit(_mfile[i])){
            if((_mfile[i] == '0' || _mfile[i] == '1') && !type_set){
                type = Sorer::ColType::BOOL;
                type_set = true;
            } else if(type != Sorer::ColType::FLOAT){
                type = Sorer::ColType::INTEGER;
                type_set = true;
            }
        } else if(!decimal && (type == Sorer::ColType::FLOAT || type == Sorer::ColType::INTEGER || type == Sorer::ColType::BOOL) && _mfile[i] == '.'){
            decimal = true;
            type = Sorer::ColType::FLOAT;
            type_set = true;
        } else if(decimal && type == Sorer::ColType::FLOAT && _mfile[i] == '.'){
            type = Sorer::ColType::STRING;
        }
    }

    return type;
}


/**
 * Private function to find and store the indices in the file that each row starts on.
 */
void Sorer::_init_row_indices(){
    /* std::cout <<"_init_row_indices" <<std::endl; */
    _row_index.push_back(_start);

    for(size_t i = _start; i < _end; ++i){
        if(_mfile[i] == '\n' && i + 1 < _end){
            _row_index.push_back(i + 1);
        }
    }

    _row_index.shrink_to_fit();
}

