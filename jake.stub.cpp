//
// jake.stub.cpp
//
// C++ file created by rpcgenerate.
//
// Meta-authors: John Little and Isabella Urdahl
//

// !! Serializer Package requirements !!

#include <string>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
using namespace std;
#ifndef JAKE_IDL
#define JAKE_IDL
#include "jake.idl"
#endif

union FloatInt {
  uint32_t i;
  float f;
};


// !! Stub Package requirements !!

#include "rpcstubhelper.h"
#include "c150debug.h"
#include "c150grading.h"
using namespace C150NETWORK;


// !! Network Formatter Package requirements !!

#include <stdexcept>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include <inttypes.h>


// !! Stub Package forward declarations !!


void __badFunction();
int getNumBytesInIncomingFunctionCall(char *buffer);
int getFunctionCallFromStream(char *buffer, unsigned int bufSize);
void __nothelpful(StupidWeird x);
void __reallynothelpful(StupidWeird x[10]);
void __useless(MT x);
void dispatchFunction();

// !! Serializer Package forward declarations !!


string serialize_int(int x);
int deserialize_int(string x);
string serialize_string(string x);
string deserialize_string(string x);
string serialize_float(float x);
float deserialize_float(string x);
string serialize_MT(MT x);
MT deserialize_MT(string x);
string serialize_Person(Person x);
Person deserialize_Person(string x);
string serialize_StupidWeird(StupidWeird x);
StupidWeird deserialize_StupidWeird(string x);
string serialize_Array_MT_5(MT x[5]);
void deserialize_Array_MT_5(string x, MT* dest);
string serialize_Array_Person_10(Person x[10]);
void deserialize_Array_Person_10(string x, Person* dest);
string serialize_Array_StupidWeird_10(StupidWeird x[10]);
void deserialize_Array_StupidWeird_10(string x, StupidWeird* dest);
string serialize_Array_float_20(float x[20]);
void deserialize_Array_float_20(string x, float* dest);

// !! Network Formatter Package forward declarations !!


// Class to handle all network formatting of data. See definitions below
// for more detail comments.
class NetworkFormatter {
  public:
    NetworkFormatter();
    NetworkFormatter(std::string offTheWire);
    ~NetworkFormatter();
    void setFunctionName(std::string name);
    std::string getFunctionName();
    void setFunctionRetType(std::string type, int typeSize);
    std::tuple<std::string, int> getFunctionRetType();
    void appendArg(std::string argTypeName, int argTypeSize, std::string argData);
    std::tuple<std::string, int, std::string> getArgAtIndex(int index);
    int getNumArgs();
    std::string getFunctionSignature();
    std::string networkForm();
  private:
    std::vector<std::tuple<std::string, int, std::string>> args;
    std::string functionName;
    int networkFormLength;
    std::tuple<std::string, int> returnType;
};
    

// !! Stub Package functions !!


void __badFunction() {
    // Any good function call must result in '0' in the first
    // byte of the response... so send 'I' for Isabella.
    char buf[2] = "I";
    RPCSTUBSOCKET->write(buf, 1);
}

int getNumBytesInIncomingFunctionCall(char *buffer) {
  unsigned int i;
  char *bufp;
  ssize_t readlen;
  unsigned int numBytes;
  bufp = buffer;

  // Read the first four bytes of the stream...
  for (i = 0; i < sizeof(numBytes); i++) {
    readlen = RPCSTUBSOCKET-> read(bufp, 1);
    if (readlen == 0) {
      break;
    }
    bufp++;
  }

  // Error handle in the event that the stream dies.
  if (readlen == 0) {
    if (RPCSTUBSOCKET->eof()) {
      *GRADING << "[getNumBytesInIncomingFunctionCall] Client signaled EOF before calling a function." << endl;
      c150debug->printf(C150RPCDEBUG, "Client signaled EOF before calling function");
      return 0;
    } else {
      throw C150Exception("unexpected zero length read without eof");
    }
  }

  // Convert the first four bytes into a string...
  string numBytesStr(buffer, sizeof(numBytes));

  // Deserialize as an int (representing the number of bytes to come)
  numBytes = deserialize_int(numBytesStr);
  return numBytes;
}

// Adapted from Noah's getFunctionName function!
int getFunctionCallFromStream(char *buffer, unsigned int bufSize) {
  unsigned int i;
  char *bufp;
  ssize_t readlen;
  unsigned int numBytes;

 // We already read four bytes and don't want to overwrite them.
  bufp = buffer + sizeof(numBytes);
  string numBytesStr(buffer, sizeof(numBytes));
  numBytes = deserialize_int(numBytesStr);

 // Read until we have read enough bytes OR our buffer is full.
  for (i = 0; i < bufSize && i < numBytes; i++) {
    readlen = RPCSTUBSOCKET-> read(bufp, 1);
    if (readlen == 0) {
      break;
    }
    bufp++;
  }

 // Error handle in the event that the stream dies.
  if (readlen == 0) {
    c150debug->printf(C150RPCDEBUG,"read zero length message, checking EOF");
    if (RPCSTUBSOCKET-> eof()) {
      *GRADING << "[getFunctionCallFromStream] Client signaled EOF before calling a function." << endl;
      c150debug->printf(C150RPCDEBUG,"EOF signaled on input");
    } else {
      throw C150Exception("unexpected zero length read without eof");
    }
  }

 // If our buffer filled up without reading all bytes...
  if (i < numBytes && i >= bufSize) {
    throw C150Exception("Incoming message was larger than bufSize");
  }
  return numBytes;
}

void __nothelpful(StupidWeird x) {
  *GRADING << "[nothelpful (stub)] Entering stub function." << endl;
    float result = nothelpful(x);
    string forTheWire = '0' + serialize_float(result);
   *GRADING << "[nothelpful (stub)] Result acquired. Writing " << forTheWire.length() << " bytes to client." << endl;
    RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}

void __reallynothelpful(StupidWeird x[10]) {
  *GRADING << "[reallynothelpful (stub)] Entering stub function." << endl;
    float result = reallynothelpful(x);
    string forTheWire = '0' + serialize_float(result);
   *GRADING << "[reallynothelpful (stub)] Result acquired. Writing " << forTheWire.length() << " bytes to client." << endl;
    RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}

void __useless(MT x) {
  *GRADING << "[useless (stub)] Entering stub function." << endl;
    MT result = useless(x);
    string forTheWire = '0' + serialize_MT(result);
   *GRADING << "[useless (stub)] Result acquired. Writing " << forTheWire.length() << " bytes to client." << endl;
    RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}

void dispatchFunction() {
  char numBytesBuf[sizeof(int)];

  // Read the number of incoming bytes from the stream...
  int numBytesIncoming = sizeof(numBytesBuf) + getNumBytesInIncomingFunctionCall(numBytesBuf);
  if (numBytesIncoming == sizeof(numBytesBuf)) return;
  *GRADING << "[dispatchFunction] Preparing to read " << numBytesIncoming << " bytes from stream." << endl;

  // Create an appropriately sized buffer for the data...
  char functionCallBuffer[numBytesIncoming];

  // Copy over the first few bytes that we already read into the new buffer...
  for (size_t i = 0; i < sizeof(numBytesBuf); i++) {
    functionCallBuffer[i] = numBytesBuf[i];
  }

  // Read the remaining bytes of data.
  int numBytesRead = getFunctionCallFromStream(functionCallBuffer,sizeof(functionCallBuffer));
  if (numBytesRead == 0) return;
  string offTheWire(functionCallBuffer, sizeof(int) + numBytesRead);
  NetworkFormatter f = NetworkFormatter(offTheWire);
  if (!RPCSTUBSOCKET-> eof()) {
    *GRADING << "[dispatchFunction] Looking for function with matching signature: " << f.getFunctionSignature() << endl;

    // Identify the appropriate function and call it...
    if (f.getFunctionSignature() == "nothelpful,float(4),StupidWeird(-1)") {
      *GRADING << "[dispatchFunction] Signature match found!" << endl;
      StupidWeird x = deserialize_StupidWeird(get<2>(f.getArgAtIndex(0)));
      __nothelpful(x);
    } else if (f.getFunctionSignature() == "reallynothelpful,float(4),Array_StupidWeird_10(-1)") {
      *GRADING << "[dispatchFunction] Signature match found!" << endl;
      StupidWeird x[10];
      deserialize_Array_StupidWeird_10(get<2>(f.getArgAtIndex(0)), (StupidWeird*)x);
      __reallynothelpful(x);
    } else if (f.getFunctionSignature() == "useless,MT(-1),MT(-1)") {
      *GRADING << "[dispatchFunction] Signature match found!" << endl;
      MT x = deserialize_MT(get<2>(f.getArgAtIndex(0)));
      __useless(x);
    } else {
        *GRADING << "[dispatchFunction] No matching signature. Bad function." << endl;
        __badFunction();
    }
  }
}


// !! Serializer Package functions !!


string serialize_int(int x) {
  uint32_t network_x = htonl((uint32_t)x);
  stringstream sstream;
  const char* ptr = reinterpret_cast<char*>(&network_x);
  sstream.write(ptr, sizeof(network_x));
  return sstream.str();
}

int deserialize_int(string x) {
  uint32_t new_item;
  std::stringstream ss(x);
  ss.read(reinterpret_cast<char*>(&new_item), sizeof(new_item));
  return (int)ntohl(new_item);
}

string serialize_string(string x) {
  return serialize_int((int)x.length()) + x;
}

string deserialize_string(string x) {
  int str_size = deserialize_int(x.substr(0, sizeof(int)));
  return x.substr(sizeof(int), str_size);
}

string serialize_float(float x) {
  FloatInt conv;
  conv.f = x;
  return serialize_int((int)conv.i);
}

float deserialize_float(string x) {
  int new_item = deserialize_int(x);
  FloatInt conv;
  conv.i = (uint32_t)new_item;
  return conv.f;
}

string serialize_MT(MT x) {
    string data = "";
    return serialize_int((int)data.length()) + data;
}

MT deserialize_MT(string x) {
    MT new_item;

    return new_item;
}

string serialize_Person(Person x) {
    string data = "";
    data += serialize_string(x.name);
    data += serialize_Array_float_20(x.array);
    return serialize_int((int)data.length()) + data;
}

Person deserialize_Person(string x) {
    Person new_item;
    int len = sizeof(int);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    new_item.name = deserialize_string(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    deserialize_Array_float_20(x.substr(0, len), (float*)new_item.array);

    return new_item;
}

string serialize_StupidWeird(StupidWeird x) {
    string data = "";
    data += serialize_Array_MT_5(x.arr);
    data += serialize_Array_Person_10(x.arr2);
    return serialize_int((int)data.length()) + data;
}

StupidWeird deserialize_StupidWeird(string x) {
    StupidWeird new_item;
    int len = sizeof(int);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    deserialize_Array_MT_5(x.substr(0, len), (MT*)new_item.arr);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    deserialize_Array_Person_10(x.substr(0, len), (Person*)new_item.arr2);

    return new_item;
}

string serialize_Array_MT_5(MT x[5]) {
    string data = "";
    for (int i = 0; i < 5; i++) {
        data += serialize_MT(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_MT_5(string x, MT* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 5; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        dest[i] = deserialize_MT(x.substr(0, len));
        x = x.substr(len);
    }
}

string serialize_Array_Person_10(Person x[10]) {
    string data = "";
    for (int i = 0; i < 10; i++) {
        data += serialize_Person(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_Person_10(string x, Person* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 10; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        dest[i] = deserialize_Person(x.substr(0, len));
        x = x.substr(len);
    }
}

string serialize_Array_StupidWeird_10(StupidWeird x[10]) {
    string data = "";
    for (int i = 0; i < 10; i++) {
        data += serialize_StupidWeird(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_StupidWeird_10(string x, StupidWeird* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 10; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        dest[i] = deserialize_StupidWeird(x.substr(0, len));
        x = x.substr(len);
    }
}

string serialize_Array_float_20(float x[20]) {
    string data = "";
    for (int i = 0; i < 20; i++) {
        data += serialize_float(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_float_20(string x, float* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 20; i++) {
        len = sizeof(float);
        dest[i] = deserialize_float(x.substr(0, len));
        x = x.substr(len);
    }
}


// !! Network Formatter Package functions !!


NetworkFormatter::NetworkFormatter() {
    functionName = "";
    returnType = make_tuple("", 0);
    networkFormLength = 0;
}

NetworkFormatter::NetworkFormatter(string offTheWire) {
    int numBytes = (*reinterpret_cast<const int*>(offTheWire.c_str()));

    offTheWire = offTheWire.substr(sizeof(int), numBytes + sizeof(int));
 
    //////
    // Find the first occurrence of ','... this character indicates the end of the function name
    size_t endOfNameIndex = offTheWire.find_first_of(",");
    if (endOfNameIndex == string::npos) {
        throw runtime_error("NetworkFormatter::NetworkFormatter(string offTheWire) -- no ',' located for the function name...");
    }
    functionName = offTheWire.substr(0, endOfNameIndex);
    // Take the substring representing the function name...
    //////

    //////
    // Find the next occurrence of '('...
    size_t endOfReturnTypeIndex = offTheWire.find_first_of("(", endOfNameIndex + 1);
    if (endOfReturnTypeIndex == string::npos) {
        throw runtime_error("NetworkFormatter::NetworkFormatter(string offTheWire) -- no '(' located for the return type name...");
    }
    string returnTypeName = offTheWire.substr(endOfNameIndex + 1, endOfReturnTypeIndex - endOfNameIndex - 1);

    // Take that substring representing the return type name...
    //////

    //////
    // Find the next occurence of ')'...
    size_t endOfReturnTypeSizeIndex = offTheWire.find_first_of(")", endOfReturnTypeIndex);
    if (endOfReturnTypeSizeIndex == string::npos) {
        throw runtime_error("NetworkFormatter::NetworkFormatter(string offTheWire) -- no ')' located for the return type size...");
    }
    int returnTypeSize = stoi(offTheWire.substr(endOfReturnTypeIndex + 1, endOfReturnTypeSizeIndex - endOfReturnTypeIndex - 1));
    // Take the subtring between the '(' and ')' as the return type size...
    //////

    //////
    // Set the return type as a tuple.
    returnType = make_tuple(returnTypeName, returnTypeSize);
    //////


    int currSectionStart = endOfReturnTypeSizeIndex + 2;
    while (currSectionStart <= (int)offTheWire.length()) {
        //////
        // Find the next occurrence of '(' in this section...
        size_t endOfArgTypeNameIndex = offTheWire.find_first_of("(", currSectionStart);

        // If no such '(' exists, then we have finished reading all of the arguments.
        if (endOfArgTypeNameIndex == string::npos) {
            break;
        }

        string argTypeName = offTheWire.substr(currSectionStart, endOfArgTypeNameIndex - currSectionStart);
        // Otherwise, take the substring from the start of the section to the '(' to be the arg type name.
        //////

        //////
        // Find the next ')'...
        size_t endOfArgSizeIndex = offTheWire.find_first_of(")", endOfArgTypeNameIndex + 1);
        if (endOfArgSizeIndex == string::npos) {
            throw runtime_error("NetworkFormatter::NetworkFormatter(string offTheWire) -- no ')' located for the arg type size...");
        }

        // Take what's between the '(' and ')' as an integer representing the size of the arg type...
        int argTypeSize = stoi(offTheWire.substr(endOfArgTypeNameIndex + 1, endOfArgSizeIndex - endOfArgTypeNameIndex - 1));

        int dataSize = argTypeSize == -1 ? sizeof(int) + deserialize_int(offTheWire.substr(endOfArgSizeIndex + 2, sizeof(int))) : argTypeSize; 
        
        // Read the next argTypeSize as the data representing the argument...
        string argData = offTheWire.substr(endOfArgSizeIndex + 2, dataSize);
        args.emplace_back(make_tuple(argTypeName, argTypeSize, argData));
        // Add the argument as a tuple to our vector.
        //////

        // Update the currSectionStart for the next iteration of the loop.
        currSectionStart = endOfArgSizeIndex + dataSize + 3;
    }   
}

NetworkFormatter::~NetworkFormatter() { }

void NetworkFormatter::setFunctionName(std::string name) {
    functionName = name;
}

std::string NetworkFormatter::getFunctionName() {
    return functionName;
}

void NetworkFormatter::setFunctionRetType(std::string type, int typeSize) {
    returnType = make_tuple(type, typeSize);
}

std::tuple<std::string, int> NetworkFormatter::getFunctionRetType() {
    return returnType;
}

void NetworkFormatter::appendArg(std::string argTypeName, int argTypeSize, std::string argData) {
    args.emplace_back(make_tuple(argTypeName, argTypeSize, argData));
}
  
std::tuple<std::string, int, std::string> NetworkFormatter::getArgAtIndex(int index) {
    if (index >= 0 && index < (int)args.size()) return args[index];
    else throw runtime_error("NetworkFormatter::getArgAtIndex -- index " + to_string(index) + " out of bounds... [0, " + to_string(args.size()) + "]");
}
  
int NetworkFormatter::getNumArgs() {
    return args.size();
}

std::string NetworkFormatter::getFunctionSignature() {
    string sig = functionName + "," + get<0>(returnType) + "(" + to_string(get<1>(returnType)) + ")";

    // For each argument in our vector...
    for (auto it : args) {
        // Add a component of the form: {,<argType>(<size>)}
        sig += "," + get<0>(it) + "(" + to_string(get<1>(it)) + ")";
    }

    return sig;
}

//////
//
// NETWORK FORM:
//
//    <numBytes><functionName>,<returnType>(<size>){,<argType>(<size>),<argData>} ...
//
// Example:
//
//    int foo(float x, myStruct y)
//
//        ==
//
//    foo,int(4),float(4),xxxx,myStruct(-1),yyyyyyyyyy
//
// Glossary & Other Hints:
//
// { ... } -- content between curly brackets is OPTIONAL and can be REPEATED. 
//
// <numBytes> -- four bytes representng a machine integer containing length of the function call in bytes.
//
// <functionName> -- a string of any length representing the name of the function being called.
// 
// <returnType> -- a string representing the return type of the function... can be "void".
//
// <size> -- a non-negative integer representing the number of bytes associated with a type.
//
// <argType> -- a string representing the type of an argument to the function.
//
// <argData> -- a string representing the data intended to be interpreted as an argument to the function.
//
//////

string NetworkFormatter::networkForm() {
    // Add the required: <functionName>,<returnType>(<size>)
    string res = functionName + "," + get<0>(returnType) + "(" + to_string(get<1>(returnType)) + ")";

    // For each argument in our vector...
    for (auto it : args) {
        // Add a component of the form: {,<argType>(<size>),<argData>}
        res += "," + get<0>(it) + "(" + to_string(get<1>(it)) + ")," + get<2>(it);
    }

    res = serialize_int((int)res.length()) + res;

    return res;
}
    