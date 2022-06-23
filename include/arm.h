#include "box2d/box2d.h"
#include <vector>

class Arm {

public:
	b2World* world;
	float max_torque;
	Arm(b2World* world, std::vector<float> lengths);

	void applySpeeds(float* speeds);
	void applySpeed(uint index, float speed);
	void getAngles(float* angles);
	float getAngle(uint index);

	void physics(float delta, bool debug = false);

};
