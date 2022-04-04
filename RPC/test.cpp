#include <iostream>
#include <inttypes.h>
#include <sstream>

#include "utility.h"

using namespace std;


struct test {
  int a;
  char b;
  char c;
  float d;
  int e[10];
};

int main() {
  test t;
  t.a = 5;
  t.b = 'a';
  t.c = 'c';
  t.d = 3.1415;
  t.e[0] = 0;
  t.e[1] = 1;
  t.e[2] = 2;
  t.e[3] = 3;
  t.e[4] = 4;
  t.e[5] = 5;
  t.e[6] = 6;
  t.e[7] = 7;
  t.e[8] = 8;
  t.e[9] = 9;

  cout << " t : " << serialize(t) << endl;

  test other = deserialize<test>(serialize<test>(t));

  cout << "a : " << other.a << endl;
  cout << "b : " << other.b << endl;
  cout << "c : " << other.c << endl;
  cout << "d : " << other.d << endl;
  for (int i = 0; i < 10; i++) {
    cout << i << " : " << other.e[i] << endl;
  }

  cout << " 3.1415 : " << deserialize<float>(serialize<float>(3.1415f)) << endl;

  NetworkFormatter f = NetworkFormatter("name,returnType(5),argTypeWithAlongerName(4),data,otherArgType(6),sixxxx,finalArgType(1),1");
  cout << "MANDATORY DATA: " << f.getFunctionName() << " " << get<0>(f.getFunctionRetType()) << " " << get<1>(f.getFunctionRetType()) << endl;
  for (int i = 0; i < f.getNumArgs(); i++) {
    cout << "ARG " << i << ": " << get<0>(f.getArgAtIndex(i)) << " " << get<1>(f.getArgAtIndex(i)) << " " << get<2>(f.getArgAtIndex(i)) << endl;
  }

  cout << "NETOWRK FORM: " << f.networkForm() << endl;

	return 0;
}