#include <gtest/gtest.h>
#include "modified_dataframe.h" 
#include "prowers.h"
#include "test_util.h"

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")

#define ROWS 1000000

void test1() {
    Schema s("IIFI");
    ModifiedDataFrame mdf(s);
    GT_TRUE(generate_large_dataframe(mdf, 1000000, nullptr));
    // no difference between single and multi threaded
    IntSumRower isr;
    mdf.map(isr);
    size_t single_sum = isr.get_sum();

    isr.reset();

    mdf.pmap(isr);
    size_t multi_sum = isr.get_sum();

    GT_EQUALS(single_sum, multi_sum);
    exit(0);
}

void test2() {
    Schema s("III");
    ModifiedDataFrame mdf(s);
    GT_TRUE(generate_large_dataframe(mdf, 1000000, nullptr));
    // initial has negatives
    NonNegativeRower nnr;
    mdf.pmap(nnr);
    GT_FALSE(nnr.sucessful());

    AbsoluteValueRower avr(mdf);
    mdf.pmap(avr);

    // Now has no negatives
    nnr.reset();
    mdf.pmap(nnr);
    GT_TRUE(nnr.sucessful());
    exit(0);
}


TEST(a4p2, t1){ ASSERT_EXIT_ZERO(test1); }
TEST(a4p2, t2){ ASSERT_EXIT_ZERO(test2); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
