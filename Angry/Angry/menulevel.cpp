#include "menulevel.h"
#include "buttonset.h"

MenuLevel::MenuLevel()
{
	isInit = false;
}

MenuLevel::~MenuLevel()
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
	delete clock;
	delete levelCamera;
	delete physicsManager;

	delete menuButtons;
}

void MenuLevel::Initialise(Game * _myGame, ShaderLoader * _shaderloader, AssetLoader * _assetLoader, InputManager * _inputManager, AudioManager* _audioManager)
{
	shaderLoader = _shaderloader;
	assetLoader = _assetLoader;
	inputManager = _inputManager;
	audioManager = _audioManager;

	levelCamera = new Camera();
	levelCamera->SetCamPos(glm::vec3(0.0f, 0.0f, 100.0f));

	glEnable(GL_TEXTURE_2D);
	glGenBuffers(1, &levelVBO);
	glBindBuffer(GL_ARRAY_BUFFER, levelVBO);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Init Clock
	clock = new Clock();
	clock->Initialise();

	//Init Text
	Texter* title = new Texter("ANGRY", "Assets/Fonts/BabyMetal.ttf", glm::vec3(-360.0f, -80.0f, 2.0f), shaderLoader, assetLoader, levelCamera);
	title->SetColor(glm::vec3(0.5f, 0.0f, 0.0f));
	title->SetScale(1.0f);
	vecTexts.push_back(title);

	title = new Texter("A GAME BY JOHN BU", "Assets/Fonts/BabyMetal.ttf", glm::vec3(220.0f, -400.0f, 2.0f), shaderLoader, assetLoader, levelCamera);
	title->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
	title->SetScale(0.25f);
	vecTexts.push_back(title);

	//Init Buttons
	menuButtons = new ButtonSet(clock);

	isInit = true;
}

void MenuLevel::Update()
{
	clock->Process();
	double deltaTime = clock->GetDeltaTick();

	//Camera
	levelCamera->ComputeView();
	levelCamera->ComputeProjection();

	ProcessKeyInput();

	//Update objects
	for (unsigned int i = 0; i < vecObjects.size(); i++)
	{
		if (vecObjects[i]->GetIsActive())
		{
			vecObjects[i]->Update(deltaTime);
		}
	}

	glutPostRedisplay();
}

void MenuLevel::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.8f, 0.0f, 0.0f, 1.0f); //clear

	//Draw objects
	for (unsigned int i = 0; i < vecObjects.size(); i++)
	{
		if (vecObjects[i]->GetIsActive())
		{
			vecObjects[i]->Draw();
		}
	}

	//Draw texts
	for (unsigned int i = 0; i < vecTexts.size(); i++)
	{
		vecTexts[i]->Render();
	}

	glutSwapBuffers();
}

void MenuLevel::ProcessKeyInput()
{
	if (inputManager->GetMouseState(MOUSE_LEFT) == KEY_DOWN)
	{
		myGame->GetGameInstance().LoadLevel(1);
	}
}
