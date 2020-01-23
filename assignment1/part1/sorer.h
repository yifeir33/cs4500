#ifndef SORER_H
#define SORER_H

#include <fstream>
#include <vector>
#include <string>

class Sorer {
public:
    enum col_type {
        INVALID,
        BOOL,
        INTEGER,
        FLOAT,
        STRING
    };

    Sorer(char *filename, size_t start, size_t end);
    ~Sorer();
    Sorer::col_type column_type(size_t col);
    std::string get(size_t col, size_t row);
    bool exists(size_t col, size_t row);


private:

    void _init_columns();
    void _init_start_end();
    void _init_col_types();
    void _init_row_indices();
    Sorer::col_type _parse_col(size_t start, size_t end);


    int _fd;
    size_t _start;
    size_t _end;
    size_t _fsize;
    const char* _mfile;
    std::vector<size_t> _row_index;
    Sorer::col_type *_col_types;
    size_t _col_cnt;
};

#endif
