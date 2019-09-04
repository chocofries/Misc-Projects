#include "game.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "menulevel.h"

// Static Variables
Game* Game::currentGame = 0;

Game::Game()
{

}

Game::~Game()
{
	while (vecLevels.size() > 0)
	{
		Level* tempLevel = vecLevels[vecLevels.size() - 1];
		vecLevels.pop_back();
		delete tempLevel;
	}

	delete shaderLoader;
	delete textureLoader;
	delete inputManager;
	delete audioManager;
}

void Game::Initialise(int _width, int _height)
{
	shaderLoader = new ShaderLoader();
	shaderLoader->CreateProgram("Assets/VertexShader.vs", "Assets/FragmentShader.fs", "vertShader0", "fragShader0");

	textureLoader = new AssetLoader();

	inputManager = new InputManager();

	audioManager = new AudioManager();
	audioManager->Initialise();

	currentLevel = new MenuLevel();
	currentLevel->Initialise(this, shaderLoader, textureLoader, inputManager, audioManager);
	vecLevels.push_back(currentLevel);

	//currentLevel = new Level1();
	//currentLevel->Initialise(this, shaderLoader, textureLoader, inputManager, audioManager);
	//vecLevels.push_back(currentLevel);

	//currentLevel = new Level2();
	//currentLevel->Initialise(this, shaderLoader, textureLoader, inputManager, audioManager);
	//vecLevels.push_back(currentLevel);

	//currentLevel = new Level3();
	//currentLevel->Initialise(this, shaderLoader, textureLoader, inputManager, audioManager);
	//vecLevels.push_back(currentLevel);

	currentLevel = vecLevels.at(0);
}

void Game::Update()
{
	if (currentLevel != nullptr)
	{
		if (currentLevel->GetIsInit())
		{
			currentLevel->Update();
			currentLevel->SetScreenMouseX(screenMouseX);
			currentLevel->SetScreenMouseY(screenMouseY);
		}
	}
	inputManager->SetMouseX(screenMouseX);
	inputManager->SetMouseY(screenMouseY);
	inputManager->UpdateKeys();

	audioManager->Update();
}

void Game::Draw()
{
	if (currentLevel != nullptr)
	{
		if (currentLevel->GetIsInit())
		{
			currentLevel->Draw();
		}
	}
}

Game& Game::GetGameInstance()
{
	if (currentGame == 0)
	{
		currentGame = new Game();
	}

	return (*currentGame);
}

void Game::DestroyGameInstance()
{
	delete currentGame;
	currentGame = 0;
}

void Game::SetScreenMouseX(int _x)
{
	screenMouseX = _x;
}

void Game::SetScreenMouseY(int _y)
{
	screenMouseY = _y;
}

void Game::SetCurrentLevel(int _index)
{
	if (vecLevels.at(_index) != nullptr)
	{
		currentIndex = _index;
		currentLevel = vecLevels.at(_index);
	}
}

void Game::ResetLevels()
{
	//Reset levels
	//while (vecLevels.size() > 1)
	//{
	//	Level* tempLevel = vecLevels[vecLevels.size() - 1];
	//	vecLevels.pop_back();
	//	delete tempLevel;
	//}
	Level* tempLevel = vecLevels.at(1);
	delete tempLevel;
	vecLevels.pop_back();
	audioManager->ReleaseSFX();
	//Level* temp = new Level1();
	//temp->Initialise(this, shaderLoader, textureLoader, inputManager, audioManager);
	//vecLevels.push_back(temp);

	//temp = new Level2();
	//temp->Initialise(this, shaderLoader, textureLoader, inputManager, audioManager);
	//vecLevels.push_back(temp);

	//temp = new Level3();
	//temp->Initialise(this, shaderLoader, textureLoader, inputManager, audioManager);
	//vecLevels.push_back(temp);

	currentLevel = vecLevels.at(0);
}

void Game::LoadLevel(int _index)
{
	Level * temp;
	switch (_index)
	{
	case 1:
		temp = new Level1();
		temp->Initialise(this, shaderLoader, textureLoader, inputManager, audioManager);
		vecLevels.push_back(temp);
		break;
	case 2:
		temp = new Level2();
		temp->Initialise(this, shaderLoader, textureLoader, inputManager, audioManager);
		vecLevels.push_back(temp);
		break;
	case 3:
		temp = new Level3();
		temp->Initialise(this, shaderLoader, textureLoader, inputManager, audioManager);
		vecLevels.push_back(temp);
		break;
	case 4:
		temp = new Level4();
		temp->Initialise(this, shaderLoader, textureLoader, inputManager, audioManager);
		vecLevels.push_back(temp);
		break;
	}

	currentLevel = vecLevels.at(1);
}

InputManager * Game::GetInputManager()
{
	return inputManager;
}
