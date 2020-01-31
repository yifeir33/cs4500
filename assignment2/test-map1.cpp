//
// Created by 王镱霏 on 1/30/20.
//

#include "map.h"
#include "object.h"
#include "string.h"
void FAIL() { exit(1); }

void OK(const char *m) { std::cout<< m <<std::endl; }

void t_true(bool p) { if (!p) FAIL(); }

void t_false(bool p) { if (p) FAIL(); }

//test
void test1(Map *hashmap) {

    String* str = new String("hello");
    String* str1 = new String("world");
    hashmap->put(str, str1);
    t_true(hashmap->size() == 1);
    hashmap->remove(str);
    t_true(hashmap->size() == 0);
    OK("test1");
}


//test storage
void test2(Map *hashmap) {
    String* str = new String("hello");
    String* str1 = new String("world");
    for(int i =0; i< 100; i++){
        hashmap->put(str, str1);
    }
    t_true(hashmap->size() == 100);
    OK("test2");
}

//test get
void test3(Map *hashmap) {
    String* str = new String("hello");
    String* str1 = new String("world");
    String* str2 = new String("hello1");
    String* str3 = new String("world1");
    String* str4 = new String("world1");
    hashmap->put(str, str1);
    hashmap->put(str2, str3);
    t_true(hashmap->get(str2)->equals(str3));
    t_true(hashmap->get(str2)->equals(str4));

    OK("test3");
}

int main(int argc, char** argv){
    Map hashmap;

    test1(&hashmap);
    test2(&hashmap);
    test3(&hashmap);

}