 #include "floatarithmetic.idl"

#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"

using namespace C150NETWORK;  // for all the comp150 utilities 


// from https://www.delftstack.com/howto/cpp/how-to-convert-float-to-string-in-cpp/#use-stdstringstream-class-and-str-method-to-convert-a-float-to-a-string-in-c%2b%2b

string serialize(float x) {

    std::stringstream sstream;

    sstream << x;
    string num_str = sstream.str();
    //auto *ptr = sstream.str().c_str(); // RESULTS in dangling pointer
    // num_str.empty() ? cout << "empty\n" : 
    // cout << num_str << endl;
    return num_str;
}

//   return result;
// }

float deserialize(string x) {

     std::stringstream sstream(x);
     float num;
     sstream >> num;

     // cout << "num: " << num << endl;

     // cout << "divide: " << num / 5.0 << endl;

     return num;

}

/*
float add(float x, float y) {
  return x+y;
}

float subtract(float x, float y) {
  return x-y;
}

float multiply(float x, float y) {
  return x*y;
}

float divide(float x, float y) {
  return x/y;
}



*/

float add(float x, float y) {
  char readBuffer[sizeof(float)];  // to read magic value DONE + null

  //
  // Send the Remote Call
  //

  string data = "add,float,float," + serialize(x) + ",float," + serialize(y);

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

