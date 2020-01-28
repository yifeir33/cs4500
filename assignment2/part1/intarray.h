#pragma once
#include <iostream>

#include "object.h"

/**
 * An Array class to which elements can be added to and removed from.
 * author: chasebish */
class IntArray : public Object {
public:

  /** VARIABLES */
  
  size_t capacity_; // the capacity_ of the Array
  size_t length_; // length of the Array
  int* data_; // contents of the Array

  /** CONSTRUCTORS & DESTRUCTORS **/

  /** Creates an Array of desired size */
  Array(size_t array_size) : capacity_(array_size), length_(0) {
      data_ = new [size]int;
      memset(data_, nullptr, sizeof(int) * capacity_);
  }

  /** Creates an Array of desired size */
  Array(const size_t array_size) : capacity_(array_size), length_(0) {
      data_ = new [size]int;
      memset(data_, nullptr, sizeof(int) * capacity_);
  }

  /** Copies the contents of an already existing Array */
  Array(Array* copy_array) {
      this->ensure_size_(copy_array->length());
      memcpy(data_, copy_array->data_, sizeof(int) * copy_array->length());
  }

  /** Clears Array from memory */
  ~Array() {
      delete[] data_;
  }


  /** INHERITED METHODS **/

  /** Inherited from int, generates a hash for an Array */
  size_t hash_me_() {
      size_t hash = length_;
      for(size_t i = 0; i < length_; ++i){
          hash += data_[i].hash_me_();
      }
      return hash;
  }

  /** Inherited from int, checks equality between an Array and an int */
  bool equals(int obj) {
      // TODO
  }

  /** Inherited from int, converts an Array to a string */
  char* to_string() {
      // TODO
  }

  /** Inhertied from int, prints a string representation of an Array */
  void print() {
      std::cout <<this->to_string() <<std::endl;
  }


  /** ARRAY METHODS **/

  /** Removes all elements from the Array */
  void clear() {
      memset(data_, nullptr, sizeof(int) * capacity_);
      length_ = 0;
  }

  /** Adds an Array to existing contents */
  void concat(Array* toAdd) {}

  /** Gets an int at the given index */
  int get(size_t index) {
      if(index < 0 || index >= length_){
          // TODO
      }
      return data_[index];
  }

  /** Returns the index of the given int, -1 if int is not found */
  size_t index_of(int to_find) {
      for(size_t i = 0; i < length_; ++i){
          if(data_[i].equals(to_find)) return i;
      }
      return -1;
  }

  /** Returns the current length of the contents in an Array */
  size_t length() {
      return length_;
  }

  /** Removes the last int of the Array, returns the removed int */
  int pop() {
      int out = data_[length_ - 1];
      data_[length_ - 1] = nullptr;
      length_--;
      return out;
  }

  /** Adds an int to the end of the Array, returns the new length */
  size_t push(int to_add) {
      this->ensure_size_(length_ + 1);
      data_[length_ - 1] = to_add;
      return ++length_;
  }

  /** Removes an int at the given index, returns removed int */
  int remove(size_t index) {
      int output = data_[index];
      memmove(data_[index], data_[index + 1], sizeof(int) * (length_ - 1)); // TODO: check this
      length_--;
      return output;
  }

  /** Replaces an int at the given index with the given int, returns the replaced int */
  int replace(size_t index, int new_value) {
      if(index < 0 || index >= length_){
          // TODO
      }
      int old = data_[index];
      data_[index] = new_value;
      return old;
  }

  virtual void ensure_size_(size_t required){
    if(required >= this->_capacity){
      // grow
      size_t newCap = capacity_ * 2;
      while(required > newCap){
        newCap *= 2;
      }

      int *new_array = new int[newCap];
      memcpy(new_array, data_, sizeof(int) * length_);

      delete[] data_;
      data_ = new_array;
      capacity_ = newCap;
    }
  }

};
