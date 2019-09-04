#pragma once

#ifndef __GAME_H__
#define __GAME_H__
#include "grid.h"

class Game
{
public:
	Game();
	~Game();
	void Swapper(int* const _pX, int* const _pY);
};

void InputNumArray();
void RandomRange(int* _Num, int _MinR, int _MaxR); //Randomizes a number within a range
void BombCoord(Grid& _Grid);

#endif // !__GAME_H__
