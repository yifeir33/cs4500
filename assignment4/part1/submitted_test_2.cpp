#include "gtest/gtest.h"
#include <iostream>
#include <string.h>
#include <dataframe.h>

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")



void test2(){
    //set up
    //create a dataframe storage name(String), age(int), height(float), isMale(Bool)

    String* annie1 = new String("Annie");
    String* bo1 = new String("Bo");
    String* jack1 = new String("Jack");
    String* lily1 = new String("Lily");
    String* course1 = new String( "course");
    Schema s1("SIFB");
    DataFrame df(s1);
    Row annie(df.get_schema());
    annie.set(0,annie1);
    annie.set(1,9);
    annie.set(2,(float)160.1);
    annie.set(3,0);

    Row bo(df.get_schema());
    bo.set(0, jack1);
    bo.set(1,20);
    bo.set(2,(float)180.2);
    bo.set(3,1);

    Row jack(df.get_schema());
    jack.set(0,jack1);
    jack.set(1,30);
    jack.set(2,(float)175.6);
    jack.set(3,1);

    Row lily(df.get_schema());
    lily.set(0,lily1);
    lily.set(1,60);
    lily.set(2, (float)165.7);
    lily.set(3,0);

    df.add_row(annie);
    df.add_row(jack);
    df.add_row(bo);
    df.add_row(lily);

    // add a column
    IntColumn* course;
    course->set(0, 1234);
    course->set(1, 1244);
    course->set(2, 1235);
    course->set(3, 3834);
    df.add_column(course, course1);
    GT_EQUALS(df.ncols(), 5);

    delete annie1, bo1, jack1, lily1, course1;

    exit(0);
}

TEST(a4, t2){ ASSERT_EXIT_ZERO(test2);
}

int main(int argc, char * argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}