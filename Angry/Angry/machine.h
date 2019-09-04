#pragma once
#include "box.h"
#include "ball.h"
#include "line.h"

enum MachineType
{
	MACH_WINDMILL,
	MACH_CART,
	MACH_PULLEY
};

class Machine : public GameObject
{
public:
	Machine(Level* _level);
	virtual ~Machine();

	void InitWindmill(glm::vec3 _pos, float _w, float _h, float _motorSpeed, bool _centerPivot);
	void InitCart(glm::vec3 _pos, float _w, float _h);
	void InitPulley(glm::vec3 _posA, glm::vec3 _posB, b2Vec2 _groundA, b2Vec2 _groundB, float _w, float _h);

	virtual void Update(double dTime);
	virtual void Draw();

private:
	Level* level;

	std::vector<GameObject*> vecParts;
	std::vector<Line*> vecLines;

	MachineType machineType;

	b2Vec2 anchorA;
	b2Vec2 anchorB;
	b2Vec2 groundA;
	b2Vec2 groundB;
};