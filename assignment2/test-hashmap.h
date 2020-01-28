//
// Created by 王镱霏 on 1/27/20.
//

#ifndef A2_TEST_HASHMAP_H
#define A2_TEST_HASHMAP_H

#include "HashMap.h"
#include "Object.h"
#include "String.h"
void FAIL() { exit(1); }

void OK(const char *m) { std::cout<< m <<std::endl; }

void t_true(bool p) { if (!p) FAIL(); }

void t_false(bool p) { if (p) FAIL(); }

//test
void test1(HashMap *hashMap) {
    std::cout<<"here"<<std::endl;
    String* str = new String("hello");
    String* str1 = new String("world");
    hashMap->put(str, str1);
    t_true(hashMap->size() == 1);
    hashMap->remove(str);
    t_true(hashMap->size() == 0);
    t_true(hashMap->isEmpty());
    OK("test1");
}


//test storage
void test2(HashMap *hashMap) {
    String* str = new String("hello");
    String* str1 = new String("world");
   for(int i =0; i< 100; i++){
       hashMap->put(str, str1);
   }
    t_true(hashMap->size() == 100);

}

int main(int argc, char** argv){
    HashMap HashMap;

    test1(&HashMap);

}
#endif //A2_TEST_HASHMAP_H

