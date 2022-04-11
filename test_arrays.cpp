#include <iostream>

using namespace std;

int* same_addr(int*arr,int i, int j) {
	cout << "i="<<i<<" j="<<j << endl;
	cout << "arr="<<arr<<" arr+1="<<arr+1 << endl;
	return (arr + (i * 4 * sizeof(int)) + (j * sizeof(int)));
}

int main() {
    int arr[2][4];
    cerr << "Arr Location: " << arr << endl;
    for (int i = 0; i < 2; i++) {
    	cerr << "arr[i] " << arr[i] << endl;
    	for (int j = 0; j < 4; j++) {
    		cerr << "--- " << i << " " << j << " ---" << endl;
    		cerr << "(&arr[i][j]) "<< (&arr[i][j]) << " same_addr " << same_addr((int*)arr, i, j) << endl;
    	}
    }
    int arr2[4][10][100];
    int* prev = (int*)arr2;
    cerr << "Arr2 Location: " << arr2 << endl;
    for (int i = 0; i < 4; i++) {
    	cerr << "arr2[i] " << arr2[i] << " diff from prev: " << (int*)arr2[i] - prev << endl;
    	prev = (int*)arr2[i];
    	for (int j = 0; j < 10; j++) {
    		for (int k = 0; k < 100; k++) {
    			// cerr << "--- " << i << " " << j << " " << k << " ---" << endl;
    		    // cerr << "(&arr2[i][j][k]) "<< (&arr2[i][j][k]) << endl;
    		}
    	}
    }

	return 0;
}