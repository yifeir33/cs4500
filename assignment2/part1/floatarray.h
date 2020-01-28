#pragma once
#include <iostream>

#include "object.h"

/**
 * An Array class to which elements can be added to and removed from.
 * author: chasebish */
class FloatArray : public Object {
public:

  /** VARIABLES */
  
  size_t capacity_; // the capacity_ of the Array
  size_t length_; // length of the Array
  float* data_; // contents of the Array

  /** CONSTRUCTORS & DESTRUCTORS **/

  /** Creates an Array of desired size */
  Array(size_t array_size) : capacity_(array_size), length_(0) {
      data_ = new [size]float;
      memset(data_, nullptr, sizeof(float) * capacity_);
  }

  /** Creates an Array of desired size */
  Array(const size_t array_size) : capacity_(array_size), length_(0) {
      data_ = new [size]float;
      memset(data_, nullptr, sizeof(float) * capacity_);
  }

  /** Copies the contents of an already existing Array */
  Array(Array* copy_array) {
      this->ensure_size_(copy_array->length());
      memcpy(data_, copy_array->data_, sizeof(float) * copy_array->length());
  }

  /** Clears Array from memory */
  ~Array() {
      delete[] data_;
  }


  /** INHERITED METHODS **/

  /** Inherited from float, generates a hash for an Array */
  size_t hash_me_() {
      size_t hash = length_;
      for(size_t i = 0; i < length_; ++i){
          hash += data_[i].hash_me_();
      }
      return hash;
  }

  /** Inherited from float, checks equality between an Array and an float */
  bool equals(float obj) {
      // TODO
  }

  /** Inherited from float, converts an Array to a string */
  char* to_string() {
      // TODO
  }

  /** Inhertied from float, prfloats a string representation of an Array */
  void prfloat() {
      std::cout <<this->to_string() <<std::endl;
  }


  /** ARRAY METHODS **/

  /** Removes all elements from the Array */
  void clear() {
      memset(data_, nullptr, sizeof(float) * capacity_);
      length_ = 0;
  }

  /** Adds an Array to existing contents */
  void concat(Array* toAdd) {}

  /** Gets an float at the given index */
  float get(size_t index) {
      if(index < 0 || index >= length_){
          // TODO
      }
      return data_[index];
  }

  /** Returns the index of the given float, -1 if float is not found */
  size_t index_of(float to_find) {
      for(size_t i = 0; i < length_; ++i){
          if(data_[i].equals(to_find)) return i;
      }
      return -1;
  }

  /** Returns the current length of the contents in an Array */
  size_t length() {
      return length_;
  }

  /** Removes the last float of the Array, returns the removed float */
  float pop() {
      float out = data_[length_ - 1];
      data_[length_ - 1] = nullptr;
      length_--;
      return out;
  }

  /** Adds an float to the end of the Array, returns the new length */
  size_t push(float to_add) {
      this->ensure_size_(length_ + 1);
      data_[length_ - 1] = to_add;
      return ++length_;
  }

  /** Removes an float at the given index, returns removed float */
  float remove(size_t index) {
      float output = data_[index];
      memmove(data_[index], data_[index + 1], sizeof(float) * (length_ - 1)); // TODO: check this
      length_--;
      return output;
  }

  /** Replaces an float at the given index with the given float, returns the replaced float */
  float replace(size_t index, float new_value) {
      if(index < 0 || index >= length_){
          // TODO
      }
      float old = data_[index];
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

      float *new_array = new float[newCap];
      memcpy(new_array, data_, sizeof(float) * length_);

      delete[] data_;
      data_ = new_array;
      capacity_ = newCap;
    }
  }

};
