//
// Created by 王镱霏 on 1/28/20.
//

#include "map.h"
#include "object.h"
#include "string.h"

void FAIL() { exit(1); }

void OK(const char *m) { std::cout<< m <<std::endl; }

void t_true(bool p) { if (!p) FAIL(); }

void t_false(bool p) { if (p) FAIL(); }

//test
void test1(Map *map) {
    String* str = new String("hello");
    String* str2 = new String("hello");
    String* str1 = new String("world");
    map->put(str, str1);

    t_true(map->size() == 1);

    map->remove(str2);

    std::cout<<map->size()<<std::endl;
    t_true(map->size() == 0);

    OK("test1");
}


//test storage
void test2(Map *map) {
    String* str = new String("hello");
    String* str1 = new String("world");
//    std::cout<<"here"<<std::endl;
    for(int i =0; i< 100; i++){
//        std::cout<<"current ith round:"<<i<<std::endl;
        map->put(str, str1);
    }
//    std::cout<<"here1"<<std::endl;
    t_true(map->size() == 100);
//    std::cout<<"here"<<std::endl;
    map->remove(str);
    t_true(map->size() == 99);
//    std::cout<<"here"<<std::endl;
    OK("test2");
}
void test3(Map *map){
    String *str = new String("hello");
    String *str1 = new String("world");
    String *str2 = new String("hello1");
    String *str3 = new String("world1");

    map->put(str, str1);
    map->put(str2, str3);

    t_true(map->get(str2) == str3);
    t_true(map->get(str) == str1);
    OK("test3");
}
int main() {
    Map map;

    test1(&map);
    test2(&map);
    test3(&map);
}