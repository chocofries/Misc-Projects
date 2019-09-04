#include "slingshot.h"
#include <Box2D\Common\b2Math.h>

Slingshot::Slingshot(Level * _level, std::vector<Ball*>* _vecBalls)
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
	vecBalls = _vecBalls;
	xRot = 0.0f;
	yRot = 0.0f;
	zRot = 1.0f;

	isShooting = false;
	isAiming = false;
	delay = 0.1f;
	aimPull = 0.0f;
}

Slingshot::~Slingshot()
{
	while (vecSprites.size() > 0)
	{
		GameObject* temp = vecSprites[vecSprites.size() - 1];
		vecSprites.pop_back();
		delete temp;
	}
}

void Slingshot::Initialise()
{
	//Init sprites
	spriteSling = new Sprite(this);
	spriteSling->InitSprite("Assets/circle.png", "circle", 0.0f, 1, 1, 1, 0, 100, 100);
	spriteSling->SetSpriteScale(0.2f);
	spriteSling->SetZ(0.0f);
	spriteSling->SetX(x);
	spriteSling->SetY(y);
	spriteSling->SetIsAttached(false);
	vecSprites.push_back(spriteSling);

	spriteBall = new Sprite(this);
	spriteBall->InitSprite("Assets/Circle.png", "circle", 0.0f, 1, 1, 1, 0, 100, 100);
	spriteBall->SetSpriteScale(0.05f);
	spriteBall->SetZ(10.0f);
	spriteBall->SetX(x);
	spriteBall->SetY(y);
	spriteBall->SetIsAttached(false);
	vecSprites.push_back(spriteBall);

	spritePull = new Sprite(this);
	spritePull->InitSprite("Assets/Square.png", "square", 0.0f, 1, 1, 1, 0, 100, 100);
	spritePull->SetSpriteScale(0.05f);
	spritePull->SetZ(50.0f);
	spritePull->SetX(x);
	spritePull->SetY(y);
	spritePull->SetIsAttached(false);
	vecSprites.push_back(spritePull);

	//Init sounds
	audioManager->GetAudioSystem()->createSound("Assets/swoosh2.wav", FMOD_DEFAULT, 0, &soundShoot);
	audioManager->AddSoundToVector(soundShoot);
}

void Slingshot::Update(double dTime)
{
	ProcessInput(dTime);

	for (unsigned int i = 0; i < vecSprites.size(); i++)
	{
		vecSprites[i]->Update(dTime);
	}
}

void Slingshot::Draw()
{
	for (unsigned int i = 0; i < vecSprites.size(); i++)
	{
		vecSprites[i]->Draw();
	}
}

void Slingshot::ProcessInput(double dTime)
{
	float mouseX = (inputManager->GetMouseX() * 0.1f) - ((float)WINDOW_WIDTH*0.05f);
	float mouseY = (inputManager->GetMouseY() * -0.1f) + ((float)WINDOW_HEIGHT*0.05f);

	float mouseDist = glm::distance(glm::vec2(mouseX, mouseY), glm::vec2(x, y));

	if (mouseDist < 5.0f)
	{
		if (inputManager->GetMouseState(MOUSE_LEFT) == KEY_DOWN)
		{
			isAiming = true;
		}
	}

	if (isAiming && !isShooting)
	{
		isAiming = true;
		aimPull = sqrt(((x - mouseX)*(x - mouseX)) + ((y - mouseY)*(y - mouseY)));
		aimPull = Utils::Clamp(aimPull, 0.0f, 20.0f);

		aimDir.Set((x - mouseX), (y - mouseY));
		aimDir.Normalize();
		aimDir *= aimPull;

		float x1, x2, y1, y2;
		x1 = x;
		y1 = y;
		x2 = x - aimDir.x;
		y2 = y - aimDir.y;

		glm::vec2 rectPos = (glm::vec2(x1, y1) + glm::vec2(x2, y2))*0.5f;
		float rectAngle = std::atan2(y2 - y1, x2 - x1) * 180.0f / MATH_PI;
		float rectDist = glm::distance(glm::vec2(x1, y1), glm::vec2(x2, y2));
		spritePull->SetWidth(rectDist*40.0f);
		spritePull->SetX(rectPos.x);
		spritePull->SetY(rectPos.y);
		spritePull->SetRotationAngle(rectAngle);

		spriteBall->SetX(x - aimDir.x);
		spriteBall->SetY(y - aimDir.y);

		if (inputManager->GetMouseState(MOUSE_LEFT) == KEY_UP)
		{
			spriteBall->SetX(x);
			spriteBall->SetY(y);

			spritePull->SetWidth(0.0f);
			spritePull->SetX(x);
			spritePull->SetY(y);
			spritePull->SetRotationAngle(0.0f);

			aimDir *= 50.0f;

			//Shoot the ball
			Shoot(aimDir);
			audioManager->GetAudioSystem()->playSound(soundShoot, 0, false, 0);

			delay = 0.2f;
			isShooting = true;
		}
	}

	if (isShooting)
	{
		if (delay > 0.0f)
		{
			delay -= 1.0f * (float)dTime;
		}
		else
		{
			if (currentBall != nullptr)
			{
				if (currentBall->GetHasHit() == true)
				{
					isShooting = false;
					isAiming = false;
				}
			}
		}
	}
}

void Slingshot::Shoot(b2Vec2 vec)
{
	std::vector<Ball*>::iterator it;
	for (it = vecBalls->begin(); it != vecBalls->end(); it++)
	{
		Ball* ball = *it;

		if (ball->GetIsActive() == false && ball->GetHasHit() == false)
		{
			currentBall = ball;
			ball->SetBallActive(true);
			ball->SetTransform(b2Vec2(x, y), (float)(rand()%360));
			ball->ShootBall(vec);
			break;
		}
	}
}
