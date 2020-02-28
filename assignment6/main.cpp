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

#define PORTNUM 2300
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
//    ps.serialize(s);

    s.write((float)3.9);
    s.write((bool) true);
//    s.write(1000);
    char* ps_buff = s.get();
    size_t buf_len = s.length();
    cout <<"Buf len: " <<buf_len <<endl;
    cout<<"buffer: "<<endl;
    for(int i = 0; i < buf_len; ++i){
        cout << ((int) ps_buff[i]) <<' ';
    }
    cout <<endl;
    cout<<"after serialize"<<endl;
    Deserializer ds;
    cout <<ds.readFloat(ps_buff, buf_len) <<endl;
    cout <<ds.readBool(ps_buff, buf_len) <<endl;
//    cout <<ds.readInt(ps_buff, buf_len) <<endl;
//    ps1.deserilize(ds,ps_buff);
    OK("here");
    cout<<ps1.get_bool()<<endl;
    cout<<ps.get_bool()<<endl;
//    t_true((bool)ps1.get_bool() == (bool)ps.get_bool());
//    cout<<ps1.get_int()<<endl;
//    t_true(ps1.get_int() == ps.get_int());
//    OK("here");
//    cout<<ps1.get_float()<<endl;
//    t_true(ps1.get_float() == ps.get_float());
    OK("test 1 pass");
}

//test String
//void test2(){
//    String* s1 = new String("Hello World");
////    String* s2 = new String("Hello World1");
//    String_in_Serialize sis(s1);
////    String_in_Serialize sis2(s2);
//    Serializer s;
////    s.write(s1);
//    sis.serialize(s);
//    char* ps_buff = s.get();
//    size_t buf_len = s.length();
//    cout <<"Buf len: " <<buf_len <<endl;
//    cout<<"buffer: "<<endl;
//    for(int i = 0; i < buf_len; ++i){
//        cout << ((int) ps_buff[i]) <<' ';
//    }
//    cout <<endl;
//    cout<<"after serialize"<<endl;
////    char* ps_buff = sis.serialize(s);
//    Deserializer ds;
//    ds.readString(ps_buff, buf_len);
////    sis2.deserilize(ds,ps_buff);
////    t_true(sis.getString() == sis2.getString());
//    OK("test 2 pass");
//
//
//    delete s1;
////    delete s2;
//}

//test array
//void test3(){
////    Array_Serialize as;
//    FloatArray fa0(5);
//    fa0.push(0.1);
//    fa0.push(0.1);
//    fa0.push(0.1);
//    fa0.push(0.1);
//    StringArray sa0(5);
//    String* s1 = new String("Hello World");
//    String* s2 = new String("Hello World1");
//    sa0.push(s1);
//    sa0.push(s2);
//    sa0.push(s1);
//    sa0.push(s1);
//    Serializer s;
//    s.write(fa0);
//    char* ps_buff = s.get();
//    size_t buf_len = s.length();
//    cout <<"Buf len: " <<buf_len <<endl;
//    cout<<"buffer: "<<endl;
//    Deserializer ds;
//    ds.readFloatArray(ps_buff,buf_len);
//    OK("test 3 pass");
//
//
//    delete s1;
//    delete s2;
//
//}


void testFloat(){
    Serializer s;
    s.write((float)3.9);

    char* ps_buff = s.get();
    size_t buf_len = s.length();
    Deserializer ds;
    float ans = ds.readFloat(ps_buff, buf_len);
//    cout << ans <<endl;
    t_true(ans == (float)3.9);
    OK("float ok");
}

void testBool(){
    Serializer s;
    s.write((bool)1);
    char* ps_buff = s.get();
    size_t buf_len = s.length();
    Deserializer ds;
    float ans = ds.readBool(ps_buff, buf_len);
//    cout << ans <<endl;
    t_true(ans == (bool) true);
    OK("bool ok");

}
void testInt(){
    Serializer s;
    s.write((int)10);
    char* ps_buff = s.get();
    size_t buf_len = s.length();
    Deserializer ds;
    float ans = ds.readInt(ps_buff, buf_len);
//    cout << ans <<endl;
    t_true(ans == (int) 10);
    OK("int ok");
}
void testString(){
    Serializer s;
    String* s1 = new String("Hello World");
    s.write(s1);
//    OK("String write ok");
    char* ps_buff = s.get();
    size_t buf_len = s.length();
    Deserializer ds;
    String* ans = ds.readString(ps_buff, buf_len);
//    OK("String read ok");
    for(int i = 0; i < buf_len; ++i){
        cout << ans->cstr_[i]<<' ';
    }
    cout << ans->size_ <<endl;
    t_true(ans->size_ == s1->size_);
    OK("String ok");
}

void testSocketAddress(){
//if required enum we could use message instead.
    sockaddr_in local_sin;
    local_sin.sin_family = AF_INET;

    local_sin.sin_port = htons (PORTNUM);
    local_sin.sin_addr.s_addr = htonl (INADDR_ANY);
    Serializer s;
    s.write(local_sin);
    char* ps_buff = s.get();
    size_t buf_len = s.length();
    Deserializer ds;
    sockaddr_in ans = ds.readSockAddrIn(ps_buff, buf_len);
//dont know how to compare socketaddr_in as object
}

void testFloatArray(){
    FloatArray fa0(5);
    fa0.push(0.1);
    fa0.push(0.1);
    fa0.push(0.1);
    fa0.push(0.1);
    Serializer s;
    s.write(fa0);
    char* ps_buff = s.get();
    size_t buf_len = s.length();
    cout <<"Buf len: " <<buf_len <<endl;
    cout<<"buffer: "<<endl;
    Deserializer ds;
    FloatArray ans = ds.readFloatArray(ps_buff,buf_len);
    t_true(ans.length() ==fa0.length());
    OK("test FloatArray pass");
//dont know how to compare socketaddr_in as object
}


int main() {
    testFloat();
    testBool();
    testInt();
    testSocketAddress();
    testString();
    testFloatArray();
//    test1();
//    test2();
//    test3();

    return 0;
}







