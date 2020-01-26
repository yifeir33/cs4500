//
// Created by 王镱霏 on 1/23/20.
//

#pragma once

#include "object.h"

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
    virtual void count(Object* val);

    // gets the index element
    virtual Object* get(int index);

    virtual int size();

    // Adds an element at the specified position
    virtual void insert(int index, char *input);

    // Removes the first item with the specified value
    virtual Object* remove(int index);

    // Add the elements of a array, to the end of the current list
    virtual void extend(int i, Array* arr1);

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

