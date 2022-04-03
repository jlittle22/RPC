 #include "floatarithmetic.idl"

#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include <string>
#include "c150debug.h"

using namespace C150NETWORK;  // for all the comp150 utilities 


template <typename T>
string serialize(T item) {
  stringstream sstream;

  const char* ptr = reinterpret_cast<char*>(&item);
  sstream.write(ptr, sizeof(T));

  return sstream.str();
}

template <typename T>
T deserialize(string x) {
    T new_item;
    stringstream ss(x);
    ss.read(reinterpret_cast<char*>(&new_item), sizeof(T));

    return new_item;
}

float add(float x, float y) {
  char readBuffer[sizeof(float)];  // to read magic value DONE + null

  //
  // Send the Remote Call
  //

  string data = "add,float(4),float(4),float(4)|" + serialize<float>(x) + serialize<float>(y);

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float add(float, float) invoked");
  RPCPROXYSOCKET->write(data, data.length()+1); // write function name including null\

  // name, return type, arg types, send the args...

  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: float add(float, float) invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("floatarithmetic.proxy.cpp: float add(float, float) received invalid response from the server");
  }
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

