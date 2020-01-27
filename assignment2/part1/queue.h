//lang::CwC
#pragma once

#include "object.h"
#include <cstdlib>

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
      _capacity = size;
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
          memcpy(_new_buf, _buffer, sizeof(Object *) * _capacity);
          _capacity *= 2;
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
      if(_size == 0) {
          // TODO
      }
      Object *output = _buffer[_front_index];
      _buffer[_front_index] = nullptr;
      _front_index = (_front_index + 1) % _capacity;
      _size--;
      return output;
    }

    // returns the object at the end of this queue but does not remove it.
    // errors if there is nothing in the queue
    virtual Object* peek() {
      if(_size == 0) {
          // TODO
      }
      return _buffer[_front_index];
    }

    // gives the total number of elements in this Queue
    virtual size_t len() {
      return _size;
    }

    // true if o is a queue and all of the elements of this queue,
    // in the same order, are equal to o's
    virtual bool equals(Object *other) {
      // TODO
    }

    // hash of this queue
    virtual size_t hash() {
      // TODO
    }
};
