#ifndef UTILITY_H
#define UTILITY_H

#include <tuple>
#include <vector>
#include <string>
#include <sstream>

template <typename T>
std::string serialize(T item) {
  std::stringstream sstream;

  const char* ptr = reinterpret_cast<char*>(&item);
  sstream.write(ptr, sizeof(T));

  return sstream.str();
}

template <typename T>
T deserialize(std::string x) {
    T new_item;
    std::stringstream ss(x);
    ss.read(reinterpret_cast<char*>(&new_item), sizeof(T));

    return new_item;
}

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
    std::vector<std::tuple<std::string, int, std::string>> args;  // type name, size, data
    std::string functionName;
    std::tuple<std::string, int> returnType;
};


#endif