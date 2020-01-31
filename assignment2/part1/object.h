#pragma once

#include <stdlib.h>

/**
 * Object : This class a base object.
 *
 * Author: resnik.n@husky.neu.edu & wang.yifei3@husky.neu.edu
 */
class Object {
public:
    Object(){};

    virtual ~Object(){};
    /** Returns true if this is the same object, false otherwise.
     *
     * @arg o - The object to compare.
     */
    virtual bool equals(Object* o){ return this == o; };

    /** Returns a unique identifier for each object */;
    virtual size_t hash(){ return reinterpret_cast<size_t>(this); };
};
