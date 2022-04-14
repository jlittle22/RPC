#include <string>
using namespace std;
#include <iostream>

#ifndef STRUCTWITHARRAY_IDL
#define STRUCTWITHARRAY_IDL
#include "structwitharray.idl"
#endif


Person findPerson(ThreePeople tp) {
	for (size_t i = 0; i < tp.p1.firstname.length(); i++){
		tp.p1.firstname[i] = (char)((int)tp.p1.firstname[i] - 32);
	}
    return tp.p1;
}

Person findOtherPerson(StructWithArrays x) {
	return x.people[x.aNumber];
}

int area(rectangle r) {
	return r.x * r.y;
}

void voidFuncThatTakesALot(int x, float y, Person z) {
    cout << "voidFuncThatTakesALot" << endl;
    cout << "    x --> " << x << endl;
    cout << "    y --> " << y << endl;
    cout << "    z --> " << z.firstname << " " << z.lastname << " " << z.age << endl;
}

Person nonVoidFuncThatTakesALot(int x, float y, Person z) {
	return z;
}

int fake(int arr[10][10]) {
	return arr[5][5];
}

int getValueAt(int arr[10][10], int i, int j) {
    return arr[i][j];
}

int tough(int arr[1][2][3][4][5][6][7][8]) {
	return arr[0][1][2][3][2][4][2][3];
}
