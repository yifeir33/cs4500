#ifndef LIST_H
#define LIST_H

#include "object.h"
#include "string.h"


/**
 * StrList : This class represents a list of String objects.
 *
 * Auther: resnik.n@husky.neu.edu
 */
class StrList : public Object {
public:
    /**
     * Constructs a new empty string list with capacity 10.
     */
    StrList() : _size(0), _capacity(10) {
        _array = new String*[this->_capacity];
        for(size_t i = 0; i < this->_capacity; ++i){
            _array[i] = nullptr;
        }
    };

    /**
     * StrList Destructor. Deletes all strings in the list, and the list itself.
     */
    ~StrList(){
        this->clear();
        delete[] _array;
    };

    /** Appends a copy of e to end
     *
     * @arg e - The string to ad to the end of list. A copy will be created for this list. Managing the initial string
     * is the creator's job.
     */
    void push_back(String* e){
        if(!e) return;
        this->_ensure_size(this->_size + 1);
        this->_array[this->_size++] = new String(e);
    };

    /** Inserts a copy of e at index i.
     *
     * @arg e - The string to ad to the end of list. A copy will be created for this list. Managing the initial string
     * is the creator's job.
     */
    void add(size_t i, String* e){
        if(!e) return;
        this->_ensure_size(this->_size + 1);

        for(size_t j = this->_size; j > i; --j){
            this->_array[j] = this->_array[j - 1];
        }

        this->_array[i] = new String(e);
        ++this->_size;
    };

    /** Inserts all of elements in c_to this list at index i.
     *
     *
     * @arg i - The index to add the elements from c at.
     * @arg c - The list whose elements should be added to this one.
     */
    void add_all(size_t i, StrList* c){
        if(!c) return;
        this->_ensure_size(this->_size + c->_size);

        if(this->_size > 0 && this->_size <= i){
            for(size_t j = i + c->size() - 1; j > i; --j){
                this->_array[j] = this->_array[j - 1];
            }
        }

        for(size_t j = i; j < c->_size; ++j){
            this->_array[j] = new String(c->get(j));
        }
        _size += c->_size;
    };

    /** Removes all of elements from this list. */
    void clear(){
        for(size_t i = 0; i < this->_size; ++i){
            delete this->_array[i];
            this->_array[i] = nullptr;
        }
        _size = 0;
    };

    /** Compares o with this list for equality.
     *
     * @returns true if the lists contain strings representing the same string in the same order,
     * false otherwise.
     */
    bool equals(Object* o){
        if(!o) return false;
        StrList *oStrList = dynamic_cast<StrList *>(o);
        if(oStrList != nullptr && oStrList->_size == this->_size){
            for(size_t i = 0; i < this->_size; ++i){
                if(!this->_array[i]->equals(oStrList->_array[i])){
                    return false;
                }
            }
            return true;
        }
        return false;
    };

    /** Returns the element at index
     *
     * @arg index - the index of the element to get.
     *
     * @returns - A pointer to the object at element index. Deleteing the object this
     * points to will result in undefined behavior.
     */
    String*  get(size_t index){
        if(index < _size){
            return this->_array[index];
        }
        return nullptr;
    };

    // Returns the hash code value for this list.
    size_t hash(){
        size_t h = 0;
        for(size_t i = 0; i < _size; ++i){
            h += this->_array[i]->hash();
        }
        return h;
    };

    /** Returns the index of the first occurrence of o, or >size() if not there.
     *
     * @arg o - The object to search for in the list.
     * 
     * @returns - The index of the object in the list. If it is not present, then returns
     * the size of the list.
     */
    size_t index_of(Object* o){
        if(!o) return _size;
        for(size_t i = 0; i < _size; ++i){
            if(_array[i]->equals(o)){
                return i;
            }
        }
        return _size;
    };

    /** Removes the element at i and returns it.
     *
     * @arg i - the index of the element to remove.
     *
     * @returns - A pointer to the element that was removed. Deleting this
     * object is now the user's responsibility.
     */
    String* remove(size_t i){
        String *el = this->_array[i];
        for(size_t j = i; j < _size - 1; ++j){
            this->_array[j] = this->_array[j + 1];
        }
        this->_array[--_size] = nullptr;
        return el;
    };

    /** Replaces the element at i with a copy of e. Returns the old element. Deleting this old element is
     * the user's responsibility.
     *
     * @arg i - The index of the element to replace.
     * @arg e - The element to put in the list.
     *
     * @return The old element of the list. Deleting this object is now the user's responsibility.
     */
    String* set(size_t i, String* e){
        if(!e) {
            return this->remove(i);
        }
        String *old = this->_array[i];
        this->_array[i] = new String(e);
        return old;
    };

    /** Return the number of elements in the collection
     *
     * @returns - The number of elements in the collection.
     */
    size_t size(){
        return _size;
    };

    /** This should be used as a private method. Ensures the internal array
     * is large enough to hold a list of length required.
     *
     * @arg required - The maximum number of elements the internal array must have capacity for.
     */
    virtual void _ensure_size(size_t required){
        if(required >= this->_capacity){
            // grow
            size_t newCap = this->_capacity * 2;
            while(required > newCap){
                newCap *= 2;
            }

            String **new_array = new String*[newCap];

            for(size_t i = 0; i < newCap; ++i){
                if(i < this->_size){
                    new_array[i] = _array[i];
                } else {
                    new_array[i] = nullptr;
                }
            }

            delete[] _array;
            _capacity = newCap;
            _array = new_array;
        }
    };

    size_t _size; // The current size of the list.
    size_t _capacity; // The current capacity of the internal array.
    String** _array; // The internal array that stores the pointers to the elements of the list.
};

/**
 * SortedStrList : This class represents a list of String objects sorted in increasing alphanumeric order..
 *
 * Auther: resnik.n@husky.neu.edu
 */
class SortedStrList : public StrList {
public:
    /** Adds an element to the list inserting it at the correct location to keep the list 
     * sorted in alphanumeric order. A copy of the element is inserted, deleting the original
     * object is the user's responsibility.
     *
     * @arg s - The string to add to the list. A copy of this string is inserted.
     */
    void sorted_add(String *s){
        for(size_t i = 0; i < this->size(); ++i){
            if(this->get(i)->compare(s) >= 0){
                this->add(i, s);
                return;
            }
        }
        this->push_back(s);
    }

    /** Checks that object o is also a SortedStrList and has strings represeting the same
     * char arrays in the same order.
     *
     * @returns true if the lists are equal, false otherwise.
     */
    bool equals(Object *o){
        return dynamic_cast<SortedStrList *>(o) != nullptr && StrList::equals(o);
    }

};

#endif
