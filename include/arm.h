#include "box2d/box2d.h"
#include <stdio.h>
#include <vector>

#include <SFML/Graphics.hpp>

#define RAD2DEG 57.325

class Arm : public sf::Drawable, public sf::Transformable {

public:
	b2World* world;
	float max_torque;
	Arm(std::vector<float> lengths);
	~Arm();

	void applySpeeds(float* speeds);
	void applySpeed(uint index, float speed);
	void getAngles(float* angles);
	float getAngle(uint index);

	void physics(float delta, bool debug = false);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	std::vector<float> lengths;
};
