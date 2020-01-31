//lang::CwC
#pragma once

#include <cstdlib>
#include <cstring>
#include <assert.h>

#include "object.h"
#include "string.h"

/**
 * Queue: Represents a FIFO data structure.
 *        Capable of holding any Object in the given order.
 *
 * mutable
 *
 * authors: dermer.s@husky.neu.edu && Sarialli.n@northeastern.edu
 */
class Queue : public Object {
public:
    Object **_buffer;
    size_t _capacity;
    size_t _front_index;
    size_t _back_index;
    size_t _size;

    // The Constructor
    Queue() {
      _buffer = new Object*[10];
      _capacity = 10;
      _front_index = 0;
      _back_index = 0;
      _size = 0;
    }

    // The Destructor
    virtual ~Queue() {
      delete[] _buffer;
    }

    // adds the given object to the beginning of this queue.
    // undefined behavior: the same pointer is pushed more than once or o is this
    virtual void push(Object* o) {
      if(_size + 1 >= _capacity){
          Object **_new_buf = new Object*[_capacity * 2];
          size_t new_index = 0;
          size_t old_index = _front_index;
          while(new_index < _size){
              _new_buf[new_index] = _buffer[old_index];
              old_index = (old_index + 1) % _capacity;
              new_index++;
          }
          _capacity *= 2;
          _front_index = 0;
          _back_index = _size;
          delete[] _buffer;
          _buffer = _new_buf;
      }

      _buffer[_back_index] = o;
      _back_index = (_back_index + 1) % _capacity;
      _size++;
    }

    // removes and returns the object at the end of this queue.
    // errors if there is nothing in the queue
    virtual Object* pop() {
      assert(_size > 0);
      Object *output = _buffer[_front_index];
      _buffer[_front_index] = nullptr;
      _front_index = (_front_index + 1) % _capacity;
      _size--;
      return output;
    }

    // returns the object at the end of this queue but does not remove it.
    // errors if there is nothing in the queue
    virtual Object* peek() {
      assert(_size > 0);
      return _buffer[_front_index];
    }

    // gives the total number of elements in this Queue
    virtual size_t len() {
      return _size;
    }

    // true if o is a queue and all of the elements of this queue,
    // in the same order, are equal to o's
    virtual bool equals(Object *other) {
        Queue *q_ptr = dynamic_cast<Queue *>(other);
        if(q_ptr && q_ptr->len() == _size){
            size_t i = _front_index;
            size_t j = q_ptr->_front_index;
            size_t count = 0;
            while(count < _size){
                if(!_buffer[i]->equals(q_ptr->_buffer[j])){
                    return false;
                }
                i = (i + 1) % _capacity;
                j = (j + 1) % q_ptr->_capacity;
                count++;
            }
            return true;
        }
        return false;
    }

    // hash of this queue
    virtual size_t hash() {
        size_t hash = this->_size;
        size_t index = _front_index;
        size_t count = 0;
        while(count < _size){
            hash += _buffer[index]->hash();
            index = (index + 1) % _capacity;
            count++;
        }
        return hash;
    }
};

/**
 * StrQueue: Represents a FIFO data structure.
 *        Capable of holding any Object in the given order.
 *
 * mutable
 *
 * authors: dermer.s@husky.neu.edu && Sarialli.n@northeastern.edu
 */
class StrQueue : public Object {
public:
    Object **_buffer;
    size_t _capacity;
    size_t _front_index;
    size_t _back_index;
    size_t _size;

    // The Constructor
    StrQueue() {
      _buffer = new Object*[10];
      _capacity = 10;
      _front_index = 0;
      _back_index = 0;
      _size = 0;
    }

    // The Destructor
    virtual ~StrQueue() {
      delete[] _buffer;
    }

    // adds the given object to the beginning of this queue.
    // undefined behavior: the same pointer is pushed more than once or o is this
    virtual void push(Object* o) {
      if(_size + 1 >= _capacity){
          Object **_new_buf = new Object*[_capacity * 2];
          size_t new_index = 0;
          size_t old_index = _front_index;
          while(new_index < _size){
              _new_buf[new_index] = _buffer[old_index];
              old_index = (old_index + 1) % _capacity;
              new_index++;
          }
          _capacity *= 2;
          _front_index = 0;
          _back_index = _size;
          delete[] _buffer;
          _buffer = _new_buf;
      }

      _buffer[_back_index] = o;
      _back_index = (_back_index + 1) % _capacity;
      _size++;
    }

    // removes and returns the object at the end of this queue.
    // errors if there is nothing in the queue
    virtual Object* pop() {
      assert(_size > 0);
      Object *output = _buffer[_front_index];
      _buffer[_front_index] = nullptr;
      _front_index = (_front_index + 1) % _capacity;
      _size--;
      return output;
    }

    // returns the object at the end of this queue but does not remove it.
    // errors if there is nothing in the queue
    virtual Object* peek() {
      assert(_size > 0);
      return _buffer[_front_index];
    }

    // gives the total number of elements in this StrQueue
    virtual size_t len() {
      return _size;
    }

    // true if o is a queue and all of the elements of this queue,
    // in the same order, are equal to o's
    virtual bool equals(Object *other) {
        StrQueue *q_ptr = dynamic_cast<StrQueue *>(other);
        if(q_ptr && q_ptr->len() == _size){
            size_t i = _front_index;
            size_t j = q_ptr->_front_index;
            size_t count = 0;
            while(count < _size){
                if(!_buffer[i]->equals(q_ptr->_buffer[j])){
                    return false;
                }
                i = (i + 1) % _capacity;
                j = (j + 1) % q_ptr->_capacity;
                count++;
            }
            return true;
        }
        return false;
    }

    // hash of this queue
    virtual size_t hash() {
        size_t hash = this->_size;
        size_t index = _front_index;
        size_t count = 0;
        while(count < _size){
            hash += _buffer[index]->hash();
            index = (index + 1) % _capacity;
            count++;
        }
        return hash;
    }
};
