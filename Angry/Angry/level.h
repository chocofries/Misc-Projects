#pragma once
#include "game.h"
#include "clock.h"
#include "gameobject.h"

class Game;
class CubeMap;

class Level
{
public:
	Level();
	virtual ~Level();

	virtual void Initialise(Game* _myGame, ShaderLoader* _shaderloader, AssetLoader* _textureLoader, InputManager* _inputManager, AudioManager* _audioManager);
	virtual void Update();
	virtual void Draw();

	virtual void ProcessKeyInput();

	std::vector<Texter*>* GetVecTexts();

	GLuint GetVBO() const;
	ShaderLoader* GetShaderLoader() const;
	AssetLoader* GetAssetLoader() const;
	InputManager* GetInputManager() const;
	PhysicsManager* GetPhysicsManager() const;
	AudioManager* GetAudioManager() const;
	Camera* GetCamera() const;
	Clock* GetClock() const;
	CubeMap* GetSkyBox() const;
	bool GetIsInit() const;

	void SetScreenMouseX(int _x);
	void SetScreenMouseY(int _y);

protected:
	GLuint levelVBO;
	Game* myGame;
	ShaderLoader* shaderLoader;
	AssetLoader* assetLoader;
	InputManager* inputManager;
	PhysicsManager* physicsManager;
	AudioManager* audioManager;
	Camera* levelCamera;
	Clock* clock;
	CubeMap* skyBox;

	std::vector<GameObject*> vecObjects;
	std::vector<Texter*> vecTexts;

	bool isInit;

	int screenMouseX;
	int screenMouseY;
	glm::vec3 rayWorld;
	glm::vec3 intersection;
};