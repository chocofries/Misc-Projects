#include <iostream>
#include <string>
#include <Windows.h>
#include <time.h>
#include <algorithm>

#include "pixelart.h"
#include "ship.h"
#include "grid.h"

Ship::Ship() //Constructor
{
	SetPosition(0, 0);
	SetSegments(0);
	SetOrient(0);
	SetHealth(1);
	SetStatus("LIVE");
}

Ship::Ship(int _X, int _Y, int _Seg, int _Or) //Constructor
{
	SetPosition(_X, _Y);
	SetSegments(_Seg);
	SetOrient(_Or);
	SetHealth(1);
	SetStatus("LIVE");
}

Ship::~Ship() //Destructor
{
	//Destructor
}

int Ship::GetSegments() const
{
	return (segments);
}

void Ship::SetSegments(int _Segments)
{
	if ((_Segments >= 2) && (_Segments <= 5))
	{
		segments = _Segments;
	}
}

void Ship::SetPosition(int _bX, int _bY)
{
	if ((_bX >= 0) && (_bX < 10))
	{
		if ((_bY >= 0) && (_bY < 10))
		{
			bowX = _bX;
			bowY = _bY;
		}
	}
}

void Ship::SetOrient(int _Orient)
{
	if ((_Orient >= 1) && (_Orient <= 4))
	{
		shipOrient = _Orient;
	}
}

std::string Ship::GetName() const
{
	return (name);
}

void Ship::SetName(std::string _Name)
{
	name = _Name;
}

int Ship::GetHealth() const
{
	return (health);
}

void Ship::SetHealth(int _Health)
{
	if (_Health > 0)
	{ 
		health = _Health;
	}
}

std::string Ship::GetStatus() const
{
	return (status);
}

void Ship::SetStatus(std::string _Status)
{
	status = _Status;
}

void Ship::DrawShip(int _X, int _Y, int _R, int _G, int _B)
{
	int dX = 32+(_X*24);
	int dY = 32+(_Y*24);

	if (shipOrient == 1) //Right
	{
		DrawShipPart(0, shipOrient, dX, dY, _R, _G, _B);
		for (int so = 1; so < (segments - 1); ++so)
		{
			DrawShipPart(1, shipOrient, dX - (24*so), dY, _R, _G, _B);
		}
		DrawShipPart(2, shipOrient, dX - (24 * (segments - 1)), dY, _R, _G, _B);
	}

	if (shipOrient == 2) //Left
	{
		DrawShipPart(0, shipOrient, dX, dY, _R, _G, _B);
		for (int so = 1; so < (segments - 1); ++so)
		{
			DrawShipPart(1, shipOrient, dX + (24 * so), dY, _R, _G, _B);
		}
		DrawShipPart(2, shipOrient, dX + (24 * (segments - 1)), dY, _R, _G, _B);
	}
		
	if (shipOrient == 3) //Down
	{
		DrawShipPart(0, shipOrient, dX, dY, _R, _G, _B);
		for (int so = 1; so < (segments - 1); ++so)
		{
			DrawShipPart(1, shipOrient, dX, dY - (24 * so), _R, _G, _B);
		}
		DrawShipPart(2, shipOrient, dX, dY - (24 * (segments-1)), _R, _G, _B);
	}

	if (shipOrient == 4) //Up
	{
		DrawShipPart(0, shipOrient, dX, dY, _R, _G, _B);
		for (int so = 1; so < (segments - 1); ++so)
		{
			DrawShipPart(1, shipOrient, dX, dY + (24 * so), _R, _G, _B);
		}
		DrawShipPart(2, shipOrient, dX, dY + (24 * (segments - 1)), _R, _G, _B);
	}
}

void Ship::CheckShipHealth(Grid& _Grid, std::string _PlayerName)
{	
	int dmg = 0;
	if (shipOrient == 1) //Right
	{
		for (int sg = bowX; sg > (bowX - segments); --sg)
		{
			if (_Grid.GetHitGrid(sg, bowY) == 1)
			{
				if (dmg < segments)
				{
					dmg += 1;
				}
			}
		}
	}
	if (shipOrient == 2) //Left
	{
		for (int sg = bowX; sg < (bowX + segments); ++sg)
		{
			if (_Grid.GetHitGrid(sg, bowY) == 1)
			{				
				if (dmg < segments)
				{
					dmg += 1;
				}
			}
		}
	}
	if (shipOrient == 3) //Down
	{
		for (int sg = bowY; sg > (bowY - segments); --sg)
		{
			if (_Grid.GetHitGrid(bowX, sg) == 1)
			{
				if (dmg < segments)
				{
					dmg += 1;
				}
			}
		}
	}
	if (shipOrient == 4) //Up
	{
		for (int sg = bowY; sg < (bowY + segments); ++sg)
		{
			if (_Grid.GetHitGrid(bowX, sg) == 1)
			{
				if (dmg < segments)
				{
					dmg += 1;
				}
			}
		}
	}
	if (dmg >= segments)
	{
		ClearLine();
		std::cout << " " << _PlayerName << "'s " << name << " destroyed!";
		Sleep(2000);
		health = 0;
	}
}

void PlaceShip(Grid& _Grid, Ship& _Ship, int _SegNum, std::string _Name)
{
	std::string sInput = "NoAnswer";
	std::string sName;
	int xInput = 100;
	int yInput = 100;
	int oInput = 100;
	int oCheck = 100;
	int xMin = 0;
	int xMax = 0;
	int yMin = 0;
	int yMax = 0;
	int segNum = _SegNum; //Number of segments
	GotoXY(0, 23);

	bool canPlace = 0;
	_Ship.SetName(_Name);
	sName = _Ship.GetName();
	
	while (canPlace == 0)
	{
		//Orientation
		while (((oInput < 1) || (oInput > 4)) || (sInput == "NoAnswer"))
		{
			ClearLine();
			std::cout << " Choose orientation of your " << sName << " (Right, Left, Down, Up): "; //0 = not set, 1 = right, 2 = left, 3 = down, 4 = up
			getline(std::cin, sInput);
			ClearLine();
			std::transform(sInput.begin(), sInput.end(), sInput.begin(), ::tolower);
			if (sInput == "right" || sInput == "r")
			{
				oInput = 1;
			}
			if (sInput == "left" || sInput == "l")
			{
				oInput = 2;
			}
			if (sInput == "down" || sInput == "d")
			{
				oInput = 3;
			}
			if (sInput == "up" || sInput == "u")
			{
				oInput = 4;
			}
		}

		switch (oInput)
		{
		case 1:
			xMin = segNum - 1;
			xMax = 0;
			yMin = 0;
			yMax = 0;
			break;
		case 2:
			xMin = 0;
			xMax = -(segNum - 1);
			yMin = 0;
			yMax = 0;
			break;
		case 3:
			xMin = 0;
			xMax = 0;
			yMin = segNum - 1;
			yMax = 0;
			break;
		case 4:
			xMin = 0;
			xMax = 0;
			yMin = 0;
			yMax = -(segNum - 1);
			break;
		}
	
		//X Position
		while ((xInput < 0 + xMin) || (xInput > 9 + xMax))
		{
			ClearLine();
			std::cout << " Choose horizontal coordinate of your " << sName << ": ";
			getline(std::cin, sInput);
			ClearLine();
			std::transform(sInput.begin(), sInput.end(), sInput.begin(), ::tolower);
			if (sInput == "a")
			{
				xInput = 0;
			}
			if (sInput == "b")
			{
				xInput = 1;
			}
			if (sInput == "c")
			{
				xInput = 2;
			}
			if (sInput == "d")
			{
				xInput = 3;
			}
			if (sInput == "e")
			{
				xInput = 4;
			}
			if (sInput == "f")
			{
				xInput = 5;
			}
			if (sInput == "g")
			{
				xInput = 6;
			}
			if (sInput == "h")
			{
				xInput = 7;
			}
			if (sInput == "i")
			{
				xInput = 8;
			}
			if (sInput == "j")
			{
				xInput = 9;
			}
		}

		//Y Position
		while ((yInput < 0 + yMin) || (yInput > 9 + yMax))
		{
			ClearLine();
			std::cout << " Choose vertical coordinate of your " << sName << ": ";
			getline(std::cin, sInput);
			ClearLine();
			yInput = atoi(sInput.c_str())-1;
			if (yInput == -1)
			{
				yInput = 9;
			}
		}

		canPlace = _Grid.SpaceForShip(xInput, yInput, segNum, oInput);
		if (canPlace == 0)
		{
			ClearLine();
			std::cout << " Position is not free...";
			xInput = 100;
			yInput = 100;
			oInput = 100;
			oCheck = 100;
			Sleep(500);
			ClearLine();
		}
	}

	if (oInput == 1) //Right
	{
		for (int sg = xInput; sg > (xInput - segNum); --sg)
		{
			_Grid.SetShipGrid(sg, yInput, 1);
		}
	}
	if (oInput == 2) //Left
	{
		for (int sg = xInput; sg < (xInput + segNum); ++sg)
		{
			_Grid.SetShipGrid(sg, yInput, 1);
		}
	}
	if (oInput == 3) //Down
	{
		for (int sg = yInput; sg > (yInput - segNum); --sg)
		{
			_Grid.SetShipGrid(xInput, sg, 1);
		}
	}
	if (oInput == 4) //Up
	{
		for (int sg = yInput; sg < (yInput + segNum); ++sg)
		{
			_Grid.SetShipGrid(xInput, sg, 1);
		}
	}

	_Ship.SetOrient(oInput);
	_Ship.SetPosition(xInput, yInput);
	_Ship.SetSegments(segNum);
	
	_Ship.DrawShip( xInput, yInput,200,200,200);

	GotoXY(0, 25);
	//_Grid.PrintShipGrid();
}

void AutoPlaceShip(Grid& _Grid, Ship& _Ship, int _Seg, std::string _Name)
{
	srand((unsigned int)time(0));

	int aX;
	int aY;
	int aO;
	int aSeg;
	int xMin = 0;
	int xMax = 0;
	int yMin = 0;
	int yMax = 0;
	bool canPlace;
	canPlace = 0;

	_Ship.SetName(_Name);

	aSeg = _Seg;

	while (canPlace == 0)
	{
		aO = (rand() % 4) + 1;

		switch (aO)
		{
		case 1: //Right --->
			xMin = aSeg - 1;
			xMax = 0;
			yMin = 0;
			yMax = 0;
			break;
		case 2: //Left <---
			xMin = 0;
			xMax = -(aSeg - 2);
			yMin = 0;
			yMax = 0;
			break;
		case 3: //Down v
			xMin = 0;
			xMax = 0;
			yMin = aSeg - 1;
			yMax = 0;
			break;
		case 4: //Up
			xMin = 0;
			xMax = 0;
			yMin = 0;
			yMax = -(aSeg - 2);
			break;
		}

		aX = (rand() % (9 + xMax - xMin)) + xMin;
		aY = (rand() % (9 + yMax - yMin)) + yMin;
		canPlace = _Grid.SpaceForShip(aX, aY, aSeg, aO);
	}


	//Sets the ship into the grid
	if (aO == 1) //Right
	{
		for (int sg = aX; sg > (aX - aSeg); --sg)
		{
			_Grid.SetShipGrid(sg, aY, 1);
		}
	}
	if (aO == 2) //Left
	{
		for (int sg = aX; sg < (aX + aSeg); ++sg)
		{
			_Grid.SetShipGrid(sg, aY, 1);
		}
	}
	if (aO == 3) //Down
	{
		for (int sg = aY; sg >(aY - aSeg); --sg)
		{
			_Grid.SetShipGrid(aX, sg, 1);
		}
	}
	if (aO == 4) //Up
	{
		for (int sg = aY; sg < (aY + aSeg); ++sg)
		{
			_Grid.SetShipGrid(aX, sg, 1);
		}
	}

	_Ship.SetOrient(aO);
	_Ship.SetPosition(aX, aY);
	_Ship.SetSegments(aSeg);

	_Ship.DrawShip(aX, aY, 200, 200, 200);

	ClearLine();
	std::cout << std::endl;
	//_Grid.PrintShipGrid();
}