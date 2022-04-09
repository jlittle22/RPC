#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <string>
using namespace std;

#ifndef STRUCTS_IDL
#define STRUCTS_IDL
#include "structs.idl"
#endif

union FloatInt {
  uint32_t i;
  float f;
};

std::string serialize(int x);

int deserialize_int(std::string x);

std::string serialize(std::string x);

std::string deserialize_string(std::string x);

std::string serialize(float x);

float deserialize_float(std::string x);

///// 

///// User-defined Serialization Methods

// struct Person {string firstname; string lastname; int age;};
std::string serialize(Person x);

Person deserialize_Person(std::string x);

std::string serialize(ThreePeople x);

ThreePeople deserialize_ThreePeople(std::string x);

std::string serialize(StructWithArrays x);

StructWithArrays deserialize_StructWithArrays(std::string x);

std::string serialize(rectangle x);
rectangle deserialize_rectangle(std::string x);

/////

#endif

