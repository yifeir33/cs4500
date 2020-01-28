//lang::CwC
#pragma once


#include <cstdlib>

#include "object.h"
#include "string.h"
#include "queue.h"
/**
 * Queue: Represents a FIFO data structure.
 *        Capable of holding any Object in the given order.
 *
 * mutable
 *
 * authors: dermer.s@husky.neu.edu && Sarialli.n@northeastern.edu
 */
class StrQueue : public Queue {
public:

    // The Constructor
    Queue() {}

    // The Destructor
    virtual ~Queue() {}

    // adds the given object to the beginning of this queue.
    // undefined behavior: the same pointer is pushed more than once or o is this
    virtual void push(String* o) {
      Queue::push(o);
    }

    // removes and returns the object at the end of this queue.
    // errors if there is nothing in the queue
    virtual String* pop() {
      return dynamic_cast<String*>(Queue::pop());
    }

    // returns the object at the end of this queue but does not remove it.
    // errors if there is nothing in the queue
    virtual String* peek() {
      return dynamic_cast<String*>(Queue::peek());
    }

    // true if o is a queue and all of the elements of this queue,
    // in the same order, are equal to o's
    virtual bool equals(Object *other) {
      Queue *other_q = dynamic_cast<Queue*>(other);
      if(other_q){
        // To be equal the other queue just needs to have the same
        // elements in the same order. The capacity and location in the
        // circular buffer don't need to be the same, hence we have to 
        // iterate over each buffer seperately from tail to head.
        if(other_q->len() == this->len()){
          size_t count = 0;
          size_t this_i = head_index_;
          size_t other_i = other_q->head_index_;
          while(count < len_){
            if(!buffer_[this_i]->equals(other_q->buffer_[other_i])){
              return false;
            }
            count++;
            this_i = (this_i + 1) % capacity_;
            other_i = (other_i + 1) % other->capacity_;
          }
          return true;
        }
      }
      return false;
    }

    // hash of this queue
    virtual size_t hash() {
      // TODO
    }
};
