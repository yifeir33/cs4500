#pragma once

#include "../object.h"
#include "../string.h"
#include "column.h"
#include "schema.h"
#include "row.h"
#include "rower.h"

/****************************************************************************
 * DataFrame::
 *
 * A DataFrame is table composed of columns of equal length. Each column
 * holds values of the same type (I, S, B, F). A dataframe has a schema that
 * describes it.
 */
class DataFrame : public Object {
public:

    /* Helper Rower to print the dataframe */
    class PrintRower : public Rower {
    public:
        /* Helper Fielder to print the dataframe */
        class PrintFielder : public Fielder {
        public:
            Sys _sys;

            virtual void start(size_t r){}
            /** Called for fields of the argument's type with the value of the field. */
            virtual void accept(bool b){
                _sys.p('<').p(b).p('>');
            }

            virtual void accept(float f){
                _sys.p('<').p(f).p('>');
            }

            virtual void accept(int i){
                _sys.p('<').p(i).p('>');
            }

            virtual void accept(String* s){
                _sys.p('<').p(s).p('>');
            }

            /** Called when all fields have been seen. */
            virtual void done(){
                _sys.p('\n');
            }

            virtual size_t hash_me() {
                return Fielder::hash() + 100;
            }

            virtual bool equals(Object *other) {
                return dynamic_cast<PrintFielder*>(other);
            }
        };

        virtual bool accept(Row& r){
            PrintFielder pf;
            r.visit(r.get_index(), pf);
            return true;
        }

        virtual size_t hash_me() {
            return Rower::hash() + 100;
        }

        virtual bool equals(Object *other) {
            return dynamic_cast<PrintRower*>(other);
        }
    };


    Schema& _schema;
    ObjectArray _columns;

    /** Create a data frame with the same columns as the given df but with no rows or rownmaes */
    DataFrame(DataFrame& df) : DataFrame(df.get_schema()) {}

    /** Create a data frame from a schema and columns. All columns are created
    * empty. */
    DataFrame(Schema& schema) : _schema(schema), _columns(schema.width()) {
        for(size_t i = 0; i < schema.width(); ++i){
            Column *col = _get_col_from_type(schema.col_type(i));
            assert(col);
            _columns.push(col);
        }
    }

    Column* _get_col_from_type(char type) {
        switch(type) {
            case 'I':
                return new IntColumn();
            case 'F':
                return new FloatColumn();
            case 'B':
                return new BoolColumn();
            case 'S':
                return new StringColumn();
            default:
                return nullptr;
        }
    }

    /** Returns the dataframe's schema. Modifying the schema after a dataframe
    * has been created in undefined. */
    Schema& get_schema() {
        return _schema;
    }

    /** Adds a column this dataframe, updates the schema, the new column
    * is external, and appears as the last column of the dataframe, the
    * name is optional and external. A nullptr colum is undefined. */
    void add_column(Column* col, String* name){
        assert(col);
        assert(name);
        _schema.add_column(col->get_type(), name);
        _columns.push(col);
    }

    /** Return the value at the given column and row. Accessing rows or
    *  columns out of bounds, or request the wrong type is undefined.*/
    int get_int(size_t col, size_t row){
        Column *generic_column = static_cast<Column*>(_columns.get(col));
        IntColumn *int_column = generic_column->as_int();
        assert(int_column);
        return int_column->get(row);
    }

    bool get_bool(size_t col, size_t row) {
        Column *generic_column = static_cast<Column*>(_columns.get(col));
        BoolColumn *bool_column = generic_column->as_bool();
        assert(bool_column);
        return bool_column->get(row);
    }

    float get_float(size_t col, size_t row) {
        Column *generic_column = static_cast<Column*>(_columns.get(col));
        FloatColumn *float_column = generic_column->as_float();
        assert(float_column);
        return float_column->get(row);
    }

    String*  get_string(size_t col, size_t row) {
        Column *generic_column = static_cast<Column*>(_columns.get(col));
        StringColumn *str_column = generic_column->as_string();
        assert(str_column);
        return str_column->get(row);
    }

    /** Return the offset of the given column name or -1 if no such col. */
    int get_col(String& col) {
        return _schema.col_idx(col.c_str());
    }

    /** Return the offset of the given row name or -1 if no such row. */
    int get_row(String& row) {
        return _schema.row_idx(row.c_str());
    }

    /** Set the value at the given column and row to the given value.
    * If the column is not  of the right type or the indices are out of
    * bound, the result is undefined. */
    void set(size_t col, size_t row, int val) {
        Column *generic_column = static_cast<Column*>(_columns.get(col));
        IntColumn *int_column = generic_column->as_int();
        assert(int_column);
        int_column->set(row, val);
    }

    void set(size_t col, size_t row, bool val) {
        Column *generic_column = static_cast<Column*>(_columns.get(col));
        BoolColumn *bool_column = generic_column->as_bool();
        assert(bool_column);
        bool_column->set(row, val);
    }

    void set(size_t col, size_t row, float val) {
        Column *generic_column = static_cast<Column*>(_columns.get(col));
        FloatColumn *float_column = generic_column->as_float();
        assert(float_column);
        float_column->set(row, val);
    }

    void set(size_t col, size_t row, String* val) {
        Column *generic_column = static_cast<Column*>(_columns.get(col));
        StringColumn *str_column = generic_column->as_string();
        assert(str_column);
        str_column->set(row, val);
    }

    /** Set the fields of the given row object with values from the columns at
    * the given offset.  If the row is not form the same schema as the
    * dataframe, results are undefined.
    */
    void fill_row(size_t idx, Row& row){
        for(size_t c = 0; c < _columns.length(); ++c){
            switch(_schema.col_type(c)){
                case 'I':
                    row.set(c, this->get_int(c, idx));
                    break;
                case 'F':
                    row.set(c, this->get_float(c, idx));
                    break;
                case 'B':
                    row.set(c, this->get_bool(c, idx));
                    break;
                case 'S':
                    row.set(c, this->get_string(c, idx));
                    break;
                default:
                    assert(false); // unreachable
            }
        }
    }

    /** Add a row at the end of this dataframe. The row is expected to have
    *  the right schema and be filled with values, otherwise undedined.  */
    void add_row(Row& row) {
        for(size_t c = 0; c < _columns.length(); ++c){
            Column *col = static_cast<Column*>(_columns.get(c));
            assert(col);
            switch(col->get_type()){
                case 'I':
                    col->push_back(row.get_int(c));
                    break;
                case 'F':
                    col->push_back(row.get_float(c));
                    break;
                case 'B':
                    col->push_back(row.get_bool(c));
                    break;
                case 'S':
                    col->push_back(row.get_string(c));
                    break;
                default:
                    assert(false); // unreachable
            }
        }
    }

    /** The number of rows in the dataframe. */
    size_t nrows() {
        return static_cast<Column*>(_columns.get(0))->size();
    }

    /** The number of columns in the dataframe.*/
    size_t ncols() {
        return _columns.length();
    }

    /** Visit rows in order */
    void map(Rower& r) {
        for(size_t i = 0; i < _schema.length(); ++i) {
            Row row(_schema);
            this->fill_row(i, row);
            r.accept(row);
        }
    }

    /** Create a new dataframe, constructed from rows for which the given Rower
    * returned true from its accept method. */
    DataFrame* filter(Rower& r) {
        DataFrame *df = new DataFrame(*this);

        for(size_t i = 0; i < _schema.length(); ++i) {
            Row row(_schema);
            this->fill_row(i, row);
            if(r.accept(row)) {
                df->add_row(row);
            }
        }
        return df;
    }


    /** Print the dataframe in SoR format to standard output. */
    void print() {
        PrintRower pr;
        this->map(pr);
    }

    virtual bool equals(Object* other) {
        DataFrame *df_other = dynamic_cast<DataFrame*>(other);
        if(!df_other) return false;
        return _columns.equals(&df_other->_columns) && _schema.equals(&df_other->_schema);
    }

    virtual Object* clone() {
        return new DataFrame(*this);
    }

    virtual size_t hash_me() {
        return _columns.hash() + _schema.hash();
    }

};

