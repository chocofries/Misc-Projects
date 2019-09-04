#pragma once

#ifndef __GRID_H__
#define __GRID_H__

void ClearLine();
void GotoXY(int _X, int _Y);

class Grid
{
public:
	Grid(); //Constructor
	~Grid(); //Destructor
	
	bool GetShipGrid(int _X, int _Y) const;
	void SetShipGrid(int _X, int _Y, bool _Value);
	bool GetHitGrid(int _X, int _Y) const;
	void SetHitGrid(int _X, int _Y, bool _Value);

	bool SpaceForShip(int _X, int _Y, int _Seg, int _Or);

	void PrintShipGrid();
	void PrintHitGrid();

	void SetEntireShipGrid(bool _Value); //Sets the entire ship grid
	void SetEntireHitGrid(bool _Value); //Sets the entire hit grid

private:
	bool shipGrid[10][10] = { 0 };
	bool hitGrid[10][10] = { 0 };

};

#endif //!__GRID_H__