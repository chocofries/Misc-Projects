#pragma once
#include "sprite.h"
#include "ball.h"

class Slingshot : public GameObject
{
public:
	Slingshot(Level* _level, std::vector<Ball*>* _vecBalls);
	virtual ~Slingshot();

	virtual void Initialise();
	virtual void Update(double dTime);
	virtual void Draw();

	void ProcessInput(double dTime);
	void Shoot(b2Vec2 vec);

private:
	Level* level;

	std::vector<Ball*>* vecBalls;
	std::vector<Sprite*> vecSprites;

	Sprite* spriteSling;
	Sprite* spritePull;

	Sprite* spriteBall;

	b2Vec2 aimDir;
	Ball* currentBall;

	FMOD::Sound* soundShoot;

	bool isShooting = false;
	bool isAiming = false;
	float delay = 0.1f;
	float aimPull = 0.0f;
};