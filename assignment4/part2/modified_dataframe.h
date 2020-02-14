#pragma once

#include <thread>
#include <mutex>

#include "../object.h"
#include "../string.h"
#include "../part1/dataframe.h"
#include "../part1/column.h"
#include "../part1/schema.h"
#include "../part1/row.h"
#include "../part1/rower.h"

#define MAX_THREADS 8
#define THREAD_ROWS 5000

/****************************************************************************
 * DataFrame::
 *
 * A DataFrame is table composed of columns of equal length. Each column
 * holds values of the same type (I, S, B, F). A dataframe has a schema that
 * describes it.
 */
class ModifiedDataFrame : public DataFrame {
public:
    /** Create a data frame with the same columns as the given df but with no rows or rownmaes */
    ModifiedDataFrame(DataFrame& df) : DataFrame(df.get_schema()) {}

    /** Create a data frame from a schema and columns. All columns are created
    * empty. */
    ModifiedDataFrame(Schema& schema) : DataFrame(schema) {}

    /** This method is used to execute a map in parallel. The row_start
     * is the starting row for the rower in this thread, the row_end is
     * the non-inclusive end row for the rower in this thread. This method
     * should be passed to a thread as the method it is executing.
     *
     * If the rower is mutating shared objects or data, it must 
     * do that in a thread safe manner internally, or reults are
     * undefined behavior.
     */
    void _pmap_helper(size_t thread, size_t row_start, size_t row_end, Rower *rower) {
        for(size_t r = row_start; r < row_end; ++r) {
            Row row(_schema);
            this->fill_row(r, row);
            rower->accept(row);
        }
    }

    /** This method clones the Rower and executes the map in parallel. Join is
      * used at the end to merge the results. */
    void pmap(Rower& r) {
        size_t row_cnt = this->nrows();
        // decide how many threads to use
        size_t thread_cnt = row_cnt / THREAD_ROWS;
        if(thread_cnt <= 1){
            // don't bother multi-threading, it will be faster to single thread
            this->map(r);
            return;
        }
        size_t step_size = THREAD_ROWS;
        if(thread_cnt > MAX_THREADS) {
            thread_cnt = MAX_THREADS;
            step_size = row_cnt / thread_cnt;
        }

        Rower **rowers = new Rower*[thread_cnt];
        rowers[0] = &r;
        for(size_t i = 1; i < thread_cnt; ++i){
            rowers[i] = static_cast<Rower*>(r.clone());
            if(i == 1 && !rowers[i]){
                // clone failed - fallback to single threading
                delete[] rowers;
                map(r);
                return;
            } else {
                assert(rowers[i]); // make sure clone suceeds
            }
        }

        std::thread **threads = new std::thread*[thread_cnt];

        // run multi-threaded
        size_t row_start = 0;
        for(size_t i = 0; i < thread_cnt; ++i) {
            // figure out bounds
            size_t row_end = (i == (thread_cnt - 1)) ? this->nrows() : row_start + step_size;
            assert(row_end <= row_cnt);
            threads[i] = new std::thread(&ModifiedDataFrame::_pmap_helper, this, i, row_start, row_end, rowers[i]);
            row_start = row_end;
        }

        // clean-up threads
        for(size_t i = 0; i < thread_cnt; ++i){
            threads[i]->join();
        }
        
        // merge rower results and clean-up allocated memory
        for(size_t i = 1; i < thread_cnt; ++i) {
            rowers[0]->join_delete(rowers[i]);
        }

        for(size_t i = 0; i < thread_cnt; ++i){
            delete threads[i];
        }
        delete[] threads;
        delete[] rowers;
    }
};
