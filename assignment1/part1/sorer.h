#ifndef SORER_H
#define SORER_H

#include <fstream>
#include <vector>
#include <string>

/**
 * Sorer opens and parses a Schema-on-read text file,
 * and after catagorizing the file then allows a usert to retrieve
 * both column types and the value in the schema at <column> <row>.
 *
 * It works by using mmap to put the file into virtual memory. As the file
 * is Read-Only and the MAP_SHARED and MAP_NORESERVE flags are passed, it does not need the
 * physical memory to hold the file, the operating system will load and unload parts of the file
 * as needed. Furthermore it lazily looks up values by storing the index in the file
 * that each row starts on, and when a value is requested it parses that row on request.
 * This helps keep memory usage low, and since lines are unlikely to exceed a page of memory the 
 * performance hit of parsing is minimal.
 */
class Sorer {
public:
    /*
     * ColType is an enum reprsenting the types
     * that can stored in the schema.
     */
    enum ColType {
        INVALID,
        BOOL,
        INTEGER,
        FLOAT,
        STRING
    };

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
    Sorer(char *filename, size_t start, size_t end);

    /**
     * Destructor.
     *
     * This deletes the heap allocated memory used to store the column types,
     * and unmaps and closes the file.
     */
    ~Sorer();

    /**
     * Returns the type of the given column.
     *
     * @param col - The column whose type you wanna get. If it
     * is an invalid column, Sorer::ColType::INVALID is returned.
     *
     * @return The type of the column, or INVALID if the column index is invalid.
     */
    Sorer::ColType column_type(size_t col);

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
    std::string get(size_t col, size_t row);

    /**
     * Returns if the value at <col> <row> exists.
     *
     * @param col - The column of the value.
     * @param row - The row of the value.
     *
     * @return true if the row is valid and the value exists, false otherwise.
     */
    bool exists(size_t col, size_t row);


private:
    /**
     * Private function to initialize the start and end values. To avoid incomplete data,
     * if non-zero offset is given all data before the first newline is dropped, and all data
     * after the last newline before end is dropped. This readjusts the _start and _end values to 
     * reflect that.
     */
    void _init_start_end();

    /**
     * Private function to initialize the column count. It parses
     * the file and figures out how many columns are in the schema and
     * stores it in the appropriate member variables.
     */
    void _init_columns();

    /**
     * Private function to initialize column types. It must run after _init_columns.
     * It parses the columns to figure out what type each column is.
     */
    void _init_col_types();

    /**
     * A helper function for _init_ColTypes that parses the value between start and end
     * and returns what type it thinks it is.
     *
     * @param start - The start index of the value.
     * @param end - The end index of the value.
     *
     * @return - The type that it thinks that value is.
     */
    Sorer::ColType _parse_type(size_t start, size_t end);

    /**
     * Private function to find and store the indices in the file that each row starts on.
     */
    void _init_row_indices();


    int _fd; // The file descriptor of the open file.
    size_t _start; // The start index of the file to parse.
    size_t _end; // The end index of the file to parse.
    size_t _fsize; // The size of the file.
    const char* _mfile; // A pointer to the beginning of the memory map of the file.
    std::vector<size_t> _row_index; // A vector storing the indices in the file of each row.
    Sorer::ColType *_ColTypes; // An array that stores the type of each column.
    size_t _col_cnt; // The number of columns in the schema.
};

#endif
