#include "../include/arm.h"

Arm::Arm(std::vector<float> lengths){

	b2Vec2 gravity(0.0f, -9.8f);
	world = new b2World(gravity);

	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.0f, 0.0f);

	b2Body* baseBody = world -> CreateBody(&bodyDef);

	b2PolygonShape base;
	base.SetAsBox(0.10f, 0.10f);

	b2FixtureDef baseFix;
	baseFix.shape = &base;
	baseFix.density = 1.0f;


	baseBody -> CreateFixture(&baseFix);

	float height = 1;
	float prev_l = 0;

	b2Body* prev = baseBody;

	for(float l : lengths){
		b2BodyDef beamBodyDef;
		beamBodyDef.type = b2_dynamicBody;
		beamBodyDef.position.Set(height + l/2, 0.0f);

		b2Body* beamBody = world -> CreateBody(&beamBodyDef);


		b2PolygonShape beam;
		beam.SetAsBox(l, 0.10f);

		b2FixtureDef beamFix;
		beamFix.shape = &beam;
		beamFix.density = 1.0f;
		beamBody -> CreateFixture(&beamFix);

		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = prev;
		revoluteJointDef.bodyB = beamBody;

		revoluteJointDef.localAnchorA.Set(prev_l/2 - 0.02f, 0.0f);
		revoluteJointDef.localAnchorB.Set(-l + 0.02f, 0.0f);

		revoluteJointDef.collideConnected = false;

		world->CreateJoint( &revoluteJointDef );

		prev = beamBody;
		height += l;

	}

}

void Arm::physics(float delta, bool debug){

	world -> Step(delta, 5, 5);


	if(debug){
		printf("Physics step (Delta: %.2f s)\n", delta);
		b2Body* body = world -> GetBodyList();
		while(body != nullptr){
			printf("%6.2fm %6.2fm    %8.1fdeg\n", body->GetPosition().x, body->GetPosition().y, body->GetAngle()*DEG2RAD);
			body = body -> GetNext();
		}
	}

}

Arm::~Arm(){
	delete world;
}
