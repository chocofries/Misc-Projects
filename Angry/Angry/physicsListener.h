#pragma comment(lib, "Box2D.lib")
#include <Box2D\Box2D.h>

class PhysicsListener : public b2ContactListener
{
public:
	PhysicsListener();
	~PhysicsListener();

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

	b2Body* GetBodyA() const;
	b2Body* GetBodyB() const;

private:
	b2Body* bodyA;
	b2Body* bodyB;
};