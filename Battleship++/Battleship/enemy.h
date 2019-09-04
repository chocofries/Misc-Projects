#pragma once

#ifndef __ENEMY_H__
#define __ENEMY_H__
#include <string>
#include "ship.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void EnemyPlaceShip(Grid& _Grid, Ship& _Ship, int _Seg, std::string _Name);
	void EnemyBomb(Grid& _Grid, bool& _ShipSunk);
	int GetTotalShots();

private:
	//Remembering the previous attack
	bool prevHit; //if the previous attack was a hit
	bool shipTarget; //if there is a ship currently targetted
	int prevX; //prev shot's x
	int prevY; //prev shot's y
	int prevO; //prev shot's orient
	int firstX; //X pos of the first hit of a ship
	int firstY; //X pos of the first hit of a ship
	int totalShots; //The total number of shots taken so far
	std::string targetName; //Name of the current targetted ship
};

#endif // !__ENEMY_H__
