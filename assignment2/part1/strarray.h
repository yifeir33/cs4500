#pragma once

#include "array.h"

// TODO: composition or inheritance?
class StrArray : public Object {
public:
  Array array_;

  Array(size_t array_size) : array_(array_size) {}

  /** Creates an Array of desired size */
  Array(const size_t array_size) : array_(array_size) {}

  /** Copies the contents of an already existing Array */
  Array(StrArray* copy_array) : array_(copy_array.length()) {
    for(int i =0; i < copy_array.length(); ++i){
      array_.push(copy_array.get(i));
    }
  }

  /** Clears Array from memory */
  ~Array() {} // TODO


  /** INHERITED METHODS **/

  /** Inherited from Object, generates a hash for an Array */
  size_t hash_me_() {
    return array_.hash_me_();
  }

  /** Inherited from Object, checks equality between an Array and an Object */
  bool equals(Object* obj) {
      // TODO
  }

  /** Inherited from Object, converts an Array to a string */
  char* to_string() {
      // TODO
  }

  /** Inhertied from Object, prints a string representation of an Array */
  void print() {
      std::cout <<this->to_string() <<std::endl;
  }


  /** ARRAY METHODS **/

  /** Removes all elements from the Array */
  void clear() {
    array_.clear();
  }

  /** Adds an Array to existing contents */
  void concat(Array* toAdd) {
    // TODO
  }

  /** Gets an Object at the given index */
  String* get(size_t index) {
    return static_cast<String*>(array_.get(index));
  }

  /** Returns the index of the given Object, -1 if Object is not found */
  size_t index_of(String* to_find) {
    return array_.index_of(to_find);
  }

  /** Returns the current length of the contents in an Array */
  size_t length() {
    return array_.length();
  }

  /** Removes the last Object of the Array, returns the removed Object */
  String* pop() {
    return static_cast<String*>(array_.pop());
  }

  /** Adds an Object to the end of the Array, returns the new length */
  size_t push(String* to_add) {
    array_.push(to_add);
  }

  /** Removes an Object at the given index, returns removed Object */
  String* remove(size_t index) {
    return static_cast<String*>(array_.remove(index));
  }

  /** Replaces an Object at the given index with the given Object, returns the replaced Object */
  String* replace(size_t index, String* new_value) {
    return static_cast<String*>(array_.replace(index, new_value));
  }
}
