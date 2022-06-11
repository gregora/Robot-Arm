#include "box2d/box2d.h"
#include <vector>

class Arm {

public:
	b2Body* body;
	float max_torque;
	Arm(std::vector<int> lengths);

	void applyTorques(float* torques);
	void applyTorques(uint index, float torque);
	void getAngles(float* angles);
	float getAngle(uint index);


};
