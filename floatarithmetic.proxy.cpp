#include "floatarithmetic.idl"

#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "./RPC/utility.h"

#include "serialize.h"

#include <iostream>

using namespace C150NETWORK;  // for all the comp150 utilities 

float add(float x, float y) {
  char readBuffer[sizeof(float)];

  NetworkFormatter f = NetworkFormatter();
  f.setFunctionName("add");
  f.setFunctionRetType("float", sizeof(float));
  f.appendArg("float", sizeof(float), serialize(x));
  f.appendArg("float", sizeof(float), serialize(y));
 
  string data = f.networkForm();
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float add(float, float) invoked");

  RPCPROXYSOCKET->write(data.c_str(), data.length()); 

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float add(float, float) invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
  
  string offTheWire(readBuffer, sizeof(float));
  
  float result = deserialize_float(offTheWire);

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float add(float, float) successful return from remote call");

  return result;
}


float subtract(float x, float y) {
  char readBuffer[sizeof(float)];

  NetworkFormatter f = NetworkFormatter();
  f.setFunctionName("subtract");
  f.setFunctionRetType("float", sizeof(float));
  f.appendArg("float", sizeof(float), serialize(x));
  f.appendArg("float", sizeof(float), serialize(y));
  string data = f.networkForm();

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float subtract(float, float) invoked");
  RPCPROXYSOCKET->write(data.c_str(), data.length());

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float subtract(float, float) invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));

  string offTheWire(readBuffer, sizeof(float));
  
  float result = deserialize_float(offTheWire);

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float subtract(float, float) successful return from remote call");

  return result;

}


float multiply(float x, float y) {
  char readBuffer[sizeof(float)];

  NetworkFormatter f = NetworkFormatter();
  f.setFunctionName("multiply");
  f.setFunctionRetType("float", sizeof(float));
  f.appendArg("float", sizeof(float), serialize(x));
  f.appendArg("float", sizeof(float), serialize(y));
  string data = f.networkForm();
  
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float multiply(float, float) invoked");
  RPCPROXYSOCKET->write(data.c_str(), data.length());
  
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float multiply(float, float) invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));

  string offTheWire(readBuffer, sizeof(float));
  
  float result = deserialize_float(offTheWire);

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float multiply(float, float) successful return from remote call");
  
  return result;

}

float divide(float x, float y) {
  char readBuffer[sizeof(float)];

  NetworkFormatter f = NetworkFormatter();
  f.setFunctionName("divide");
  f.setFunctionRetType("float", sizeof(float));
  f.appendArg("float", sizeof(float), serialize(x));
  f.appendArg("float", sizeof(float), serialize(y));
  string data = f.networkForm();

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float divide(float, float) invoked");
  RPCPROXYSOCKET->write(data.c_str(), data.length());

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float divide(float, float) invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
  string offTheWire(readBuffer, sizeof(float));
  
  float result = deserialize_float(offTheWire);

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float divide(float, float) successful return from remote call");
  
  return result;

}

