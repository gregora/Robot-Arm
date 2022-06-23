#include "../include/arm.h"

Arm::Arm(b2World* world, std::vector<float> lengths){

	this -> world = world;

	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);

	b2Body* baseBody = world -> CreateBody(&bodyDef);

	b2PolygonShape base;
	base.SetAsBox(1.0f, 1.0f);

	b2FixtureDef baseFix;
	baseFix.shape = &base;
	baseFix.density = 1.0f;


	baseBody -> CreateFixture(&baseFix);

	float height = 0;
	float prev_l = 0;

	b2Body* prev = baseBody;

	for(float l : lengths){
		b2BodyDef beamBodyDef;
		beamBodyDef.type = b2_dynamicBody;
		beamBodyDef.position.Set(0.0f, height - 0.02f + l/2);

		b2Body* beamBody = world -> CreateBody(&beamBodyDef);


		b2PolygonShape beam;
		beam.SetAsBox(0.10f, l);

		b2FixtureDef beamFix;
		beamFix.shape = &beam;
		beamFix.density = 1.0f;
		beamBody -> CreateFixture(&beamFix);

		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.localAnchorA.Set(0, prev_l / 2);
		revoluteJointDef.localAnchorB.Set(0, l/2);

		revoluteJointDef.bodyA = prev;
		revoluteJointDef.bodyB = beamBody;
		world->CreateJoint( &revoluteJointDef );

		prev = beamBody;
		height += l;

	}

}
