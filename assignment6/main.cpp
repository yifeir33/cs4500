#include <iostream>
#include <cstdlib>
#include "part2/Deserializer.h"
#include "part2/Serializer.h"
#include "part2/array.h"
#include "part2/string.h"
#include "part2/primitive_serialize.h"
#include "part2/Array_serialize.h"
#include "part2/sockaddr_in_serialize.h"
#include "part2/String_serialize.h"

//test primitive type
using namespace std;

void FAIL() { exit(1); }

void OK(const char *m) { std::cout<< m <<std::endl; }

void t_true(bool p) { if (!p) FAIL(); }

void t_false(bool p) { if (p) FAIL(); }

void test1(){
    Serializer s;
    //used for define
    Primitive_Serialize ps(3.9, (bool)1, 1000);
    //used for verify
    Primitive_Serialize ps1;
    char* ps_buff = ps.serialize(s);
    cout<<"here before"<<endl;
    printf("%s\n", ps_buff);
    cout<<"after serialize"<<endl;
    Deserializer ds;
    ps1.deserilize(ds,ps_buff);
    OK("here");
    cout<<ps1.get_bool()<<endl;
    cout<<ps.get_bool()<<endl;
    t_true((bool)ps1.get_bool() == (bool)ps.get_bool());
    cout<<ps1.get_int()<<endl;
    t_true(ps1.get_int() == ps.get_int());
    OK("here");
    cout<<ps1.get_float()<<endl;
    t_true(ps1.get_float() == ps.get_float());
    OK("test 1 pass");

}

//test String
void test2(){
    String* s1 = new String("Hello World");
    String* s2 = new String("Hello World1");
    String_in_Serialize sis(s1);
    String_in_Serialize sis2(s2);
    Serializer s;
    char* ps_buff = sis.serialize(s);
    Deserializer ds;
    sis2.deserilize(ds,ps_buff);
    t_true(sis.getString() == sis2.getString());
    OK("test 2 pass");


    delete s1;
    delete s2;
}

//test array
void test3(){
    Array_Serialize as;
    FloatArray fa0(5);
    fa0.push(0.1);
    fa0.push(0.1);
    fa0.push(0.1);
    fa0.push(0.1);
    StringArray sa0(5);
    String* s1 = new String("Hello World");
    String* s2 = new String("Hello World1");
    sa0.push(s1);
    sa0.push(s2);
    sa0.push(s1);
    sa0.push(s1);
    OK("test 3 pass");

    delete s1;
    delete s2;

}
void test4(){
//    Sockaddr_in_Serialize sais;
}
void test5(){
//if required enum we could use message instead.
}


int main() {
//    test1();
//    test2();
    test3();
//    test4();
//    test5();
    return 0;
}







