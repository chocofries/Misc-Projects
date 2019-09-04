#include "physicsmanager.h"

PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
	delete physicsListener;
	delete world;
}

void PhysicsManager::Initialise()
{
	gravity = b2Vec2(0.0f,-10.0f);
	world = new b2World(gravity);
	physicsListener = new PhysicsListener();
	world->SetContactListener(physicsListener);
	timeStep = 1.0f/60.0f;
	velocityIter = 8;
	positionIter = 3;
}

void PhysicsManager::Update(float delta)
{
	world->Step(timeStep, velocityIter, positionIter);
}

b2World * PhysicsManager::GetWorld() const
{
	return world;
}

PhysicsListener * PhysicsManager::GetPhysicsListener() const
{
	return physicsListener;
}
