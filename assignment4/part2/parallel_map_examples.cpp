#include <thread>
#include <mutex>
#include <chrono>

#include <assert.h>
#include <stdlib.h>

#include "modified_dataframe.h"
#include "test_util.h"
#include "prowers.h"

#define LOOPS 100

#define SIZE_ONE    100000
#define SIZE_TWO    1000000
#define SIZE_THREE  10000000




void benchmark1() {
    Schema s("IIIII");

    for(int i = 0; i < 3; ++i) {
        size_t multi_thread_faster = 0;
        double avg_speedup = 0;

        size_t ROWS = 0;
        if(i == 0){
            ROWS = SIZE_ONE;
        }else if(i == 1){
            ROWS = SIZE_TWO;
        }else{
            ROWS = SIZE_THREE;
        }

        for(int j = 0; j < LOOPS; ++j){
            ModifiedDataFrame *mdf = new ModifiedDataFrame(s);
            assert(generate_large_dataframe(*mdf, ROWS, nullptr));
            IntSumRower isr;

            auto single_thread_start = std::chrono::high_resolution_clock::now();
            mdf->map(isr);
            auto single_thread_end = std::chrono::high_resolution_clock::now();
            size_t single_thread_time = std::chrono::duration_cast<std::chrono::milliseconds>(single_thread_end - single_thread_start).count(); 

            size_t single_thread_result = isr.get_sum();

            isr.reset();

            auto multi_thread_start = std::chrono::high_resolution_clock::now();
            mdf->pmap(isr);
            auto multi_thread_end = std::chrono::high_resolution_clock::now();
            size_t multi_thread_time = std::chrono::duration_cast<std::chrono::milliseconds>(multi_thread_end - multi_thread_start).count(); 

            size_t multi_thread_result = isr.get_sum();

            assert(single_thread_result == multi_thread_result);

            if(multi_thread_time >= single_thread_time) {
                ++multi_thread_faster;
                avg_speedup += (multi_thread_time / single_thread_time);
            }
            delete mdf;
        }
        std::cout <<"Dataframe Size: " <<ROWS <<std::endl;
        std::cout <<"Times Multi-Threaded was faster: " <<multi_thread_faster <<"/" <<LOOPS <<std::endl;
        std::cout <<"Average Speedup: " <<(avg_speedup / LOOPS) <<std::endl;
    }
}


void benchmark2() {
    Schema s("SIFSS");

    for(int i = 0; i < 3; ++i) {
        size_t multi_thread_faster = 0;
        double avg_speedup = 0;

        size_t ROWS = 0;
        if(i == 0){
            ROWS = SIZE_ONE;
        }else if(i == 1){
            ROWS = SIZE_TWO;
        }else{
            ROWS = SIZE_THREE;
        }

        for(int i = 0; i < LOOPS; ++i){
            ModifiedDataFrame *mdf = new ModifiedDataFrame(s);
            assert(generate_large_dataframe(*mdf, ROWS, nullptr));

            StringCleanupRower srr1(*mdf);
            auto single_thread_start = std::chrono::high_resolution_clock::now();
            mdf->map(srr1);
            auto single_thread_end = std::chrono::high_resolution_clock::now();
            size_t single_thread_time = std::chrono::duration_cast<std::chrono::milliseconds>(single_thread_end - single_thread_start).count(); 

            delete mdf;
            mdf = new ModifiedDataFrame(s);
            assert(generate_large_dataframe(*mdf, 1000000, nullptr));

            StringCleanupRower srr2(*mdf);
            auto multi_thread_start = std::chrono::high_resolution_clock::now();
            mdf->pmap(srr2);
            auto multi_thread_end = std::chrono::high_resolution_clock::now();
            size_t multi_thread_time = std::chrono::duration_cast<std::chrono::milliseconds>(multi_thread_end - multi_thread_start).count(); 

            if(multi_thread_time >= single_thread_time) {
                ++multi_thread_faster;
            } else {
                ++single_thread_time;
            }
            delete mdf;
        }
        std::cout <<"Dataframe Size: " <<ROWS <<std::endl;
        std::cout <<"Times Multi-Threaded was faster: " <<multi_thread_faster <<"/" <<LOOPS <<std::endl;
        std::cout <<"Average Speedup: " <<avg_speedup <<std::endl;
    }
}


int main(int argc, char **argv) {
    benchmark1();
    benchmark2();
}
