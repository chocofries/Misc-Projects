#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fmod.hpp>
#include "shaderloader.h"
#include "assetloader.h"
#include "physicsmanager.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "level.h"
#include "inputmanager.h"
#include "audiomanager.h"

class Level;
class InputManager;

class Game
{
public:
	Game();
	~Game();

	void Initialise(int _width, int _height);
	void Update();
	void Draw();

	static Game& GetGameInstance();
	static void DestroyGameInstance();

	void SetScreenMouseX(int _x);
	void SetScreenMouseY(int _y);
	void SetCurrentLevel(int _index);

	void ResetLevels();
	void LoadLevel(int _index);

	InputManager* GetInputManager();

protected:
	//Singleton
	static Game* currentGame;

private:
	ShaderLoader * shaderLoader;
	AssetLoader* textureLoader;
	InputManager* inputManager;
	AudioManager* audioManager;
	Level* currentLevel;
	std::vector<Level*> vecLevels;

	int currentIndex; //Index of the currentlevel in the vecLevels

	int currentRows;
	int currentColumns;
	int screenMouseX;
	int screenMouseY;
};