#include <iostream>
#include <inttypes.h>
#include <string.h>
#include <sstream>

using namespace std;


// endianness?

string serialize(float x) {

    std::stringstream sstream;

    sstream << x;
    string num_str = sstream.str();
    //auto *ptr = sstream.str().c_str(); // RESULTS in dangling pointer
    // num_str.empty() ? cout << "empty\n" : 
    // cout << num_str << endl;
    return num_str;
}

//   return result;
// }

float deserialize(string x) {

     std::stringstream sstream(x);
     float num;
     sstream >> num;

     // cout << "num: " << num << endl;

     // cout << "divide: " << num / 5.0 << endl;

     return num;

}



int main () {

   float n1 = 123.456;
    cout << "serialize " << n1 << "is: " << serialize(n1) << endl;

    for (float i = 0.000;  i < 9999999.9999999; i += .001) {
        cout << "serialize " << i << " is: " << serialize(i) << endl;
        cout << "deserialize is: " << deserialize(serialize(i)) << endl;
        cout << "deserialize divide is: " << deserialize(serialize(i))  / 5.5 << endl;
        cout << "serialize concat is: " << serialize(i) + "hi" << endl;
    }

    // string floatstr = "123.456";

    // cout << "deserialize " << floatstr << "is: " << deserialize(floatstr) << endl;


}