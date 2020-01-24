//
// Created by 王镱霏 on 1/24/20.
//

#include <iostream>

#include "sorer.h"

using namespace std;

void FAIL() { exit(1); }

void OK(const char *m) { std::cout<< m <<std::endl; }

void t_true(bool p) { if (!p) FAIL(); }

void t_false(bool p) { if (p) FAIL(); }



//test get
void test1(Sorer *sorer) {
    t_true(sorer->get(2,2).compare("") == 0);
    t_true(sorer->get(1,1).compare("12") ==0);
    t_true(sorer->get(0,0).compare("0") == 0);
    OK("ok1");

}

//check type
void test2(Sorer *sorer) {
    t_true(sorer->column_type(1) == Sorer::ColType::INTEGER);
    t_true(sorer->column_type(0) == Sorer::ColType::BOOL);
    t_true(sorer->column_type(2) == Sorer::ColType::STRING);
    t_true(sorer->column_type(100) == Sorer::ColType::INVALID);
    OK("ok2");

}

//check exist
void test3(Sorer *sorer) {
    t_true(sorer->exists(1,1) == true);
    t_true(sorer->exists(0,0) == true);
    t_true(sorer->exists(4,4) == false);
    OK("ok3");
}


int main(int argc, char** argv){
    Sorer sorer("SORfile", 0, 100);

    test1(&sorer);
    test2(&sorer);
    test3(&sorer);
}
