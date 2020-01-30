//
// Created by 王镱霏 on 1/23/20.
//

#pragma once

#include "object.h"
#include "string.h"

class Array : public Object{
public:

    Array();

    Array(int size);

    virtual ~Array();

    // Adds an element at the end of the list
    virtual void append(Object* input);

    //Removes all the elements from the list
    virtual void clear();

    // Returns the number of elements with the specified value
    virtual int count(Object* val);

    // gets the index element
    virtual Object* get(int index);

    virtual int size();

    // Adds an element at the specified position
    virtual void insert(int index, Object* input);

    // Removes the first item with the specified value
    virtual Object* remove(Object* val);

    // Add the elements of a array, to the end of the current list
    virtual void extend(Array** arr1);

    // Returns the index of the first element with the specified value
    virtual int index(Object* input);
    
    // 	Removes the element at the specified position
    virtual Object* pop(int index);

    // Reverses the order of the list
    virtual void reverse();

    // Sorts the list
    virtual void sort();

    // set the position
    virtual Object* set(int index, Object* input);

    virtual bool equals(Object* o);

    virtual size_t hash();

    virtual void _ensure_size(int required);
};

class StringArray : public Object{
public:

    StringArray();

    StringArray(int size);

    virtual ~StringArray();

    // Adds an element at the end of the list
    virtual void append(String* input);

    //Removes all the elements from the list
    virtual void clear();

    // Returns the number of elements with the specified value
    virtual int count(String* val);

    // gets the index element
    virtual String* get(int index);

    virtual int size();

    // Adds an element at the specified position
    virtual void insert(int index, String* input);

    // Removes the first item with the specified value
    virtual String* remove(String* val);

    // Add the elements of a array, to the end of the current list
    virtual void extend(Array** arr1);

    // Returns the index of the first element with the specified value
    virtual int index(String* input);
    
    // 	Removes the element at the specified position
    virtual String* pop(int index);

    // Reverses the order of the list
    virtual void reverse();

    // Sorts the list
    virtual void sort();

    // set the position
    virtual String* set(int index, String* input);

    virtual bool equals(String* o);

    virtual size_t hash();

    virtual void _ensure_size(int required);
};

class IntArray : public Object{
public:

    IntArray();

    IntArray(int size);

    virtual ~IntArray();

    // Adds an element at the end of the list
    virtual void append(int input);

    //Removes all the elements from the list
    virtual void clear();

    // Returns the number of elements with the specified value
    virtual int count(int val);

    // gets the index element
    virtual int get(int index);

    virtual int size();

    // Adds an element at the specified position
    virtual void insert(int index, int input);

    // Removes the first item with the specified value
    virtual int remove(int val);

    // Add the elements of a array, to the end of the current list
    virtual void extend(IntArray** arr1);

    // Returns the index of the first element with the specified value
    virtual int index(int input);
    
    // 	Removes the element at the specified position
    virtual int pop(int index);

    // Reverses the order of the list
    virtual void reverse();

    // Sorts the list
    virtual void sort();

    // set the position
    virtual int set(int index, int input);

    virtual bool equals(int o);

    virtual size_t hash();

    virtual void _ensure_size(int required);
};

class FloatArray : public Object{
public:

    FloatArray();

    FloatArray(float size);

    virtual ~FloatArray();

    // Adds an element at the end of the list
    virtual void append(float input);

    //Removes all the elements from the list
    virtual void clear();

    // Returns the number of elements with the specified value
    virtual float count(float val);

    // gets the index element
    virtual float get(float index);

    virtual float size();

    // Adds an element at the specified position
    virtual void insert(float index, float input);

    // Removes the first item with the specified value
    virtual float remove(float val);

    // Add the elements of a array, to the end of the current list
    virtual void extend(IntArray** arr1);

    // Returns the index of the first element with the specified value
    virtual float index(float input);
    
    // 	Removes the element at the specified position
    virtual float pop(float index);

    // Reverses the order of the list
    virtual void reverse();

    // Sorts the list
    virtual void sort();

    // set the position
    virtual float set(float index, float input);

    virtual bool equals(float o);

    virtual size_t hash();

    virtual void _ensure_size(float required);
};

class BoolArray : public Object{
public:

    BoolArray();

    BoolArray(bool size);

    virtual ~BoolArray();

    // Adds an element at the end of the list
    virtual void append(bool input);

    //Removes all the elements from the list
    virtual void clear();

    // Returns the number of elements with the specified value
    virtual bool count(bool val);

    // gets the index element
    virtual bool get(bool index);

    virtual bool size();

    // Adds an element at the specified position
    virtual void insert(bool index, bool input);

    // Removes the first item with the specified value
    virtual bool remove(bool val);

    // Add the elements of a array, to the end of the current list
    virtual void extend(IntArray** arr1);

    // Returns the index of the first element with the specified value
    virtual bool index(bool input);
    
    // 	Removes the element at the specified position
    virtual bool pop(bool index);

    // Reverses the order of the list
    virtual void reverse();

    // Sorts the list
    virtual void sort();

    // set the position
    virtual bool set(bool index, bool input);

    virtual bool equals(bool o);

    virtual size_t hash();

    virtual void _ensure_size(bool required);
};
