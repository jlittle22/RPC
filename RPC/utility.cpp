#include "utility.h"
#include <stdexcept>
#include <iostream>

using namespace std;

NetworkFormatter::NetworkFormatter() {
	functionName = "";
	returnType = make_tuple("", 0);
}

NetworkFormatter::NetworkFormatter(string offTheWire) {

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
    while (1) {

    	//////
    	// Find the next occurrence of '(' in this section...
    	int endOfArgTypeNameIndex = offTheWire.find_first_of("(", currSectionStart);

    	// If no such '(' exists, then we have finished reading all of the arguments.
        if (endOfArgTypeNameIndex == string::npos) {
	    	break;
	    }

	    string argTypeName = offTheWire.substr(currSectionStart, endOfArgTypeNameIndex - currSectionStart);
	    // Otherwise, take the substring from the start of the section to the '(' to be the arg type name.
	    //////

	    //////
	    // Find the next ')'...
	    int endOfArgSizeIndex = offTheWire.find_first_of(")", endOfArgTypeNameIndex + 1);
        if (endOfArgSizeIndex == string::npos) {
		    throw runtime_error("NetworkFormatter::NetworkFormatter(string offTheWire) -- no ')' located for the arg type size...");
	    }

        // Take what's between the '(' and ')' as an integer representing the size of the arg type...
	    int argTypeSize = stoi(offTheWire.substr(endOfArgTypeNameIndex + 1, endOfArgSizeIndex - endOfArgTypeNameIndex - 1));

	    // Read the next argTypeSize as the data representing the argument...
	    string argData = offTheWire.substr(endOfArgSizeIndex + 2, argTypeSize);

	    args.emplace_back(make_tuple(argTypeName, argTypeSize, argData));
	    // Add the argument as a tuple to our vector.
	    //////

	    // Update the currSectionStart for the next iteration of the loop.
	    currSectionStart = endOfArgSizeIndex + argTypeSize + 3;
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
	if (index >= 0 && index < args.size()) return args[index];
	else throw runtime_error("NetworkFormatter::getArgAtIndex -- index " + to_string(index) + " out of bounds... [0, " + to_string(args.size()) + "]");
}
  
int NetworkFormatter::getNumArgs() {
    return args.size();
}

// TODO @Jake: Still figuring out how / if this will be used. Ignore for now.
std::string NetworkFormatter::getFunctionSignature() {
    return "";
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

    return res;
}