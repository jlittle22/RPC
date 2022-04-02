#include <iostream>
#include <inttypes.h>

using namespace std;


// Memcopy in and out of string --> https://stackoverflow.com/questions/21005845/how-to-get-float-in-bytes
string serialize(float x) {
  string result = "";
  for (int i = sizeof(float) - 1; i >= 0; i--) {
    char curr = (char)(x >> (i * 8));  
    result += curr;
  }

  return result;
}

// concerned about what happens if a string has a leading 0 bytes
// does that get misinterpretted as null character???
float deserialize(string x) {
  float result = 0;
  for (int i = x.length() - 1; i >= 0; i--) {
    result += uint8_t(x[i]) << ((x.length() - i - 1) * 8);
  }
  return result;
}


int main() {
	string test = serialize(10000.0f);
	cout << "Bytes of 10: " << endl;
	for (int i = 0; i < test.length(); i++) {
		cout  << "    " << i << " : " << int(test[i]) << endl;
	}

    cout << deserialize(serialize(0.0f)) << endl;


	return 0;
}