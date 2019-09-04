#pragma once

#ifndef __SHIP_H__
#define __SHIP_H__
#include "grid.h"

class Ship
{
public:
	Ship();
	Ship(const int _X, const int _Y, const int _Seg, const int _Or); //Constructor
	~Ship(); //Destructor
	
	int GetSegments() const;
	void SetSegments(int _Segments);
	void DrawShip(int _X, int _Y, int _R, int _G, int _B);
	void SetPosition(int _bX, int _bY);
	void SetOrient(int _Orient);
	int GetHealth() const;
	void SetHealth(int _Health);

	std::string GetStatus() const;
	void SetStatus(std::string _Status);

	std::string GetName() const;
	void SetName(std::string _Name);
	void CheckShipHealth(Grid& _Grid, std::string _PlayerName); //Checks if there is a hit on the ship, and if a ship is destroyed, prints result

private:
	std::string name;
	std::string status;
	int segments; //This is the length of the ship.
	int bowX;
	int bowY;
	int sternX;
	int sternY;
	int shipOrient; //Orientation of the ship, 0 = not set, 1 = right, 2 = left, 3 = down, 4 = up.
	int health;

};

void PlaceShip(Grid& _Grid, Ship& _Ship, int _SegNum, std::string _Name);
void AutoPlaceShip(Grid& _Grid, Ship& _Ship, int _Seg, std::string _Name);

#endif //!__SHIP__H_
