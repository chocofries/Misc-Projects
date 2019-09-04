#pragma once
#include "gameobject.h"
#include "sprite.h"
#include "level.h"

enum BallType
{
	BALL_DASH,		//Dash ability
	BALL_SHOTGUN,	//Shotgun ability
	BALL_BOMB,		//Bomb ability
	BALL_WHEEL,		//Wheel
	BALL_MINI,		//Mini ball, no ability, used in bomb and shotgun
	BALL_BLOOD		//Blood effect, does not collide with scene items
};

class Ball : public GameObject
{
public:
	Ball(Level* _level, float _radius, BallType _type);
	Ball(Level* _level, float _radius, BallType _type, std::vector<Ball*>* _vecMinis);
	virtual ~Ball();

	virtual void Initialise();
	virtual void Update(double dTime);
	virtual void Draw();

	void SetRadius(float r);
	void SetTransform(b2Vec2 pos, float angle);
	void ShootBall(b2Vec2 velocity);
	void SetBallActive(bool _isActive);

	bool GetHasHit() const;

	b2Body* GetBody() const;

private:
	float radius;
	float prevX;
	float prevY;
	float prevDist;			//Distance between previous position and current (used to determine speed)

	float destroySpeed;		//The minimum speed of the box when it hits, to determine if it is destroyed
	float destroyDelay;		//The slight delay before it destroys
	bool isDestructible;	//If the box can be destroyed
	bool isDestroying;		//If the ball is soon to be destroyed
	bool hasHit;
	bool abilityUsed;

	BallType ballType;
	std::vector<Ball*>* vecMinis;

	FMOD::Sound* soundAbility;

	Sprite* sprite;
	Level* level;
	b2BodyDef ballBodyDef;
	b2Body* ballBody;
	PhysicsListener* listener;
};