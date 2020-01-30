#pragma once
#include <iostream>
#include <string.h>

#include "object.h"

/**
 * An Array class to which elements can be added to and removed from.
 * author: chasebish */
class Array : public Object {
public:

  /** VARIABLES */
  
  size_t capacity_; // the capacity_ of the Array
  size_t length_; // length of the Array
  Object** data_; // contents of the Array

  /** CONSTRUCTORS & DESTRUCTORS **/

  /** Creates an Array of desired size */
  /* Array(size_t array_size) : capacity_(array_size), length_(0) { */
  /*     data_ = new Object*[capacity_]; */
  /*     memset(data_, nullptr, sizeof(Object*) * capacity_); */
  /* } */

  /** Creates an Array of desired size */
  Array(const size_t array_size) : capacity_(array_size), length_(0) {
      data_ = new Object*[capacity_];
      memset(data_, nullptr, sizeof(Object*) * capacity_);
  }

  /** Copies the contents of an already existing Array */
  Array(Array* copy_array) {
      this->ensure_size_(copy_array->length());
      memcpy(data_, copy_array->data_, sizeof(Object*) * copy_array->length());
  }

  /** Clears Array from memory */
  ~Array() {
      delete[] data_;
  }


  /** INHERITED METHODS **/

  /** Inherited from Object, generates a hash for an Array */
  size_t hash() {
      size_t hash = length_;
      for(size_t i = 0; i < length_; ++i){
          hash += data_[i]->hash();
      }
      return hash;
  }

  /** Inherited from Object, checks equality between an Array and an Object */
  bool equals(Object* obj) {
      // TODO
      return true;
  }

  /** Inherited from Object, converts an Array to a string */
  char* to_string() {
      // TODO
      return "";
  }

  /** Inhertied from Object, prints a string representation of an Array */
  void print() {
      std::cout <<this->to_string() <<std::endl;
  }


  /** ARRAY METHODS **/

  /** Removes all elements from the Array */
  void clear() {
      memset(data_, nullptr, sizeof(Object*) * capacity_);
      length_ = 0;
  }

  /** Adds an Array to existing contents */
  void concat(Array* toAdd) {}

  /** Gets an Object at the given index */
  Object* get(size_t index) {
      if(index < 0 || index >= length_){
          // TODO
      }
      return data_[index];
  }

  /** Returns the index of the given Object, -1 if Object is not found */
  size_t index_of(Object* to_find) {
      for(size_t i = 0; i < length_; ++i){
          if(data_[i]->equals(to_find)) return i;
      }
      return -1;
  }

  /** Returns the current length of the contents in an Array */
  size_t length() {
      return length_;
  }

  /** Removes the last Object of the Array, returns the removed Object */
  Object* pop() {
      Object *out = data_[length_ - 1];
      data_[length_ - 1] = nullptr;
      length_--;
      return out;
  }

  /** Adds an Object to the end of the Array, returns the new length */
  size_t push(Object* to_add) {
      this->ensure_size_(length_ + 1);
      data_[length_] = to_add;
      return ++length_;
  }

  /** Removes an Object at the given index, returns removed Object */
  Object* remove(size_t index) {
      Object *output = data_[index];
      memmove(data_[index], data_[index + 1], sizeof(Object*) * (length_ - 1)); // TODO: check this
      length_--;
      return output;
  }

  /** Replaces an Object at the given index with the given Object, returns the replaced Object */
  Object* replace(size_t index, Object* new_value) {
      if(index < 0 || index >= length_){
          // TODO
      }
      Object *old = data_[index];
      data_[index] = new_value;
      return old;
  }

  virtual void ensure_size_(size_t required){
    if(required >= this->capacity_){
      // grow
      size_t newCap = capacity_ * 2;
      while(required > newCap){
        newCap *= 2;
      }

      Object **new_array = new Object*[newCap];
      memcpy(new_array, data_, sizeof(Object*) * length_);

      delete[] data_;
      data_ = new_array;
      capacity_ = newCap;
    }
  }
};

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
  /* Array(size_t array_size) : capacity_(array_size), length_(0) { */
  /*     data_ = new bool[capacity_]; */
  /*     memset(data_, nullptr, sizeof(Object*) * capacity_); */
  /* } */

  /** Creates an Array of desired size */
  BoolArray(const size_t array_size) : capacity_(array_size), length_(0) {
      data_ = new bool[capacity_];
      memset(data_, false, sizeof(bool) * capacity_);
  }

  /** Copies the contents of an already existing Array */
  BoolArray(BoolArray* copy_array) {
      this->ensure_size_(copy_array->length());
      memcpy(data_, copy_array->data_, sizeof(bool) * copy_array->length());
  }

  /** Clears Array from memory */
  ~BoolArray() {
      delete[] data_;
  }


  /** INHERITED METHODS **/

  /** Inherited from Object, generates a hash for an Array */
  size_t hash() {
      size_t hash = length_;
      for(size_t i = 0; i < length_; ++i){
          hash += data_[i];
      }
      return hash;
  }

  /** Inherited from Object, checks equality between an Array and an Object */
  bool equals(Object* obj) {
      // TODO
      return true;
  }

  /** Inherited from Object, converts an Array to a string */
  char* to_string() {
      // TODO
      return "";
  }

  /** Inhertied from Object, prints a string representation of an Array */
  void print() {
      std::cout <<this->to_string() <<std::endl;
  }


  /** ARRAY METHODS **/

  /** Removes all elements from the Array */
  void clear() {
      memset(data_, false, sizeof(bool) * capacity_);
      length_ = 0;
  }

  /** Adds an Array to existing contents */
  void concat(Array* toAdd) {}

  /** Gets an Object at the given index */
  bool get(size_t index) {
      if(index < 0 || index >= length_){
          // TODO
      }
      return data_[index];
  }

  /** Returns the index of the given Object, -1 if Object is not found */
  size_t index_of(bool to_find) {
      for(size_t i = 0; i < length_; ++i){
          if(data_[i] == to_find) return i;
      }
      return -1;
  }

  /** Returns the current length of the contents in an Array */
  size_t length() {
      return length_;
  }

  /** Removes the last Object of the Array, returns the removed Object */
  bool pop() {
      bool out = data_[length_ - 1];
      length_--;
      return out;
  }

  /** Adds an Object to the end of the Array, returns the new length */
  size_t push(bool to_add) {
      this->ensure_size_(length_ + 1);
      data_[length_] = to_add;
      return ++length_;
  }

  /** Removes an Object at the given index, returns removed Object */
  bool remove(size_t index) {
      bool output = data_[index];
      memmove(data_[index], data_[index + 1], sizeof(bool) * (length_ - 1)); // TODO: check this
      length_--;
      return output;
  }

  /** Replaces an Object at the given index with the given Object, returns the replaced Object */
  bool replace(size_t index, bool new_value) {
      if(index < 0 || index >= length_){
          // TODO
      }
      bool old = data_[index];
      data_[index] = new_value;
      return old;
  }

  virtual void ensure_size_(size_t required){
    if(required >= this->capacity_){
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
    /* Array(size_t array_size) : capacity_(array_size), length_(0) { */
    /*     data_ = new float[capacity_]; */
    /*     memset(data_, nullptr, sizeof(Object*) * capacity_); */
    /* } */

    /** Creates an Array of desired size */
    FloatArray(const size_t array_size) : capacity_(array_size), length_(0) {
        data_ = new float[capacity_];
        memset(data_, 0, sizeof(float) * capacity_);
    }

    /** Copies the contents of an already existing Array */
    FloatArray(BoolArray* copy_array) {
        this->ensure_size_(copy_array->length());
        memcpy(data_, copy_array->data_, sizeof(float) * copy_array->length());
    }

    /** Clears Array from memory */
    ~FloatArray() {
        delete[] data_;
    }


    /** INHERITED METHODS **/

    /** Inherited from Object, generates a hash for an Array */
    size_t hash() {
        size_t hash = length_;
        for(size_t i = 0; i < length_; ++i){
            hash += data_[i];
        }
        return hash;
    }

    /** Inherited from Object, checks equality between an Array and an Object */
    float equals(Object* obj) {
        // TODO
        return true;
    }

    /** Inherited from Object, converts an Array to a string */
    char* to_string() {
        // TODO
        return "";
    }

    /** Inhertied from Object, prints a string representation of an Array */
    void print() {
        std::cout <<this->to_string() <<std::endl;
    }


    /** ARRAY METHODS **/

    /** Removes all elements from the Array */
    void clear() {
        memset(data_, 0, sizeof(float) * capacity_);
        length_ = 0;
    }

    /** Adds an Array to existing contents */
    void concat(Array* toAdd) {}

    /** Gets an Object at the given index */
    float get(size_t index) {
        if(index < 0 || index >= length_){
            // TODO
        }
        return data_[index];
    }

    /** Returns the index of the given Object, -1 if Object is not found */
    size_t index_of(float to_find) {
        for(size_t i = 0; i < length_; ++i){
            if(data_[i] == to_find) return i;
        }
        return -1;
    }

    /** Returns the current length of the contents in an Array */
    size_t length() {
        return length_;
    }

    /** Removes the last Object of the Array, returns the removed Object */
    float pop() {
        float out = data_[length_ - 1];
        length_--;
        return out;
    }

    /** Adds an Object to the end of the Array, returns the new length */
    size_t push(float to_add) {
        this->ensure_size_(length_ + 1);
        data_[length_] = to_add;
        return ++length_;
    }

    /** Removes an Object at the given index, returns removed Object */
    float remove(size_t index) {
        float output = data_[index];
        memmove(data_[index], data_[index + 1], sizeof(float) * (length_ - 1)); // TODO: check this
        length_--;
        return output;
    }

    /** Replaces an Object at the given index with the given Object, returns the replaced Object */
    float replace(size_t index, float new_value) {
        if(index < 0 || index >= length_){
            // TODO
        }
        float old = data_[index];
        data_[index] = new_value;
        return old;
    }

    virtual void ensure_size_(size_t required){
      if(required >= this->capacity_){
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
  /* Array(size_t array_size) : capacity_(array_size), length_(0) { */
  /*     data_ = new [size]int; */
  /*     memset(data_, nullptr, sizeof(int) * capacity_); */
  /* } */

  /** Creates an Array of desired size */
  IntArray(const size_t array_size) : capacity_(array_size), length_(0) {
      data_ = new int[capacity_];
      memset(data_, 0, sizeof(int) * capacity_);
  }

  /** Copies the contents of an already existing Array */
  IntArray(Array* copy_array) {
      this->ensure_size_(copy_array->length());
      memcpy(data_, copy_array->data_, sizeof(int) * copy_array->length());
  }

  /** Clears Array from memory */
  ~IntArray() {
      delete[] data_;
  }


  /** INHERITED METHODS **/

  /** Inherited from int, generates a hash for an Array */
  size_t hash() {
      size_t hash = length_;
      for(size_t i = 0; i < length_; ++i){
          hash += data_[i];
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
      memset(data_, 0, sizeof(int) * capacity_);
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
          if(data_[i] == to_find) return i;
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
      /* data_[length_ - 1] = nullptr; */
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

/**
 * An Array class to which elements can be added to and removed from.
 * author: chasebish */
class StringArray : public String {
public:

  /** VARIABLES */
  
  size_t capacity_; // the capacity_ of the Array
  size_t length_; // length of the Array
  String** data_; // contents of the Array

  /** CONSTRUCTORS & DESTRUCTORS **/

  /** Creates an Array of desired size */
  /* Array(size_t array_size) : capacity_(array_size), length_(0) { */
  /*     data_ = new String*[capacity_]; */
  /*     memset(data_, nullptr, sizeof(String*) * capacity_); */
  /* } */

  /** Creates an Array of desired size */
  StringArray(const size_t array_size) : capacity_(array_size), length_(0) {
      data_ = new String*[capacity_];
      memset(data_, nullptr, sizeof(String*) * capacity_);
  }

  /** Copies the contents of an already existing Array */
  StringArray(Array* copy_array) {
      this->ensure_size_(copy_array->length());
      memcpy(data_, copy_array->data_, sizeof(String*) * copy_array->length());
  }

  /** Clears Array from memory */
  ~StringArray() {
      delete[] data_;
  }


  /** INHERITED METHODS **/

  /** Inherited from String, generates a hash for an Array */
  size_t hash() {
      size_t hash = length_;
      for(size_t i = 0; i < length_; ++i){
          hash += data_[i]->hash();
      }
      return hash;
  }

  /** Inherited from String, checks equality between an Array and an String */
  bool equals(String* obj) {
      // TODO
      return true;
  }

  /** Inherited from String, converts an Array to a string */
  char* to_string() {
      // TODO
      return "";
  }

  /** Inhertied from String, prints a string representation of an Array */
  void print() {
      std::cout <<this->to_string() <<std::endl;
  }


  /** ARRAY METHODS **/

  /** Removes all elements from the Array */
  void clear() {
      memset(data_, nullptr, sizeof(String*) * capacity_);
      length_ = 0;
  }

  /** Adds an Array to existing contents */
  void concat(Array* toAdd) {}

  /** Gets an String at the given index */
  String* get(size_t index) {
      if(index < 0 || index >= length_){
          // TODO
      }
      return data_[index];
  }

  /** Returns the index of the given String, -1 if String is not found */
  size_t index_of(String* to_find) {
      for(size_t i = 0; i < length_; ++i){
          if(data_[i]->equals(to_find)) return i;
      }
      return -1;
  }

  /** Returns the current length of the contents in an Array */
  size_t length() {
      return length_;
  }

  /** Removes the last String of the Array, returns the removed String */
  String* pop() {
      String *out = data_[length_ - 1];
      data_[length_ - 1] = nullptr;
      length_--;
      return out;
  }

  /** Adds an String to the end of the Array, returns the new length */
  size_t push(String* to_add) {
      this->ensure_size_(length_ + 1);
      data_[length_] = to_add;
      return ++length_;
  }

  /** Removes an String at the given index, returns removed String */
  String* remove(size_t index) {
      String *output = data_[index];
      memmove(data_[index], data_[index + 1], sizeof(String*) * (length_ - 1)); // TODO: check this
      length_--;
      return output;
  }

  /** Replaces an String at the given index with the given String, returns the replaced String */
  String* replace(size_t index, String* new_value) {
      if(index < 0 || index >= length_){
          // TODO
      }
      String *old = data_[index];
      data_[index] = new_value;
      return old;
  }

  virtual void ensure_size_(size_t required){
    if(required >= this->capacity_){
      // grow
      size_t newCap = capacity_ * 2;
      while(required > newCap){
        newCap *= 2;
      }

      String **new_array = new String*[newCap];
      memcpy(new_array, data_, sizeof(String*) * length_);

      delete[] data_;
      data_ = new_array;
      capacity_ = newCap;
    }
  }
};
