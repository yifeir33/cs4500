#include <gtest/gtest.h>
#include "dataframe.h"

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")


/**
 * test on rows
 */
void test4() {
    String* allen1 = new String("allen");
    String* jack1 = new String("jack");
    //create schema and test row
    Schema s0("SIFB");
    Row r0(s0);
    r0.set(0,allen1);
    r0.set(1,33);
    r0.set(2,(float)170.2);
    r0.set(3,1);
    r0.set_index(0);
    GT_EQUALS(r0.get_index(), 0);
    GT_EQUALS(r0.get_bool(3), 1);
    GT_EQUALS(r0.get_int(1), 33);
    GT_EQUALS(r0.get_string(0), allen1);
    GT_EQUALS(r0.get_float(2), (float)170.2 );
    GT_EQUALS(r0.width() , 4);
    GT_EQUALS(r0.col_type(0), "S");
    GT_EQUALS(r0.col_type(1), "I");
    GT_EQUALS(r0.col_type(2), "F");
    GT_EQUALS(r0.col_type(3), "B");

    Schema s1("SIFFBB");
    Row r1(s1);
    r1.set(0,"JACK");
    r1.set(1, 22);
    r1.set(2, (float)190.3);
    r1.set(3, (float)11.3);
    r1.set(4, 0);
    r1.set(5,1);
    r1.set_index(1);
    GT_EQUALS(r1.get_index(), 1);
    GT_EQUALS(r1.get_bool(4), 0);
    GT_EQUALS(r1.get_bool(5), 1);
    GT_EQUALS(r1.get_int(1), 22);
    GT_EQUALS(r1.get_string(0), jack1);
    GT_EQUALS(r1.get_float(2), (float)190.3 );
    GT_EQUALS(r1.get_float(3), (float)11.3 );
    GT_EQUALS(r1.width() , 6);
    GT_EQUALS(r0.col_type(0), "S");
    GT_EQUALS(r0.col_type(1), "I");
    GT_EQUALS(r0.col_type(2), "F");
    GT_EQUALS(r0.col_type(3), "F");
    GT_EQUALS(r0.col_type(4), "B");
    GT_EQUALS(r0.col_type(5), "B");

    delete allen1, jack1;

    exit(0);
}

TEST(a4, t1){ ASSERT_EXIT_ZERO(test4); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

