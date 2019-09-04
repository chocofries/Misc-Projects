#pragma once
#include "sprite.h"
#include "level.h"

class Line : public GameObject
{
public:
	Line(Level* _level, glm::vec2 _posA, glm::vec2 _posB, float _w);
	virtual ~Line();

	virtual void Initialise();
	virtual void Update(double dTime);
	virtual void Draw();

	void SetPosA(glm::vec2 _posA);
	void SetPosB(glm::vec2 _posB);

private:
	Level* level;
	Sprite* spriteA;
	Sprite* spriteB;
	Sprite* spritePlank;

	glm::vec2 posA;
	glm::vec2 posB;
	float width;
	float length;
	float direction;
};