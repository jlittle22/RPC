#include "arithmetic.idl"

#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "./RPC/utility.h"

#include "serialize.h"

#include <iostream>

using namespace C150NETWORK;  // for all the comp150 utilities 

int add(int x, int y) {
  char readBuffer[sizeof(int)];

  NetworkFormatter f = NetworkFormatter();
  f.setFunctionName("add");
  f.setFunctionRetType("int", sizeof(int));
  f.appendArg("int", sizeof(int), serialize(x));
  f.appendArg("int", sizeof(int), serialize(y));
 
  string data = f.networkForm();
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: int add(int, int) invoked");

  RPCPROXYSOCKET->write(data.c_str(), data.length()); 

  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: int add(int, int) invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
  
  string offTheWire(readBuffer, sizeof(int));
  
  int result = deserialize_int(offTheWire);
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: int add(int, int) successful return from remote call");

  return result;
}


int subtract(int x, int y) {
  char readBuffer[sizeof(int)];

  NetworkFormatter f = NetworkFormatter();
  f.setFunctionName("subtract");
  f.setFunctionRetType("int", sizeof(int));
  f.appendArg("int", sizeof(int), serialize(x));
  f.appendArg("int", sizeof(int), serialize(y));
  string data = f.networkForm();

  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func2() invoked");
  RPCPROXYSOCKET->write(data.c_str(), data.length());

  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func2() invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));

  string offTheWire(readBuffer, sizeof(int));
  
  int result = deserialize_int(offTheWire);
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func2() successful return from remote call");

  return result;

}


int multiply(int x, int y) {
  char readBuffer[sizeof(int)];

  NetworkFormatter f = NetworkFormatter();
  f.setFunctionName("multiply");
  f.setFunctionRetType("int", sizeof(int));
  f.appendArg("int", sizeof(int), serialize(x));
  f.appendArg("int", sizeof(int), serialize(y));
  string data = f.networkForm();
  
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func3() invoked");
  RPCPROXYSOCKET->write(data.c_str(), data.length());
  
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func3() invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
  
  string offTheWire(readBuffer, sizeof(int));
  
  int result = deserialize_int(offTheWire);
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func3() successful return from remote call");
  
  return result;

}

int divide(int x, int y) {
  char readBuffer[sizeof(int)];

  NetworkFormatter f = NetworkFormatter();
  f.setFunctionName("divide");
  f.setFunctionRetType("int", sizeof(int));
  f.appendArg("int", sizeof(int), serialize(x));
  f.appendArg("int", sizeof(int), serialize(y));
  string data = f.networkForm();

  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func3() invoked");
  RPCPROXYSOCKET->write(data.c_str(), data.length());

  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func3() invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));

  string offTheWire(readBuffer, sizeof(int));
  
  int result = deserialize_int(offTheWire);
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func3() successful return from remote call");
  
  return result;

}

