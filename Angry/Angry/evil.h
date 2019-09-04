#pragma once
#include "gameobject.h"
#include "sprite.h"
#include "level.h"
#include "ball.h"

class Evil : public GameObject
{
public:
	Evil(Level* _level, std::vector<Ball*>* _vecBlood);
	virtual ~Evil();

	virtual void Initialise();
	virtual void Update(double dTime);
	virtual void Draw();

private:
	float width;
	float height;
	float prevX;
	float prevY;
	float prevDist; //Distance between previous position and current (used to determine speed)

	float destroySpeed; //The minimum speed of the box when it hits, to determine if it is destroyed
	bool isDestructible; //If the box can be destroyed

	bool isDestroying;
	float destroyDelay;

	Sprite* sprite;
	Level* level;
	b2BodyDef boxBodyDef;
	b2Body* boxBody;
	PhysicsListener* listener;

	FMOD::Sound* soundDeath;

	std::vector<Ball*>* vecBlood;
};