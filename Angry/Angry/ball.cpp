#include "ball.h"

Ball::Ball(Level * _level, float _radius, BallType _type)
{
	this->level = _level;
	levelCamera = level->GetCamera();
	shaderLoader = level->GetShaderLoader();
	assetLoader = level->GetAssetLoader();
	physicsManager = level->GetPhysicsManager();
	inputManager = level->GetInputManager();
	clock = level->GetClock();
	VBO = level->GetVBO();
	xRot = 0.0f;
	yRot = 0.0f;
	zRot = 1.0f;

	radius = _radius;
	destroySpeed = 0.2f;
	isDestructible = false;
		
	hasHit = false;
	abilityUsed = false;

	ballType = _type;
}

Ball::Ball(Level * _level, float _radius, BallType _type, std::vector<Ball*>* _vecMinis)
{
	this->level = _level;
	levelCamera = level->GetCamera();
	shaderLoader = level->GetShaderLoader();
	assetLoader = level->GetAssetLoader();
	physicsManager = level->GetPhysicsManager();
	inputManager = level->GetInputManager();
	audioManager = level->GetAudioManager();
	clock = level->GetClock();
	VBO = level->GetVBO();
	xRot = 0.0f;
	yRot = 0.0f;
	zRot = 1.0f;

	radius = _radius;
	destroySpeed = 5.0f;
	isDestructible = false;
	hasHit = false;
	abilityUsed = false;

	ballType = _type;
	vecMinis = _vecMinis;
}

Ball::~Ball()
{
	delete sprite;
}

void Ball::Initialise()
{
	sprite = new Sprite(this);

	switch (ballType)
	{
	case BALL_DASH:
		sprite->InitSprite("Assets/Dash.png", "dash", 0.0f, 1, 1, 1, 0, 100, 100);
		audioManager->GetAudioSystem()->createSound("Assets/swoosh1.wav", FMOD_DEFAULT, 0, &soundAbility);
		audioManager->AddSoundToVector(soundAbility);
		break;
	case BALL_SHOTGUN:
		sprite->InitSprite("Assets/Shotgun.png", "shotgun", 0.0f, 1, 1, 1, 0, 100, 100);
		audioManager->GetAudioSystem()->createSound("Assets/explode1.wav", FMOD_DEFAULT, 0, &soundAbility);
		audioManager->AddSoundToVector(soundAbility);
		break;
	case BALL_BOMB:
		sprite->InitSprite("Assets/Angry.png", "angry", 0.0f, 1, 1, 1, 0, 100, 100);
		audioManager->GetAudioSystem()->createSound("Assets/explode2.wav", FMOD_DEFAULT, 0, &soundAbility);
		audioManager->AddSoundToVector(soundAbility);
		break;
	case BALL_WHEEL:
		sprite->InitSprite("Assets/Wheel.png", "wheel", 0.0f, 1, 1, 1, 0, 100, 100);
		break;
	case BALL_MINI:
		sprite->InitSprite("Assets/Circle.png", "circle", 0.0f, 1, 1, 1, 0, 100, 100);
		break;
	case BALL_BLOOD:
		sprite->InitSprite("Assets/Blood.png", "blood", 0.0f, 1, 1, 1, 0, 100, 100);
		break;
	}
	sprite->SetWidth(2.08f*radius);
	sprite->SetHeight(2.08f*radius);

	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.userData = this;
	ballBodyDef.position.Set(x, y);
	ballBody = level->GetPhysicsManager()->GetWorld()->CreateBody(&ballBodyDef);
	listener = level->GetPhysicsManager()->GetPhysicsListener();

	b2CircleShape ballShape;
	ballShape.m_radius = radius*0.5f;

	b2FixtureDef fixDef;
	fixDef.shape = &ballShape;
	fixDef.density = 2.5f;
	fixDef.friction = 0.8f;
	fixDef.restitution = 0.5f;
	if (ballType == BALL_BLOOD)
	{
		fixDef.filter.categoryBits = COL_EFFECT;
		fixDef.filter.maskBits = COL_EFFECT;
	}
	ballBody->CreateFixture(&fixDef);

	if (ballType != BALL_WHEEL)
	{
		SetBallActive(false);
	}
	else
	{
		SetBallActive(true);
	}

	if (ballType == BALL_MINI)
	{
		isDestructible = true;
	}
}

void Ball::Update(double dTime)
{
	x = ballBody->GetPosition().x;
	y = ballBody->GetPosition().y;

	if (!hasHit)
	{
		b2Vec2 dir = ballBody->GetLinearVelocity();
		dir.Normalize();
		rotationAngle = Utils::RadToDeg(atan2f(dir.y, dir.x));
	}
	else
	{
		rotationAngle = Utils::RadToDeg(ballBody->GetAngle());
	}

	prevDist = glm::distance(glm::vec2(x, y), glm::vec2(prevX, prevY));

	//Activating ability
	if (ballType != BALL_WHEEL && !abilityUsed && ballType != BALL_MINI && ballType != BALL_BLOOD)
	{
		if (inputManager->GetMouseState(MOUSE_LEFT) == KEY_DOWN)
		{
			if (ballType == BALL_DASH)
			{
				//Dash ability, boosts the ball's velocity when activated
				b2Vec2 dash(ballBody->GetLinearVelocity());
				dash *= 100.0f;

				ballBody->SetLinearVelocity(dash);
			}
			else if (ballType == BALL_SHOTGUN && vecMinis != nullptr)
			{
				//Shotgun ability, explodes and sends out miniballs in a cone like a shotgun
				int numMinis = 40;
				float blastForce = 100.0f;

				for (int i = 0; i < numMinis; i++)
				{
					float angle = Utils::DegToRad((i / (float)numMinis) * 180.0f);

					b2Vec2 bodyDir = ballBody->GetLinearVelocity();
					b2Vec2 blastDir(sinf(angle) + bodyDir.x, cosf(angle) + bodyDir.y);
					blastDir.Normalize();
					blastDir *= blastForce;

					std::vector<Ball*>::iterator it;
					for (it = vecMinis->begin(); it != vecMinis->end(); it++)
					{
						Ball* mini = *it;
						if (mini->GetIsActive() == false)
						{
							mini->SetBallActive(true);
							mini->SetTransform(b2Vec2(x, y), (float)(rand() % 360));
							mini->GetBody()->SetLinearVelocity(blastDir);
							break;
						}
					}
				}
				isDestroying = true;
			}
			else if (ballType == BALL_BOMB && vecMinis != nullptr)
			{
				//Bomb ability, explodes and sends out miniballs in an omnidirectional blast
				int numMinis = 100;
				float blastForce = 75.0f;

				for (int i = 0; i < numMinis; i++)
				{
					float angle = Utils::DegToRad((i / (float)numMinis) * 360.0f);
					b2Vec2 blastDir(sinf(angle), cosf(angle));
					blastDir *= blastForce;

					std::vector<Ball*>::iterator it;
					for (it = vecMinis->begin(); it != vecMinis->end(); it++)
					{
						Ball* mini = *it;
						if (mini->GetIsActive() == false)
						{
							mini->SetBallActive(true);
							mini->SetTransform(b2Vec2(x, y), (float)(rand() % 360));
							mini->GetBody()->SetLinearVelocity(blastDir);
							break;
						}
					}
				}
				isDestroying = true;
			}

			audioManager->GetAudioSystem()->playSound(soundAbility, 0, false, 0);
			abilityUsed = true;
		}
	}

	//Check Collision
	if (listener->GetBodyA() != nullptr && listener->GetBodyB() != nullptr)
	{
		if (listener->GetBodyA()->GetUserData() == this || listener->GetBodyB()->GetUserData() == this)
		{
			hasHit = true;
			abilityUsed = true;
			if (prevDist >= destroySpeed && isDestructible)
			{
				isDestroying = true;
			}
		}
	}

	prevX = x;
	prevY = y;
	sprite->Update(dTime);

	//Check bounds
	if (x < WINDOW_WIDTH*-0.055f || x > WINDOW_WIDTH*0.055f || y < WINDOW_HEIGHT*-0.055f || y > WINDOW_HEIGHT*0.15f)
	{
		if (ballType == BALL_MINI || ballType == BALL_BLOOD)
		{
			isDestroying = true;
		}
		hasHit = true;
	}

	//Destroying at the end of update
	if (isDestroying)
	{
		if (destroyDelay <= 0.01f)
		{
			destroyDelay += 1.0f * (float)dTime;
		}
		else
		{
			SetBallActive(false);

			if (ballType == BALL_BOMB || ballType == BALL_SHOTGUN)
			{
				hasHit = true;
			}
		}
	}

}

void Ball::Draw()
{
	sprite->Draw();
}

void Ball::SetRadius(float r)
{
	radius = r;
}

void Ball::SetTransform(b2Vec2 pos, float angle)
{
	ballBody->SetTransform(pos, angle);
}

void Ball::ShootBall(b2Vec2 velocity)
{
	ballBody->ApplyTorque((float)(rand() % 360), true);
	ballBody->ApplyLinearImpulse(velocity, b2Vec2(x, y), true);
}

void Ball::SetBallActive(bool _isActive)
{
	isActive = _isActive;
	ballBody->SetActive(_isActive);

	if (!isActive)
	{
		if (ballType == BALL_MINI || ballType == BALL_BLOOD)
		{
			hasHit = false;
			isDestroying = false;
		}
		ballBody->SetLinearVelocity(b2Vec2(0, 0));
		ballBody->SetAngularVelocity(0);
		destroyDelay = 0.0f;
	}
}

bool Ball::GetHasHit() const
{
	return hasHit;
}

b2Body * Ball::GetBody() const
{
	return ballBody;
}
