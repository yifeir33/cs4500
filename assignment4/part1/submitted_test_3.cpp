#include <gtest/gtest.h>
#include "dataframe.h"

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")


/**
 * test on columns
 */
void test3() {
    //create
    String* a  = new String("a");
    String* b  = new String("b");
    String* c  = new String("c");
    String* d  = new String("d");
    String* e  = new String("e");
    String* f  = new String("f");


    IntColumn* i = new IntColumn(5,1,2,3,4,5);
    StringColumn* s = new StringColumn(5, a, b,c,d,e);
    FloatColumn* f_c = new FloatColumn(5, 0.1, 0.2, 0.3, 0.4, 0.5);
    BoolColumn* b_c = new BoolColumn(5,0,0,0,1,1);
    //test size of column
    GT_EQUALS(i->size() , 5);
    GT_EQUALS(s->size() , 5);
    GT_EQUALS(f->size() , 5);
    GT_EQUALS(b_c->size() , 5);
    //test push back
    i->push_back(6);
    s->push_back(f);
    f_c->push_back(0.6);
    b_c->push_back(1);
    //test size again
    GT_EQUALS(i->size() , 6);
    GT_EQUALS(s->size() , 6);
    GT_EQUALS(f_c->size() , 6);
    GT_EQUALS(b_c->size() , 6);
    //test get
    GT_EQUALS(i->get(0) , 1);
    GT_EQUALS(s->get(1) , b);
    GT_EQUALS(f_c->get(3) , 0.4);
    GT_EQUALS(b_c->get(1) , 0);
    //test set
    i->set(0,2);
    s->set(0,b);
    f_c->set(0, 0.2);
    b_c->set(0, 1 );
    GT_EQUALS(i->get(0) , 2);
    GT_EQUALS(s->get(0) , b);
    GT_EQUALS(f_c->get(0) , 0.2);
    GT_EQUALS(b_c->get(0) , 1);
    //test get type
    GT_EQUALS(i->get_type() , "I");
    GT_EQUALS(s->get_type() , "S");
    GT_EQUALS(f_c->get_type() , "F");
    GT_EQUALS(b_c->get_type() , "B");

    delete i,f_c,s,b_c,a,b,c,d,e,f;

    exit(0);
}

TEST(a4, t1){ ASSERT_EXIT_ZERO(test3); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}