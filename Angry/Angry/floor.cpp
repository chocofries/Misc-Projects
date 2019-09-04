#include "floor.h"

Floor::Floor(Level* _level)
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

	width = 800.0f;
	height = 100.0f;
}

Floor::~Floor()
{
	delete sprite;
}

void Floor::Initialise()
{
	sprite = new Sprite(this);
	sprite->InitSprite("Assets/Square.png", "square", 0.0f, 1, 1, 1, 0, 100, 100);
	sprite->SetWidth(2.1f*width);
	sprite->SetHeight(2.1f*height);

	floorBodyDef.position.Set(x, y);
	floorBodyDef.userData = this;
	floorBody = level->GetPhysicsManager()->GetWorld()->CreateBody(&floorBodyDef);

	b2PolygonShape floorBox;
	floorBox.SetAsBox(width*0.5f, height*0.5f);
	floorBody->CreateFixture(&floorBox, 0.0f);
}

void Floor::Update(double dTime)
{
	sprite->Update(dTime);
}

void Floor::Draw()
{
	sprite->Draw();
}