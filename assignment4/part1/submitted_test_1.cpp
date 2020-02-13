//
// Created by 王镱霏 on 2/12/20.
//

#include "gtest/gtest.h"
#include <iostream>
#include <string.h>
#include <dataframe.h>

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")

void set_up_dataframe(){
    //create a dataframe storage name(String), age(int), height(float), isMale(Bool)
    Schema s1("SIFB")
    DataFrame df(s1);
    Row annie(df.get_schema());
    annie.set(0,"Annie");
    annie.set(1,9);
    annie.set(2,160.1);
    annie.set(3,0);

    Row bo(df.get_schema());
    bo.set(0,"Bo");
    bo.set(1,20);
    bo.set(2,180.2);
    bo.set(3,1);

    Row jack(df.get_schema());
    jack.set(0,"Jack");
    jack.set(1,30);
    jack.set(2,175.6);
    jack.set(3,1);

    Row lily(df.get_schema());
    lily.set(0,"Lily");
    lily.set(1,60);
    lily.set(2,165.7);
    lily.set(3,0);

    df.add_row(annie);
    df.add_row(jack);
    df.add_row(bo);
    df.add_row(lily);
}

void test1(){
    set_up_dataframe();
    Row peter(df.get_schema());
    peter.set(0,"Peter");
    peter.set(1, 18);
    peter.set(2, 183.3);
    peter.set(4, 1);
    df.fill_row(4,peter);
    GT_EQUALS(df.get_int((size_t)0,1), 9);
    GT_EQUALS(df.get_bool((size_t)0,1), nullptr);
    GT_EQUALS(df.get_bool((size_t)0,3), 0);
    GT_EQUALS(df.get_float((size_t)0,2),160.1);
    GT_EQUALS(df.get_string((size_t)0,0),"Annie");
    GT_EQUALS(df.nrows(), 5);
    exit(0);
}

void test2(){
    set_up_dataframe();
    IntColumn course;
    course.set(0, 1234);
    course.set(1, 1244);
    course.set(2, 1235);
    course.set(3, 3834);
    df.add_column(course, "course");
    GT_EQUALS(df.ncols(), 5);
    exit(0);
}

TEST(a4, t1){ ASSERT_EXIT_ZERO(test1);
ASSERT_EXIT_ZERO(test2);}

int main(int argc, char * argv[]){
    test();
    test1();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}