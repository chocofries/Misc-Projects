#include <iostream>
#include <string>
#include <cstring>
#include <math.h>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <list>

#define _WIN32_WINNT 0x0500
#include <Windows.h>

#include "pixelart.h"
#include "ship.h"
#include "grid.h"
#include "enemy.h"
#include "game.h"

int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 800, 600, TRUE);
	Sleep(30);
	GotoXY(2, 25);
	DrawGrid(10, 32, 32, 100, 150, 200);
	DrawGrid(10, 320, 32, 100, 200, 150);

	//Setting Player Grid and Ships
	
	Grid playerGrid;

	Ship carrier;
	Ship battleship;
	Ship destroyer;
	Ship submarine;
	Ship patrol;

	ClearLine();
	std::string pInput = "NoAnswer";

	GotoXY(0,33);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << " ----- Battleship++ ----- John (Zheng Yu) Bu ----- November 2017 -----";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	while (pInput == "NoAnswer")
	{ 
		ClearLine();
		std::cout << " Quick start? (Automatic ship placement): ";
		getline(std::cin, pInput);
		std::transform(pInput.begin(), pInput.end(), pInput.begin(), ::tolower);
		if (pInput == "yes" || pInput == "y")
		{
			AutoPlaceShip(playerGrid, carrier, 5, "Aircraft Carrier");
			AutoPlaceShip(playerGrid, battleship, 4, "Battleship");
			AutoPlaceShip(playerGrid, destroyer, 3, "Destroyer");
			AutoPlaceShip(playerGrid, submarine, 3, "Submarine");
			AutoPlaceShip(playerGrid, patrol, 2, "Patrol Ship");
		}
		else if(pInput == "no" || pInput == "n")
		{ 
			PlaceShip(playerGrid, carrier, 5, "Aircraft Carrier");
			PlaceShip(playerGrid, battleship, 4, "Battleship");
			PlaceShip(playerGrid, destroyer, 3, "Destroyer");
			PlaceShip(playerGrid, submarine, 3, "Submarine");
			PlaceShip(playerGrid, patrol, 2, "Patrol Ship");
		}
		else
		{
			pInput = "NoAnswer";
			ClearLine();
		}
	}
	//

	//Setting Enemy Grid and Ships
	Grid enemyGrid;
	Enemy eBot;

	Ship eCarrier;
	Ship eBattleship;
	Ship eDestroyer;
	Ship eSubmarine;
	Ship ePatrol;

	eBot.EnemyPlaceShip(enemyGrid, eCarrier, 5, "Aircraft Carrier");
	eBot.EnemyPlaceShip(enemyGrid, eBattleship, 4, "Battleship");
	eBot.EnemyPlaceShip(enemyGrid, eDestroyer, 3, "Destroyer");
	eBot.EnemyPlaceShip(enemyGrid, eSubmarine, 3, "Submarine");
	eBot.EnemyPlaceShip(enemyGrid, ePatrol, 2, "Patrol Ship");


	//Game Turns Initialize
	int looper = 1; //If the game turns are looping
	bool shipSunk = 0; //To determine for the AI if one of the Player's ships has been sunk

	int pShipsSunk = 0; //To determine how many of the player's ships are sunk 
	int eShipsSunk = 0; //To determine how many of the enemy's ships are sunk

	std::string status0 = "           | Carrier | Battleship | Destroyer | Submarine | Patrol |";
	std::string status1 = " Player:   |  LIVE   |    LIVE    |   LIVE    |   LIVE    |  LIVE  |";
	std::string status2 = " Computer: |  LIVE   |    LIVE    |   LIVE    |   LIVE    |  LIVE  |";

	GotoXY(0, 27);
	std::cout << status0 << std::endl;
	std::cout << status1 << std::endl;
	std::cout << status2 << std::endl;

	//Taking a shot
	//---Choose coordinate of enemy grid
	while (looper == 1)
	{
		
		BombCoord(enemyGrid); //Player Turn
		ClearLine();

		//Checking if any enemy ships were sunk
		if (eCarrier.GetHealth() > 0)
		{ 
			eCarrier.CheckShipHealth(enemyGrid, "Computer");
			if (eCarrier.GetHealth() == 0)
			{
				eCarrier.SetStatus("SUNK");
				eShipsSunk += 1;
			}
		}
		if (eBattleship.GetHealth() > 0)
		{
			eBattleship.CheckShipHealth(enemyGrid, "Computer");
			if (eBattleship.GetHealth() == 0)
			{
				eBattleship.SetStatus("SUNK");
				eShipsSunk += 1;
			}
		}
		if (eDestroyer.GetHealth() > 0)
		{
			eDestroyer.CheckShipHealth(enemyGrid, "Computer");
			if (eDestroyer.GetHealth() == 0)
			{
				eDestroyer.SetStatus("SUNK");
				eShipsSunk += 1;
			}
		}
		if (eSubmarine.GetHealth() > 0)
		{
			eSubmarine.CheckShipHealth(enemyGrid, "Computer");
			if (eSubmarine.GetHealth() == 0)
			{
				eSubmarine.SetStatus("SUNK");
				eShipsSunk += 1;
			}
		}
		if (ePatrol.GetHealth() > 0)
		{
			ePatrol.CheckShipHealth(enemyGrid, "Computer");
			if (ePatrol.GetHealth() == 0)
			{
				ePatrol.SetStatus("SUNK");
				eShipsSunk += 1;
			}
		}

		status2 = " Computer: |  " + eCarrier.GetStatus() + "   |    " + eBattleship.GetStatus() + "    |   " + eDestroyer.GetStatus() + "    |   " + eSubmarine.GetStatus() + "    |  " + ePatrol.GetStatus() + "  |";

		GotoXY(0, 27);
		std::cout << status0 << std::endl;
		std::cout << status1 << std::endl;
		std::cout << status2 << std::endl;

		//Breaking out of the loop if the player has won
		if (eShipsSunk >= 5)
		{
			looper = 0;
			ClearLine();
			std::cout << " The Player has won! Wow you must be so proud!";
			break;
		}

		eBot.EnemyBomb(playerGrid, shipSunk); //Enemy Turn

		//Checking if any player ships were sunk
		if (carrier.GetHealth() > 0)
		{
			carrier.CheckShipHealth(playerGrid, "Player");
			if (carrier.GetHealth() == 0)
			{
				carrier.SetStatus("SUNK");
				shipSunk = 1;
				pShipsSunk += 1;
			}
		}
		if (battleship.GetHealth() > 0)
		{
			battleship.CheckShipHealth(playerGrid, "Player");
			if (battleship.GetHealth() == 0)
			{
				battleship.SetStatus("SUNK");
				shipSunk = 1;
				pShipsSunk += 1;
			}
		}
		if (destroyer.GetHealth() > 0)
		{
			destroyer.CheckShipHealth(playerGrid, "Player");
			if (destroyer.GetHealth() == 0)
			{
				destroyer.SetStatus("SUNK");
				shipSunk = 1;
				pShipsSunk += 1;
			}
		}
		if (submarine.GetHealth() > 0)
		{
			submarine.CheckShipHealth(playerGrid,"Player");
			if (submarine.GetHealth() == 0)
			{
				submarine.SetStatus("SUNK");
				shipSunk = 1;
				pShipsSunk += 1;
			}
		}
		if (patrol.GetHealth() > 0)
		{
			patrol.CheckShipHealth(playerGrid, "Player");
			if (patrol.GetHealth() == 0)
			{
				patrol.SetStatus("SUNK");
				shipSunk = 1;
				pShipsSunk += 1;
			}
		}

		status1 = " Player:   |  " + carrier.GetStatus() + "   |    " + battleship.GetStatus() + "    |   " + destroyer.GetStatus() + "    |   " + submarine.GetStatus() + "    |  " + patrol.GetStatus() + "  |";
		
		GotoXY(0,27);
		std::cout << status0 << std::endl;
		std::cout << status1 << std::endl;
		std::cout << status2 << std::endl << std::endl;
		std::cout << " Turns so far: "<< eBot.GetTotalShots() << std::endl;

		//Breaking out of the loop if the computer has won
		if (pShipsSunk >= 5)
		{
			looper = 0;
			ClearLine();
			std::cout << " The Computer has won! Get good!";
			break;
		}
	}

	int iTemp;
	std::cin >> iTemp;

	return(0);
}