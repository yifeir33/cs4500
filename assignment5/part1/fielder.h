#pragma once

#include "../part1/object.h"
#include "../part1/string.h"
#include "../part1/helper.h"

/*****************************************************************************
 * Fielder::
 * A field vistor invoked by Row.
 */
class Fielder : public Object {
public:

    /** Called before visiting a row, the argument is the row offset in the
    dataframe. */
    virtual void start(size_t r){}

    /** Called for fields of the argument's type with the value of the field. */
    virtual void accept(bool b){}
    virtual void accept(float f){}
    virtual void accept(int i){}
    virtual void accept(String* s){}

    /** Called when all fields have been seen. */
    virtual void done(){}

    virtual size_t hash_me() {
        return 1000;
    }
};
