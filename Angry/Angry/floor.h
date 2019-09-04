#pragma once
#include "gameobject.h"
#include "sprite.h"
#include "level.h"

class Floor : public GameObject
{
public:
	Floor(Level* _level);
	virtual ~Floor();

	virtual void Initialise();
	virtual void Update(double dTime);
	virtual void Draw();

private:
	float width;
	float height;

	Sprite* sprite;
	Level* level;
	b2BodyDef floorBodyDef;
	b2Body* floorBody;
};