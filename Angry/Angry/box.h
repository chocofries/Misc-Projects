#pragma once
#include "gameobject.h"
#include "sprite.h"
#include "level.h"

enum BoxType
{
	BOX_HOLLOW,
	BOX_SOLID
};

class Box : public GameObject
{
public:
	Box(Level* _level, BoxType _type, float _w, float _h, float _angle, bool _isStatic, bool _isGhost);
	Box(Level* _level, BoxType _type, float _w, float _h, float _angle, bool _isStatic, bool _isGhost, std::vector<Box*>* _vecDebris);
	virtual ~Box();

	virtual void Initialise();
	virtual void Update(double dTime);
	virtual void Draw();

	void SetBoxType(BoxType _type);
	void SetWidth(float w);
	void SetHeight(float h);
	void SetWidthHeight(float w, float h);

	b2Body* GetBody() const;
	void SetTransform(b2Vec2 pos, float angle);

	float GetWidth() const;
	float GetHeight() const;

private:
	float width;
	float height;
	float prevX;
	float prevY;
	float prevDist;			//Distance between previous position and current (used to determine speed)

	float destroySpeed;		//The minimum speed of the box when it hits, to determine if it is destroyed
	bool isDestructible;	//If the box can be destroyed
	bool isDestroying;
	float destroyDelay;

	float spawnAngle;

	bool isStatic;			//If the box is static or not
	bool isGhost;			//If the box is a ghost (cannot be collided with)

	BoxType boxType;

	Sprite* spriteA;
	Sprite* spriteB;
	Sprite* spritePlank;
	Level* level;
	b2BodyDef boxBodyDef;
	b2Body* boxBody;
	PhysicsListener* listener;

	FMOD::Sound* soundBreak;

	std::vector<Box*>* vecDebris;
};