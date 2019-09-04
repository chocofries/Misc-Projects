#include "machine.h"

Machine::Machine(Level * _level)
{
	this->level = _level;
	levelCamera = level->GetCamera();
	shaderLoader = level->GetShaderLoader();
	assetLoader = level->GetAssetLoader();
	physicsManager = level->GetPhysicsManager();
	clock = level->GetClock();
	VBO = level->GetVBO();
	xRot = 0.0f;
	yRot = 0.0f;
	zRot = 1.0f;
}

Machine::~Machine()
{
	while (vecParts.size() > 0)
	{
		GameObject* temp = vecParts[vecParts.size() - 1];
		vecParts.pop_back();
		delete temp;
	}

	while (vecLines.size() > 0)
	{
		GameObject* temp = vecLines[vecLines.size() - 1];
		vecLines.pop_back();
		delete temp;
	}
}

void Machine::InitWindmill(glm::vec3 _pos, float _w, float _h, float _motorSpeed, bool _centerPivot)
{
	machineType = MACH_WINDMILL;
	x = _pos.x;
	y = _pos.y;
	z = _pos.z;

	//Create boxes
	Box* boxA = new Box(level, BOX_SOLID, _w, _h, 0.0f, false, false); //Dynamic Moving Part

	if (_centerPivot)
	{
		boxA->SetX(x);
	}
	else
	{
		boxA->SetX(x + _w*0.4f);
	}
	boxA->SetY(y);
	boxA->SetZ(z);
	boxA->Initialise();
	vecParts.push_back(boxA);

	Box* boxB = new Box(level, BOX_SOLID, _h, _h, 0.0f, true, false); //Static Pivot Point
	boxB->SetX(x);
	boxB->SetY(y);
	boxB->SetZ(z + 0.1f);
	boxB->Initialise();
	vecParts.push_back(boxB);

	//Define revolute joint
	b2RevoluteJointDef revJointDef;
	revJointDef.Initialize(boxB->GetBody(), boxA->GetBody(), boxB->GetBody()->GetWorldCenter());
	revJointDef.motorSpeed = _motorSpeed;
	revJointDef.maxMotorTorque = 10000.0f;
	revJointDef.enableMotor = true;

	//Create joint
	b2Joint* revJoint = physicsManager->GetWorld()->CreateJoint(&revJointDef);
}

void Machine::InitCart(glm::vec3 _pos, float _w, float _h)
{
	machineType = MACH_CART;
	x = _pos.x;
	y = _pos.y;
	z = _pos.z;

	//Create cart and wheels
	Ball* wheelA = new Ball(level, 4.0f, BALL_WHEEL);
	wheelA->SetX(x - _w * 0.4f);
	wheelA->SetY(y - _h * 0.6f);
	wheelA->SetZ(z);
	wheelA->Initialise();
	vecParts.push_back(wheelA);

	Ball* wheelB = new Ball(level, 4.0f, BALL_WHEEL);
	wheelB->SetX(x + _w * 0.4f);
	wheelB->SetY(y - _h * 0.6f);
	wheelB->SetZ(z);
	wheelB->Initialise();
	vecParts.push_back(wheelB);

	Box* cart = new Box(level, BOX_SOLID, _w, _h, 0.0f, false, false);
	cart->SetX(x);
	cart->SetY(y);
	cart->SetZ(z + 0.1f);
	cart->Initialise();
	vecParts.push_back(cart);

	//Define wheel joints
	b2WheelJointDef wheelADef;
	wheelADef.Initialize(cart->GetBody(), wheelA->GetBody(), wheelA->GetBody()->GetWorldCenter(), b2Vec2(0.0f, 1.0f));
	wheelADef.frequencyHz = 4.0f;
	wheelADef.dampingRatio = 0.5f;

	b2WheelJointDef wheelBDef;
	wheelBDef.Initialize(cart->GetBody(), wheelB->GetBody(), wheelB->GetBody()->GetWorldCenter(), b2Vec2(0.0f, 1.0f));
	wheelBDef.frequencyHz = 4.0f;
	wheelBDef.dampingRatio = 0.5f;

	//Create wheel joints
	b2Joint* wheelAJoint = physicsManager->GetWorld()->CreateJoint(&wheelADef);
	b2Joint* wheelBJoint = physicsManager->GetWorld()->CreateJoint(&wheelBDef);
}

void Machine::InitPulley(glm::vec3 _posA, glm::vec3 _posB, b2Vec2 _groundA, b2Vec2 _groundB, float _w, float _h)
{
	machineType = MACH_PULLEY;

	//Create platforms
	Box* platA = new Box(level, BOX_SOLID, _w, _h, 0.0f, false, false);
	platA->SetX(_posA.x);
	platA->SetY(_posA.y);
	platA->SetZ(_posA.z);
	platA->Initialise();
	vecParts.push_back(platA);

	Box* platB = new Box(level, BOX_SOLID, _w, _h, 0.0f, false, false);
	platB->SetX(_posB.x);
	platB->SetY(_posB.y);
	platB->SetZ(_posB.z);
	platB->Initialise();
	vecParts.push_back(platB);

	//Create cosmetic lines
	for (int i = 0; i < 3; i++)
	{
		Line* line = new Line(level, glm::vec2(), glm::vec2(), 2.0f);
		line->Initialise();
		line->SetZ(z - 2.0f);
		vecLines.push_back(line);
	}

	//Define pulley joint
	anchorA = platA->GetBody()->GetWorldCenter();
	anchorB = platB->GetBody()->GetWorldCenter();
	anchorA.y += _w * 0.5f;
	anchorB.y += _w * 0.5f;

	groundA = _groundA;
	groundB = _groundB;

	b2PulleyJointDef pulleyDef;
	pulleyDef.Initialize(platA->GetBody(), platB->GetBody(), groundA, groundB, anchorA, anchorB, 1.0f);
	pulleyDef.collideConnected = true;

	//Create pulley joint
	b2Joint* pulleyJoint = physicsManager->GetWorld()->CreateJoint(&pulleyDef);
}

void Machine::Update(double dTime)
{
	if (machineType == MACH_PULLEY)
	{
		Line* lineBase = vecLines[0];
		Line* lineA = vecLines[1];
		Line* lineB = vecLines[2];

		Box* platA = dynamic_cast<Box*>(vecParts.at(0));
		Box* platB = dynamic_cast<Box*>(vecParts.at(1));

		lineBase->SetPosA(glm::vec2(groundA.x, groundA.y));
		lineBase->SetPosB(glm::vec2(groundB.x, groundB.y));

		lineA->SetPosA(glm::vec2(platA->GetX(),platA->GetY()));
		lineA->SetPosB(glm::vec2(groundA.x, groundA.y));

		lineB->SetPosA(glm::vec2(platB->GetX(), platB->GetY()));
		lineB->SetPosB(glm::vec2(groundB.x, groundB.y));
	}

	//Update parts
	for (unsigned int i = 0; i < vecParts.size(); i++)
	{
		if (vecParts[i]->GetIsActive())
		{
			vecParts[i]->Update(dTime);
		}
	}

	//Update lines
	for (unsigned int i = 0; i < vecLines.size(); i++)
	{
		if (vecLines[i]->GetIsActive())
		{
			vecLines[i]->Update(dTime);
		}
	}
}

void Machine::Draw()
{
	//Draw lines
	for (unsigned int i = 0; i < vecLines.size(); i++)
	{
		if (vecLines[i]->GetIsActive())
		{
			vecLines[i]->Draw();
		}
	}

	//Draw parts
	for (unsigned int i = 0; i < vecParts.size(); i++)
	{
		if (vecParts[i]->GetIsActive())
		{
			vecParts[i]->Draw();
		}
	}
}
