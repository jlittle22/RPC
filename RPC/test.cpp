#include <iostream>
#include <inttypes.h>
#include <sstream>

//#include "utility.h"
#include <string>
#include <arpa/inet.h>

using namespace std;

struct Person {
  string name;
  string age;
};

struct test {
  int a;
  char b;
  char c;
  float d;
  int e[10];
};

union FloatInt {
  uint32_t i;
  float f;
};

string serialize(string x) {
  return x + '\0';
}

string deserialize_string(string x) {
  size_t null_term_index = x.find_first_of("\0");
  if (null_term_index == string::npos) {
    return x;
  }
  return x.substr(0, null_term_index);
}

string serialize(int x) {
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

string serialize(float x) {
  FloatInt conv;
  conv.f = x;
  return serialize((int)conv.i);
}

float deserialize_float(string x) {
  int new_item = deserialize_int(x);
  FloatInt conv;
  conv.i = (uint32_t)new_item;
  return conv.f;
}

int main() {

  cout << "String: " << deserialize_string(serialize("[This is a \0long string]")) << endl;
  cout << "Int: " << deserialize_int(serialize(9999999)) << endl;
  cout << "Float: " << deserialize_float(serialize((float)3.1415584729)) << endl;


  // Person jake;
  // jake.name = "JAKE LITTLE IS LOONG NAME";
  // jake.age = "twenty two";

  // cout << "age len : " << jake.age.length() << endl;
  // jake.age += '\0';
  // cout << "age len 2: " << jake.age.length() << endl;


  // string yuh = "longlonglonglongplongoplognlonglonglonglongplongoplognlonglonglonglongplongoplognlonglonglonglongplongoplognlonglonglonglongplongoplognlonglonglonglongplongoplognlonglonglonglongplongoplognlonglonglonglongplongoplogn"; 
  // cout << "sizeof(string) : " << sizeof(string) << endl;
  // cout << "sizeof(yuh)    : " << sizeof(yuh) << endl;
  // cout << "sizeof(Person) : " << sizeof(Person) << endl;
  // cout << "sizeof(jake)   : " << sizeof(jake) << endl;


  // test t;
  // t.a = 5;
  // t.b = 'a';
  // t.c = 'c';
  // t.d = 3.1415;
  // t.e[0] = 0;
  // t.e[1] = 1;
  // t.e[2] = 2;
  // t.e[3] = 3;
  // t.e[4] = 4;
  // t.e[5] = 5;
  // t.e[6] = 6;
  // t.e[7] = 7;
  // t.e[8] = 8;
  // t.e[9] = 9;

  // cout << " t : " << serialize(t) << endl;

  // test other = deserialize<test>(serialize<test>(t));

  // cout << "a : " << other.a << endl;
  // cout << "b : " << other.b << endl;
  // cout << "c : " << other.c << endl;
  // cout << "d : " << other.d << endl;
  // for (int i = 0; i < 10; i++) {
  //   cout << i << " : " << other.e[i] << endl;
  // }


  // cout << " 3.1415 : " << deserialize<float>(serialize<float>(3.1415f)) << endl;

  // NetworkFormatter f = NetworkFormatter("name,returnType(5),argTypeWithAlongerName(4),data,otherArgType(6),sixxxx,finalArgType(1),1");
  // cout << "MANDATORY DATA: " << f.getFunctionName() << " " << get<0>(f.getFunctionRetType()) << " " << get<1>(f.getFunctionRetType()) << endl;
  // for (int i = 0; i < f.getNumArgs(); i++) {
  //   cout << "ARG " << i << ": " << get<0>(f.getArgAtIndex(i)) << " " << get<1>(f.getArgAtIndex(i)) << " " << get<2>(f.getArgAtIndex(i)) << endl;
  // }

  // cout << "NETOWRK FORM: " << f.networkForm() << endl;

	return 0;
}