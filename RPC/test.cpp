#include <iostream>
#include <inttypes.h>
#include <sstream>

using namespace std;


// Memcopy in and out of string --> https://stackoverflow.com/questions/21005845/how-to-get-float-in-bytes
// string serialize(float x) {
//   string result = "";
//   for (int i = sizeof(float) - 1; i >= 0; i--) {
//     char curr = (char)(x >> (i * 8));  
//     result += curr;
//   }

//   return result;
// }

template <typename T>
string serialize(T item) {
  stringstream sstream;

  const char* ptr = reinterpret_cast<char*>(&item);
  sstream.write(ptr, sizeof(T));

  return sstream.str();
}

template <typename T>
T deserialize(string x) {
    T new_item;
    stringstream ss(x);
    ss.read(reinterpret_cast<char*>(&new_item), sizeof(T));

    return new_item;
}

int sigcmp(string sig1, string sig2) {
  
}

// concerned about what happens if a string has a leading 0 bytes
// does that get misinterpretted as null character???
// float deserialize(string x) {
//   float result = 0;
//   for (int i = x.length() - 1; i >= 0; i--) {
//     result += uint8_t(x[i]) << ((x.length() - i - 1) * 8);
//   }
//   return result;
// }

struct test {
  int a;
  char b;
  char c;
  float d;
  int e[10];
};

int main() {
  test t;
  t.a = 5;
  t.b = 'a';
  t.c = 'c';
  t.d = 3.1415;
  t.e[0] = 0;
  t.e[1] = 1;
  t.e[2] = 2;
  t.e[3] = 3;
  t.e[4] = 4;
  t.e[5] = 5;
  t.e[6] = 6;
  t.e[7] = 7;
  t.e[8] = 8;
  t.e[9] = 9;

  cout << " t : " << serialize(t) << endl;

  test other = deserialize<test>(serialize<test>(t));

  cout << "a : " << other.a << endl;
  cout << "b : " << other.b << endl;
  cout << "c : " << other.c << endl;
  cout << "d : " << other.d << endl;
  for (int i = 0; i < 10; i++) {
    cout << i << " : " << other.e[i] << endl;
  }

  cout << " 3.1415 : " << deserialize<float>(serialize<float>(0.0)) << endl;


  // for (float i = 1; i < 10000000000; i *= 1.01) {
  //   cout << i << " : " << deserialize<float>(serialize(i)) << endl;
  // }


	return 0;
}