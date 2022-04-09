
#include "arithmetic.idl"

#include "rpcstubhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "./RPC/utility.h"
#include <ctype.h>

#include "serialize.h"

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
  

void __add(int x, int y) {

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: invoking __add()");
  int res = add(x, y);

  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: returned from  __add() -- responding to client");
  RPCSTUBSOCKET->write(serialize(res).c_str(), sizeof(res));
}

void __subtract(int x, int y) {
  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: invoking __subtract()");
  int res = subtract(x, y);

  //
  // Send the response to the client
  //
  // If __subtract returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: returned from  __subtract() -- responding to client");
  RPCSTUBSOCKET->write(serialize(res).c_str(), sizeof(res));
}

void __multiply(int x, int y) {
  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: invoking __multiply()");
  int res = multiply(x, y);

  //
  // Send the response to the client
  //
  // If __multiply returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: returned from  __multiply() -- responding to client");
  RPCSTUBSOCKET->write(serialize(res).c_str(), sizeof(res));
}

void __divide(int x, int y) {
  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: invoking __divide()");
  int res = divide(x, y);

  //
  // Send the response to the client
  //
  // If __multiply returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: returned from  __divide() -- responding to client");
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

  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: received call for nonexistent function %s()",functionName);
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
  cout << "Here" << endl;

  char functionCallBuffer[500];

  //
  // Read the function name from the stream -- note
  // REPLACE THIS WITH YOUR OWN LOGIC DEPENDING ON THE 
  // WIRE FORMAT YOU USE
  //
  
  int numBytes = getFunctionCallFromStream(functionCallBuffer,sizeof(functionCallBuffer));

  string offTheWire(functionCallBuffer, numBytes);

  NetworkFormatter f = NetworkFormatter(offTheWire);

  cout << "Matcbing: " << f.getFunctionSignature() << endl;

  if (!RPCSTUBSOCKET-> eof()) {
    if (f.getFunctionSignature() == "add,int(4),int(4),int(4)") {
      string argDataStr1 = get<2>(f.getArgAtIndex(0));
      string argDataStr2 = get<2>(f.getArgAtIndex(1));

      __add(deserialize_int(argDataStr1), deserialize_int(argDataStr2));
    } else if (f.getFunctionSignature() == "subtract,int(4),int(4),int(4)") {
      string argDataStr1 = get<2>(f.getArgAtIndex(0));
      string argDataStr2 = get<2>(f.getArgAtIndex(1));

      __subtract(deserialize_int(argDataStr1), deserialize_int(argDataStr2));
    } else if (f.getFunctionSignature() == "multiply,int(4),int(4),int(4)") {
      string argDataStr1 = get<2>(f.getArgAtIndex(0));
      string argDataStr2 = get<2>(f.getArgAtIndex(1));

      __multiply(deserialize_int(argDataStr1), deserialize_int(argDataStr2));
    } else if (f.getFunctionSignature() == "divide,int(4),int(4),int(4)") {
      string argDataStr1 = get<2>(f.getArgAtIndex(0));
      string argDataStr2 = get<2>(f.getArgAtIndex(1));

      __divide(deserialize_int(argDataStr1), deserialize_int(argDataStr2));
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
  cout << "top of GFCFS" << endl;

  for (i = 0; i < sizeof(numBytes); i++) {
    readlen = RPCSTUBSOCKET-> read(bufp, 1);  // read a byte
    if (readlen == 0) {
      break;
    }

    bufp++;
  }

  string numBytesStr(buffer, sizeof(numBytes));
  numBytes = deserialize_int(numBytesStr);

  cout << "Numvytes : " << numBytes << endl;

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





