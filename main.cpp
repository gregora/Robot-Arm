#include "include/arm.h"
#include <stdio.h>

using namespace std;

int main(){

	vector<float> sizes = {1, 1, 1};
	b2World world(b2Vec2(0, 10));
	Arm a(&world, sizes);


}
