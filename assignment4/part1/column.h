#pragma once

#include <assert.h>

#include "../object.h"
#include "../string.h"
#include "../array.h"

// Forward Declarations for Column
class IntColumn;
class BoolColumn;
class FloatColumn;
class StringColumn;

/**************************************************************************
 * Column ::
 * Represents one column of a data frame which holds values of a single type.
 * This abstract class defines methods overriden in subclasses. There is
 * one subclass per element type. Columns are mutable, equality is pointer
 * equality. */
class Column : public Object {
public:
 
  /** Type converters: Return same column under its actual type, or
   *  nullptr if of the wrong type.  */
  virtual IntColumn* as_int() { return nullptr; }
  virtual BoolColumn*  as_bool() { return nullptr; }
  virtual FloatColumn* as_float() { return nullptr; }
  virtual StringColumn* as_string() { return nullptr; }
 
  /** Type appropriate push_back methods. Calling the wrong method is
    * undefined behavior. **/
  virtual void push_back(int val){};
  virtual void push_back(bool val){};
  virtual void push_back(float val){};
  virtual void push_back(String* val){};
 
 /** Returns the number of elements in the column. */
  virtual size_t size();
 
  /** Return the type of this column as a char: 'S', 'B', 'I' and 'F'. */
  virtual char get_type();
};
 
/*************************************************************************
 * IntColumn::
 * Holds int values.
 */
class IntColumn : public Column {
public:
    IntArray _data;

    IntColumn();

    IntColumn(int n, ...);

    virtual void push_back(int val) {
      _data.push(val);
    }

    int get(size_t idx) {
      return _data.get(idx);
    }

    virtual IntColumn* as_int() {
      return this;
    }
    /** Set value at idx. An out of bound idx is undefined.  */
    void set(size_t idx, int val) {
      _data.replace(idx, val);
    }

    virtual size_t size() {
      return _data.length();
    }


    virtual char get_type() {
      return 'I';
    }
};
 
/*************************************************************************
 * FloatColumn::
 * Holds floating point values.
 */
class FloatColumn : public Column {
public:
    FloatArray _data;

    FloatColumn();

    FloatColumn(int n, ...);

    virtual void push_back(float val) {
      _data.push(val);
    }

    float get(size_t idx) {
      return _data.get(idx);
    }

    virtual FloatColumn* as_float() {
      return this;
    }
    /** Set value at idx. An out of bound idx is undefined.  */
    void set(size_t idx, float val) {
      _data.replace(idx, val);
    }

    virtual size_t size() {
      return _data.length();
    }


    virtual char get_type() {
      return 'F';
    }
};

/*************************************************************************
 * BoolColumn::
 * Holds boolean values.
 */
class BoolColumn : public Column {
public:
    BoolArray _data;

    BoolColumn();

    BoolColumn(int n, ...);

    virtual void push_back(bool val) {
      _data.push(val);
    }

    bool get(size_t idx) {
      return _data.get(idx);
    }

    virtual BoolColumn* as_bool() {
      return this;
    }
    /** Set value at idx. An out of bound idx is undefined.  */
    void set(size_t idx, bool val) {
      _data.replace(idx, val);
    }

    virtual size_t size() {
      return _data.length();
    }


    virtual char get_type() {
      return 'B';
    }
};
 
/*************************************************************************
 * StringColumn::
 * Holds string pointers. The strings are external.  Nullptr is a valid
 * value.
 */
class StringColumn : public Column {
public:
    StringArray _data;

    StringColumn();

    StringColumn(int n, ...);

    StringColumn* as_string() {
      return this;
    }

    virtual void push_back(String* val){
      _data.push(val);
    }

    /** Returns the string at idx; undefined on invalid idx.*/
    String* get(size_t idx) {
      return _data.get(idx);
    }

    /** Out of bound idx is undefined. */
    void set(size_t idx, String* val) {
      _data.replace(idx, val);
    }

    size_t size() {
      return _data.length();
    }

    virtual char get_type() {
      return 'S';
    }
};
