#include "physicsListener.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void Initialise();
	void Update(float delta);

	b2World* GetWorld() const;
	PhysicsListener* GetPhysicsListener() const;

private:
	b2World* world;
	b2Vec2 gravity;

	PhysicsListener* physicsListener;

	float timeStep;
	int velocityIter;
	int positionIter;
};