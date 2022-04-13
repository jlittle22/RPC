#ifndef UTILITY_H
#define UTILITY_H

#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include <arpa/inet.h>
#include <inttypes.h>

// void, int, float, string
// 

/*     for (int i = 0; i < data.length(); i++) {
        cerr << i << " : " << int(data[i]);
        if (isalnum(data[i])) {
            cerr << " (" << data[i] << ")"; 
        }

        cerr << endl;
    }*/

// string x = "this is a long strng that has lots of data";

// -> string(43),this is a long string that has lots of data

// Need more sophisticated method of serializing and deserializing for 
// string and string-based custom types.

// Need helper method used to get size of variable in bytes
// regardless of POD or variable-length... used in serialization
// and in the network form (length of args)

// getsizeof(x) --> 32 --> 12. <-- needs to work for structs and such... ??
// 
// Person {
//   string name; -> "jake little"
//   string age;  -> "twenty two"
// } 
///

// seriali

//. serialize(Person x)...
//.     res = serialize(x.name) + serialize(x.age)
//.     return res. 
//
//.   x -->  Person(22),jake little\0 twenty two\0
//

// deserialize (string x)...
// 
//    

// Person incoming = reinterpret_cast<Person*>(char_ptr);

// If we can figure out how to do those two things, then the 
// network formatter can stay the same and the stubs 
// will also basically be the same (I think?)... need to investigate how 
// string deserialization will work...

// Also endianness being the same is no guaranteed so we need to address
// that:

// convert all integer and float values to big endian for network

// 1234 --> "1234"
// 2.12354456363 --> ""

// Struct offsets not necessarily the same on all machines

// hard-coded serialize / deserialize for each struct in our type system..


class NetworkFormatter {
  public:
	NetworkFormatter();                        // ... for WRITING to the network
	NetworkFormatter(std::string offTheWire);  // ... for READING from the network
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
    std::vector<std::tuple<std::string, int, std::string>> args;  // type name, size, data
    std::string functionName;
    int networkFormLength;
    std::tuple<std::string, int> returnType;
};


#endif