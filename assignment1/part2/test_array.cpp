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
void testObjectArray1() {
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
  OK("test1 - ObjectArray");
}

// test insert
void testStringArray1() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  String ok3_2("ok3");
  StringArray *arr = new StringArray(3);
  assert(arr->size() == 0);
  arr->insert(0, &ok1);
  assert(arr->size() == 1);
  arr->insert(1, &ok2);
  assert(arr->size() == 2);
  arr->insert(0, &ok3);
  assert(arr->get(0)->equals(&ok3_2));
  delete arr;
  OK("test1 - StringArray");
}

// test insert
void testBoolArray1() {
  BoolArray *arr = new BoolArray(3);
  assert(arr->size() == 0);
  arr->insert(0, false);
  assert(arr->size() == 1);
  arr->insert(1, true);
  assert(arr->size() == 2);
  arr->insert(0, true);
  assert(arr->get(0) == true);
  delete arr;
  OK("test1 - BoolArray");
}

// test insert
void testIntArray1() {
  IntArray *arr = new IntArray(3);
  assert(arr->size() == 0);
  arr->insert(0, 10);
  assert(arr->size() == 1);
  arr->insert(1, 9);
  assert(arr->size() == 2);
  arr->insert(0, 8);
  assert(arr->get(0) == 8);
  delete arr;
  OK("test1 - IntArray");
}

// test insert
void testFloatArray1() {
  FloatArray *arr = new FloatArray(3);
  assert(arr->size() == 0);
  arr->insert(0, 10.1);
  assert(arr->size() == 1);
  arr->insert(1, 9.9);
  assert(arr->size() == 2);
  arr->insert(0, 8.8);
  assert(abs(arr->get(0) - 8.8) < 0.001);
  delete arr;
  OK("test1 - FloatArray");
}

// test append & clear
void testObjectArray2() {
  String ok1("ok1");
  String ok2("ok2");
  Array *arr = new Array();
  arr->append(&ok1);
  assert(arr->size() == 1);
  arr->append(&ok2);
  assert(arr->size() == 2);
  arr->clear();
  assert(arr->size() == 0);
  delete arr;
  OK("test2 - ObjectArray");
}

// test append & clear
void testStringArray2() {
  String ok1("ok1");
  String ok2("ok2");
  StringArray *arr = new StringArray();
  arr->append(&ok1);
  assert(arr->size() == 1);
  arr->append(&ok2);
  assert(arr->size() == 2);
  arr->clear();
  assert(arr->size() == 0);
  delete arr;
  OK("test2 - StringArray");
}

// test append & clear
void testBoolArray2() {
  BoolArray *arr = new BoolArray();
  arr->append(false);
  assert(arr->size() == 1);
  arr->append(true);
  assert(arr->size() == 2);
  arr->clear();
  assert(arr->size() == 0);
  delete arr;
  OK("test2 - BoolArray");
}

// test append & clear
void testIntArray2() {
  IntArray *arr = new IntArray();
  arr->append(1);
  assert(arr->size() == 1);
  arr->append(2);
  assert(arr->size() == 2);
  arr->clear();
  assert(arr->size() == 0);
  delete arr;
  OK("test2 - IntArray");
}

// test append & clear
void testFloatArray2() {
  FloatArray *arr = new FloatArray();
  arr->append(1.1);
  assert(arr->size() == 1);
  arr->append(2.2);
  assert(arr->size() == 2);
  arr->clear();
  assert(arr->size() == 0);
  delete arr;
  OK("test2 - FloatArray");
}

// test count
void testObjectArray3() {
  String ok1("ok1");
  String ok2("ok2");
  Array *arr = new Array();
  arr->append(&ok1);
  assert(arr->size() == 1);
  arr->append(&ok1);
  assert(arr->size() == 2);
  arr->append(&ok1);
  assert(arr->size() == 3);
  arr->append(&ok1);
  assert(arr->size() == 4);
  assert(arr->count(&ok1) == 3);
  delete arr;
  OK("test3 - ObjectArray");
}

// test count
void testStringArray3() {
  String ok1("ok1");
  String ok2("ok2");
  StringArray *arr = new StringArray();
  arr->append(&ok1);
  assert(arr->size() == 1);
  arr->append(&ok2);
  assert(arr->size() == 2);
  arr->append(&ok1);
  assert(arr->size() == 3);
  arr->append(&ok1);
  assert(arr->size() == 4);
  assert(arr->count(&ok1) == 3);
  delete arr;
  OK("test3 - StringArray");
}

// test count
void testBoolArray3() {
  BoolArray *arr = new BoolArray();
  arr->append(false);
  assert(arr->size() == 1);
  arr->append(true);
  assert(arr->size() == 2);
  arr->append(false);
  assert(arr->size() == 3);
  arr->append(true);
  assert(arr->size() == 4);
  assert(arr->count(true) == 2);
  delete arr;
  OK("test3 - BoolArray");
}

// test count
void testIntArray3() {
  IntArray *arr = new IntArray();
  arr->append(1);
  assert(arr->size() == 1);
  arr->append(2);
  assert(arr->size() == 2);
  arr->append(1);
  assert(arr->size() == 3);
  arr->append(1);
  assert(arr->size() == 4);
  assert(arr->count(1) == 3);
  delete arr;
  OK("test3 - IntArray");
}

// test count
void testFloatArray3() {
  FloatArray *arr = new FloatArray();
  arr->append(1.1);
  assert(arr->size() == 1);
  arr->append(2.2);
  assert(arr->size() == 2);
  arr->append(1.1);
  assert(arr->size() == 3);
  arr->append(1.1);
  assert(arr->size() == 4);
  assert(arr->count(1.1) == 3);
  delete arr;
  OK("test3 - FloatArray");
}

// test get
void testObjectArray4() {
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
  OK("test4 - ObjectArray");
}

// test get
void testStringArray4() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  StringArray *arr = new StringArray(10);
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  arr->append(&ok3);
  assert(arr->get(2)->equals(&ok3));
  delete arr;
  OK("test4 - StringArray");
}

// test get
void testBoolArray4() {
  BoolArray *arr = new BoolArray(10);
  arr->append(true);
  arr->append(true);
  arr->append(false);
  arr->append(true);
  assert(arr->get(2) == false);
  delete arr;
  OK("test4 - BoolArray");
}

// test get
void testIntArray4() {
  IntArray *arr = new IntArray(10);
  arr->append(3);
  arr->append(2);
  arr->append(1);
  arr->append(0);
  assert(arr->get(2) == 1);
  delete arr;
  OK("test4 - IntArray");
}

// test get
void testFloatArray4() {
  FloatArray *arr = new FloatArray(10);
  arr->append(3.3);
  arr->append(2.2);
  arr->append(1.1);
  arr->append(0.1);
  assert(abs(arr->get(2) - 1.1) < 0.001);
  delete arr;
  OK("test4 - FloatArray");
}

// test insert & remove
void testObjectArray5() {
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
  OK("test5 - ObjectArray");
}

// test insert & remove
void testStringArray5() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  String ok4("ok4");
  StringArray *arr = new StringArray(10);
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
  OK("test5 - StringArray");
}

// test insert & remove
void testBoolArray5() {
  BoolArray *arr = new BoolArray(10);
  arr->append(false);
  arr->append(true);
  arr->append(false);
  arr->append(true);
  arr->insert(3, false);
  assert(arr->size() == 5);
  assert(arr->get(3) == false);
  arr->remove(false);
  assert(arr->size() == 4);
  assert(arr->get(0) == true);
  delete arr;
  OK("test5 - BoolArray");
}

// test insert & remove
void testIntArray5() {
  IntArray *arr = new IntArray(10);
  arr->append(5);
  arr->append(4);
  arr->append(3);
  arr->append(2);
  arr->insert(3, 1);
  assert(arr->size() == 5);
  assert(arr->get(3) == 1);
  arr->remove(5);
  assert(arr->size() == 4);
  assert(arr->get(0) == 4);
  delete arr;
  OK("test5 - IntArray");
}

// test insert & remove
void testFloatArray5() {
  FloatArray *arr = new FloatArray(10);
  arr->append(1.1);
  arr->append(2.2);
  arr->append(3.3);
  arr->append(4.4);
  arr->insert(3, 5.5);
  assert(arr->size() == 5);
  assert(abs(arr->get(3) - 5.5) < 0.001);
  arr->remove(1.1);
  assert(arr->size() == 4);
  assert(abs(arr->get(0) - 2.2) < 0.001);
  delete arr;
  OK("test5 - FloatArray");
}

// test extend
void testObjectArray6() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  Array *arr = new Array();
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  arr->append(&ok3);
  Array *arr1 = new Array(5);
  arr1->append(&ok1);
  arr1->append(&ok2);
  arr1->append(&ok3);
  arr1->append(&ok3);
  arr->extend(&arr1);
  assert(arr->size() == 8);
  assert(arr->get(0)->equals(&ok1));
  assert(arr->get(7)->equals(&ok3));
  delete arr;
  delete arr1;
  OK("test6 - ObjectArray");
}

// test extend
void testStringArray6() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  StringArray *arr = new StringArray();
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  arr->append(&ok3);
  StringArray *arr1 = new StringArray(5);
  arr1->append(&ok1);
  arr1->append(&ok2);
  arr1->append(&ok3);
  arr1->append(&ok3);
  arr->extend(&arr1);
  assert(arr->size() == 8);
  assert(arr->get(0)->equals(&ok1));
  assert(arr->get(7)->equals(&ok3));
  delete arr;
  delete arr1;
  OK("test6 - StringArray");
}

// test extend
void testBoolArray6() {
  BoolArray *arr = new BoolArray();
  arr->append(false);
  arr->append(false);
  arr->append(false);
  arr->append(false);
  BoolArray *arr1 = new BoolArray(5);
  arr1->append(true);
  arr1->append(true);
  arr1->append(true);
  arr1->append(true);
  arr->extend(&arr1);
  assert(arr->size() == 8);
  assert(arr->get(0) == false);
  assert(arr->get(7) == true);
  delete arr;
  delete arr1;
  OK("test6 - BoolArray");
}

// test extend
void testIntArray6() {
  IntArray *arr = new IntArray();
  arr->append(10);
  arr->append(11);
  arr->append(12);
  arr->append(13);
  IntArray *arr1 = new IntArray(5);
  arr1->append(0);
  arr1->append(1);
  arr1->append(2);
  arr1->append(3);
  arr->extend(&arr1);
  assert(arr->size() == 8);
  assert(arr->get(0) == 10);
  assert(arr->get(7) == 3);
  delete arr;
  delete arr1;
  OK("test6 - IntArray");
}

// test extend
void testFloatArray6() {
  FloatArray *arr = new FloatArray();
  arr->append(10.1);
  arr->append(11.2);
  arr->append(12.3);
  arr->append(13.4);
  FloatArray *arr1 = new FloatArray(5);
  arr1->append(0.4);
  arr1->append(1.3);
  arr1->append(2.2);
  arr1->append(3.1);
  arr->extend(&arr1);
  assert(arr->size() == 8);
  assert(abs(arr->get(0) - 10.1) < 0.001);
  assert(abs(arr->get(7) - 3.1) < 0.001);
  delete arr;
  delete arr1;
  OK("test6 - FloatArray");
}

// test index
void testObjectArray7() {
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
  OK("test7 - ObjectArray");
}

// test index
void testStringArray7() {
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
  OK("test7 - StringArray");
}

// test index
void testBoolArray7() {
  BoolArray *arr = new BoolArray(10);
  arr->append(false);
  arr->append(false);
  arr->append(true);
  arr->append(false);
  assert(arr->index(true) == 2);
  delete arr;
  OK("test7 - BoolArray");
}

// test index
void testIntArray7() {
  IntArray *arr = new IntArray(10);
  arr->append(0);
  arr->append(1);
  arr->append(2);
  arr->append(3);
  assert(arr->index(2) == 2);
  delete arr;
  OK("test7 - IntArray");
}

// test index
void testFloatArray7() {
  FloatArray *arr = new FloatArray(10);
  arr->append(0.1);
  arr->append(1.2);
  arr->append(2.3);
  arr->append(3.4);
  assert(arr->index(2.3) == 2);
  delete arr;
  OK("test7 - FloatArray");
}

// test pop
void testObjectArray8() {
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
  OK("test8 - ObjectArray");
}

// test pop
void testStringArray8() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  StringArray *arr = new StringArray();
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  arr->append(&ok3);
  assert(arr->pop(1)->equals(&ok2));
  assert(arr->size() == 3);
  delete arr;
  OK("test8 - StringArray");
}

// test pop
void testBoolArray8() {
  BoolArray *arr = new BoolArray();
  arr->append(false);
  arr->append(false);
  arr->append(true);
  arr->append(true);
  assert(arr->pop(1) == false);
  assert(arr->size() == 3);
  delete arr;
  OK("test8 - BoolArray");
}

// test pop
void testIntArray8() {
  IntArray *arr = new IntArray();
  arr->append(10);
  arr->append(11);
  arr->append(12);
  arr->append(13);
  assert(arr->pop(1) == 11);
  assert(arr->size() == 3);
  delete arr;
  OK("test8 - IntArray");
}

// test pop
void testFloatArray8() {
  FloatArray *arr = new FloatArray();
  arr->append(10.1);
  arr->append(11.2);
  arr->append(12.3);
  arr->append(13.4);
  assert(abs(arr->pop(1) - 11.2) < 0.001);
  assert(arr->size() == 3);
  delete arr;
  OK("test8 - FloatArray");
}

// test reverse
void testObjectArray9() {
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
  OK("test9 - ObjectArray");
}

// test reverse
void testStringArray9() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  StringArray *arr = new StringArray(5);
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  assert(arr->index(&ok1) == 0);
  arr->reverse();
  assert(arr->size() == 3);
  assert(arr->index(&ok1) == 2);
  delete arr;
  OK("test9 - StringArray");
}

// test reverse
void testBoolArray9() {
  BoolArray *arr = new BoolArray(5);
  arr->append(false);
  arr->append(true);
  arr->append(true);
  assert(arr->index(false) == 0);
  arr->reverse();
  assert(arr->size() == 3);
  assert(arr->index(false) == 2);
  delete arr;
  OK("test9 - BoolArray");
}

// test reverse
void testIntArray9() {
  IntArray *arr = new IntArray(5);
  arr->append(20);
  arr->append(21);
  arr->append(22);
  assert(arr->index(20) == 0);
  arr->reverse();
  assert(arr->size() == 3);
  assert(arr->index(20) == 2);
  delete arr;
  OK("test9 - IntArray");
}

// test reverse
void testFloatArray9() {
  FloatArray *arr = new FloatArray(5);
  arr->append(20.1);
  arr->append(21.2);
  arr->append(22.3);
  assert(arr->index(20.1) == 0);
  arr->reverse();
  assert(arr->size() == 3);
  assert(arr->index(20.1) == 2);
  delete arr;
  OK("test9 - FloatArray");
}

void testObjectArray10() {
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
  OK("test10 - ObjectArray");
}

void testStringArray10() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  StringArray *arr = new StringArray(5);
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  assert(arr->index(&ok3) == 2);
  arr->set(1, &ok3);
  assert(arr->index(&ok3) == 1);
  delete arr;
  OK("test10 - StringArray");
}

void testBoolArray10() {
  BoolArray *arr = new BoolArray(5);
  arr->append(false);
  arr->append(false);
  arr->append(false);
  assert(arr->get(1) == false);
  arr->set(1, true);
  assert(arr->get(1) == true);
  delete arr;
  OK("test10 - BoolArrayA");
}

void testIntArray10() {
  IntArray *arr = new IntArray(5);
  arr->append(-1);
  arr->append(-2);
  arr->append(-3);
  assert(arr->get(1) == -2);
  arr->set(1, -4);
  assert(arr->get(1) == -4);
  delete arr;
  OK("test10 - IntArray");
}

void testFloatArray10() {
  FloatArray *arr = new FloatArray(5);
  arr->append(-1.1);
  arr->append(-2.2);
  arr->append(-3.3);
  assert(abs(arr->get(1) - -2.2) < 0.001);
  arr->set(1, -4.4);
  assert(abs(arr->get(1) - -4.4) < 0.001);
  delete arr;
  OK("test10 - FloatArray");
}

void testObjectArray11() {
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
  OK("test11 - ObjectArray");
}

void testStringArray11() {
  String ok1("ok1");
  String ok2("ok2");
  String ok3("ok3");
  StringArray *arr = new StringArray(5);
  arr->append(&ok1);
  arr->append(&ok2);
  arr->append(&ok3);
  StringArray *arr1 = new StringArray(5);
  arr1->append(&ok1);
  arr1->append(&ok2);
  arr1->append(&ok3);
  assert(arr->equals(arr1));
  delete arr;
  delete arr1;
  OK("test11 - StringArray");
}

void testBoolArray11() {
  BoolArray *arr = new BoolArray(5);
  arr->append(true);
  arr->append(true);
  arr->append(false);
  BoolArray *arr1 = new BoolArray(5);
  arr1->append(true);
  arr1->append(true);
  arr1->append(false);
  assert(arr->equals(arr1));
  delete arr;
  delete arr1;
  OK("test11 - BoolArray");
}

void testIntArray11() {
  IntArray *arr = new IntArray(5);
  arr->append(1);
  arr->append(2);
  arr->append(3);
  IntArray *arr1 = new IntArray(5);
  arr1->append(1);
  arr1->append(2);
  arr1->append(3);
  assert(arr->equals(arr1));
  delete arr;
  delete arr1;
  OK("test11 - IntArray");
}

void testFloatArray11() {
  FloatArray *arr = new FloatArray(5);
  arr->append(1.1);
  arr->append(2.2);
  arr->append(3.3);
  FloatArray *arr1 = new FloatArray(5);
  arr1->append(1.1);
  arr1->append(2.2);
  arr1->append(3.3);
  assert(arr->equals(arr1));
  delete arr;
  delete arr1;
  OK("test11 - FloatArray");
}

int main(int argc, char **argv) {
  // ObjectArray
  testObjectArray1();
  testObjectArray2();
  testObjectArray3();
  testObjectArray4();
  testObjectArray5();
  testObjectArray6();
  testObjectArray7();
  testObjectArray8();
  testObjectArray9();
  testObjectArray10();
  testObjectArray11();

  // StringArray
  testStringArray1();
  testStringArray2();
  testStringArray3();
  testStringArray4();
  testStringArray5();
  testStringArray6();
  testStringArray7();
  testStringArray8();
  testStringArray9();
  testStringArray10();
  testStringArray11();

  // BoolArray
  testBoolArray1();
  testBoolArray2();
  testBoolArray3();
  testBoolArray4();
  testBoolArray5();
  testBoolArray6();
  testBoolArray7();
  testBoolArray8();
  testBoolArray9();
  testBoolArray10();
  testBoolArray11();

  // IntArray
  testIntArray1();
  testIntArray2();
  testIntArray3();
  testIntArray4();
  testIntArray5();
  testIntArray6();
  testIntArray7();
  testIntArray8();
  testIntArray9();
  testIntArray10();
  testIntArray11();

  // FloatArray
  testFloatArray1();
  testFloatArray2();
  testFloatArray3();
  testFloatArray4();
  testFloatArray5();
  testFloatArray6();
  testFloatArray7();
  testFloatArray8();
  testFloatArray9();
  testFloatArray10();
  testFloatArray11();
}
