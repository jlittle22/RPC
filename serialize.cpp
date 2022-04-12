#include "serialize.h"
#include <arpa/inet.h>
#include <sstream>
#include <iostream>

string serialize(int x) {
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

string serialize(string x) {
  return serialize((int)x.length()) + x;
}

string deserialize_string(string x) {
  int str_size = deserialize_int(x.substr(0, sizeof(int)));
  cout << "STR SIZE: " << str_size << endl;

  return x.substr(sizeof(int), str_size);
}

string serialize(float x) {
  FloatInt conv;
  conv.f = x;
  return serialize((int)conv.i);
}

float deserialize_float(string x) {
  int new_item = deserialize_int(x);
  FloatInt conv;
  conv.i = (uint32_t)new_item;
  return conv.f;
}

///// 

///// User-defined Serialization Methods

// struct Person {string firstname; string lastname; int age;};
string serialize(Person x) {
  cout << "Attempting to Serialize Person:"<< endl;
  cout << " FN : " << x.firstname << endl;
  cout << " LN : " << x.lastname << endl;
  cout << " age: " << x.age << endl;
  for (int i = 0 ; i < x.firstname.length(); i++ ) { 
    cout << i << " : " << int(x.firstname[i]);
    if (isalnum(x.firstname[i])) {
      cout << " " << x.firstname[i];
    }

    cout << endl;
  }
  string data = serialize(x.firstname) + serialize(x.lastname) + serialize(x.age);
  cout << "SERIALIZED PERSON: " << endl;
  for (int i = 0 ; i < data.length(); i++ ) { 
    cout << i << " : " << int(data[i]);
    if (isalnum(data[i])) {
      cout << " " << data[i];
    }

    cout << endl;
  }
  return serialize((int)data.length()) + data;
}

Person deserialize_Person(string x) {
  Person new_item;
  string data = x.substr(sizeof(int));

  int len = deserialize_int(data.substr(0, sizeof(int)));
  new_item.firstname = deserialize_string(data);
 
  data = data.substr(sizeof(int) + len);

  len = deserialize_int(data.substr(0, sizeof(int)));
  new_item.lastname = deserialize_string(data);
  data = data.substr(sizeof(int) + len);

  new_item.age = deserialize_int(data);
  
  return new_item;

}

string serialize(ThreePeople x) {
  string data = serialize(x.p1) + serialize(x.p2) + serialize(x.p3);
  return serialize((int)data.length()) + data;
}

ThreePeople deserialize_ThreePeople(string x) {
  ThreePeople new_item;
  int len;
  string data;
  
  data = x.substr(sizeof(int));
  len = deserialize_int(data.substr(0, sizeof(int)));
  new_item.p1 = deserialize_Person(data.substr(0, sizeof(int) + len));

  data = data.substr(sizeof(int) + len);
  len = deserialize_int(data.substr(0, sizeof(int)));
  new_item.p2 = deserialize_Person(data.substr(0, sizeof(int) + len));

  data = data.substr(sizeof(int) + len);
  len = deserialize_int(data.substr(0, sizeof(int)));
  new_item.p2 = deserialize_Person(data.substr(0, sizeof(int) + len));
  
  return new_item;
}

/* 
struct StructWithArrays {
  int aNumber;
  Person people[10];
};
*/

string serialize(StructWithArrays x) {
  string data = serialize(x.aNumber);
  for (int i = 0; i < 10; i++) {
    data += serialize(x.people[i]);
  }

  return serialize((int)data.length()) + data;
}

StructWithArrays deserialize_StructWithArrays(string x) {
  StructWithArrays new_item;
  int len;

  x = x.substr(sizeof(int));
  
  len = sizeof(new_item.aNumber);
  new_item.aNumber = deserialize_int(x.substr(0, len));
  x = x.substr(len);

  for (int i = 0; i < 10; i++) {
    len = deserialize_int(x.substr(0, sizeof(int)));
    new_item.people[i] = deserialize_Person(x.substr(0, sizeof(int) + len));
    x = x.substr(len + sizeof(int));
  }

  return new_item;
}

// struct rectangle {int x; int y;};
string serialize(rectangle x) {
  string data = serialize(x.x) + serialize(x.y);
  return serialize((int)data.length()) + data;
}

rectangle deserialize_rectangle(std::string x) {
  rectangle new_item;
  int len;

  x = x.substr(sizeof(int));
  
  len = sizeof(new_item.x);
  new_item.x = deserialize_int(x.substr(0, len));

  x = x.substr(len);

  len = sizeof(new_item.y);
  new_item.y = deserialize_int(x.substr(0, len));

  return new_item;

}


/////
