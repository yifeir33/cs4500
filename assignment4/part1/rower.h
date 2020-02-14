#pragma once

#include "../helper.h"
#include "../object.h"
#include "../string.h"
#include "row.h"
#include "fielder.h"

/*******************************************************************************
 *  Rower::
 *  An interface for iterating through each row of a data frame. The intent
 *  is that this class should subclassed and the accept() method be given
 *  a meaningful implementation. Rowers can be cloned for parallel execution.
 */
class Rower : public Object {
public:
    /** This method is called once per row. The row object is on loan and
      should not be retained as it is likely going to be reused in the next
      call. The return value is used in filters to indicate that a row
      should be kept. */
    virtual bool accept(Row& r) {
        return true;
    }

    /** Once traversal of the data frame is complete the rowers that were
      split off will be joined.  There will be one join per split. The
      original object will be the last to be called join on. The join method
      is reponsible for cleaning up memory. */
    virtual void join_delete(Rower* other){
        if(!other || other == this) return;
        delete other;
    }

    virtual size_t hash_me() {
        return 2000;
    }
};


