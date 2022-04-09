
#include <string>
using namespace std;          // for C++ std library
#ifndef STRUCTS_IDL
#define STRUCTS_IDL
#include "structs.idl"
#endif
#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "./RPC/utility.h"
#include "serialize.h"

#include <iostream>

using namespace C150NETWORK;  // for all the comp150 utilities 

///// Built-in Serialization Methods

Person findOtherPerson(StructWithArrays x) {
  NetworkFormatter f = NetworkFormatter();
  f.setFunctionName("findOtherPerson");
  f.setFunctionRetType("Person", -1);
  f.appendArg("StructWithArrays", -1, serialize(x));

  string data = f.networkForm();

  RPCPROXYSOCKET->write(data.c_str(), data.length()); 
  
  char readBuffer[500];
  RPCPROXYSOCKET->read(readBuffer, sizeof(int));

  string readLengthStr(readBuffer, 4);

  int len = deserialize_int(readLengthStr);


  RPCPROXYSOCKET->read(readBuffer + sizeof(int), len);

  string offTheWire(readBuffer, len + sizeof(int));

  Person result = deserialize_Person(offTheWire);

  return result;

}

Person findPerson(ThreePeople tp) {
  cout << "top of find person" << endl;
  NetworkFormatter f = NetworkFormatter();
  f.setFunctionName("findPerson");
  f.setFunctionRetType("Person", -1);
  f.appendArg("ThreePeople", -1, serialize(tp));
  cout << "formatter done" << endl;

  string data = f.networkForm();
  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: Person findPerson(ThreePeople) invoked");
  cout << "writing" << endl;

  RPCPROXYSOCKET->write(data.c_str(), data.length()); 

  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: Person findPerson(ThreePeople) invocation sent, waiting for response");
  cout << "reading" << endl;
  
  char readBuffer[500];
  RPCPROXYSOCKET->read(readBuffer, sizeof(int));

  string readLengthStr(readBuffer, 4);

  int len = deserialize_int(readLengthStr);
  cout << "Incoming msg Len: " << len << endl;


  RPCPROXYSOCKET->read(readBuffer + sizeof(int), len);

  string offTheWire(readBuffer, len + sizeof(int));
  cout << "done" << endl;

  Person result = deserialize_Person(offTheWire);

  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: Person findPerson(ThreePeople) successful return from remote call");

  return result;
}

int area(rectangle r) {
  char readBuffer[sizeof(int)];

  NetworkFormatter f = NetworkFormatter();
  f.setFunctionName("area");
  f.setFunctionRetType("int", sizeof(int));
  f.appendArg("rectangle", -1, serialize(r));

  string data = f.networkForm();
  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: int area(rectangle) invoked");

  RPCPROXYSOCKET->write(data.c_str(), data.length()); 

  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: int area(rectangle) invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));

  string resultStr(readBuffer, sizeof(readBuffer));
  for (int i = 0; i < 4; i++) {
    cout << i << " ? " << int(resultStr[i]) << endl;
  }

  int result = deserialize_int(resultStr);
  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: int area(rectangle) successful return from remote call");

  return result;
}
