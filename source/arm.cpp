#include "../include/arm.h"

Arm::Arm(std::vector<float> lengths, float max_torque){

	this -> lengths = lengths;

	b2Vec2 gravity(0.0f, -9.8f);
	world = new b2World(gravity);

	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.0f, 0.0f);

	b2Body* baseBody = world -> CreateBody(&bodyDef);

	b2PolygonShape base;
	base.SetAsBox(0.05f, 0.05f);

	b2FixtureDef baseFix;
	baseFix.shape = &base;
	baseFix.density = 1.0f;


	baseBody -> CreateFixture(&baseFix);

	float height = 0;
	float prev_l = 0;

	b2Body* prev = baseBody;

	int i = 0;

	for(float l : lengths){
		b2BodyDef beamBodyDef;
		beamBodyDef.type = b2_dynamicBody;
		beamBodyDef.position.Set(0.0f, height + l/2);

		b2Body* beamBody = world -> CreateBody(&beamBodyDef);


		b2PolygonShape beam;
		beam.SetAsBox(0.05f, l/2);

		b2FixtureDef beamFix;
		beamFix.shape = &beam;
		beamFix.density = 1.0f;
		beamFix.friction = 1.0f;

		beamBody -> CreateFixture(&beamFix);


		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = prev;
		revoluteJointDef.bodyB = beamBody;

		revoluteJointDef.localAnchorA.Set(0.0f, prev_l/2);
		revoluteJointDef.localAnchorB.Set(0.0f, -l/2);

		revoluteJointDef.collideConnected = false;

		revoluteJointDef.enableMotor = true;
		revoluteJointDef.maxMotorTorque = max_torque;

		(b2RevoluteJoint*)world->CreateJoint( &revoluteJointDef );

		prev = beamBody;
		height += l;
		prev_l = l;

		i++;


	}

}

void Arm::physics(float delta, bool debug){

	world -> Step(delta, 5, 5);


	if(debug){
		printf("Physics step (Delta: %.2f s)\n", delta);
		b2Body* body = world -> GetBodyList();
		while(body != nullptr){
			printf("%6.2fm %6.2fm    %8.1fdeg\n", body->GetPosition().x, body->GetPosition().y, body->GetAngle()*RAD2DEG);
			body = body -> GetNext();
		}
	}

}

Arm::~Arm(){
	delete world;
}

void Arm::applySpeeds(std::vector<float> speeds){
	b2RevoluteJoint* joint = (b2RevoluteJoint*) world -> GetJointList();

	int i = speeds.size() - 1;

	while(joint != nullptr){

		joint -> SetMotorSpeed(speeds[i]);

		i--;
		joint = (b2RevoluteJoint*) joint -> GetNext();
	}
}

void Arm::getAngles(float* angles){
	b2RevoluteJoint* joint = (b2RevoluteJoint*) world -> GetJointList();

	int i = lengths.size() - 1;

	while(joint != nullptr){

		angles[i] = joint -> GetJointAngle();

		i--;
		joint = (b2RevoluteJoint*) joint -> GetNext();
	}
}

b2Vec2 Arm::getArmLocation(){
	b2Body* arm = world -> GetBodyList();

	b2Vec2 position = arm -> GetPosition();
	float angle = arm -> GetAngle();

	uint last = lengths.size() - 1;
	float length = lengths[last] / 2;

	return b2Vec2(position.x + cos(angle + 3.14/2)*length, position.y + sin(angle + 3.14/2)*length);
}

void Arm::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	sf::RectangleShape square;
	sf::CircleShape circle;
	circle.setFillColor(sf::Color(100, 100, 100));
	circle.setRadius(0.1 / 2);
	circle.setOrigin(0.1 / 2, 0.1 / 2);

	int i = 0;

	b2Body* body = world -> GetBodyList();
	while(body != nullptr){

		float x = body->GetPosition().x;
		float y = body->GetPosition().y;

		float ang = body->GetAngle();


		float length;
		if(i == lengths.size()){
			square.setSize(sf::Vector2f(0.3, 0.3));
			square.setOrigin(0.3 / 2, 0.3 / 2);

			square.setFillColor(sf::Color(50, 50, 50));

		}else{
			length = lengths[lengths.size() - i - 1];
			square.setSize(sf::Vector2f(0.1, length));
			square.setOrigin(0.1 / 2, length / 2);

			square.setFillColor(sf::Color(100, 100, 100));

			circle.setPosition(x + cos(ang + 3.14/2)*length/2, -(y + sin(ang + 3.14/2)*length/2));
			target.draw(circle, states.transform*getTransform());
		}

		square.setPosition(x, -y);
		square.setRotation(-ang*RAD2DEG);


		target.draw(square, states.transform*getTransform());

		body = body -> GetNext();
		i++;
	}

}
