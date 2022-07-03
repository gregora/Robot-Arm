#include "../include/arm.h"

Arm::Arm(std::vector<float> lengths){

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
		beamBodyDef.position.Set(height + l/2, 0.0f);

		b2Body* beamBody = world -> CreateBody(&beamBodyDef);


		b2PolygonShape beam;
		beam.SetAsBox(l/2, 0.05f);

		b2FixtureDef beamFix;
		beamFix.shape = &beam;
		beamFix.density = 1.0f;
		beamBody -> CreateFixture(&beamFix);

		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = prev;
		revoluteJointDef.bodyB = beamBody;

		revoluteJointDef.localAnchorA.Set(prev_l/2, 0.0f);
		revoluteJointDef.localAnchorB.Set(-l/2, 0.0f);

		revoluteJointDef.collideConnected = false;

		b2RevoluteJoint* joint = (b2RevoluteJoint*)world->CreateJoint( &revoluteJointDef );

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

void Arm::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	sf::RectangleShape square;

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
			square.setSize(sf::Vector2f(length, 0.1));
			square.setOrigin(length / 2, 0.1 / 2);

			square.setFillColor(sf::Color(100, 100, 100));

		}

		square.setPosition(x, -y);
		square.setRotation(-ang*RAD2DEG);

		target.draw(square, states.transform*getTransform());

		body = body -> GetNext();
		i++;
	}

}
