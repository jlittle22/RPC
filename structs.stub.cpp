#include <string>
using namespace std;          // for C++ std library

#ifndef STRUCTS_IDL
#define STRUCTS_IDL
#include "structs.idl"
#endif

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
  
void __findOtherPerson(StructWithArrays x) {
  Person res = findOtherPerson(x);

  string forTheWire = serialize(res);

  RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}


void __findPerson(ThreePeople tp) {
  c150debug->printf(C150RPCDEBUG, "structs.stubs.cpp: invoking __findPerson(ThreePeople)");
  Person res = findPerson(tp);

  string forTheWire = serialize(res);

  c150debug->printf(C150RPCDEBUG, "structs.stubs.cpp: returned from  __findPerson(ThreePeople) -- responding to client");
  RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}

void __area(rectangle r) {
  c150debug->printf(C150RPCDEBUG, "structs.stubs.cpp: invoking __area(rectangle)");
  int res = area(r);

  cout << "Area Res (no serialization): " << res << endl;

  const char * resStr = serialize(res).c_str();
  for (int i = 0; i < 4; i++) {
    cout << i << " : " << int(resStr[i]) << endl;
  }

  string forTheWire = serialize(res);

  c150debug->printf(C150RPCDEBUG, "structs.stubs.cpp: returned from  __area(rectangle) -- responding to client");
  RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
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

  cout << "top of dispatch" << endl;

  
  int numBytes = getFunctionCallFromStream(functionCallBuffer,sizeof(functionCallBuffer));


  cout << "get function call domne" << endl;

  string offTheWire(functionCallBuffer, numBytes);

  NetworkFormatter f = NetworkFormatter(offTheWire);
  cout << "checking which function to call" << endl;
  if (!RPCSTUBSOCKET-> eof()) {
    if (f.getFunctionSignature() == "findPerson,Person(-1),ThreePeople(-1)") {
      cout << "trying to call findPerson" << endl;
      string argDataStr1 = get<2>(f.getArgAtIndex(0));
      for (int i = 0; i < argDataStr1.length(); i++) {
        cout << i << " : " << int(argDataStr1[i]);
        if(isalnum(argDataStr1[i])) {
          cout << " (" << argDataStr1[i] << ")";
        }
        cout << endl;
      }
      __findPerson(deserialize_ThreePeople(argDataStr1));
    } else if (f.getFunctionSignature() == "area,int(4),rectangle(-1)") {
      cout << "trying to call area" << endl;
      string argDataStr1 = get<2>(f.getArgAtIndex(0));

      __area(deserialize_rectangle(argDataStr1));
    } else if (f.getFunctionSignature() == "findOtherPerson,Person(-1),StructWithArrays(-1)") {
      string argDataStr1 = get<2>(f.getArgAtIndex(0));

      __findOtherPerson(deserialize_StructWithArrays(argDataStr1));
    } else {
      cout << "bad func: " << f.getFunctionSignature() << endl;
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


