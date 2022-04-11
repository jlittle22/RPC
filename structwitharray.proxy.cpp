

// !! serializer_package requirements !!

#include <string>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
using namespace std;
#ifndef STRUCTWITHARRAY_IDL
#define STRUCTWITHARRAY_IDL
#include "structwitharray.idl"
#endif

union FloatInt {
  uint32_t i;
  float f;
};


// !! proxy_package requirements !!

#include "rpcproxyhelper.h"
#include "c150debug.h"
#include "./RPC/utility.h"
using namespace C150NETWORK;


// !! serializer_package functions !!


string serialize_int(int x);

int deserialize_int(string x);

string serialize_string(string x);

string deserialize_string(string x);

string serialize_float(float x);

float deserialize(string x);

string serialize_Person(Person x);

Person deserialize_Person(string x);

string serialize_StructWithArrays(StructWithArrays x);

StructWithArrays deserialize_StructWithArrays(string x);

string serialize_ThreePeople(ThreePeople x);

ThreePeople deserialize_ThreePeople(string x);

string serialize_Array_Person_10(Person x[10]);

void deserialize_Array_Person_10(string x, Person* dest);

string serialize_Array_int_100(int x[100]);

void deserialize_Array_int_100(string x, int* dest);

string serialize_Array_int_10(int x[10]);

void deserialize_Array_int_10(string x, int* dest);

string serialize_Array_int_10_100(int x[10][100]);

void deserialize_Array_int_10_100(string x, int* dest);

string serialize_Array_int_4(int x[4]);

void deserialize_Array_int_4(string x, int* dest);

string serialize_Array_int_4_10(int x[4][10]);

void deserialize_Array_int_4_10(string x, int* dest);

string serialize_Array_int_4_10_100(int x[4][10][100]);

void deserialize_Array_int_4_10_100(string x, int* dest);

string serialize_rectangle(rectangle x);

rectangle deserialize_rectangle(string x);

string serialize_s(s x);

s deserialize_s(string x);

string serialize_int(int x) {
  uint32_t network_x = htonl((uint32_t)x);
  stringstream sstream;
  const char* ptr = reinterpret_cast<char*>(&network_x);
  sstream.write(ptr, sizeof(network_x));
  return sstream.str();
}

int deserialize_int(string x) {
  uint32_t new_item;
  std::stringstream ss(x);
  ss.read(reinterpret_cast<char*>(&new_item), sizeof(new_item));
  return (int)ntohl(new_item);
}

string serialize_string(string x) {
  return serialize_int((int)x.length()) + x;
}

string deserialize_string(string x) {
  int str_size = deserialize_int(x.substr(0, sizeof(int)));
  return x.substr(sizeof(int), str_size);
}

string serialize_float(float x) {
  FloatInt conv;
  conv.f = x;
  return serialize_int((int)conv.i);
}

float deserialize_float(string x) {
  int new_item = deserialize_int(x);
  FloatInt conv;
  conv.i = (uint32_t)new_item;
  return conv.f;
}

string serialize_Person(Person x) {
    string data = "";
    data += serialize_string(x.firstname);
    data += serialize_string(x.lastname);
    data += serialize_int(x.age);
    return serialize_int((int)data.length()) + data;
}

Person deserialize_Person(string x) {
    Person new_item;
    int len = sizeof(int);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    new_item.firstname = deserialize_string(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    new_item.lastname = deserialize_string(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int);
    new_item.age = deserialize_int(x.substr(0, len));

    return new_item;
}

string serialize_StructWithArrays(StructWithArrays x) {
    string data = "";
    data += serialize_int(x.aNumber);
    data += serialize_Array_Person_10(x.people);
    return serialize_int((int)data.length()) + data;
}

StructWithArrays deserialize_StructWithArrays(string x) {
    StructWithArrays new_item;
    int len = sizeof(int);

    x = x.substr(len);
    len = sizeof(int);
    new_item.aNumber = deserialize_int(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    deserialize_Array_Person_10(x.substr(0, len), (Person*)new_item.people);

    return new_item;
}

string serialize_ThreePeople(ThreePeople x) {
    string data = "";
    data += serialize_Person(x.p1);
    data += serialize_Person(x.p2);
    data += serialize_Person(x.p3);
    return serialize_int((int)data.length()) + data;
}

ThreePeople deserialize_ThreePeople(string x) {
    ThreePeople new_item;
    int len = sizeof(int);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    new_item.p1 = deserialize_Person(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    new_item.p2 = deserialize_Person(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    new_item.p3 = deserialize_Person(x.substr(0, len));

    return new_item;
}

string serialize_Array_Person_10(Person x[10]) {
    string data = "";
    for (int i = 0; i < 10; i++) {
        data += serialize_Person(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_Person_10(string x, Person* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 10; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        dest[i] = deserialize_Person(x.substr(0, len));
        x = x.substr(len);
    }
}

string serialize_Array_int_100(int x[100]) {
    string data = "";
    for (int i = 0; i < 100; i++) {
        data += serialize_int(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_100(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 100; i++) {
        len = sizeof(int);
        dest[i] = deserialize_int(x.substr(0, len));
        x = x.substr(len);
    }
}

string serialize_Array_int_10(int x[10]) {
    string data = "";
    for (int i = 0; i < 10; i++) {
        data += serialize_int(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_10(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 10; i++) {
        len = sizeof(int);
        dest[i] = deserialize_int(x.substr(0, len));
        x = x.substr(len);
    }
}

string serialize_Array_int_10_100(int x[10][100]) {
    string data = "";
    for (int i = 0; i < 10; i++) {
        data += serialize_Array_int_100(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_10_100(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 10; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_100(x.substr(0, len), dest + (i * 100));
        x = x.substr(len);
    }
}

string serialize_Array_int_4(int x[4]) {
    string data = "";
    for (int i = 0; i < 4; i++) {
        data += serialize_int(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_4(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 4; i++) {
        len = sizeof(int);
        dest[i] = deserialize_int(x.substr(0, len));
        x = x.substr(len);
    }
}

string serialize_Array_int_4_10(int x[4][10]) {
    string data = "";
    for (int i = 0; i < 4; i++) {
        data += serialize_Array_int_10(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_4_10(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 4; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_10(x.substr(0, len), dest + (i * 10));
        x = x.substr(len);
    }
}

string serialize_Array_int_4_10_100(int x[4][10][100]) {
    string data = "";
    for (int i = 0; i < 4; i++) {
        data += serialize_Array_int_10_100(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_4_10_100(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 4; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_10_100(x.substr(0, len), dest + (i * 1000));
        x = x.substr(len);
    }
}

string serialize_rectangle(rectangle x) {
    string data = "";
    data += serialize_int(x.x);
    data += serialize_int(x.y);
    return serialize_int((int)data.length()) + data;
}

rectangle deserialize_rectangle(string x) {
    rectangle new_item;
    int len = sizeof(int);

    x = x.substr(len);
    len = sizeof(int);
    new_item.x = deserialize_int(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int);
    new_item.y = deserialize_int(x.substr(0, len));

    return new_item;
}

string serialize_s(s x) {
    string data = "";
    data += serialize_Array_int_4(x.m1);
    data += serialize_Array_int_4_10(x.m2);
    data += serialize_Array_int_4_10_100(x.m3);
    return serialize_int((int)data.length()) + data;
}

s deserialize_s(string x) {
    s new_item;
    int len = sizeof(int);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    deserialize_Array_int_4(x.substr(0, len), (int*)new_item.m1);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    deserialize_Array_int_4_10(x.substr(0, len), (int*)new_item.m2);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    deserialize_Array_int_4_10_100(x.substr(0, len), (int*)new_item.m3);

    return new_item;
}

// !! network_formatter_package code !!


// !! proxy_package functions !!
code