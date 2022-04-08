
#include "floatarithmetic.idl"

#include "rpcstubhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "./RPC/utility.h"
#include <ctype.h>


#include <iostream>

using namespace C150NETWORK;  // for all the comp150 utilities 

// ======================================================================
//                             STUBS
//
//    Each of these is generated to match the signature of the 
//    function for which it is a stub. The names are prefixed with "__"
//    to keep them distinct from the actual routines, which we call!
//
//    Note that when functions take arguments, these are the routines
//    that will read them from the input stream. These routines should
//    be generated dynamically from your rpcgen program (and so should the
//    code above).
//
// ======================================================================
  

void __add(float x, float y) {

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: invoking __add()");
  float res = add(x, y);

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: returned from  __add() -- responding to client");
  RPCSTUBSOCKET->write(serialize(res).c_str(), sizeof(res));
}

void __subtract(float x, float y) {
  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: invoking __subtract()");
  float res = subtract(x, y);

  //
  // Send the response to the client
  //
  // If __subtract returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: returned from  __subtract() -- responding to client");
  RPCSTUBSOCKET->write(serialize(res).c_str(), sizeof(res));
}

void __multiply(float x, float y) {
  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: invoking __multiply()");
  float res = multiply(x, y);

  //
  // Send the response to the client
  //
  // If __multiply returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: returned from  __multiply() -- responding to client");
  RPCSTUBSOCKET->write(serialize(res).c_str(), sizeof(res));
}

void __divide(float x, float y) {
  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: invoking __divide()");
  float res = divide(x, y);

  //
  // Send the response to the client
  //
  // If __multiply returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: returned from  __divide() -- responding to client");
  RPCSTUBSOCKET->write(serialize(res).c_str(), sizeof(res));
}



//
//     __badFunction
//
//   Pseudo-stub for missing functions.
//

void __badFunction(char *functionName) {
  char doneBuffer[5] = "BAD";  // to write magic value DONE + null


  //
  // Send the response to the client indicating bad function
  //

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: received call for nonexistent function %s()",functionName);
  RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
}



// ======================================================================
//
//                        COMMON SUPPORT FUNCTIONS
//
// ======================================================================

// forward declaration
int getFunctionCallFromStream(char *buffer, unsigned int bufSize);


//
//                         dispatchFunction()
//
//   Called when we're ready to read a new invocation request from the stream
//

void dispatchFunction() {

  char functionCallBuffer[500];

  //
  // Read the function name from the stream -- note
  // REPLACE THIS WITH YOUR OWN LOGIC DEPENDING ON THE 
  // WIRE FORMAT YOU USE
  //

  
  int numBytes = getFunctionCallFromStream(functionCallBuffer,sizeof(functionCallBuffer));

  string offTheWire(functionCallBuffer, numBytes);

  NetworkFormatter f = NetworkFormatter(offTheWire);

  if (!RPCSTUBSOCKET-> eof()) {
    if (f.getFunctionSignature() == "add,float(4),float(4),float(4)") {
      string argDataStr1 = get<2>(f.getArgAtIndex(0));
      string argDataStr2 = get<2>(f.getArgAtIndex(1));

      __add(deserialize<float>(argDataStr1), deserialize<float>(argDataStr2));
    } else if (f.getFunctionSignature() == "subtract,float(4),float(4),float(4)") {
      string argDataStr1 = get<2>(f.getArgAtIndex(0));
      string argDataStr2 = get<2>(f.getArgAtIndex(1));

      __subtract(deserialize<float>(argDataStr1), deserialize<float>(argDataStr2));
    } else if (f.getFunctionSignature() == "multiply,float(4),float(4),float(4)") {
      string argDataStr1 = get<2>(f.getArgAtIndex(0));
      string argDataStr2 = get<2>(f.getArgAtIndex(1));

      __multiply(deserialize<float>(argDataStr1), deserialize<float>(argDataStr2));
    } else if (f.getFunctionSignature() == "divide,float(4),float(4),float(4)") {
      string argDataStr1 = get<2>(f.getArgAtIndex(0));
      string argDataStr2 = get<2>(f.getArgAtIndex(1));

      __divide(deserialize<float>(argDataStr1), deserialize<float>(argDataStr2));
    } else {
      __badFunction(functionCallBuffer);
    }
  }
}

// if name is makeStruct
    // if return typs 
    // else return type

// if it's return type <--- idl_to_json
   // call func 

 
//
//                   getFunctionCallFromStream
//
//   Helper routine to read function name from the stream. 
//   Note that this code is the same for all stubs, so can be generated
//   as boilerplate.
//
//   Important: this routine must leave the sock open but at EOF
//   when eof is read from client.
//
int getFunctionCallFromStream(char *buffer, unsigned int bufSize) {
  unsigned int i;
  char *bufp;
  ssize_t readlen;
  unsigned int numBytes;

  bufp = buffer;

  for (i = 0; i < sizeof(numBytes); i++) {
    readlen = RPCSTUBSOCKET-> read(bufp, 1);  // read a byte
    if (readlen == 0) {
      break;
    }

    bufp++;
  }

  numBytes = (*(reinterpret_cast<unsigned int*>(buffer)));

  for (i = 0; i < bufSize && i < numBytes; i++) {
    readlen = RPCSTUBSOCKET-> read(bufp, 1);  // read a byte

    if (readlen == 0) {
      break;
    }

    bufp++;
  }
  
  if (readlen == 0) {
    c150debug->printf(C150RPCDEBUG,"arithmetic.stub: read zero length message, checking EOF");
    if (RPCSTUBSOCKET-> eof()) {
      c150debug->printf(C150RPCDEBUG,"arithmetic.stub: EOF signaled on input");

    } else {
      throw C150Exception("arithmetic.stub: unexpected zero length read without eof");
    }
  }

  if (i < numBytes && i >= bufSize) {
    throw C150Exception("arithmetic.stub: Incoming message was larger than bufSize");
  }

  return numBytes + sizeof(numBytes);

}


