//
// Created by 王镱霏 on 1/23/20.
//

#include <iostream>

#include "array.h"

using namespace std;

void FAIL() { exit(1); }

void OK(const char *m) { std::cout<< m <<std::endl; }

void t_true(bool p) { if (!p) FAIL(); }

void t_false(bool p) { if (p) FAIL(); }

//test insert
void test1() {

    Array* arr = new Array(3);
    t_true(arr->size() == 0);
    arr->insert(0, "ok1");
    t_true(arr->size() == 1);
    arr->insert(1, "ok2");
    t_true(arr->size() == 2);
    bool exception_caught = false;
    try {
        arr->insert(100, "ok11");
    } catch (exception& e){
        exception_caught = true;
    }
    t_true(exception_caught);
    OK("test1");
}

//test append & clear
void test2(){
    Array* arr = new Array(10);
    arr->append("ok1");
    t_true(arr->size() == 1);
    arr->append("ok1");
    t_true(arr->size() == 2);
    arr->clear();
    t_true(arr->size() == 0);
    OK("test2");
}

//test count
void test3(){
    Array* arr = new Array(10);
    arr->append("ok1");
    t_true(arr->size() == 1);
    arr->append("ok1");
    t_true(arr->size() == 2);
    arr->append("ok1");
    t_true(arr->size() == 3);
    arr->append("ok1");
    t_true(arr->size() == 4);
    t_true(arr->count("ok1") == 4);
    OK("test3");
}

//test get
void test4(){
    Array* arr = new Array(10);
    arr->append("ok1");
    arr->append("ok2");
    arr->append("ok3");
    arr->append("ok3");
    t_true(arr->get(2)== "ok3");
    OK("test4");

}

// test insert & remove
void test5(){
    Array* arr = new Array(10);
    arr->append("ok1");
    arr->append("ok2");
    arr->append("ok3");
    arr->append("ok3");
    arr->insert(3,"ok4");
    t_true(arr->size()== 5);
    t_true(arr->get(4) =="ok3");
    arr->remove(0);
    t_true(arr->size() == 4);
    t_true(arr->get(0) == "ok2");
    OK("test5");

}

// test extend
void test6(){
    Array* arr = new Array(10);
    arr->append("ok1");
    arr->append("ok2");
    arr->append("ok3");
    arr->append("ok3");
    Array* arr1 = new Array(5);
    arr1->append("ok1");
    arr1->append("ok2");
    arr1->append("ok3");
    arr1->append("ok3");
    arr->extend(4, arr1);
    t_true(arr->size() ==8 );
    OK("test6");

}

//test index
void test7(){
    Array* arr = new Array(10);
    arr->append("ok1");
    arr->append("ok2");
    arr->append("ok3");
    arr->append("ok3");
    t_true(arr->index("ok3") == 2);
    OK("test7");
}

//test pop
void test8(){
    Array* arr = new Array(5);
    arr->append("ok1");
    arr->append("ok2");
    arr->append("ok3");
    arr->append("ok3");
    t_true(arr->pop(1) == "ok2");
    t_true(arr->size() == 3);
    OK("test8");
}

//test reverse
void test9(){
    Array* arr = new Array(5);
    arr->append("ok1");
    arr->append("ok2");
    arr->append("ok3");
    t_true(arr->index("ok1") == 0);
    arr->reverse();
    t_true(arr->size() == 3);
    t_true(arr->index("ok1") == 2);
    OK("test9");
}

void test10(){
    Array* arr = new Array(5);
    arr->append("ok1");
    arr->append("ok2");
    arr->append("ok3");
    t_true(arr->index("ok3") ==2);
    arr->set(1,"ok3");
    t_true(arr->index("ok3") ==1);
}

void test11(){
    Array* arr = new Array(5);
    arr->append("ok1");
    arr->append("ok2");
    arr->append("ok3");
    Array* arr1 = new Array(5);
    arr1->append("ok1");
    arr1->append("ok2");
    arr1->append("ok3");
    t_true(arr->equals(arr1));
}

int main(int argc, char** argv){
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
}
