#include <string>
using namespace std;

#ifndef JAKE_IDL
#define JAKE_IDL
#include "jake.idl"
#endif

MT useless(MT x) {
	return x;
}

float nothelpful(StupidWeird x) {
	return x.arr2[5].array[10];
}

float reallynothelpful(StupidWeird x[10]) {
	return x[5].arr2[5].array[10];
}