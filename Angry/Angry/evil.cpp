#include "evil.h"

Evil::Evil(Level * _level, std::vector<Ball*>* _vecBlood)
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

	width = 5.0f;
	height = 5.0f;
	destroySpeed = 0.1f;
	isDestructible = true;
	isDestroying = false;
	destroyDelay = 0.0f;

	vecBlood = _vecBlood;
}

Evil::~Evil()
{
	delete sprite;
}

void Evil::Initialise()
{
	sprite = new Sprite(this);
	sprite->InitSprite("Assets/Evil.png", "evil", 0.0f, 1, 1, 1, 0, 100, 100);
	sprite->SetWidth(2.08f*width);
	sprite->SetHeight(2.08f*height);

	boxBodyDef.type = b2_dynamicBody;
	boxBodyDef.userData = this;
	boxBodyDef.position.Set(x, y);
	boxBody = level->GetPhysicsManager()->GetWorld()->CreateBody(&boxBodyDef);
	listener = level->GetPhysicsManager()->GetPhysicsListener();

	b2PolygonShape boxShape;
	boxShape.SetAsBox(width*0.5f, height*0.5f);

	b2FixtureDef fixDef;
	fixDef.shape = &boxShape;
	fixDef.density = 1.0f;
	fixDef.friction = 0.1f;
	fixDef.restitution = 0.5f;
	boxBody->CreateFixture(&fixDef);
	boxBody->SetLinearDamping(0.1f);
	boxBody->SetAngularDamping(0.1f);

	audioManager->GetAudioSystem()->createSound("Assets/blood2.wav", FMOD_DEFAULT, 0, &soundDeath);
	audioManager->AddSoundToVector(soundDeath);
}

void Evil::Update(double dTime)
{
	x = boxBody->GetPosition().x;
	y = boxBody->GetPosition().y;
	rotationAngle = Utils::RadToDeg(boxBody->GetAngle());

	prevDist = glm::distance(glm::vec2(x, y), glm::vec2(prevX, prevY));

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
		
		if (x < WINDOW_WIDTH*-0.05f || x > WINDOW_WIDTH*0.05f || y < WINDOW_HEIGHT*-0.05f)
		{
			isDestroying = true;
		}
	}

	if (isDestroying)
	{
		if (destroyDelay <= 0.01f)
		{
			destroyDelay += 1.0f * (float)dTime;
		}
		else
		{
			//Blood splatter effect
			for (int i = 0; i < 50; i++)
			{
				float angle = (float)(rand() % 360);
				b2Vec2 blastDir(sinf(angle), cosf(angle));
				blastDir.Normalize();
				blastDir *= (float)(rand() % 4000)*0.01f;

				std::vector<Ball*>::iterator it;
				for (it = vecBlood->begin(); it != vecBlood->end(); it++)
				{
					Ball* blood = *it;

					if (blood->GetIsActive() == false)
					{
						blood->SetBallActive(true);
						blood->SetTransform(b2Vec2(x, y), (float)(rand() % 360));
						blood->GetBody()->SetLinearVelocity(blastDir);
						break;
					}
				}
			}

			audioManager->GetAudioSystem()->playSound(soundDeath, 0, false, 0);
			isActive = false;
			boxBody->SetActive(false);
		}
	}

	prevX = x;
	prevY = y;
	sprite->Update(dTime);
}

void Evil::Draw()
{
	sprite->Draw();
}
