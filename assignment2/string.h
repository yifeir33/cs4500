// lang:CwC
/*
* Authors: Ryan Heminway (heminway.r@husky.neu.edu), David Tandetnik 
* CS4500 A1 Part 2 (String definition)
*/
#pragma once
#include "object.h"

/*
    String represents a wrapper around a character array.
*/
class String : public Object {
   public:
    String() {}

    // Create a String given an existing char array
    String(char* s) {}

    // Create a String given a c string
    String(const char* s) {}

    // Copy constructor given an existing String
    String(String* s) {}

    ~String() {}

    // Returns whether this String is equal to given object o
    virtual bool equals(Object* o) {}

    // Returns length of this string
    virtual unsigned int size() {}

    // Returns whether this string should come alphanumerically before another string
    virtual bool compare(String* other) {}

    // Returns concatenation of given string to this string
    String* concat(String* s) {}
};
