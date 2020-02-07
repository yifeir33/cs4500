// lang: CwC
#pragma once

#include <stdarg.h>

#include "string.h"
#include "array.h"

/**
 * An enum to represent the different types that a column in a Schema-On-Read (SOR) file
 * can contain.
 *
 * API Authors: Neil Resnik (resnik.n@husky.neu.edu) & Yifei Wang (wang.yifei3@husky.neu.edu)
 */
enum ColumnType {
    STRING,
    BOOL,
    INTEGER,
    FLOAT
};

/**
 * An abstract class to encompass all columns of all types.
 *
 * API Authors: Neil Resnik (resnik.n@husky.neu.edu) & Yifei Wang (wang.yifei3@husky.neu.edu)
 */
class SorColumn : public Object {
public:
    /**
     * A constructor that makes a SorColumn with no name.
     */
    SorColumn();

    /**
     * A constructor that makes a SorColumn named the given name.
     *
     * @param name - The name of this column.
     */
    SorColumn(const char* name);

    /**
     * Destructor
     */
    virtual ~SorColumn();

    /**
     * Sets the name of this SorColumn.
     *
     * @param name - The name to set this column to.
     */
    virtual void setName(const char* name);

    /**
     * Gets the name of this column.
     *
     * @returns - The name of this column.
     */
    virtual const char* getName();

    /**
     * Returns the type of this column.
     *
     * @returns - The type of this column.
     */
    virtual ColumnType getType();

    /**
     * Appends a integer value to this column if it is of the correct type.
     *
     * @param value - The value to append.
     *
     * @returns true if the value is appended, false otherwise.
     */
    virtual bool appendValue(int value);

    /**
     * Appends a boolean value to this column if it is of the correct type.
     *
     * @param value - The value to append.
     *
     * @returns true if the value is appended, false otherwise.
     */
    virtual bool appendValue(bool value);

    /**
     * Appends a floating point value to this column if it is of the correct type.
     *
     * @param value - The value to append.
     *
     * @returns true if the value is appended, false otherwise.
     */
    virtual bool appendValue(double value);

    /**
     * Appends a boolean value to this column if it is of the correct type.
     *
     * @param value - The value to append.
     *
     * @returns true if the value is appended, false otherwise.
     */
    virtual bool appendValue(String* value);

    /**
     * Returns the boolean value in this column at the given row index,
     * if this column is of the correct type.
     *
     * @param row - The index of the row whose value is wanted.
     *
     * @returns - The boolean value at the given index if this column is of the correct type.
     */
    virtual bool getBool(size_t row);

    /**
     * Returns the String pointer in this column at the given row index,
     * if this column is of the correct type.
     *
     * @param row - The index of the row whose value is wanted.
     *
     * @returns - The boolean value at the given index if this column is of the correct type.
     */
    virtual String* getString(size_t row);

    /**
     * Returns the integer value in this column at the given row index,
     * if this column is of the correct type.
     *
     * @param row - The index of the row whose value is wanted.
     *
     * @returns - The boolean value at the given index if this column is of the correct type.
     */
    virtual int getInt(size_t row);

    /**
     * Returns the floating point value in this column at the given row index,
     * if this column is of the correct type.
     *
     * @param row - The index of the row whose value is wanted.
     *
     * @returns - The boolean value at the given index if this column is of the correct type.
     */
    virtual double getFloat(size_t row);

    /**
     * Returns the number of rows in this column.
     *
     * @returns - The number of rows in this column.
     */
    virtual size_t nrows();
};

/**
 * A concrete class to represent a column of integers.
 *
 * API Authors: Neil Resnik (resnik.n@husky.neu.edu) & Yifei Wang (wang.yifei3@husky.neu.edu)
 */
class IntColumn : public SorColumn {
public:
    /**
     * Constructs an IntColumn with no name and no data.
     */
    IntColumn();

    /**
     * Constructs an IntColumn with the given name and no data.
     *
     * @param name - The name of this column.
     */
    IntColumn(const char* name);

    /**
     * Constructs an IntColumn with no name and containing the data in the given
     * array, where each index is a new row.
     *
     * @param arr - The data stored in this column.
     */
    IntColumn(IntArray arr);

    /**
     * Constructs an IntColumn with the given name and containing the data in the given
     * array, where each index is a new row.
     *
     * @param name - The name of this column.
     * @param arr - The data stored in this column.
     */
    IntColumn(const char* name, IntArray arr);

    /**
     * Destructor
     */
    virtual ~IntColumn();
};

/**
 * A concrete class to represent a column of strings.
 *
 * API Authors: Neil Resnik (resnik.n@husky.neu.edu) & Yifei Wang (wang.yifei3@husky.neu.edu)
 */
class StringColumn : public SorColumn {
public:
    /**
     * Constructs an StringColumn with no name and no data.
     */
    StringColumn();

    /**
     * Constructs an StringColumn with the given name and no data.
     *
     * @param name - The name of this column.
     */
    StringColumn(const char* name);

    /**
     * Constructs an StringColumn with no name and containing the data in the given
     * array, where each index is a new row.
     *
     * @param arr - The data stored in this column.
     */
    StringColumn(StringArray arr);

    /**
     * Constructs an StringColumn with the given name and containing the data in the given
     * array, where each index is a new row.
     *
     * @param name - The name of this column.
     * @param arr - The data stored in this column.
     */
    StringColumn(const char* name, StringArray arr);

    /**
     * Destructor
     */
    virtual ~StringColumn();
};

/**
 * A concrete class to represent a column of booleans.
 *
 * API Authors: Neil Resnik (resnik.n@husky.neu.edu) & Yifei Wang (wang.yifei3@husky.neu.edu)
 */
class BoolColumn : public SorColumn {
public:
    /**
     * Constructs an BoolColumn with no name and no data.
     */
    BoolColumn();
    
    /**
     * Constructs an BoolColumn with the given name and no data.
     *
     * @param name - The name of this column.
     */
    BoolColumn(const char* name);

    /**
     * Constructs an BoolColumn with no name and containing the data in the given
     * array, where each index is a new row.
     *
     * @param arr - The data stored in this column.
     */
    BoolColumn(BoolArray arr);

    /**
     * Constructs an BoolColumn with the given name and containing the data in the given
     * array, where each index is a new row.
     *
     * @param name - The name of this column.
     * @param arr - The data stored in this column.
     */
    BoolColumn(const char* name, BoolArray arr);

    /**
     * Destructor
     */
    virtual ~BoolColumn();
};

/**
 * A concrete class to represent a column of floating point values.
 *
 * API Authors: Neil Resnik (resnik.n@husky.neu.edu) & Yifei Wang (wang.yifei3@husky.neu.edu)
 */
class FloatColumn : public SorColumn {
public:
    /**
     * Constructs an FloatColumn with no name and no data.
     */
    FloatColumn();

    /**
     * Constructs an FloatColumn with the given name and no data.
     *
     * @param name - The name of this column.
     */
    FloatColumn(const char* name);

    /**
     * Constructs an FloatColumn with no name and containing the data in the given
     * array, where each index is a new row.
     *
     * @param arr - The data stored in this column.
     */
    FloatColumn(FloatArray arr);

    /**
     * Constructs an FloatColumn with the given name and containing the data in the given
     * array, where each index is a new row.
     *
     * @param name - The name of this column.
     * @param arr - The data stored in this column.
     */
    FloatColumn(const char* name, FloatArray arr);

    /**
     * Destructor
     */
    virtual ~FloatColumn();
};
