#include "physicsListener.h"
#include <iostream>

PhysicsListener::PhysicsListener()
{
}

PhysicsListener::~PhysicsListener()
{
}

void PhysicsListener::BeginContact(b2Contact * contact)
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();
	bodyA = fixA->GetBody();
	bodyB = fixB->GetBody();

	//std::cout << "Contact Began with A:(" << bodyA->GetUserData() << ") and B:(" << bodyB->GetUserData() << ")" << std::endl;
}

void PhysicsListener::EndContact(b2Contact * contact)
{
	//std::cout << "Contact Ended" << std::endl;
}

b2Body * PhysicsListener::GetBodyA() const
{
	return bodyA;
}

b2Body * PhysicsListener::GetBodyB() const
{
	return bodyB;
}
