//
// Created by 王镱霏 on 2/12/20.
//

#include "gtest/gtest.h"
#include <iostream>
#include <string.h>
#include "dataframe.h"


#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")


void test1(){
    //set up:
    //create a dataframe storage name(String), age(int), height(float), isMale(Bool)
    String* annie1 = new String("Annie");
    String* bo1 = new String("Bo");
    String* jack1 = new String("Jack");
    String* lily1 = new String("Lily");
    String* peter1 = new String("Peter");

    Schema  s1("SIFB");
    DataFrame df(s1);
    Row annie(df.get_schema());
    annie.set(0,annie1);
    annie.set(1,9);
    annie.set(2,(float)160.1);
    annie.set(3,(bool)0);

    Row bo(df.get_schema());
    bo.set(0,bo1);
    bo.set(1,20);
    bo.set(2,(float)180.2);
    bo.set(3,(bool)1);

    Row jack(df.get_schema());
    jack.set(0,jack1);
    jack.set(1,30);
    jack.set(2,(float)175.6);
    jack.set(3,(bool)1);

    Row lily(df.get_schema());
    lily.set(0,lily1);
    lily.set(1,60);
    lily.set(2,(float)165.7);
    lily.set(3,(bool)0);

    df.add_row(annie);
    df.add_row(jack);
    df.add_row(bo);
    df.add_row(lily);

    //add a new row to dataframe
    Row peter(df.get_schema());
    peter.set(0,peter1);
    peter.set(1, 18);
    peter.set(2, (float)183.3);
    peter.set(3, (bool)1);

    df.fill_row(3,peter);
    GT_EQUALS(df.get_int(1,0), 9);
    GT_EQUALS(df.get_bool(3,1),(bool)1 );
    GT_EQUALS(df.get_float(2,0),(float)160.1);
    GT_TRUE(df.get_string(0,3)->equals(lily1));
    GT_EQUALS(df.nrows(), 4);
    GT_EQUALS(df.ncols(), 4);

    delete annie1;
    delete jack1;
    delete bo1;
    delete peter1;
    delete lily1;

    df.print();
    exit(0);
}



TEST(a4, t1){ ASSERT_EXIT_ZERO(test1);
}

int main(int argc, char * argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}