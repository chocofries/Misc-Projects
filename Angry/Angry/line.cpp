#include "line.h"

Line::Line(Level * _level, glm::vec2 _posA, glm::vec2 _posB, float _w)
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

	posA = _posA;
	posB = _posB;
	width = _w;
}

Line::~Line()
{
	delete spriteA;
	delete spriteB;
	delete spritePlank;
}

void Line::Initialise()
{
	spriteA = new Sprite(this);
	spriteB = new Sprite(this);
	spritePlank = new Sprite(this);

	//Init Sprites
	spriteA->InitSprite("Assets/LightBox.png", "lightBox", 0.0f, 1, 1, 1, 0, 1000, 1000);
	spriteB->InitSprite("Assets/LightBox.png", "lightBox", 0.0f, 1, 1, 1, 0, 1000, 1000);
	spritePlank->InitSprite("Assets/LightSquare.png", "lightSquare", 0.0f, 1, 1, 1, 0, 1000, 1000);

	spriteA->SetIsAttached(false);
	spriteB->SetIsAttached(false);
	spritePlank->SetIsAttached(false);

	spriteA->SetSpriteScale(0.0021f*width);
	spriteB->SetSpriteScale(0.0021f*width);
	spritePlank->SetSpriteScale(0.0021f*width);
}

void Line::Update(double dTime)
{
	//Sprite positioning and rotation
	float x1, x2, y1, y2;
	x1 = posA.x;
	y1 = posA.y;
	x2 = posB.x;
	y2 = posB.y;

	length = glm::distance(posA, posB);
	direction = std::atan2(y2 - y1, x2 - x1) * 180.0f / MATH_PI;

	glm::vec2 rectPos = (glm::vec2(x1, y1) + glm::vec2(x2, y2))*0.5f;
	float rectDist = glm::distance(glm::vec2(x1, y1), glm::vec2(x2, y2));
	spritePlank->SetWidth(rectDist*500.0f);
	spritePlank->SetX(rectPos.x);
	spritePlank->SetY(rectPos.y);
	spritePlank->SetZ(z + 0.2f);
	spritePlank->SetRotationAngle(direction);

	spriteA->SetX(x1);
	spriteA->SetY(y1);
	spriteA->SetZ(z);
	spriteB->SetX(x2);
	spriteB->SetY(y2);
	spriteB->SetZ(z + 0.1f);
	spriteA->SetRotationAngle(direction);
	spriteB->SetRotationAngle(direction + 180.0f);

	//Update sprites
	spritePlank->Update(dTime);
	spriteA->Update(dTime);
	spriteB->Update(dTime);
}

void Line::Draw()
{
	spritePlank->Draw();
	spriteA->Draw();
	spriteB->Draw();
}

void Line::SetPosA(glm::vec2 _posA)
{
	posA = _posA;
}

void Line::SetPosB(glm::vec2 _posB)
{
	posB = _posB;
}
