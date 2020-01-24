//
// Created by 王镱霏 on 1/24/20.
//

#ifndef GITCS4500_TEST_SORER_H
#define GITCS4500_TEST_SORER_H

using namespace std;

void FAIL() { exit(1); }

void OK(const char *m) { std::cout<< m <<std::endl; }

void t_true(bool p) { if (!p) FAIL(); }

void t_false(bool p) { if (p) FAIL(); }

//test insert
void test1() {


}

#endif //GITCS4500_TEST_SORER_H
