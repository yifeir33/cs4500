#pragma once

#include <assert.h>

#include "../object.h"
#include "../string.h"
#include "../array.h"
#include "column.h"

/*************************************************************************
 * Schema::
 * A schema is a description of the contents of a data frame, the schema
 * knows the number of columns and number of rows, the type of each column,
 * optionally columns and rows can be named by strings.
 * The valid types are represented by the chars 'S', 'B', 'I' and 'F'.
 */
class Schema : public Object {
public:
    StringArray _columnNames;
    StringArray _rowNames;
    IntArray _columnTypes;
    size_t _width;
    size_t _length;
 
    /** Copying constructor */
    Schema(Schema& from) : _columnNames(from._columnNames.length()), _rowNames(from._rowNames.length()), _columnTypes(from._columnTypes.length()), _width(from._width), _length(from._length) {};

    /** Create an empty schema **/
    Schema() : _columnNames(10), _rowNames(10), _columnTypes(10), _width(0), _length(0) {};

    /** Create a schema from a string of types. A string that contains
    * characters other than those identifying the four type results in
    * undefined behavior. The argument is external, a nullptr argument is
    * undefined. **/
    Schema(const char* types) : _columnNames(10), _rowNames(10), _columnTypes(10), _width(0), _length(0) {
        assert(types);
        const char *c = types;
        while(*c !='\0') {
            if(*c != ' '){
                _columnTypes.push(*c);
            }
            ++c;
            ++_width;
        }
    };

    /** Add a column of the given type and name (can be nullptr), name
    * is external. Names are expectd to be unique, duplicates result
    * in undefined behavior. */
    void add_column(char typ, String* name) {
        _columnTypes.push(typ);
        _columnNames.push(name);
        ++_width;
    }

    /** Add a row with a name (possibly nullptr), name is external.  Names are
    *  expectd to be unique, duplicates result in undefined behavior. */
    void add_row(String* name) {
        _rowNames.push(name);
        ++_length;
    }

    /** Return name of row at idx; nullptr indicates no name. An idx >= width
    * is undefined. */
    String* row_name(size_t idx) {
        return _rowNames.get(idx);
    }

    /** Return name of column at idx; nullptr indicates no name given.
    *  An idx >= width is undefined.*/
    String* col_name(size_t idx) {
        return _columnNames.get(idx);
    }

    /** Return type of column at idx. An idx >= width is undefined. */
    char col_type(size_t idx) {
        return _columnTypes.get(idx);
    }

    /** Given a column name return its index, or -1. */
    int col_idx(const char* name) {
        String name_str(name);
        return _columnNames.index_of(&name_str);
    }

    /** Given a row name return its index, or -1. */
    int row_idx(const char* name){
        String name_str(name);
        return _rowNames.index_of(&name_str);
    }

    /** The number of columns */
    size_t width() {
        return _width;
    }

    /** The number of rows */
    size_t length() {
        return _length;
    }

    virtual bool equals(Object* other) {
        Schema *other_schema = dynamic_cast<Schema*>(other);
        if(other_schema && this->_width == other_schema->_width && this->_length == other_schema->_length) {
            return _rowNames.equals(&other_schema->_rowNames) 
                   && _columnNames.equals(&other_schema->_columnNames) 
                   && _columnTypes.equals(&other_schema->_columnTypes);
        }
        return false;
    }

    virtual size_t hash_me() {
        return _rowNames.hash() + _columnNames.hash() + _columnTypes.hash();
    }
};
