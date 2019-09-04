#include "box.h"

Box::Box(Level * _level, BoxType _type, float _w, float _h, float _angle, bool _isStatic, bool _isGhost)
{
	this->level = _level;
	levelCamera = level->GetCamera();
	shaderLoader = level->GetShaderLoader();
	assetLoader = level->GetAssetLoader();
	physicsManager = level->GetPhysicsManager();
	audioManager = level->GetAudioManager();
	clock = level->GetClock();
	VBO = level->GetVBO();
	xRot = 0.0f;
	yRot = 0.0f;
	zRot = 1.0f;

	isStatic = _isStatic;
	isGhost = _isGhost;
	boxType = _type;
	width = _w;
	height = _h;
	spawnAngle = _angle;
	destroySpeed = 0.01f;

	if (boxType == BOX_HOLLOW)
	{
		isDestructible = true;
	}
	else
	{
		isDestructible = false;
	}

	isDestroying = false;
	destroyDelay = 0.0f;
}

Box::Box(Level * _level, BoxType _type, float _w, float _h, float _angle, bool _isStatic, bool _isGhost, std::vector<Box*>* _vecDebris)
{
	this->level = _level;
	levelCamera = level->GetCamera();
	shaderLoader = level->GetShaderLoader();
	assetLoader = level->GetAssetLoader();
	physicsManager = level->GetPhysicsManager();
	audioManager = level->GetAudioManager();
	clock = level->GetClock();
	VBO = level->GetVBO();
	xRot = 0.0f;
	yRot = 0.0f;
	zRot = 1.0f;

	isStatic = _isStatic;
	isGhost = _isGhost;
	boxType = _type;
	width = _w;
	height = _h;
	spawnAngle = _angle;
	destroySpeed = 0.2f;

	if (boxType == BOX_HOLLOW)
	{
		isDestructible = true;
	}
	else
	{
		isDestructible = false;
	}

	isDestroying = false;
	destroyDelay = 0.0f;

	vecDebris = _vecDebris;
}

Box::~Box()
{
	delete spriteA;
	delete spriteB;
	delete spritePlank;
}

void Box::Initialise()
{
	spriteA = new Sprite(this);
	spriteB = new Sprite(this);
	spritePlank = new Sprite(this);

	if (!isGhost)
	{
		switch (boxType)
		{
		case BOX_HOLLOW:
			spriteA->InitSprite("Assets/BoxHollow.png", "boxHollow", 0.0f, 1, 1, 1, 0, 1000, 1000);
			spriteB->InitSprite("Assets/BoxHollow.png", "boxHollow", 0.0f, 1, 1, 1, 0, 1000, 1000);
			spritePlank->InitSprite("Assets/PlankHollow.png", "plankHollow", 0.0f, 1, 1, 1, 0, 1000, 1000);
			break;
		case BOX_SOLID:
			spriteA->InitSprite("Assets/Box.png", "box", 0.0f, 1, 1, 1, 0, 1000, 1000);
			spriteB->InitSprite("Assets/Box.png", "box", 0.0f, 1, 1, 1, 0, 1000, 1000);
			spritePlank->InitSprite("Assets/Square.png", "square", 0.0f, 1, 1, 1, 0, 1000, 1000);
			break;
		}
	}
	else
	{
		spriteA->InitSprite("Assets/LightBox.png", "lightBox", 0.0f, 1, 1, 1, 0, 1000, 1000);
		spriteB->InitSprite("Assets/LightBox.png", "lightBox", 0.0f, 1, 1, 1, 0, 1000, 1000);
		spritePlank->InitSprite("Assets/LightSquare.png", "lightSquare", 0.0f, 1, 1, 1, 0, 1000, 1000);
	}

	spriteA->SetIsAttached(false);
	spriteB->SetIsAttached(false);
	spritePlank->SetIsAttached(false);

	spriteA->SetWidth(2.1f*height);
	spriteA->SetHeight(2.1f*height);
	spriteB->SetWidth(2.1f*height);
	spriteB->SetHeight(2.1f*height);
	spritePlank->SetWidth(2.1f*width);
	spritePlank->SetHeight(2.1f*height);

	if (!isStatic) { boxBodyDef.type = b2_dynamicBody; }
	else { boxBodyDef.type = b2_staticBody; }
	boxBodyDef.userData = this;
	boxBodyDef.position.Set(x, y);
	boxBodyDef.angle = Utils::DegToRad(spawnAngle);
	boxBody = level->GetPhysicsManager()->GetWorld()->CreateBody(&boxBodyDef);
	listener = level->GetPhysicsManager()->GetPhysicsListener();

	b2PolygonShape boxShape;
	boxShape.SetAsBox(width*0.5f, height*0.5f);

	b2FixtureDef fixDef;
	fixDef.shape = &boxShape;
	fixDef.density = 1.0f;
	fixDef.friction = 0.8f;
	fixDef.restitution = 0.2f;
	if (isGhost)
	{
		fixDef.filter.maskBits = 0x000; //Disable collisions
	}
	boxBody->CreateFixture(&fixDef);
	boxBody->SetLinearDamping(0.1f);
	boxBody->SetAngularDamping(0.1f);

	//Init sound
	audioManager->GetAudioSystem()->createSound("Assets/wood2.wav", FMOD_DEFAULT, 0, &soundBreak);
	audioManager->AddSoundToVector(soundBreak);
}

void Box::Update(double dTime)
{
	x = boxBody->GetPosition().x;
	y = boxBody->GetPosition().y;
	rotationAngle = Utils::RadToDeg(boxBody->GetAngle());

	prevDist = glm::distance(glm::vec2(x, y), glm::vec2(prevX, prevY));

	//Sprite positioning and rotation
	float halfDist = (width - height)*0.5f;
	float x1, x2, y1, y2;
	x1 = x + Utils::LengthDirX(-halfDist, rotationAngle);
	y1 = y + Utils::LengthDirY(-halfDist, rotationAngle);
	x2 = x + Utils::LengthDirX(halfDist, rotationAngle);
	y2 = y + Utils::LengthDirY(halfDist, rotationAngle);

	glm::vec2 rectPos = (glm::vec2(x1, y1) + glm::vec2(x2, y2))*0.5f;
	float rectAngle = std::atan2(y2 - y1, x2 - x1) * 180.0f / MATH_PI;
	float rectDist = glm::distance(glm::vec2(x1, y1), glm::vec2(x2, y2));
	spritePlank->SetWidth(rectDist*2.1f);
	spritePlank->SetX(rectPos.x);
	spritePlank->SetY(rectPos.y);
	spritePlank->SetZ(z+0.2f);
	spritePlank->SetRotationAngle(rectAngle);

	spriteA->SetX(x1);
	spriteA->SetY(y1);
	spriteA->SetZ(z);
	spriteB->SetX(x2);
	spriteB->SetY(y2);
	spriteB->SetZ(z+0.1f);
	spriteA->SetRotationAngle(rotationAngle);
	spriteB->SetRotationAngle(rotationAngle+180.0f);

	//Check Collision
	if (isDestructible && !isDestroying)
	{
		if (listener->GetBodyA() != nullptr && listener->GetBodyB() != nullptr)
		{
			if (listener->GetBodyA()->GetUserData() == this || listener->GetBodyB()->GetUserData() == this)
			{
				if (prevDist >= destroySpeed)
				{
					isDestroying = true;
				}
			}
		}
	}

	if (isDestroying)
	{
		if (destroyDelay <= 0.05f)
		{
			destroyDelay += 1.0f * (float)dTime;
		}
		else
		{
			//Debris scatter
			for (int i = 0; i < (int)(width*0.25f); i++)
			{
				float angle = (float)(rand() % 360);
				b2Vec2 blastDir(sinf(angle), cosf(angle));
				blastDir.Normalize();
				blastDir *= (float)(rand() % 1000)*0.01f;

				std::vector<Box*>::iterator it;
				for (it = vecDebris->begin(); it != vecDebris->end(); it++)
				{
					Box* debris = *it;

					if (debris->GetIsActive() == false)
					{
						debris->SetIsActive(true);
						debris->GetBody()->SetActive(true);
						debris->SetTransform(b2Vec2(x, y), (float)(rand() % 360));
						debris->GetBody()->SetLinearVelocity(blastDir);
						break;
					}
				}
			}

			audioManager->GetAudioSystem()->playSound(soundBreak, 0, false, 0);
			isActive = false;
			boxBody->SetActive(false);
		}
	}

	prevX = x;
	prevY = y;

	spritePlank->Update(dTime);
	spriteA->Update(dTime);
	spriteB->Update(dTime);
}

void Box::Draw()
{
	if (width != height)
	{
		spritePlank->Draw();
	}
	spriteA->Draw();
	spriteB->Draw();
}

void Box::SetBoxType(BoxType _type)
{
	boxType = _type;
}

void Box::SetWidth(float w)
{
	width = w;
}

void Box::SetHeight(float h)
{
	height = h;
}

void Box::SetWidthHeight(float w, float h)
{
	width = w;
	height = h;
}

b2Body * Box::GetBody() const
{
	return boxBody;
}

void Box::SetTransform(b2Vec2 pos, float angle)
{
	boxBody->SetTransform(pos, angle);
}

float Box::GetWidth() const
{
	return width;
}

float Box::GetHeight() const
{
	return height;
}
