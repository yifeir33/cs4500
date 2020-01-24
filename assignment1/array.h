//
// Created by 王镱霏 on 1/23/20.
//

#ifndef HW3_ARRAY_H
#define HW3_ARRAY_H

class Array: public Object{
public:
    int _size;
    int _capacity;
    char** array[_capacity];
    Array(): _size(0), _capacity(10){
        for(int i =0; i < this->_capacity; i++){
            array[i] = nullptr;
        }
    }

    ~Array(){
        this->clear();
        delete [] array;
    }

    // Adds an element at the end of the list
    void append(char* input){
        if(!input) return;
        this->_ensure_size(this->_size+1);
        this->array[this->size()++] = input;
    }

    //Removes all the elements from the list
    void clear(){
        for(int i =0; i< _size+1; i++ ){
            delete this->array[i];
            this.array[i] = nullptr;
        }
        _size =0;
    }

    // Returns the number of elements with the specified value
    void count(char* val){
        int count =0;
        for(int i =0; i< _size;i++){
            if(strcmp(val, array[i]) ==0){
                count++;
            }
        }
        retun count;
    }

    // gets the index element
    char* get(int index){
        if(index <_size){
            return array[index];
        }
        return nullptr;
    }

    char* &operator[](int index){}



    int size(){
        int size = 0;
        for(int i =0; i < this->_size+1; i++){
            if(array[i] != nullptr){
                size++;
            }
        }
    }


    // Adds an element at the specified position
    void insert(int index, char input){
        if(!input){
            return;
        }
        this->_ensure_size(this->size()+1);
        if(array[index] == nullptr){
            array[index] = input;
        }else {
            for (int j = this->size(); j > index; --j) {
                this->array[j] = this->array[j - 1];
            }
            this->array[i] =input;
            ++this->_size;
        }

    }

    // Removes the first item with the specified value
    char* remove(int index){
        char* cur = this->array[i];
        for(int i = index; i< _size - 1; i++){
            this->array[i] = this->array[i+1];
        }
        this->array[_size -1 ] = nullptr;
        this->_size--;
        return cur;
    }

    // Add the elements of a list (or any iterable), to the end of the current list
    void extend(int i, Array* arr1){
        this->_ensure_size(this->size()+arr1->size());

        if(this->size()<= i){
            for
        }
    }

    // Returns the index of the first element with the specified value
    char* index(char* input){

    }
    // 	Removes the element at the specified position
    char* pop(int index){

    }

    // Reverses the order of the list
    void reverse(){
        char** new_array[_capacity];
        for (int i =0; i < this->_size; i++){
            for (int j = _size; j> 0; j-- ){
                new_array[i] = array[j];
            }
        }
        this->array = new_array;
    }

//    // Sorts the list
//    void sort(){
//
//    }
    // set the position
    char* set(int index, char* input){
        if(!input){
            return this->remove(index);
        }
        char* old = array[i];
        this->array[i] = input;
        return old;
    }

    bool equals(Object* o){

    }

    size_t hash(){
        size_t h = 0;
        for(size_t i =0; i< _size; i++){
            h+= this-> (int) array[i];
        }
        return h;
    }

    virtual void _ensure_size(int required){
        if(required >= this->_capacity){

            int newCap = this->_capacity * 2;
            while(required > newCap){
                newCap *= 2;
            }

            char**  new_array[newCap];

            for(int i = 0; i < newCap; ++i){
                if(i < this->_size){
                    new_array[i] = array[i];
                } else {
                    new_array[i] = nullptr;
                }
            }

            delete[] array;
            _capacity = newCap;
            array = new_array;
        }
    };




};

#endif //HW3_ARRAY_H
