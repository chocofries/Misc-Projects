#pragma once
#pragma once
#include "level.h"

class Ball;
class Box;
class Evil;
class Slingshot;
class Level2 : public Level
{
public:
	Level2();
	virtual ~Level2();

	virtual void Initialise(Game* _myGame, ShaderLoader* _shaderloader, AssetLoader* _assetLoader, InputManager* _inputManager, AudioManager* _audioManager);
	virtual void Update();
	virtual void Draw();

	virtual void ProcessKeyInput();

	void CheckWinLose();

private:
	std::vector<Ball*> vecBalls;
	std::vector<Ball*> vecMinis;
	std::vector<Ball*> vecBlood;
	std::vector<Evil*> vecEvils;
	std::vector<Box*> vecDebris;

	int shootableBalls;
	int activeEvils;

	float loseTimer;
	float winTimer;

	bool isResetting;
	bool isWinning;
	bool hasFailed;

	Slingshot* slingshot;

	Texter* textLevel;
	Texter* textAngry;
	Texter* textEvil;
	Texter* textTimer;
};