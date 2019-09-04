#include <iostream>
#include <string>
#include <Windows.h>

#include "ship.h"
#include "grid.h"

Grid::Grid()
{
	//Constructor
	SetEntireShipGrid(0);
	SetEntireHitGrid(0);
}

Grid::~Grid()
{
	//Destructor
}

bool Grid::GetShipGrid( int _X, int _Y) const
{
	bool rValue = shipGrid[_X][_Y];
	return (rValue);
}

void Grid::SetShipGrid( int _X, int _Y, bool _Value)
{
	shipGrid[_X][_Y] = _Value;
}

bool Grid::GetHitGrid(int _X, int _Y) const
{
	bool rValue = hitGrid[_X][_Y];
	return (rValue);
}

void Grid::SetHitGrid(int _X, int _Y, bool _Value)
{
	hitGrid[_X][_Y] = _Value;
}

void Grid::SetEntireShipGrid(bool _Value)
{
	for (int sv = 0; sv < 10; ++sv)
	{
		for (int sh = 0; sh < 10; ++sh)
		{
			shipGrid[sh][sv] = _Value;
		}
	}
}

void Grid::SetEntireHitGrid(bool _Value)
{
	for (int sv = 0; sv < 10; ++sv)
	{
		for (int sh = 0; sh < 10; ++sh)
		{
			hitGrid[sh][sv] = _Value;
		}
	}
}

bool Grid::SpaceForShip(int _X, int _Y, int _Seg, int _Or) //--------------------------------------------------------
{
	bool isFree = 0;

	if (_Or == 1) //Right
	{
		for (int sg = _X; sg > (_X - _Seg); --sg)
		{
			if (GetShipGrid(sg, _Y) == 1)
			{
				isFree = 0;
				break;
			}
			else
			{
				isFree = 1;
			}
		}
	}
	if (_Or == 2) //Left
	{
		for (int sg = _X; sg < (_X + _Seg); ++sg)
		{
			if (GetShipGrid(sg, _Y) == 1)
			{
				isFree = 0;
				break;
			}
			else
			{
				isFree = 1;
			}
		}
	}
	if (_Or == 3) //Down
	{
		for (int sg = _Y; sg >(_Y - _Seg); --sg)
		{
			if (GetShipGrid(_X, sg) == 1)
			{
				isFree = 0;
				break;
			}
			else
			{
				isFree = 1;
			}
		}
	}
	if (_Or == 4) //Up
	{
		for (int sg = _Y; sg < (_Y + _Seg); ++sg)
		{
			if (GetShipGrid(_X, sg) == 1)
			{
				isFree = 0;
				break;
			}
			else
			{
				isFree = 1;
			}
		}
	}

	return (isFree);
}

void Grid::PrintShipGrid()
{
	std::cout << std::endl;
	for (int pv = 0; pv < 10; ++pv)
	{
		for (int ph = 0; ph < 10; ++ph)
		{
			if (GetShipGrid(ph, pv) == 1)
			{
				std::cout << " #";
			}
			else
			{
				std::cout << " -";
			}
		}
		std::cout << std::endl;
	}
}

void Grid::PrintHitGrid()
{
	for (int pv = 0; pv < 10; ++pv)
	{
		for (int ph = 0; ph < 10; ++ph)
		{
			if (GetHitGrid(ph, pv) == 1)
			{
				std::cout << " 1";
			}
			else
			{
				std::cout << " 0";
			}
		}
		std::cout << std::endl;
	}
}

void ClearLine()
{
	GotoXY(0, 25);  
	std::cout << "                                                                                         ";
	GotoXY(0, 25);
}

void GotoXY(int _X, int _Y)
{
	COORD point;
	point.X = _X;
	point.Y = _Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}