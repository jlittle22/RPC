#include "arithmetic.idl"

#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"

using namespace C150NETWORK;  // for all the comp150 utilities 

string serialize(int x) {
  string result = "";
  for (int i = sizeof(int) - 1; i >= 0; i--) {
    char curr = (char)(x >> (i * 8));  
    result += curr;
  }

  return result;
}

int deserialize(string x) {
  int result = 0;
  for (int i = x.length() - 1; i >= 0; i--) {
    result += uint8_t(x[i]) << ((x.length() - i - 1) * 8);
  }
  return result;
}


int add(int x, int y) {
  char readBuffer[sizeof(int)];  // to read magic value DONE + null

  //
  // Send the Remote Call
  //

  string data = "add,int,int," + serialize(x) + ",int," + serialize(y);

  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: int add(int, int) invoked");
  RPCPROXYSOCKET->write(data, data.length()+1); // write function name including null\

  // name, return type, arg types, send the args...
  // 

 

  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: int add(int, int) invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("arithmetic.proxy.cpp: int add(int, int) received invalid response from the server");
  }
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: int add(int, int) successful return from remote call");

}


int subtract(int x, int y) {
  char readBuffer[5];  // to read magic value DONE + null
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func2() invoked");
  RPCPROXYSOCKET->write("func2", strlen("func2")+1); // write function name including null
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func2() invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("simplefunction.proxy: func2() received invalid response from the server");
  }
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func2() successful return from remote call");

}


int multiply(int x, int y) {
  char readBuffer[5];  // to read magic value DONE + null
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func3() invoked");
  RPCPROXYSOCKET->write("func3", strlen("func3")+1); // write function name including null
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func3() invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("simplefunction.proxy: func3() received invalid response from the server");
  }
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func3() successful return from remote call");

}

int divide(int x, int y) {
  char readBuffer[5];  // to read magic value DONE + null
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func3() invoked");
  RPCPROXYSOCKET->write("func3", strlen("func3")+1); // write function name including null
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func3() invocation sent, waiting for response");
  RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer)); // only legal response is DONE

  //
  // Check the response
  //
  if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
    throw C150Exception("simplefunction.proxy: func3() received invalid response from the server");
  }
  c150debug->printf(C150RPCDEBUG,"simplefunction.proxy.cpp: func3() successful return from remote call");

}

