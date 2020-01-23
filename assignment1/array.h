//
// Created by 王镱霏 on 1/23/20.
//

#ifndef HW3_ARRAY_H
#define HW3_ARRAY_H

class Array{
public:
    int size_;
    char** array[size_];
    Array();
    Array(int size);

    ~Array(){
        delete size_;
        delete [] array;
    }

    // Adds an element at the end of the list
    void append(char* input){

    }

    //Removes all the elements from the list
    void clear(){

    }

    // Returns the number of elements with the specified value
    void count(char* val){

    }

    // gets the index element
    char* get(int index){

    }

    char* &operator[](int index){}



    int size(){ return  this->size_;}


    // Adds an element at the specified position
    void insert(int index, char input){

    }

    // Removes the first item with the specified value
    void remove(int index){

    }

    // Add the elements of a list (or any iterable), to the end of the current list
    void extend(Array* arr1){

    }

    // Returns the index of the first element with the specified value
    char* index(char* input){

    }
    // 	Removes the element at the specified position
    char* pop(int index){

    }

    // Reverses the order of the list
    void reverse(){

    }

    // Sorts the list
    void sort(){

    }
    // set the position
    void set(int index, char* input){

    }


};

#endif //HW3_ARRAY_H
