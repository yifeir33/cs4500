// lang:CwC
/*
* Authors: Ryan Heminway (heminway.r@husky.neu.edu), David Tandetnik 
* CS4500 A1 Part 2 (Object definition)
*/
#pragma once

/*
* Base class for all objects in CwC. This object has no fields and 
* is therefore immutable. 
*/
class Object {
   public:
    Object() {}

    virtual ~Object() {}

    // Compute and return the hash value of this object. Hash values
    // of equal objects should be the same.
    unsigned int hash() {}

    // Return a bool representing whether this Object is equivalent
    // to the given Object.
    virtual bool equals(Object* other) {}

    // Return a character array describing this object. Expected to be
    // re-implemented by subclasses.
    virtual char* to_string() {}
};
