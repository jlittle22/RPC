

// !! Serializer Package requirements !!

#include <string>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
using namespace std;
#ifndef STRUCTWITHARRAY_IDL
#define STRUCTWITHARRAY_IDL
#include "structwitharray.idl"
#endif

union FloatInt {
  uint32_t i;
  float f;
};


// !! Stub Package requirements !!

#include "rpcstubhelper.h"
#include "c150debug.h"
#define FUNC_CALL_BUFFER_SIZE 50000
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
void __area(rectangle r);
void __fake(int arr[10][10]);
void __findOtherPerson(StructWithArrays x);
void __findPerson(ThreePeople tp);
void __getValueAt(int arr[10][10], int i, int j);
void __nonVoidFuncThatTakesALot(int x, float y, Person z);
void __tough(int arr[1][2][3][4][5][6][7][8]);
void __voidFuncThatTakesALot(int x, float y, Person z);
void dispatchFunction();

// !! Serializer Package forward declarations !!


string serialize_int(int x);
int deserialize_int(string x);
string serialize_string(string x);
string deserialize_string(string x);
string serialize_float(float x);
float deserialize_float(string x);
string serialize_Person(Person x);
Person deserialize_Person(string x);
string serialize_StructWithArrays(StructWithArrays x);
StructWithArrays deserialize_StructWithArrays(string x);
string serialize_ThreePeople(ThreePeople x);
ThreePeople deserialize_ThreePeople(string x);
string serialize_Array_Person_10(Person x[10]);
void deserialize_Array_Person_10(string x, Person* dest);
string serialize_Array_int_100(int x[100]);
void deserialize_Array_int_100(string x, int* dest);
string serialize_Array_int_10(int x[10]);
void deserialize_Array_int_10(string x, int* dest);
string serialize_Array_int_10_100(int x[10][100]);
void deserialize_Array_int_10_100(string x, int* dest);
string serialize_Array_int_10_10(int x[10][10]);
void deserialize_Array_int_10_10(string x, int* dest);
string serialize_Array_int_1_2_3_4_5_6_7_8(int x[1][2][3][4][5][6][7][8]);
void deserialize_Array_int_1_2_3_4_5_6_7_8(string x, int* dest);
string serialize_Array_int_2_3_4_5_6_7_8(int x[2][3][4][5][6][7][8]);
void deserialize_Array_int_2_3_4_5_6_7_8(string x, int* dest);
string serialize_Array_int_3_4_5_6_7_8(int x[3][4][5][6][7][8]);
void deserialize_Array_int_3_4_5_6_7_8(string x, int* dest);
string serialize_Array_int_4(int x[4]);
void deserialize_Array_int_4(string x, int* dest);
string serialize_Array_int_4_10(int x[4][10]);
void deserialize_Array_int_4_10(string x, int* dest);
string serialize_Array_int_4_10_100(int x[4][10][100]);
void deserialize_Array_int_4_10_100(string x, int* dest);
string serialize_Array_int_4_5_6_7_8(int x[4][5][6][7][8]);
void deserialize_Array_int_4_5_6_7_8(string x, int* dest);
string serialize_Array_int_5_6_7_8(int x[5][6][7][8]);
void deserialize_Array_int_5_6_7_8(string x, int* dest);
string serialize_Array_int_6_7_8(int x[6][7][8]);
void deserialize_Array_int_6_7_8(string x, int* dest);
string serialize_Array_int_7_8(int x[7][8]);
void deserialize_Array_int_7_8(string x, int* dest);
string serialize_Array_int_8(int x[8]);
void deserialize_Array_int_8(string x, int* dest);
string serialize_rectangle(rectangle x);
rectangle deserialize_rectangle(string x);
string serialize_s(s x);
s deserialize_s(string x);

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
    

// !! Stub Package functions !!

void __badFunction() {
    char buf[2] = "I";
    RPCSTUBSOCKET->write(buf, 1);
}
int getNumBytesInIncomingFunctionCall(char *buffer) {
  unsigned int i;
  char *bufp;
  ssize_t readlen;
  unsigned int numBytes;
  bufp = buffer;
  for (i = 0; i < sizeof(numBytes); i++) {
    readlen = RPCSTUBSOCKET-> read(bufp, 1);
    if (readlen == 0) {
      break;
    }
    bufp++;
  }
  if (readlen == 0) {
    if (RPCSTUBSOCKET->eof()) {
      c150debug->printf(C150RPCDEBUG, "Client signaled EOF before calling function");
      return 0;
    } else {
      throw C150Exception("arithmetic.stub: unexpected zero length read without eof");
    }
  }
  string numBytesStr(buffer, sizeof(numBytes));
  numBytes = deserialize_int(numBytesStr);
  return numBytes;
}
int getFunctionCallFromStream(char *buffer, unsigned int bufSize) {
  unsigned int i;
  char *bufp;
  ssize_t readlen;
  unsigned int numBytes;
  bufp = buffer + sizeof(numBytes);
  string numBytesStr(buffer, sizeof(numBytes));
  numBytes = deserialize_int(numBytesStr);
  for (i = 0; i < bufSize && i < numBytes; i++) {
    readlen = RPCSTUBSOCKET-> read(bufp, 1);
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
  return numBytes;
}

void __area(rectangle r) {
    int result = area(r);
    string forTheWire = '0' + serialize_int(result);
    RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}

void __fake(int arr[10][10]) {
    int result = fake(arr);
    string forTheWire = '0' + serialize_int(result);
    RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}

void __findOtherPerson(StructWithArrays x) {
    Person result = findOtherPerson(x);
    string forTheWire = '0' + serialize_Person(result);
    RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}

void __findPerson(ThreePeople tp) {
    Person result = findPerson(tp);
    string forTheWire = '0' + serialize_Person(result);
    RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}

void __getValueAt(int arr[10][10], int i, int j) {
    int result = getValueAt(arr, i, j);
    string forTheWire = '0' + serialize_int(result);
    RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}

void __nonVoidFuncThatTakesALot(int x, float y, Person z) {
    Person result = nonVoidFuncThatTakesALot(x, y, z);
    string forTheWire = '0' + serialize_Person(result);
    RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}

void __tough(int arr[1][2][3][4][5][6][7][8]) {
    int result = tough(arr);
    string forTheWire = '0' + serialize_int(result);
    RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}

void __voidFuncThatTakesALot(int x, float y, Person z) {
    string forTheWire = "0";
    voidFuncThatTakesALot(x, y, z);
    RPCSTUBSOCKET->write(forTheWire.c_str(), forTheWire.length());
}

void dispatchFunction() {
  char numBytesBuf[sizeof(int)];
  int numBytesIncoming = sizeof(numBytesBuf) + getNumBytesInIncomingFunctionCall(numBytesBuf);
  if (numBytesIncoming == sizeof(numBytesBuf)) return;
 char functionCallBuffer[numBytesIncoming];
  for (size_t i = 0; i < sizeof(numBytesBuf); i++) {
    functionCallBuffer[i] = numBytesBuf[i];
  }
  int numBytesRead = getFunctionCallFromStream(functionCallBuffer,sizeof(functionCallBuffer));
  if (numBytesRead == 0) return;
  string offTheWire(functionCallBuffer, sizeof(int) + numBytesRead);
  NetworkFormatter f = NetworkFormatter(offTheWire);
  if (!RPCSTUBSOCKET-> eof()) {
    if (f.getFunctionSignature() == "area,int(4),rectangle(-1)") {
      rectangle r = deserialize_rectangle(get<2>(f.getArgAtIndex(0)));
      __area(r);
    } else if (f.getFunctionSignature() == "fake,int(4),Array_int_10_10(-1)") {
      int arr[10][10];
      deserialize_Array_int_10_10(get<2>(f.getArgAtIndex(0)), (int*)arr);
      __fake(arr);
    } else if (f.getFunctionSignature() == "findOtherPerson,Person(-1),StructWithArrays(-1)") {
      StructWithArrays x = deserialize_StructWithArrays(get<2>(f.getArgAtIndex(0)));
      __findOtherPerson(x);
    } else if (f.getFunctionSignature() == "findPerson,Person(-1),ThreePeople(-1)") {
      ThreePeople tp = deserialize_ThreePeople(get<2>(f.getArgAtIndex(0)));
      __findPerson(tp);
    } else if (f.getFunctionSignature() == "getValueAt,int(4),Array_int_10_10(-1),int(4),int(4)") {
      int arr[10][10];
      deserialize_Array_int_10_10(get<2>(f.getArgAtIndex(0)), (int*)arr);
      int i = deserialize_int(get<2>(f.getArgAtIndex(1)));
      int j = deserialize_int(get<2>(f.getArgAtIndex(2)));
      __getValueAt(arr, i, j);
    } else if (f.getFunctionSignature() == "nonVoidFuncThatTakesALot,Person(-1),int(4),float(4),Person(-1)") {
      int x = deserialize_int(get<2>(f.getArgAtIndex(0)));
      float y = deserialize_float(get<2>(f.getArgAtIndex(1)));
      Person z = deserialize_Person(get<2>(f.getArgAtIndex(2)));
      __nonVoidFuncThatTakesALot(x, y, z);
    } else if (f.getFunctionSignature() == "tough,int(4),Array_int_1_2_3_4_5_6_7_8(-1)") {
      int arr[1][2][3][4][5][6][7][8];
      deserialize_Array_int_1_2_3_4_5_6_7_8(get<2>(f.getArgAtIndex(0)), (int*)arr);
      __tough(arr);
    } else if (f.getFunctionSignature() == "voidFuncThatTakesALot,void(-1),int(4),float(4),Person(-1)") {
      int x = deserialize_int(get<2>(f.getArgAtIndex(0)));
      float y = deserialize_float(get<2>(f.getArgAtIndex(1)));
      Person z = deserialize_Person(get<2>(f.getArgAtIndex(2)));
      __voidFuncThatTakesALot(x, y, z);
    } else {
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

string serialize_Person(Person x) {
    string data = "";
    data += serialize_string(x.firstname);
    data += serialize_string(x.lastname);
    data += serialize_int(x.age);
    return serialize_int((int)data.length()) + data;
}

Person deserialize_Person(string x) {
    Person new_item;
    int len = sizeof(int);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    new_item.firstname = deserialize_string(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    new_item.lastname = deserialize_string(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int);
    new_item.age = deserialize_int(x.substr(0, len));

    return new_item;
}

string serialize_StructWithArrays(StructWithArrays x) {
    string data = "";
    data += serialize_int(x.aNumber);
    data += serialize_Array_Person_10(x.people);
    return serialize_int((int)data.length()) + data;
}

StructWithArrays deserialize_StructWithArrays(string x) {
    StructWithArrays new_item;
    int len = sizeof(int);

    x = x.substr(len);
    len = sizeof(int);
    new_item.aNumber = deserialize_int(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    deserialize_Array_Person_10(x.substr(0, len), (Person*)new_item.people);

    return new_item;
}

string serialize_ThreePeople(ThreePeople x) {
    string data = "";
    data += serialize_Person(x.p1);
    data += serialize_Person(x.p2);
    data += serialize_Person(x.p3);
    return serialize_int((int)data.length()) + data;
}

ThreePeople deserialize_ThreePeople(string x) {
    ThreePeople new_item;
    int len = sizeof(int);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    new_item.p1 = deserialize_Person(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    new_item.p2 = deserialize_Person(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    new_item.p3 = deserialize_Person(x.substr(0, len));

    return new_item;
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

string serialize_Array_int_100(int x[100]) {
    string data = "";
    for (int i = 0; i < 100; i++) {
        data += serialize_int(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_100(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 100; i++) {
        len = sizeof(int);
        dest[i] = deserialize_int(x.substr(0, len));
        x = x.substr(len);
    }
}

string serialize_Array_int_10(int x[10]) {
    string data = "";
    for (int i = 0; i < 10; i++) {
        data += serialize_int(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_10(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 10; i++) {
        len = sizeof(int);
        dest[i] = deserialize_int(x.substr(0, len));
        x = x.substr(len);
    }
}

string serialize_Array_int_10_100(int x[10][100]) {
    string data = "";
    for (int i = 0; i < 10; i++) {
        data += serialize_Array_int_100(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_10_100(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 10; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_100(x.substr(0, len), dest + (i * 100));
        x = x.substr(len);
    }
}

string serialize_Array_int_10_10(int x[10][10]) {
    string data = "";
    for (int i = 0; i < 10; i++) {
        data += serialize_Array_int_10(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_10_10(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 10; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_10(x.substr(0, len), dest + (i * 10));
        x = x.substr(len);
    }
}

string serialize_Array_int_1_2_3_4_5_6_7_8(int x[1][2][3][4][5][6][7][8]) {
    string data = "";
    for (int i = 0; i < 1; i++) {
        data += serialize_Array_int_2_3_4_5_6_7_8(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_1_2_3_4_5_6_7_8(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 1; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_2_3_4_5_6_7_8(x.substr(0, len), dest + (i * 40320));
        x = x.substr(len);
    }
}

string serialize_Array_int_2_3_4_5_6_7_8(int x[2][3][4][5][6][7][8]) {
    string data = "";
    for (int i = 0; i < 2; i++) {
        data += serialize_Array_int_3_4_5_6_7_8(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_2_3_4_5_6_7_8(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 2; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_3_4_5_6_7_8(x.substr(0, len), dest + (i * 20160));
        x = x.substr(len);
    }
}

string serialize_Array_int_3_4_5_6_7_8(int x[3][4][5][6][7][8]) {
    string data = "";
    for (int i = 0; i < 3; i++) {
        data += serialize_Array_int_4_5_6_7_8(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_3_4_5_6_7_8(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 3; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_4_5_6_7_8(x.substr(0, len), dest + (i * 6720));
        x = x.substr(len);
    }
}

string serialize_Array_int_4(int x[4]) {
    string data = "";
    for (int i = 0; i < 4; i++) {
        data += serialize_int(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_4(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 4; i++) {
        len = sizeof(int);
        dest[i] = deserialize_int(x.substr(0, len));
        x = x.substr(len);
    }
}

string serialize_Array_int_4_10(int x[4][10]) {
    string data = "";
    for (int i = 0; i < 4; i++) {
        data += serialize_Array_int_10(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_4_10(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 4; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_10(x.substr(0, len), dest + (i * 10));
        x = x.substr(len);
    }
}

string serialize_Array_int_4_10_100(int x[4][10][100]) {
    string data = "";
    for (int i = 0; i < 4; i++) {
        data += serialize_Array_int_10_100(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_4_10_100(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 4; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_10_100(x.substr(0, len), dest + (i * 1000));
        x = x.substr(len);
    }
}

string serialize_Array_int_4_5_6_7_8(int x[4][5][6][7][8]) {
    string data = "";
    for (int i = 0; i < 4; i++) {
        data += serialize_Array_int_5_6_7_8(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_4_5_6_7_8(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 4; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_5_6_7_8(x.substr(0, len), dest + (i * 1680));
        x = x.substr(len);
    }
}

string serialize_Array_int_5_6_7_8(int x[5][6][7][8]) {
    string data = "";
    for (int i = 0; i < 5; i++) {
        data += serialize_Array_int_6_7_8(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_5_6_7_8(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 5; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_6_7_8(x.substr(0, len), dest + (i * 336));
        x = x.substr(len);
    }
}

string serialize_Array_int_6_7_8(int x[6][7][8]) {
    string data = "";
    for (int i = 0; i < 6; i++) {
        data += serialize_Array_int_7_8(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_6_7_8(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 6; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_7_8(x.substr(0, len), dest + (i * 56));
        x = x.substr(len);
    }
}

string serialize_Array_int_7_8(int x[7][8]) {
    string data = "";
    for (int i = 0; i < 7; i++) {
        data += serialize_Array_int_8(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_7_8(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 7; i++) {
        len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
        deserialize_Array_int_8(x.substr(0, len), dest + (i * 8));
        x = x.substr(len);
    }
}

string serialize_Array_int_8(int x[8]) {
    string data = "";
    for (int i = 0; i < 8; i++) {
        data += serialize_int(x[i]);
    }
    return serialize_int((int)data.length()) + data;
}

void deserialize_Array_int_8(string x, int* dest) {
    int len = sizeof(int);
    x = x.substr(len);

    for (int i = 0; i < 8; i++) {
        len = sizeof(int);
        dest[i] = deserialize_int(x.substr(0, len));
        x = x.substr(len);
    }
}

string serialize_rectangle(rectangle x) {
    string data = "";
    data += serialize_int(x.x);
    data += serialize_int(x.y);
    return serialize_int((int)data.length()) + data;
}

rectangle deserialize_rectangle(string x) {
    rectangle new_item;
    int len = sizeof(int);

    x = x.substr(len);
    len = sizeof(int);
    new_item.x = deserialize_int(x.substr(0, len));

    x = x.substr(len);
    len = sizeof(int);
    new_item.y = deserialize_int(x.substr(0, len));

    return new_item;
}

string serialize_s(s x) {
    string data = "";
    data += serialize_Array_int_4(x.m1);
    data += serialize_Array_int_4_10(x.m2);
    data += serialize_Array_int_4_10_100(x.m3);
    return serialize_int((int)data.length()) + data;
}

s deserialize_s(string x) {
    s new_item;
    int len = sizeof(int);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    deserialize_Array_int_4(x.substr(0, len), (int*)new_item.m1);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    deserialize_Array_int_4_10(x.substr(0, len), (int*)new_item.m2);

    x = x.substr(len);
    len = sizeof(int) + deserialize_int(x.substr(0, sizeof(int)));
    deserialize_Array_int_4_10_100(x.substr(0, len), (int*)new_item.m3);

    return new_item;
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
    