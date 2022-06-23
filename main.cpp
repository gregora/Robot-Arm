#include "include/arm.h"
#include <stdio.h>

using namespace std;

int main(){

	vector<float> sizes = {1.0f, 1.0f, 1.0f, 2.0f};
	Arm a(sizes);

	for(int i = 0; i < 100; i++){
		a.physics(1.0f / 60.0f, true);
	}

}
