#include <gtest/gtest.h>
#include "dataframe.h"

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")


//test schema
void test5() {
    Schema sch("");
    String* name = new String("Name");
    String* isMale = new String("isMale");
    String* age = new String("Age");
    String* height = new String("Height");
    String* pT = new String("President Trump");
    String* pX = new String("President Xi");

    sch.add_column('S', name);
    sch.add_column('B', isMale);
    sch.add_column('I', age);
    sch.add_column('F', height);
    sch.add_row(pT);
    sch.add_row(pX);
    GT_EQUALS(sch.row_name(0), pT);
    GT_EQUALS(sch.row_name(1), pX);
    GT_EQUALS(sch.col_name(0), name);
    GT_EQUALS(sch.col_name(1), isMale);
    GT_EQUALS(sch.col_name(2), age);
    GT_EQUALS(sch.col_name(3), height);
    GT_EQUALS(sch.col_type(0), 'S');
    GT_EQUALS(sch.col_type(1), 'B');
    GT_EQUALS(sch.col_type(2), 'I');
    GT_EQUALS(sch.col_type(3), 'F');
    GT_EQUALS(sch.col_idx("Name"), 0);
    GT_EQUALS(sch.col_idx("isMale"), 1);
    GT_EQUALS(sch.col_idx("Age"), 2);
    GT_EQUALS(sch.col_idx("Height"), 3);
    GT_EQUALS(sch.row_idx("President Trump"),0);
    GT_EQUALS(sch.row_idx("President Xi"),1);
    GT_EQUALS(sch.width(),4);
    GT_EQUALS(sch.length(), 2);

    delete name;
    delete isMale;
    delete age;
    delete height;
    delete pT;
    delete pX;

    exit(0);
}

TEST(a4p1, t5){ ASSERT_EXIT_ZERO(test5); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

