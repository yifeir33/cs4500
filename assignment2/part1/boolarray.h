#pragma once
#include <iostream>

#include "object.h"

/**
 * An Array class to which elements can be added to and removed from.
 * author: chasebish */
class BoolArray : public Object {
public:

  /** VARIABLES */
  
  size_t capacity_; // the capacity_ of the Array
  size_t length_; // length of the Array
  bool* data_; // contents of the Array

  /** CONSTRUCTORS & DESTRUCTORS **/

  /** Creates an Array of desired size */
  Array(size_t array_size) : capacity_(array_size), length_(0) {
      data_ = new [size]bool;
      memset(data_, nullptr, sizeof(bool) * capacity_);
  }

  /** Creates an Array of desired size */
  Array(const size_t array_size) : capacity_(array_size), length_(0) {
      data_ = new [size]bool;
      memset(data_, nullptr, sizeof(bool) * capacity_);
  }

  /** Copies the contents of an already existing Array */
  Array(Array* copy_array) {
      this->ensure_size_(copy_array->length());
      memcpy(data_, copy_array->data_, sizeof(bool) * copy_array->length());
  }

  /** Clears Array from memory */
  ~Array() {
      delete[] data_;
  }


  /** INHERITED METHODS **/

  /** Inherited from bool, generates a hash for an Array */
  size_t hash_me_() {
      size_t hash = length_;
      for(size_t i = 0; i < length_; ++i){
          hash += data_[i].hash_me_();
      }
      return hash;
  }

  /** Inherited from bool, checks equality between an Array and an bool */
  bool equals(bool obj) {
      // TODO
  }

  /** Inherited from bool, converts an Array to a string */
  char* to_string() {
      // TODO
  }

  /** Inhertied from bool, prbools a string representation of an Array */
  void prbool() {
      std::cout <<this->to_string() <<std::endl;
  }


  /** ARRAY METHODS **/

  /** Removes all elements from the Array */
  void clear() {
      memset(data_, nullptr, sizeof(bool) * capacity_);
      length_ = 0;
  }

  /** Adds an Array to existing contents */
  void concat(Array* toAdd) {}

  /** Gets an bool at the given index */
  bool get(size_t index) {
      if(index < 0 || index >= length_){
          // TODO
      }
      return data_[index];
  }

  /** Returns the index of the given bool, -1 if bool is not found */
  size_t index_of(bool to_find) {
      for(size_t i = 0; i < length_; ++i){
          if(data_[i].equals(to_find)) return i;
      }
      return -1;
  }

  /** Returns the current length of the contents in an Array */
  size_t length() {
      return length_;
  }

  /** Removes the last bool of the Array, returns the removed bool */
  bool pop() {
      bool out = data_[length_ - 1];
      data_[length_ - 1] = nullptr;
      length_--;
      return out;
  }

  /** Adds an bool to the end of the Array, returns the new length */
  size_t push(bool to_add) {
      this->ensure_size_(length_ + 1);
      data_[length_ - 1] = to_add;
      return ++length_;
  }

  /** Removes an bool at the given index, returns removed bool */
  bool remove(size_t index) {
      bool output = data_[index];
      memmove(data_[index], data_[index + 1], sizeof(bool) * (length_ - 1)); // TODO: check this
      length_--;
      return output;
  }

  /** Replaces an bool at the given index with the given bool, returns the replaced bool */
  bool replace(size_t index, bool new_value) {
      if(index < 0 || index >= length_){
          // TODO
      }
      bool old = data_[index];
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

      bool *new_array = new bool[newCap];
      memcpy(new_array, data_, sizeof(bool) * length_);

      delete[] data_;
      data_ = new_array;
      capacity_ = newCap;
    }
  }

};
