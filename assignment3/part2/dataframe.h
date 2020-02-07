// lang: CwC
#pragma once

#include <stdint.h>
#include <stdarg.h>

#include "sorcolumn.h"
#include "string.h"

/**
 * This class represents a data frame that provides and interface
 * to retrieve ata from a Schema-On-Read (SOR) file.
 *
 * API Authors: Neil Resnik (resnik.n@husky.neu.edu) & Yifei Wang (wang3.yi@husky.neu.edu)
 */
class DataFrame : public Object {
public:

    /**
     * Constructs a DataFrame with the given number of columns 
     *
     * @param column_count - The number of columns in this DataFrame.
     */
    DataFrame(size_t column_count);

    /**
     * Destructor for a DataFrame 
     */
    virtual ~DataFrame();

    /** 
     * Sets the column at the given index to be the given column.
     *
     * @param c - The SorColumn that represents the column.
     * @param index - The index of the given column.
     */
    virtual void setColumn(size_t index, SorColumn* c);

    /**
     * Prints this Dataframe to stdout.
     */
    virtual void print();

    /**
     * Returns the enum representing the type of the column
     * at index 'col'.
     *
     * @param col - The index of the column whose type is wanted.
     *
     * @returns - The type of the data in the column
     */
    virtual ColumnType getColumnType(size_t col);

    /**
     * Returns the enum representing the type of the column
     * at index 'col'.
     *
     * @param name - The name of the column whose type is wanted.
     *
     * @returns - The type of the data in the column.
     */
    virtual ColumnType getColumnType(const char* name);

    /**
     * Sets the name of the column at index 'col'.
     *
     * @param col - The index of the column to name.
     * @param name - The name of the column.
     */
    virtual void setColumnName(size_t col, const char* name);

    /**
     * Returns the name of the column at index 'col'.
     *
     * @param col - The index of the column whose name is wanted.
     *
     * @returns The name of the column.
     */
    virtual const char* getColumnName(size_t col);

    /**
     * Sets the name of the row at index 'row'.
     *
     * @param row - The index of the row to name.
     * @param name - The name of the row.
     */
    virtual void setRowName(size_t row, const char* name);

    /**
     * Returns the name of the row at index 'row'.
     *
     * @param row - The index of the row whose name is wanted.
     *
     * @returns The name of the row.
     */
    virtual const char* getRowName(size_t row);

    /**
     * If the column is of type Bool, returns the boolean
     * value at the given index.
     *
     * @param col - The index of the column.
     * @param row - The index of the row.
     *
     * @returns - The value at the given index if the column is the correct type.
     */
    virtual bool getBool(size_t col, size_t row);

    /**
     * If the column is of type Bool, returns the boolean
     * value at the given index.
     *
     * @param column_name - The name of the column.
     * @param row_name - The name of the row.
     *
     * @returns - The value at the given index if the column is the correct type.
     */
    virtual bool getBool(const char* column_name, const char* row_name);

    /**
     * If the column is of type String, returns a pointer to the string
     * value at the given index.
     *
     * @param col - The index of the column.
     * @param row - The index of the row.
     *
     * @returns - The value at the given index if the column is the correct type.
     */
    virtual String* getString(size_t col, size_t row);

    /**
     * If the column is of type String, returns a pointer to the string
     * value at the given index.
     *
     * @param column_name - The name of the column.
     * @param row_name - The name of the row.
     *
     * @returns - The value at the given index if the column is the correct type.
     */
    virtual String* getString(const char* column_name, const char* row_name);

    /**
     * If the column is of type Integer, returns the integer 
     * value at the given index.
     *
     * @param col - The index of the column.
     * @param row - The index of the row.
     *
     * @returns - The value at the given index if the column is the correct type.
     */
    virtual int getInt(size_t col, size_t row);

    /**
     * If the column is of type Integer, returns the integer
     * value at the given index.
     *
     * @param column_name - The name of the column.
     * @param row_name - The name of the row.
     *
     * @returns - The value at the given index if the column is the correct type.
     */
    virtual int getInt(const char* column_name, const char* row_name);

    /**
     * If the column is of type Float, returns the floating point
     * value at the given index.
     *
     * @param col - The index of the column.
     * @param row - The index of the row.
     *
     * @returns - The value at the given index if the column is the correct type.
     */
    virtual double getFloat(size_t col, size_t row);

    /**
     * If the column is of type Float, returns the floating point
     * value at the given index.
     *
     * @param column_name - The name of the column.
     * @param row_name - The name of the row.
     *
     * @returns - The value at the given index if the column is the correct type.
     */
    virtual double getFloat(const char* column_name, const char* row_name);

    /**
     * Returns the number of columns in the DataFrame.
     *
     * @returns - The number of columns.
     */
    virtual size_t ncol();

    /**
     * Returns the number of rows in the DataFrame.
     *
     * @returns - The number of rows.
     */
    virtual size_t nrow();
};
