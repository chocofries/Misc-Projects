#include "level3.h"
#include "sprite.h"
#include "cubemap.h"
#include "model.h"
#include "floor.h"
#include "box.h"
#include "evil.h"
#include "ball.h"
#include "slingshot.h"
#include "machine.h"

Level3::Level3()
{
	isInit = false;
}

Level3::~Level3()
{
	while (vecObjects.size() > 0)
	{
		GameObject* temp = vecObjects[vecObjects.size() - 1];
		vecObjects.pop_back();
		delete temp;
	}

	while (vecTexts.size() > 0)
	{
		Texter* temp = vecTexts[vecTexts.size() - 1];
		vecTexts.pop_back();
		delete temp;
	}

	vecBalls.clear();
	vecEvils.clear();

	delete clock;
	delete levelCamera;
	delete physicsManager;
}

void Level3::Initialise(Game * _myGame, ShaderLoader * _shaderloader, AssetLoader * _assetLoader, InputManager * _inputManager, AudioManager* _audioManager)
{
	shaderLoader = _shaderloader;
	assetLoader = _assetLoader;
	inputManager = _inputManager;
	audioManager = _audioManager;

	physicsManager = new PhysicsManager();
	physicsManager->Initialise();

	levelCamera = new Camera();
	levelCamera->SetCamPos(glm::vec3(0.0f, 0.0f, 100.0f));

	glEnable(GL_TEXTURE_2D);
	glGenBuffers(1, &levelVBO);
	glBindBuffer(GL_ARRAY_BUFFER, levelVBO);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Init Clock
	clock = new Clock();
	clock->Initialise();

	//Init Floor
	Floor* floor = new Floor(this);
	floor->SetY(-90.0f);
	floor->Initialise();
	vecObjects.push_back(floor);

	//Init Slingshot
	slingshot = new Slingshot(this, &vecBalls);
	slingshot->SetY(0.0f);
	slingshot->SetX(0.0f);
	slingshot->Initialise();
	vecObjects.push_back(slingshot);

	//Verticals
	Box* plat = new Box(this, BOX_SOLID, 16.0f, 4.0f, 90.0f, true, false, &vecDebris);
	plat->SetX(15.0f);
	plat->SetY(0.0f);
	plat->SetZ(0.1f);
	plat->Initialise();
	vecObjects.push_back(plat);

	plat = new Box(this, BOX_SOLID, 16.0f, 4.0f, 90.0f, true, false, &vecDebris);
	plat->SetX(-15.0f);
	plat->SetY(0.0f);
	plat->SetZ(0.1f);
	plat->Initialise();
	vecObjects.push_back(plat);

	//Init Pile of Boxes
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Box* box;
			box = new Box(this, BOX_HOLLOW, 16.0f - (2.0f*j), 4.0f, 0.0f, false, false, &vecDebris);
			box->SetX(-40.0f + (i*80.0f));
			box->SetY(-20.0f + (j*4.2f));
			box->SetZ(0.1f*i);
			box->Initialise();
			vecObjects.push_back(box);
		}
	}

	//Init Evils
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			Evil* evil = new Evil(this, &vecBlood);
			evil->SetX(-40.0f + (i*80.0f));
			evil->SetY(0.0f);
			evil->SetZ(0.0f);
			evil->Initialise();
			vecObjects.push_back(evil);
			vecEvils.push_back(evil);
		}
	}


	//Init Debris
	for (int i = 0; i < 200; i++)
	{
		Box* debris = new Box(this, BOX_SOLID, 2.0f + (float)(rand() % 4), 1.0f, (float)(rand() % 360), false, false);
		debris->SetY(0.0f);
		debris->SetX(0.0f);
		debris->SetZ(1.0f + 0.1f*i);
		debris->Initialise();
		debris->SetIsActive(false);
		debris->GetBody()->SetActive(false);
		vecObjects.push_back(debris);
		vecDebris.push_back(debris);
	}

	Machine* pulley = new Machine(this);
	pulley->InitPulley(glm::vec3(-40.0f, -25.0f, -1.0f), glm::vec3(40.0f, -25.0f, -1.0f), b2Vec2(-40.0f,30.0f), b2Vec2(40.0f, 30.0f), 16.0f, 4.0f);
	vecObjects.push_back(pulley);

	//Init Balls
	for (int i = 0; i < 2; i++)
	{
		Ball* ball = new Ball(this, 4.0f, BALL_BOMB, &vecMinis);
		ball->SetY(0.0f);
		ball->SetX(0.0f);
		ball->SetZ(1.0f + 0.1f*i);
		ball->Initialise();
		vecObjects.push_back(ball);
		vecBalls.push_back(ball);
	}

	//Init Mini Balls
	for (int i = 0; i < 500; i++)
	{
		Ball* mini = new Ball(this, 1.0f, BALL_MINI);
		mini->SetY(0.0f);
		mini->SetX(0.0f);
		mini->SetZ(1.0f + 0.1f*i);
		mini->Initialise();
		vecObjects.push_back(mini);
		vecMinis.push_back(mini);
	}

	//Init Blood Effect Balls
	for (int i = 0; i < 500; i++)
	{
		Ball* blood = new Ball(this, 0.5f + ((float)(rand() % 20)*0.1f), BALL_BLOOD);
		blood->SetY(0.0f);
		blood->SetX(0.0f);
		blood->SetZ(1.0f + 0.1f*i);
		blood->Initialise();
		vecObjects.push_back(blood);
		vecBlood.push_back(blood);
	}

	//Init Texts
	textLevel = new Texter("", "Assets/Fonts/BabyMetal.ttf", glm::vec3(-5.0f, 350.0f, 200.0f), shaderLoader, assetLoader, levelCamera, true);
	textLevel->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
	textLevel->SetScale(0.5f);
	vecTexts.push_back(textLevel);

	textAngry = new Texter("", "Assets/Fonts/BabyMetal.ttf", glm::vec3(-360.0f, 350.0f, 200.0f), shaderLoader, assetLoader, levelCamera, true);
	textAngry->SetColor(glm::vec3(0.5f, 0.0f, 0.0f));
	textAngry->SetScale(0.25f);
	vecTexts.push_back(textAngry);

	textEvil = new Texter("", "Assets/Fonts/BabyMetal.ttf", glm::vec3(120.0f, 350.0f, 200.0f), shaderLoader, assetLoader, levelCamera, true);
	textEvil->SetColor(glm::vec3(0.5f, 0.0f, 0.0f));
	textEvil->SetScale(0.25f);
	vecTexts.push_back(textEvil);

	textTimer = new Texter("", "Assets/Fonts/BabyMetal.ttf", glm::vec3(-50.0f, -50.0f, 200.0f), shaderLoader, assetLoader, levelCamera, true);
	textTimer->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
	textTimer->SetScale(1.0f);
	vecTexts.push_back(textTimer);

	isInit = true;
}

void Level3::Update()
{
	clock->Process();
	double deltaTime = clock->GetDeltaTick();

	//Camera
	levelCamera->ComputeView();
	levelCamera->ComputeProjection();

	//Update physics
	if (!hasFailed)
	{
		physicsManager->Update((float)deltaTime);
	}

	//Update objects
	for (unsigned int i = 0; i < vecObjects.size(); i++)
	{
		if (vecObjects[i]->GetIsActive())
		{
			vecObjects[i]->Update(deltaTime);
		}
	}

	textAngry->SetText("ANGRY: " + std::to_string(shootableBalls));
	textEvil->SetText("EVIL: " + std::to_string(activeEvils));

	CheckWinLose();
	ProcessKeyInput();

	if (isResetting)
	{
		myGame->GetGameInstance().ResetLevels();
	}
	else if (isWinning)
	{
		myGame->GetGameInstance().ResetLevels();
		myGame->GetGameInstance().LoadLevel(4);
	}

	glutPostRedisplay();
}

void Level3::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.8f, 0.0f, 0.0f, 1.0f); //clear

										  //Draw texts
	for (unsigned int i = 0; i < vecTexts.size(); i++)
	{
		vecTexts[i]->Render();
	}

	//Draw objects
	for (unsigned int i = 0; i < vecObjects.size(); i++)
	{
		if (vecObjects[i]->GetIsActive())
		{
			vecObjects[i]->Draw();
		}
	}

	glutSwapBuffers();
}

void Level3::ProcessKeyInput()
{
}

void Level3::CheckWinLose()
{
	//Count active balls and evils
	shootableBalls = 0;
	activeEvils = 0;

	for (unsigned int i = 0; i < vecBalls.size(); i++)
	{
		if (vecBalls[i]->GetHasHit() == false)
		{
			shootableBalls += 1;
		}
	}
	for (unsigned int i = 0; i < vecEvils.size(); i++)
	{
		if (vecEvils[i]->GetIsActive())
		{
			activeEvils += 1;
		}
	}

	if (activeEvils > 0)
	{
		if (shootableBalls <= 0)
		{
			slingshot->SetIsActive(false);
			loseTimer += 1.0f * (float)clock->GetDeltaTick();

			if (loseTimer < 10.0f)
			{
				textTimer->SetText(std::to_string(10 - (int)loseTimer));
			}
			else if (loseTimer >= 10.0f && loseTimer < 12.5f)
			{
				hasFailed = true;
				textTimer->SetPosition(glm::vec3(-450.0f, -50.0f, 200.0f));
				textTimer->SetText("FAILURE");
				textAngry->SetText("");
				textEvil->SetText("");
				textLevel->SetText("");
			}
			else //Lose and return to main menu
			{
				isResetting = true;
			}
		}
	}
	else //Win and go to next level
	{
		slingshot->SetIsActive(false);
		textTimer->SetPosition(glm::vec3(-450.0f, -50.0f, 200.0f));
		textTimer->SetText("VICTORY");
		textAngry->SetText("");
		textEvil->SetText("");
		textLevel->SetText("");

		if (winTimer < 5.0f)
		{
			winTimer += 1.0f*(float)clock->GetDeltaTick();
		}
		else
		{
			isWinning = true;
		}
	}
}
