//
// Created by 王镱霏 on 1/23/20.
//

#ifndef HW3_ARRAY_H
#define HW3_ARRAY_H

#include "object.h"

class Array : public Object{
public:
    int _size;
    int _capacity;
    char** _array;

    Array();

    Array(int size);

    virtual ~Array();

    // Adds an element at the end of the list
    void append(char* input);

    //Removes all the elements from the list
    void clear();

    // Returns the number of elements with the specified value
    void count(char* val);

    // gets the index element
    char* get(int index);

    char* &operator[](int index);

    int size();

    // Adds an element at the specified position
    void insert(int index, char *input);

    // Removes the first item with the specified value
    char* remove(int index);

    // Add the elements of a array, to the end of the current list
    void extend(int i, Array* arr1);

    // Returns the index of the first element with the specified value
    int index(char* input);
    
        // 	Removes the element at the specified position
    char* pop(int index);

    // Reverses the order of the list
    void reverse();

    // Sorts the list
    void sort();

    // set the position
    char* set(int index, char* input);

    bool equals(Object* o);

    size_t hash();

    virtual void _ensure_size(int required);
};

#endif //HW3_ARRAY_H
