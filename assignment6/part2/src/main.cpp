#include <iostream>
#include <cstdlib>
#include <sys/socket.h>

#include "deserializer.h"
#include "serializer.h"
#include "array.h"
#include "string.h"

#define PORTNUM 2300
//test primitive type
using namespace std;

void FAIL() { exit(1); }

void OK(const char *m) { std::cout<< m <<std::endl; }

void t_true(bool p) { if (!p) FAIL(); }

void t_false(bool p) { if (p) FAIL(); }

void test1(){
    float first = 3.9;
    bool second = true;
    int third = 1000;

    Serializer s;
    s.write((float)3.9);
    s.write((bool) true);
    s.write(1000);

    char* buf = s.get();
    size_t buf_len = s.length();

    Deserializer ds(buf, buf_len);

    t_true(std::abs(ds.readFloat() - first) < 0.00001);
    t_true(ds.readBool() == second);
    t_true(ds.readInt() == third);
    OK("test 1 pass");
    delete[] buf;
}

void testFloat(){
    Serializer s;
    s.write((float) 3.9);

    char* ps_buff = s.get();
    size_t buf_len = s.length();

    Deserializer ds(ps_buff, buf_len);

    float ans = ds.readFloat();
    t_true(std::abs(3.9 - ans) < 0.0001);
    OK("float ok");
    delete[] ps_buff;
}

void testBool(){
    Serializer s;
    s.write((bool)true);

    char* ps_buff = s.get();
    size_t buf_len = s.length();

    Deserializer ds(ps_buff, buf_len);
    bool ans = ds.readBool();
    t_true(ans == true);
    OK("bool ok");
    delete[] ps_buff;
}

void testInt(){
    Serializer s;
    s.write(10);

    char* ps_buff = s.get();
    size_t buf_len = s.length();

    Deserializer ds(ps_buff, buf_len);
    int ans = ds.readInt();
    t_true(ans == 10);
    OK("int ok");
    delete[] ps_buff;
}

void testString(){
    Serializer s;
    String s1("Hello World");
    s.write(&s1);

    char* ps_buff = s.get();
    size_t buf_len = s.length();

    Deserializer ds(ps_buff, buf_len);
    String* ans = ds.readString();

    t_true(ans->equals(&s1));
    OK("String ok");
    delete ans;
    delete[] ps_buff;
}

void testSocketAddress(){
    sockaddr_in local_sin;
    local_sin.sin_family = AF_INET;
    local_sin.sin_port = htons(PORTNUM);
    local_sin.sin_addr.s_addr = htonl(INADDR_ANY);

    Serializer s;
    s.write(local_sin);
    char* ps_buff = s.get();
    size_t buf_len = s.length();

    Deserializer ds(ps_buff, buf_len);
    sockaddr_in *ans = ds.readSockAddrIn();
    t_true(ans->sin_family == local_sin.sin_family);
    t_true(ans->sin_addr.s_addr == local_sin.sin_addr.s_addr);
    t_true(ans->sin_port == local_sin.sin_port);
    OK("Socket Address Ok");
    delete[] ps_buff;
    delete ans;
}

void testFloatArray(){
    FloatArray fa0(5);
    fa0.push(0.1);
    fa0.push(0.1);
    fa0.push(0.1);
    fa0.push(0.1);

    Serializer s;
    s.write(&fa0);

    char* ps_buff = s.get();
    size_t buf_len = s.length();

    Deserializer ds(ps_buff, buf_len);
    FloatArray *ans = ds.readFloatArray();
    t_true(ans->equals(&fa0));
    OK("test FloatArray pass");
    delete[] ps_buff;
    delete ans;
}


int main() {
    testFloat();
    testBool();
    testInt();
    testString();
    /* testSocketAddress(); */
    testFloatArray();
    test1();

    return 0;
}







