 #include "floatarithmetic.idl"

#include "rpcproxyhelper.h"
#include "./RPC/utility.h"

#include <cstdio>
#include <cstring>
#include <string>
#include "c150debug.h"

using namespace C150NETWORK;  // for all the comp150 utilities 

float add(float x, float y) {
  char readBuffer[sizeof(float)];

  NetworkFormatter f = NetworkFormatter();
  f.setFunctionName("add");
  f.setReturnType("float", sizeof(float));
  f.appendArg("float", sizeof(float), serialize<float>(x));
  f.appendArg("float", sizeof(float), serialize<float>(y));

  string data = f.networkForm();

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float add(float, float) invoked");
  RPCPROXYSOCKET->write(data, data.length()+1);

  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float add(float, float) invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));

  float result = *(reinterpret_cast<float*>(readBuffer));
  cerr << "Got Result: " << result << endl;

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float add(float, float) successful return from remote call");

}


float subtract(float x, float y) {
  char readBuffer[sizeof(float)];  // to read magic value DONE + null
  //
  // Send the Remote Call
  //

  string data = "subtract,float,float," + serialize(x) + ",float," + serialize(y);

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float subtract(float, float) invoked");
  RPCPROXYSOCKET->write(data, data.length()+1); // write function name including null\

  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float subtract(float, float) invocation sent, waiting for response");
  RPCPROXYSOCKET->write(data, data.length()+1); // write function name including null\

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("floatarithmetic.proxy.cpp: float subtract(float, float) received invalid response from the server");
  }
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float subtract(float, float) successful return from remote call");

}


float multiply(float x, float y) {
  char readBuffer[sizeof(float)];  // to read magic value DONE + null
  //
  // Send the Remote Call
  //

  string data = "multiply,float,float," + serialize(x) + ",float," + serialize(y);

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float multiply(float, float) invoked");
  RPCPROXYSOCKET->write(data, data.length()+1); // write function name including null\

  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float multiply(float, float) invocation sent, waiting for response");
  RPCPROXYSOCKET->write(data, data.length()+1); // write function name including null\

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("floatarithmetic.proxy.cpp: float multiply(float, float) received invalid response from the server");
  }
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float multiply(float, float) successful return from remote call");
}

float divide(float x, float y) {
  char readBuffer[sizeof(float)];  // to read magic value DONE + null
  //
  // Send the Remote Call
  //

  string data = "divide,float,float," + serialize(x) + ",float," + serialize(y);

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float divide(float, float) invoked");
  RPCPROXYSOCKET->write(data, data.length()+1); // write function name including null\

  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float divide(float, float) invocation sent, waiting for response");
  RPCPROXYSOCKET->write(data, data.length()+1); // write function name including null\

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("floatarithmetic.proxy.cpp: float divide(float, float) received invalid response from the server");
  }
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float divide(float, float) successful return from remote call");

}

