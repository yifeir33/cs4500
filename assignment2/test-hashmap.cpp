//
// Created by 王镱霏 on 1/28/20.
//

#include "HashMap.h"
#include "object.h"
#include "string.h"
void FAIL() { exit(1); }

void OK(const char *m) { std::cout<< m <<std::endl; }

void t_true(bool p) { if (!p) FAIL(); }

void t_false(bool p) { if (p) FAIL(); }

//test
void test1(HashMap *hashmap) {
    String* str = new String("hello");
    String* str2 = new String("hello");
    String* str1 = new String("world");
    hashmap->put(str, str1);
    std::cout<<"here"<<std::endl;
    t_true(hashmap->size() == 1);
    std::cout<<"here2"<<std::endl;
    hashmap->remove(str2);
    std::cout<<"here3"<<std::endl;
    std::cout<<hashmap->size()<<std::endl;
    t_true(hashmap->size() == 0);
    std::cout<<"here4"<<std::endl;
    t_true(hashmap->isEmpty());

    OK("test1");
}


//test storage
void test2(HashMap *hashmap) {
    String* str = new String("hello");
    String* str1 = new String("world");
    for(int i =0; i< 100; i++){
        hashmap->put(str, str1);
    }
    t_true(hashmap->size() == 100);
    hashmap->remove(str);
    t_true(hashmap->size() == 99);

}

int main(int argc, char** argv){
    HashMap* hashmap = new HashMap();
    test1(hashmap);
    test2(hashmap);
    return 0;
}