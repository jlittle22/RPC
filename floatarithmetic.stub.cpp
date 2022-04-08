
#include "floatarithmetic.idl"

#include "rpcstubhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "./RPC/utility.h"

using namespace C150NETWORK;  // for all the comp150 utilities 

void getFunctionCallFromStream();

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
  
  // read args from stream
// call function 1
// sends done 

float __add(float x, float y) {
  char doneBuffer[5] = "DONE";  // to write magic value DONE + null

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: invoking __add()");
  float res = add(x, y);

  //
  // Send the response to the client
  //
  // If add returned something other than void, this is
  // where we'd send the return value back.
  //

  // check if void
  // send return value back?? 
  // am confused - do you send result or the done?
  // should we not read into a read buffer?

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: returned from  __add() -- responding to client");
  RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
}

void __subtract(float x, float y) {
  char doneBuffer[5] = "DONE";  // to write magic value DONE + null

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: invoking __subtract()");
  float res = subtract(x, y);

  //
  // Send the response to the client
  //
  // If subtract returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: returned from  __subtract() -- responding to client");
  RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
}

void __multiply(float x, float y) {
  char doneBuffer[5] = "DONE";  // to write magic value DONE + null

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: invoking __multiply()");
  float res = multiply(x, y);

  //
  // Send the response to the client
  //
  // If multiply returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: returned from  __multiply() -- responding to client");
  RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
}


void __divide(float x, float y) {
  char doneBuffer[5] = "DONE";  // to write magic value DONE + null

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: invoking __divide()");
  float res = divide(x, y);

  //
  // Send the response to the client
  //
  // If divide returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: returned from  __divide() -- responding to client");
  RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
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
void getFunctionNameFromStream(char *buffer, unsigned int bufSize); // @BELLA: function call subject to change



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

  
  getFunctionCallFromStream(functionNameBuffer,sizeof(functionCallBuffer));
 
  string offTheWire(functionNameBuffer, 500);

  NetworkFormatter f = NetworkFormatter(offTheWire);
  string functionName = f.getFunctionName();
  auto [ returnTypeName, returnTypeSize ] = f.getFunctionRetType();

  for (int i = 0; i < f.getNumArgs(); i++) {
      auto [ argTypeName, argTypeSize, dataString ] = f.getArgAtIndex(i);
  }

  // should we be using this?? to get the first one?

  //
  // We've read the function name, call the stub for the right one
  // The stub will invoke the function and send response.
  //

  // signaturecompare()
  // then create a big switch statement thing to check the incoming signature 
  // against each of the signatures we read from the idl_to_json...

  if (!RPCSTUBSOCKET-> eof()) {
    if (strcmp(functionCallBuffer,"add,float(4),float(4),float(4)") == 0)
      float x = f.getArgAtIndex(0);
      float y = f.getArgAtIndex(1); // wrong???
      // whateverFunctionJakeWrites(&x, &y);
      __add(x,y); // __add(x, y)
    else   if (strcmp(functionCallBuffer,"subtract,float(4),float(4),float(4)") == 0)
      float x = f.getArgAtIndex(0);
      float y = f.getArgAtIndex(1);
      // whateverFunctionJakeWrites(&x, &y);
      __subtract(x,y); // __add(x, y)
    else   if (strcmp(functionCallBuffer,"multiply,float(4),float(4),float(4)") == 0)
      float x = f.getArgAtIndex(0);
      float y = f.getArgAtIndex(1);
      // whateverFunctionJakeWrites(&x, &y);
      __multiply(x,y); // __add(x, y)
    else if (strcmp(functionCallBuffer,"divide,float(4),float(4),float(4)") == 0)
      float x = f.getArgAtIndex(0);
      float y = f.getArgAtIndex(1);
      // whateverFunctionJakeWrites(&x, &y);
      __divide(x,y); // __add(x, y)
    else
      __badFunction(functionCallBuffer);
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
void getFunctionCallFromStream(char *buffer, unsigned int bufSize) {
  unsigned int i;
  char *bufp;    // next char to read
  bool readnull;
  ssize_t readlen;             // amount of data read from socket
  
  //
  // Read a message from the stream
  // -1 in size below is to leave room for null
  //
  readnull = false;
  bufp = buffer;
  for (i=0; i< bufSize; i++) {
    readlen = RPCSTUBSOCKET-> read(bufp, 1);  // read a byte
    // check for eof or error
    if (readlen == 0) {
      break;
    }
    // check for null and bump buffer pointer
    if (*bufp++ == '\0') {
      readnull = true;
      break;
    }
  }
  
  //
  // With TCP streams, we should never get a 0 length read
  // except with timeouts (which we're not setting in pingstreamserver)
  // or EOF
  //
  if (readlen == 0) {
    c150debug->printf(C150RPCDEBUG,"simplefunction.stub: read zero length message, checking EOF");
    if (RPCSTUBSOCKET-> eof()) {
      c150debug->printf(C150RPCDEBUG,"simplefunction.stub: EOF signaled on input");

    } else {
      throw C150Exception("simplefunction.stub: unexpected zero length read without eof");
    }
  }

  //
  // If we didn't get a null, input message was poorly formatted
  //
  else if(!readnull) 
    throw C150Exception("simplefunction.stub: method name not null terminated or too long");

  
  //
  // Note that eof may be set here for our caller to check
  //

}


