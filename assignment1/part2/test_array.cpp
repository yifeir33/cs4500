//
// Auther: resnik.n@husky.neu.edu & wang.yifei3@husky.neu.edu
//

#include <assert.h>
#include <iostream>

#include "array.h"
#include "string.h"

using namespace std;

void FAIL() { exit(1); }

void OK(const char *m) { std::cout << m << std::endl; }

// test insert
void test1() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  String ok3_2("ok3");
  Array *arr = new Array(3);
  assert(arr->size() == 0);
  arr->insert(0, &ok1);
  assert(arr->size() == 1);
  arr->insert(1, &ok2);
  assert(arr->size() == 2);
  arr->insert(0, &ok3);
  assert(arr->get(0)->equals(&ok3_2));
  delete arr;
  OK("test1");
}

// test append & clear
void test2() {
  String ok1("ok1");
  String ok2("ok2");
  Array *arr = new Array(10);
  arr->append(&ok1);
  assert(arr->size() == 1);
  arr->append(&ok2);
  assert(arr->size() == 2);
  arr->clear();
  assert(arr->size() == 0);
  delete arr;
  OK("test2");
}

// test count
void test3() {
  String ok1("ok1");
  Array *arr = new Array(10);
  arr->append(&ok1);
  assert(arr->size() == 1);
  arr->append(&ok1);
  assert(arr->size() == 2);
  arr->append(&ok1);
  assert(arr->size() == 3);
  arr->append(&ok1);
  assert(arr->size() == 4);
  assert(arr->count(&ok1) == 4);
  delete arr;
  OK("test3");
}

// test get
void test4() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  Array *arr = new Array(10);
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  arr->append(&ok3);
  assert(arr->get(2)->equals(&ok3));
  delete arr;
  OK("test4");
}

// test insert & remove
void test5() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  String ok4("ok4");
  Array *arr = new Array(10);
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  arr->append(&ok3);
  arr->insert(3, &ok4);
  assert(arr->size() == 5);
  assert(arr->get(4)->equals(&ok3));
  arr->remove(&ok1);
  assert(arr->size() == 4);
  assert(arr->get(0)->equals(&ok2));
  delete arr;
  OK("test5");
}

// test extend
void test6() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  Array *arr = new Array(10);
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  arr->append(&ok3);
  Array *arr1 = new Array(5);
  arr1->append(&ok1);
  arr1->append(&ok2);
  arr1->append(&ok3);
  arr1->append(&ok3);
  arr->extend(arr1);
  assert(arr->size() == 8);
  delete arr;
  delete arr1;
  OK("test6");
}

// test index
void test7() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  Array *arr = new Array(10);
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  arr->append(&ok3);
  assert(arr->index(&ok3) == 2);
  delete arr;
  OK("test7");
}

// test pop
void test8() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  Array *arr = new Array(5);
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  arr->append(&ok3);
  assert(arr->pop(1)->equals(&ok2));
  assert(arr->size() == 3);
  delete arr;
  OK("test8");
}

// test reverse
void test9() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  Array *arr = new Array(5);
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  assert(arr->index(&ok1) == 0);
  arr->reverse();
  assert(arr->size() == 3);
  assert(arr->index(&ok1) == 2);
  delete arr;
  OK("test9");
}

void test10() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  Array *arr = new Array(5);
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  assert(arr->index(&ok3) == 2);
  arr->set(1, &ok3);
  assert(arr->index(&ok3) == 1);
  delete arr;
  OK("test10");
}

void test11() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  Array *arr = new Array(5);
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  Array *arr1 = new Array(5);
  arr1->append(&ok1);
  arr1->append(&ok2);
  arr1->append(&ok3);
  assert(arr->equals(arr1));
  delete arr;
  delete arr1;
  OK("test11");
}

int main(int argc, char **argv) {
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
