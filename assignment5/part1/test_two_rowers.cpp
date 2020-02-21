//
// Created by 王镱霏 on 2/20/20.
//

#include <gtest/gtest.h>
#include "../part1/modified_dataframe.h"
#include "SimpleRower.h"
#include "ComplexRower.h"
#include "txt_reader.cpp"

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")

#define SIZE_ONE    10000
#define SIZE_TWO    100000
#define SIZE_THREE   297432

#define LOOPS 100


void benchmark1() {

    Txt_reader* tx_r = new Txt_reader();

    cout<<"here"<<endl;
    ModifiedDataFrame* mdf = tx_r->output();
    cout<<"here"<<endl;

    for(int i = 0; i < 3; ++i) {
        cout<<"here"<<endl;
        size_t multi_thread_faster = 0;
        double avg_speedup = 0;

        size_t ROWS = 0;
        if (i == 0) {
            ROWS = SIZE_ONE;
        } else if (i == 1) {
            ROWS = SIZE_TWO;
        } else {
            ROWS = SIZE_THREE;
        }

        for(int j = 0; j < LOOPS; ++j){

            //this step should be mdf reads in the dataframe

            SimpleRower sr;

            auto single_thread_start = std::chrono::high_resolution_clock::now();
            mdf->map(sr);
            auto single_thread_end = std::chrono::high_resolution_clock::now();
            size_t single_thread_time = std::chrono::duration_cast<std::chrono::milliseconds>(single_thread_end - single_thread_start).count();

            size_t single_thread_result = sr.get_sofar();

            sr.reset();

            auto multi_thread_start = std::chrono::high_resolution_clock::now();
            mdf->pmap(sr);
            auto multi_thread_end = std::chrono::high_resolution_clock::now();
            size_t multi_thread_time = std::chrono::duration_cast<std::chrono::milliseconds>(multi_thread_end - multi_thread_start).count();

            size_t multi_thread_result = sr.get_sofar();

            assert(single_thread_result == multi_thread_result);

            if(multi_thread_time >= single_thread_time) {
                ++multi_thread_faster;
                avg_speedup += (multi_thread_time / single_thread_time);
            }
            delete mdf;
        }
        std::cout <<"Benchmark 1" <<std::endl;
        std::cout <<"Dataframe Size: " <<ROWS <<std::endl;
        std::cout <<"Times Multi-Threaded was faster: " <<multi_thread_faster <<"/" <<LOOPS <<std::endl;
        std::cout <<"Average Speedup: " <<(avg_speedup / multi_thread_faster) <<std::endl;
    }
    delete tx_r;

}

void benchmark2() {
    Txt_reader* tx_r = new Txt_reader();
    ModifiedDataFrame* mdf = tx_r->output();
    for(int i = 0; i < 3; ++i) {
        size_t multi_thread_faster = 0;
        double avg_speedup = 0;

        size_t ROWS = 0;
        if (i == 0) {
            ROWS = SIZE_ONE;
        } else if (i == 1) {
            ROWS = SIZE_TWO;
        } else {
            ROWS = SIZE_THREE;
        }
        for(int j = 0; j < LOOPS; ++j){


            //this step should be mdf reads in the dataframe
//            assert(generate_large_dataframe(*mdf, ROWS, nullptr));

            ComplexRower cr(mdf->get_schema());

            auto single_thread_start = std::chrono::high_resolution_clock::now();
            mdf->map(cr);
            auto single_thread_end = std::chrono::high_resolution_clock::now();
            size_t single_thread_time = std::chrono::duration_cast<std::chrono::milliseconds>(single_thread_end - single_thread_start).count();

            bool single_thread_result1 = cr.get_bool();
            int single_thread_result2 = cr.get_weather_sum();
            float single_thread_result3 = cr.get_float_sum();
            int single_thread_result4 = cr.get_int_sum();

            cr.reset();

            auto multi_thread_start = std::chrono::high_resolution_clock::now();
            mdf->pmap(cr);
            auto multi_thread_end = std::chrono::high_resolution_clock::now();
            size_t multi_thread_time = std::chrono::duration_cast<std::chrono::milliseconds>(multi_thread_end - multi_thread_start).count();

            bool multi_thread_result1 = cr.get_bool();
            int multi_thread_result2 = cr.get_weather_sum();
            float multi_thread_result3 = cr.get_float_sum();
            int multi_thread_result4 = cr.get_int_sum();

            assert(single_thread_result1 == multi_thread_result1);
            assert(single_thread_result2 == multi_thread_result2);
            assert(single_thread_result3 == multi_thread_result3);
            assert(single_thread_result4 == multi_thread_result4);

            if(multi_thread_time >= single_thread_time) {
                ++multi_thread_faster;
                avg_speedup += (multi_thread_time / single_thread_time);
            }
            delete mdf;
        }
        std::cout <<"Benchmark 2" <<std::endl;
        std::cout <<"Dataframe Size: " <<ROWS <<std::endl;
        std::cout <<"Times Multi-Threaded was faster: " <<multi_thread_faster <<"/" <<LOOPS <<std::endl;
        std::cout <<"Average Speedup: " <<(avg_speedup / multi_thread_faster) <<std::endl;

    }
    delete tx_r;
}


TEST(a5, b1){ ASSERT_EXIT_ZERO(benchmark1); }
TEST(a5, b2){ ASSERT_EXIT_ZERO(benchmark2); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

