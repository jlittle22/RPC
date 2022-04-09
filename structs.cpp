#include <string>
using namespace std;

#include "structs.idl"

Person findPerson(ThreePeople tp) {
	return tp.p1;
}

int area(rectangle r) {
	return r.x * r.y;
}

Person findOtherPerson(StructWithArrays x) {
	return x.people[x.aNumber];
}