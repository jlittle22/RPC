

// !! Serializer Package requirements !!

#include <string>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
using namespace std;
#ifndef ARITHMETIC_IDL
#define ARITHMETIC_IDL
#include "arithmetic.idl"
#endif

union FloatInt {
  uint32_t i;
  float f;
};


// !! Proxy Package requirements !!

#include "rpcproxyhelper.h"
#include "c150debug.h"
#define STD_READ_SIZE 20
using namespace C150NETWORK;


// !! Network Formatter Package requirements !!

#include <stdexcept>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include <inttypes.h>


// !! Proxy Package forward declarations !!

int add(int x, int y);
int divide(int x, int y);
int multiply(int x, int y);
int subtract(int x, int y);


// !! Serializer Package forward declarations !!


string serialize_int(int x);
int deserialize_int(string x);
string serialize_string(string x);
string deserialize_string(string x);
string serialize_float(float x);
float deserialize_float(string x);

// !! Network Formatter Package forward declarations !!


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
    

// !! Proxy Package functions !!


int add(int x, int y) {
    char readBuffer[STD_READ_SIZE];
    readBuffer[0] = 'J';  // sanity check
    NetworkFormatter f = NetworkFormatter();
    f.setFunctionName("add");
    f.setFunctionRetType("int", sizeof(int));
    f.appendArg("int", sizeof(int), serialize_int(x));
    f.appendArg("int", sizeof(int), serialize_int(y));
    string data = f.networkForm();
    RPCPROXYSOCKET->write(data.c_str(), data.length());
    RPCPROXYSOCKET->read(readBuffer, 1);
    if (readBuffer[0] != '0') {
        throw C150Exception("int add(int x, int y): call not recognized by the server.");
    }
    RPCPROXYSOCKET->read(readBuffer, sizeof(int));
    string resultStr(readBuffer, sizeof(int));
    return deserialize_int(resultStr);
}

int divide(int x, int y) {
    char readBuffer[STD_READ_SIZE];
    readBuffer[0] = 'J';  // sanity check
    NetworkFormatter f = NetworkFormatter();
    f.setFunctionName("divide");
    f.setFunctionRetType("int", sizeof(int));
    f.appendArg("int", sizeof(int), serialize_int(x));
    f.appendArg("int", sizeof(int), serialize_int(y));
    string data = f.networkForm();
    RPCPROXYSOCKET->write(data.c_str(), data.length());
    RPCPROXYSOCKET->read(readBuffer, 1);
    if (readBuffer[0] != '0') {
        throw C150Exception("int divide(int x, int y): call not recognized by the server.");
    }
    RPCPROXYSOCKET->read(readBuffer, sizeof(int));
    string resultStr(readBuffer, sizeof(int));
    return deserialize_int(resultStr);
}

int multiply(int x, int y) {
    char readBuffer[STD_READ_SIZE];
    readBuffer[0] = 'J';  // sanity check
    NetworkFormatter f = NetworkFormatter();
    f.setFunctionName("multiply");
    f.setFunctionRetType("int", sizeof(int));
    f.appendArg("int", sizeof(int), serialize_int(x));
    f.appendArg("int", sizeof(int), serialize_int(y));
    string data = f.networkForm();
    RPCPROXYSOCKET->write(data.c_str(), data.length());
    RPCPROXYSOCKET->read(readBuffer, 1);
    if (readBuffer[0] != '0') {
        throw C150Exception("int multiply(int x, int y): call not recognized by the server.");
    }
    RPCPROXYSOCKET->read(readBuffer, sizeof(int));
    string resultStr(readBuffer, sizeof(int));
    return deserialize_int(resultStr);
}

int subtract(int x, int y) {
    char readBuffer[STD_READ_SIZE];
    readBuffer[0] = 'J';  // sanity check
    NetworkFormatter f = NetworkFormatter();
    f.setFunctionName("subtract");
    f.setFunctionRetType("int", sizeof(int));
    f.appendArg("int", sizeof(int), serialize_int(x));
    f.appendArg("int", sizeof(int), serialize_int(y));
    string data = f.networkForm();
    RPCPROXYSOCKET->write(data.c_str(), data.length());
    RPCPROXYSOCKET->read(readBuffer, 1);
    if (readBuffer[0] != '0') {
        throw C150Exception("int subtract(int x, int y): call not recognized by the server.");
    }
    RPCPROXYSOCKET->read(readBuffer, sizeof(int));
    string resultStr(readBuffer, sizeof(int));
    return deserialize_int(resultStr);
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
//    <functionName>,<returnType>(<size>){,<argType>(<size>),<argData>} ...
//
// Example:
//
//    int foo(float x, myStruct y)
//
//        ==
//
//    foo,int(4),float(4),xxxx,myStruct(10),yyyyyyyyyy
//
// Glossary & Other Hints:
//
// { ... } -- content between curly brackets is OPTIONAL and can be REPEATED. 
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
    