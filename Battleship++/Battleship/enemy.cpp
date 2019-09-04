#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
//#include <mmsystem.h>

#include "enemy.h"
#include "ship.h"
#include "grid.h"
#include "pixelart.h"
#include "game.h"

Enemy::Enemy() //Constructor
{
	shipTarget = 0; //If there is a ship being targetted
	prevHit = 0;
	prevX = 0;
	prevY = 0;
	prevO = 1;
	firstX = 0;
	firstY = 0;
	totalShots = 0;
}

Enemy::~Enemy()
{
	//Destructor
}

int Enemy::GetTotalShots()
{
	return(totalShots);
}

void Enemy::EnemyPlaceShip(Grid& _Grid, Ship& _Ship, int _Seg, std::string _Name)
{
	srand((unsigned int)time(0));

	int eX;
	int eY;
	int eO;
	int eSeg;
	int xMin = 0;
	int xMax = 0;
	int yMin = 0;
	int yMax = 0;
	bool canPlace;
	canPlace = 0;

	_Ship.SetName(_Name);

	eSeg = _Seg;

	while (canPlace == 0)
	{
		eO = (rand() % 4) + 1;

		switch (eO)
		{
		case 1: //Right --->
			xMin = eSeg - 1;
			xMax = 0;
			yMin = 0;
			yMax = 0;
			break;
		case 2: //Left <---
			xMin = 0;
			xMax = -(eSeg - 2);
			yMin = 0;
			yMax = 0;
			break;
		case 3: //Down v
			xMin = 0;
			xMax = 0;
			yMin = eSeg - 1;
			yMax = 0;
			break;
		case 4: //Up
			xMin = 0;
			xMax = 0;
			yMin = 0;
			yMax = -(eSeg - 2);
			break;
		}

		eX = (rand() % (9+xMax-xMin))+xMin;
		eY = (rand() % (9+yMax-yMin))+yMin;
		canPlace = _Grid.SpaceForShip(eX, eY, eSeg, eO);
	}


	//Sets the ship into the grid
	if (eO == 1) //Right
	{
		for (int sg = eX; sg > (eX - eSeg); --sg)
		{
			_Grid.SetShipGrid(sg, eY, 1);
		}
	}
	if (eO == 2) //Left
	{
		for (int sg = eX; sg < (eX + eSeg); ++sg)
		{
			_Grid.SetShipGrid(sg, eY, 1);
		}
	}
	if (eO == 3) //Down
	{
		for (int sg = eY; sg >(eY - eSeg); --sg)
		{
			_Grid.SetShipGrid(eX, sg, 1);
		}
	}
	if (eO == 4) //Up
	{
		for (int sg = eY; sg < (eY + eSeg); ++sg)
		{
			_Grid.SetShipGrid(eX, sg, 1);
		}
	}

	_Ship.SetOrient(eO);
	_Ship.SetPosition(eX, eY);
	_Ship.SetSegments(eSeg);

	//_Ship.DrawShip(eX + 12, eY, 200, 100, 100);

	ClearLine();
	std::cout << std::endl;
	//_Grid.PrintShipGrid();
}

void Enemy::EnemyBomb(Grid& _Grid, bool& _ShipSunk)
{
	srand((unsigned int)time(0)); //Seed the RNG

	bool canBomb = 0;
	int bX;
	int bY;
	int bO; //Orient to bomb, 1-4, Left, Right, Up, Down
	int tries = 0; //How many tries so far determining the orientation
	int aiTest = 1; //0 = Testing the ai, 1 = normal mode
	int randSpeech = 0;
	
	RandomRange(&randSpeech, 0, 4);

	ClearLine();

	switch (randSpeech)
	{ 
	case 0:
		std::cout << " Time to destroy you...";
		break;
	case 1:
		std::cout << " Finally, you sure took your time...";
		break;
	case 2:
		std::cout << " This one better hit...";
		break;
	case 3:
		std::cout << " You will be sorry...";
		break;
	}

	Sleep(1000* aiTest);

	if (_ShipSunk == 1)
	{
		shipTarget = 0;
		_ShipSunk = 0;
	}
	
	if (shipTarget == 1) //if a ship is currently targetted------------------------------------------------------
	{
		if (prevHit == 1) //If previous attack was a hit 
		{ 
			bO = prevO; //Setting orient as previous orient
		}
		else
		{
			bO = rand() % 4 + 1;
		}

		while (canBomb == 0)
		{
			ClearLine();
			std::cout << " Let's see...";
			++tries;

			if (bO == 1) //if orient is going Left ################## LEFT #######################
			{
				if (tries >= 10)
				{
					canBomb = 0; //Give up for now
					shipTarget = 0;
					break;
				}

				if (prevX-1 >= 0) //If can bomb left of the previous position
				{
					if (_Grid.GetHitGrid(prevX-1,prevY) == 0)
					{
						ClearLine();
						std::cout << " I'll hit left of the previous hit...";
						Sleep(1000 * aiTest);

						bX = prevX - 1;
						bY = prevY;
						prevO = bO;
						canBomb = 1;
						break;
					}
					else
					{
						bO = 2; //Switch orient to right
					}
				}
				else //Reset the orient of the attack
				{
					bO = 2; //Switch orient to right
				}
			} //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END LEFT ^^^^^^^^^^^^^^^^^^


			if (bO == 2) //if orient is going Right ################## RIGHT #######################
			{
				if (tries >= 10)
				{
					canBomb = 0; //Give up for now
					shipTarget = 0;
					break;
				}

				if (prevX + 1 <= 9) //If can bomb right of the previous position
				{
					if (_Grid.GetHitGrid(prevX + 1, prevY) == 0)
					{
						ClearLine();
						std::cout << " I'll hit right of the previous hit...";
						Sleep(1000 * aiTest);

						bX = prevX + 1;
						bY = prevY;
						prevO = bO;
						canBomb = 1;
						break;
					}
					else
					{
						bO = 3; //Switch orient to up
					}
				}
				else //Reset the orient of the attack
				{
					bO = 3; //Switch orient to up
				}
			} //----------------------####################### END RIGHT ###########################


			if (bO == 3) //if orient is going Up ################## UP #######################
			{
				if (tries >= 10)
				{
					canBomb = 0; //Give up for now
					shipTarget = 0;
					break;
				}

				if (prevY - 1 >= 0) //If can bomb up of the previous position
				{
					if (_Grid.GetHitGrid(prevX, prevY - 1) == 0)
					{
						ClearLine();
						std::cout << " I'll hit above the previous hit...";
						Sleep(1000 * aiTest);

						bX = prevX;
						bY = prevY - 1;
						prevO = bO;
						canBomb = 1;
						break;
					}
					else
					{
						bO = 4; //Switch orient to down
					}
				}
				else //Reset the orient of the attack
				{
					bO = 4; //Switch orient to down
				}
			} //----------------------####################### END UP ###########################


			if (bO == 4) //if orient is going Down ################## DOWN #######################
			{
				if (tries >= 10)
				{
					canBomb = 0; //Give up for now
					shipTarget = 0;
					break;
				}

				if (prevY + 1 <= 9) //If can bomb down of the previous position
				{
					if (_Grid.GetHitGrid(prevX, prevY + 1) == 0)
					{
						ClearLine();
						std::cout << " I'll hit under the previous hit...";
						Sleep(1000*aiTest);

						bX = prevX;
						bY = prevY + 1;
						prevO = bO;
						canBomb = 1;
						break;
					}
					else
					{
						bO = 1; //Switch orient to left
					}
				}
				else //Reset the orient of the attack
				{
					bO = 1; //Switch orient to left

				}
			} //----------------------####################### END DOWN ###########################

			if (tries = 5)
			{
				prevX = firstX;
				prevY = firstY;
			}

			if (tries >= 10)
			{ 
				canBomb = 0; //Give up for now
				shipTarget = 0;
				break;
			}

		} //End of while loop
	}
	
	if (shipTarget == 0)//If no ship is currently targetted ------------------------------------------------------------------
	{
		bO = rand() % 4 + 1; //Randomizing the orient (Not used for this attack)
		while (canBomb == 0)
		{
			//Get random coord

			if (totalShots < 30) //If total shots taken are less than 30
			{ 
				bX = rand() % 10;
				if (bX % 2 == 0) //if bX is even
				{ 
					bY = ((rand() % 5) * 2) + 1; //bY will be even
				}
				else //if bX is odd
				{
					bY = ((rand() % 5) * 2); //bY will be odd
				}
			}
			if (totalShots >= 30 && totalShots < 50)
			{
				bX = rand() % 10;
				if (bX % 2 == 0) //if bX is even
				{
					bY = ((rand() % 5) * 2); //bY will be odd
				}
				else //if bX is odd
				{
					bY = ((rand() % 5) * 2) + 1; //bY will be even
				}
			}
			if (totalShots >= 50)
			{
				bX = rand() % 10; //Bomb all spaces
				bY = rand() % 10;
			}

			if (_Grid.GetHitGrid(bX, bY) == 0) //Check if coord has been bombed
			{
				canBomb = 1;
				break;
			}
			else
			{
				canBomb = 0;
			}
		}
	}
	
	//Bomb the position
	if (canBomb == 1)
	{
		ClearLine();
		_Grid.SetHitGrid(bX,bY,1);
		if (_Grid.GetShipGrid(bX, bY) == 1) //If it is a hit
		{
			prevHit = 1;
			if (shipTarget == 0)
			{
				firstX = bX;
				firstY = bY;
				shipTarget = 1;
			}
			prevX = bX;
			prevY = bY;
			prevO = bO;
			DrawHit(1, bX * 24, (bY * 24) + 24, 150, 200, 250, 32);
			ClearLine();
			std::cout << " Hah! What an obvious place to put that!";
			Sleep(1000 * aiTest);
		}
		else //If it is a miss
		{
			prevHit = 0;
			DrawHit(0, bX * 24, (bY * 24) + 24, 150, 200, 250, 32);
			ClearLine();
			std::cout << " Wow, you must be lucky...";
			Sleep(1000 * aiTest);
		}
		totalShots += 1;
	}
}