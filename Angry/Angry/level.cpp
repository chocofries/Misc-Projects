#include "level.h"
#include "sprite.h"
#include "cubemap.h"
#include "model.h"

Level::Level()
{
	isInit = false;
}

Level::~Level()
{
	//OVERWRITE IN CHILD CLASS
}

void Level::Initialise(Game* _myGame, ShaderLoader* _shaderloader, AssetLoader* _textureloader, InputManager* _inputManager, AudioManager* _audioManager)
{
	//OVERWRITE IN CHILD CLASS
}

void Level::Update()
{
	//OVERWRITE IN CHILD CLASS
}

void Level::Draw()
{
	//OVERWRITE IN CHILD CLASS
}

void Level::ProcessKeyInput()
{
	//OVERWRITE IN CHILD CLASS
}

std::vector<Texter*>* Level::GetVecTexts()
{
	return &vecTexts;
}

GLuint Level::GetVBO() const
{
	return levelVBO;
}

ShaderLoader * Level::GetShaderLoader() const
{
	return shaderLoader;
}

AssetLoader * Level::GetAssetLoader() const
{
	return assetLoader;
}

InputManager * Level::GetInputManager() const
{
	return inputManager;
}

PhysicsManager * Level::GetPhysicsManager() const
{
	return physicsManager;
}

AudioManager * Level::GetAudioManager() const
{
	return audioManager;
}

Camera * Level::GetCamera() const
{
	return levelCamera;
}

Clock * Level::GetClock() const
{
	return clock;
}

CubeMap * Level::GetSkyBox() const
{
	return skyBox;
}

bool Level::GetIsInit() const
{
	return isInit;
}

void Level::SetScreenMouseX(int _x)
{
	screenMouseX = _x;
}

void Level::SetScreenMouseY(int _y)
{
	screenMouseY = _y;
}
