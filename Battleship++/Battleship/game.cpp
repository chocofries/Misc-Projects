#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>
#include <time.h>

#include "game.h"
#include "grid.h"
#include "pixelart.h"

Game::Game()
{
	//Constructor
}

Game::~Game()
{
	//Destructor
}

void Game::Swapper(int* const pX, int* const pY)
{
	int temp = *pX;
	*pX = *pY;
	*pY = temp;
}

void InputNumArray()
{
	int num = 0;
	std::string nInput;
	std::cout << "Input size of the array: ";

	getline(std::cin, nInput);
	num = atoi(nInput.c_str());

	int* nArray = new int[num];

	for (int a = 0; a < sizeof(nArray); ++a)
	{
		std::cout << " " << a << " " ;
	}

	delete[] nArray;
}

void RandomRange(int* _Num, int _MinR, int _MaxR)
{
	srand((unsigned int)time(0)); //Seed the RNG

	*_Num = (rand() % _MaxR) + _MinR;
}

void BombCoord(Grid& _Grid)
{
	int iX = 100;
	int iY = 100;
	bool canBomb = 0;
	std::string cInput = "NoAnswer";
	ClearLine();

	while (canBomb == 0) //Getting Bomb-able Coordinates
	{
		while (iX < 0 || iX > 9) //Get X
		{
			ClearLine();
			std::cout << " Enter horizontal coordinate for bombing: ";
			getline(std::cin, cInput);
			std::transform(cInput.begin(), cInput.end(), cInput.begin(), ::tolower);
			
			if (cInput == "a")
			{
				iX = 0;
			}
			else if (cInput == "b")
			{
				iX = 1;
			}
			else if (cInput == "c")
			{
				iX = 2;
			}
			else if (cInput == "d")
			{
				iX = 3;
			}
			else if (cInput == "e")
			{
				iX = 4;
			}
			else if (cInput == "f")
			{
				iX = 5;
			}
			else if (cInput == "g")
			{
				iX = 6;
			}
			else if (cInput == "h")
			{
				iX = 7;
			}
			else if (cInput == "i")
			{
				iX = 8;
			}
			else if (cInput == "j")
			{
				iX = 9;
			}
			else
			{
				iX = 100;
			}
		

			while (iY < 0 || iY > 9) //Get Y
			{
				ClearLine();
				std::cout << " Enter vertical coordinate for bombing: ";
				getline(std::cin, cInput);
				iY = atoi(cInput.c_str())-1;
				if (iY == -1)
				{
					iY = 9;
				}
			}
		}

		//Check if can bomb (space was not bombed before)
		if (_Grid.GetHitGrid(iX, iY) == 0)
		{
			ClearLine();
			std::cout << " Bombs away!";
			canBomb = 1;
			Sleep(1500);
		}
		else
		{
			ClearLine();
			iX = 100;
			iY = 100;
			std::cout << " You already bombed here.";
			Sleep(500);
		}
	}

	//Bombing
	if (canBomb == 1)
	{
		_Grid.SetHitGrid(iX, iY, 1); //Setting the Hit Grid for the enemy grid

		if (_Grid.GetShipGrid(iX, iY) == 1) //if the bomb is a hit
		{
			DrawHit(1, iX * 24, (iY * 24)+24, 150, 250, 200, 320);
			ClearLine();
			std::cout << " It's a hit!";
			Sleep(1000);
		}
		else //if the bomb is a miss
		{
			DrawHit(0, iX * 24, (iY * 24)+24, 150, 250, 200, 320);
			ClearLine();
			std::cout << " It's a miss...";
			Sleep(1000);
		}
	}
}