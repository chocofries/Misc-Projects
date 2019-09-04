#pragma once
#include "level.h"

class ButtonSet;

class MenuLevel : public Level
{
public:
	MenuLevel();
	virtual ~MenuLevel();

	virtual void Initialise(Game* _myGame, ShaderLoader* _shaderloader, AssetLoader* _assetLoader, InputManager* _inputManager, AudioManager* _audioManager);
	virtual void Update();
	virtual void Draw();

	virtual void ProcessKeyInput();

private:
	ButtonSet* menuButtons;
	FMOD::Sound* bgm;
};