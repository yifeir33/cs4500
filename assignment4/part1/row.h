#pragma once

#include "../object.h"
#include "../string.h"
#include "schema.h"
#include "fielder.h"



/*************************************************************************
 * Row::
 *
 * This class represents a single row of data constructed according to a
 * dataframe's schema. The purpose of this class is to make it easier to add
 * read/write complete rows. Internally a dataframe hold data in columns.
 * Rows have pointer equality.
 */
class Row : public Object {
public:
    union Schema_Value {
        int i;
        float f;
        bool b;
        String *s;
    };

    size_t _width;
    char *_types;
    Schema_Value *_values;
    size_t _index;


    /** Build a row following a schema. */
    Row(Schema& scm) : _width(scm.width()), _types(new char[_width]), _values(new Schema_Value[_width]), _index(0) {
        for(size_t i = 0; i < _width; ++i) {
            _types[i] = scm.col_type(i);
        }
    }

    ~Row() {
        delete[] _types;
        delete[] _values;
    }

    /** Setters: set the given column with the given value. Setting a column with
    * a value of the wrong type is undefined. */
    void set(size_t col, int val) {
        assert(col >= 0 && col < _width);
        assert(_types[col] == 'I');
        _values[col].i = val;
    }

    void set(size_t col, float val) {
        assert(col >= 0 && col < _width);
        assert(_types[col] == 'F');
        _values[col].f = val;
    }

    void set(size_t col, bool val) {
        assert(col >= 0 && col < _width);
        assert(_types[col] == 'B');
        _values[col].b = val;
    }

    /** The string is external. */
    void set(size_t col, String* val) {
        assert(col >= 0 && col < _width);
        assert(_types[col] == 'S');
        _values[col].s = val;
    }

    /** Set/get the index of this row (ie. its position in the dataframe. This is
    *  only used for informational purposes, unused otherwise */
    void set_index(size_t idx) {
        _index = idx;

    }

    size_t get_index() {
        return _index;
    }

    /** Getters: get the value at the given column. If the column is not
    * of the requested type, the result is undefined. */
    int get_int(size_t col){
        assert(col >= 0 && col < _width);
        assert(_types[col] == 'I');
        return _values[col].i;
    }

    bool get_bool(size_t col) {
        assert(col >= 0 && col < _width);
        assert(_types[col] == 'B');
        return _values[col].b;
    }

    float get_float(size_t col) {
        assert(col >= 0 && col < _width);
        assert(_types[col] == 'F');
        return _values[col].f;
    }

    String* get_string(size_t col) {
        assert(col >= 0 && col < _width);
        assert(_types[col] == 'S');
        return _values[col].s;
    }

    /** Number of fields in the row. */
    size_t width() {
        return _width;
    }

    /** Type of the field at the given position. An idx >= width is  undefined. */
    char col_type(size_t idx) {
        assert(idx >= 0 && idx < _width);
        return _types[idx];
    }

    /** Given a Fielder, visit every field of this row. The first argument is
    * index of the row in the dataframe.
    * Calling this method before the row's fields have been set is undefined. */
    void visit(size_t idx, Fielder& f) {
        if(idx != _index) return; // TODO ?

        for(size_t i = 0; i < _width; ++i) {
            switch(_types[i]){
                case 'I':
                    f.accept(this->get_int(i));
                    break;
                case 'F':
                    f.accept(this->get_float(i));
                    break;
                case 'B':
                    f.accept(this->get_bool(i));
                    break;
                case 'S':
                    f.accept(this->get_string(i));
                    break;
            }
        }
        f.done();
    }
};
