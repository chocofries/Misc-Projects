#include <iostream>
#include <string>
#include <cctype>
#include <cstring>

#define _WIN32_WINNT 0x0500
#include <Windows.h>

#include "pixelart.h"

void DrawBlock(int _X, int _Y, int sizeX, int sizeY, int _R, int _G, int _B)
{
	//Get a console handle
	HWND myconsole = GetConsoleWindow();
	//Get a handle to device context
	HDC mydc = GetDC(myconsole);

	//Choose any color
	COLORREF COLOR = RGB(_R, _G, _B);

	//Draw Block
	for (int gy = 0; gy < sizeY; ++gy)
	{
		for (int gx = 0; gx < sizeX; ++gx)
		{
			SetPixel(mydc, _X + (gx), _Y + (gy), COLOR);
		}
	}
}

void DrawGrid(int _GridSize, int _X, int _Y, int _R, int _G, int _B)
{
	//Draw Background
	for (int gy = 0; gy < _GridSize; ++gy)
	{
		for (int gx = 0; gx < _GridSize; ++gx)
		{
			DrawBlock(_X + (24 * gx), _Y + (24 * gy), 24, 24, (int)(_R * 0.5), (int)(_G * 0.5), (int)(_B * 0.5));
		}
	}

	//Draw Lines
	for (int gl = 1; gl <= _GridSize + 1; ++gl)
	{
		DrawBlock((_X-24) + (24 * gl), (_Y - 24) + 24, 1, 24 * _GridSize + 1, _R, _G, _B);
		DrawBlock((_X - 24) + 24, (_Y - 24) + (24 * gl), 24 * _GridSize + 1, 1, _R, _G, _B);
	}
	
	//Draw Alphabet/Numbers
	for (int ga = 1; ga <= _GridSize; ++ga)
	{
		DrawAlphabet(ga, 2, (_X-32) + 10+(ga*24), (_Y-32) + 12, 255, 255, 255);
		DrawNumber(ga, 2, (_X-32) + 12, (_Y-32) + 10 + (ga * 24), 255, 255, 255);
	}
}

void DrawFromOneZero(char _MyDraw[], int _Width, int _Height, int _PixSize, int _X, int _Y, int _R, int _G, int _B)
{
	int pixNum = 0;
	char c;

	for (int dv = 0; dv < _Height; ++dv)
	{
		for (int dh = 0; dh < _Width; ++dh)
		{
			c = _MyDraw[pixNum];
			if(isalnum(c))
			{
				DrawBlock(_X +(dh*_PixSize), _Y+(dv*_PixSize), _PixSize, _PixSize, _R, _G, _B);
			}
			pixNum += 1;
		}
	}
	pixNum = 0;
}

void DrawAlphabet(int _Letter, int _AlphaSize, int _X, int _Y, int _R, int _G, int _B)
{
	if (_Letter == 1) //A
	{
		DrawFromOneZero("-AAA-A---AA---AAAAAAA---AA---A", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 2) //B
	{
		DrawFromOneZero("BBBB-B---BBBBB-B---BB---BBBBB-", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 3) //C
	{
		DrawFromOneZero("-CCC-C---CC----C----C---C-CCC-", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 4) //D
	{
		DrawFromOneZero("DDDD-D---DD---DD---DD---DDDDD-", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 5) //E
	{
		DrawFromOneZero("EEEEEE----EEEEEE----E----EEEEE", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 6) //F
	{
		DrawFromOneZero("FFFFFF----FFFF-F----F----F----", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 7) //G
	{
		DrawFromOneZero("-GGGGG----G-GGGG---GG---G-GGGG", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 8) //H
	{
		DrawFromOneZero("H---HH---HHHHHHH---HH---HH---H", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 9) //I
	{
		DrawFromOneZero("-III---I----I----I----I---III-", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 10) //J
	{
		DrawFromOneZero("--JJJ---J----J----J-J--J--JJ--", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 11) //K
	{
		DrawFromOneZero("K---KK--K-KKK--K--K-K---KK---K", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 12) //L
	{
		DrawFromOneZero("L----L----L----L----L----LLLLL", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 13) //M
	{
		DrawFromOneZero("M---MMM-MMM-M-MM---MM---MM---M", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 14) //N
	{
		DrawFromOneZero("N---NNN--NN-N-NN--NNN---NN---N", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 15) //O
	{
		DrawFromOneZero("-OOO-O---OO---OO---OO---O-OOO-", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 16) //P
	{
		DrawFromOneZero("PPPP-P---PP---PPPPP-P----P----", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 17) //Q
	{
		DrawFromOneZero("-QQQ-Q---QQ---QQ-Q-QQ--Q--QQ-Q", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 18) //R
	{
		DrawFromOneZero("RRRR-R---RRRRR-R---RR---RR---R", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 19) //S
	{
		DrawFromOneZero("-SSS-S-----SSS-----SS---S-SSS-", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 20) //T
	{
		DrawFromOneZero("TTTTT--T----T----T----T----T--", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 21) //U
	{
		DrawFromOneZero("U---UU---UU---UU---UU---U-UUU-", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 22) //V
	{
		DrawFromOneZero("V---VV---VV---VV---V-V-V---V--", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 23) //W
	{
		DrawFromOneZero("W---WW---WW-W-WW-W-WWW-WWW---W", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 24) //X
	{
		DrawFromOneZero("X---X-X-X---X---X-X-X---XX---X", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 25) //Y
	{
		DrawFromOneZero("Y---YY---Y-Y-Y---Y----Y----Y--", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}
	if (_Letter == 26) //Z
	{
		DrawFromOneZero("ZZZZZ---Z---Z---Z---Z----ZZZZZ", 5, 6, _AlphaSize, _X, _Y, _R, _G, _B);
	}

};

void DrawHit(int _Type, int _X, int _Y, int _R, int _G, int _B, int _Xoff)
{
	if (_Type == 0) //Miss
	{ 
		/*
		for (float fAngle = 0.0f; fAngle < (2.0f * 3.14596f); fAngle += (2.0f * 3.14596f) / 24)
		{
			float fX = 1.0f * cos(fAngle);
			float fY = 1.0f * sin(fAngle);
			DrawBlock(fX + (_X + 12 + _Xoff), fY + (_Y + 20), 2, 2, _R, _G, _B);
		}
		*/
		for (float fAngle = 0.0f; fAngle < (2.0f * 3.14596f); fAngle += (2.0f * 3.14596f) / 16)
		{
			float fX = 5.0f * cos(fAngle);
			float fY = 5.0f * sin(fAngle);
			DrawBlock(fX + (_X + 12 + _Xoff), fY + (_Y + 20), 2, 2, (int)(_R*0.8f), (int)(_G*0.8f), (int)(_B*0.8f));
		}
		/*
		for (float fAngle = 0.0f; fAngle < (2.0f * 3.14596f); fAngle += (2.0f * 3.14596f) / 24)
		{
			float fX = 9.0f * cos(fAngle);
			float fY = 9.0f * sin(fAngle);
			DrawBlock(fX+(int)(_X + 12 + _Xoff), fY+(int)(_Y + 20), 2, 2, (int)(_R*0.6), (int)(_G*0.6), (int)(_B*0.6));
		}*/
	}
	else //if it is a hit
	{
		/*
		for (float fAngle = 0.0f; fAngle < (2.0f * 3.14596f); fAngle += (2.0f * 3.14596f) / 16)
		{
			float fX = 1.0f * cos(fAngle);
			float fY = 1.0f * sin(fAngle);
			DrawBlock(fX + (_X + 12 + _Xoff), fY + (_Y + 20), 3, 3, 250, 250, 0);
		}
		
		for (float fAngle = 0.0f; fAngle < (2.0f * 3.14596f); fAngle += (2.0f * 3.14596f) / 24)
		{
			float fX = 5.0f * cos(fAngle);
			float fY = 5.0f * sin(fAngle);
			DrawBlock(fX + (_X + 12 + _Xoff), fY + (_Y + 20), 3, 3, 250, 150, 0);
		}*/
		for (float fAngle = 0.0f; fAngle < (2.0f * 3.14596f); fAngle += (2.0f * 3.14596f) / 24)
		{
			float fX = 9.0f * cos(fAngle);
			float fY = 9.0f * sin(fAngle);
			DrawBlock(fX + (int)(_X + 12 + _Xoff), fY + (int)(_Y + 20), 3, 3, 200, 50, 0);
		}
	}
}

void DrawNumber(int _Number, int _NumberSize, int _X, int _Y, int _R, int _G, int _B)
{
	if (_Number == 0 || _Number == 10) //0
	{
		DrawFromOneZero("-000-0---000--00-0-00--00-000-", 5, 6, _NumberSize, _X, _Y, _R, _G, _B);
	}
	if (_Number == 1) //1
	{
		DrawFromOneZero("--1---11----1----1----1---111-", 5, 6, _NumberSize, _X, _Y, _R, _G, _B);
	}
	if (_Number == 2) //2
	{
		DrawFromOneZero("-222-2---2---2---2---2---22222", 5, 6, _NumberSize, _X, _Y, _R, _G, _B);
	}
	if (_Number == 3) //3
	{
		DrawFromOneZero("33333---3--333-----33---3-333-", 5, 6, _NumberSize, _X, _Y, _R, _G, _B);
	}
	if (_Number == 4) //4
	{
		DrawFromOneZero("--44--4-4-4--4-44444---4----4-", 5, 6, _NumberSize, _X, _Y, _R, _G, _B);
	}
	if (_Number == 5) //5
	{
		DrawFromOneZero("555555----5555-----55---5-555-", 5, 6, _NumberSize, _X, _Y, _R, _G, _B);
	}
	if (_Number == 6) //6
	{
		DrawFromOneZero("-666-6----6666-6---66---6-666-", 5, 6, _NumberSize, _X, _Y, _R, _G, _B);
	}
	if (_Number == 7) //7
	{
		DrawFromOneZero("77777----7---7---7----7----7--", 5, 6, _NumberSize, _X, _Y, _R, _G, _B);
	}
	if (_Number == 8) //8
	{
		DrawFromOneZero("-888-8---8-888-8---88---8-888-", 5, 6, _NumberSize, _X, _Y, _R, _G, _B);
	}
	if (_Number == 9) //9
	{
		DrawFromOneZero("-999-9---9-9999----9---9--99--", 5, 6, _NumberSize, _X, _Y, _R, _G, _B);
	}
}

void DrawShipPart(int _Type, int _Orient, int _X, int _Y, int _R, int _G, int _B)
{
	int pX = _X;
	int pY = _Y;

	//std::cout << "(" << pX << "," << pY << ")";

	if (_Type == 0) //Bow of ship
	{
		if (_Orient == 1) //Right --->
		{
			DrawFromOneZero("--------------------------------000000----------000000000-------000000000000----0000000000000---00000000000000--000000000000000-000000000000000-00000000000000--0000000000000---000000000000----000000000-------000000------------------------------------------", 16, 16, 1, pX, pY + 4, (int)(_R * 0.75), (int)(_G * 0.75), (int)(_B * 0.75)); //Fill
			DrawFromOneZero("--------------------------------000000----------000000000-------------000000-------------0000--------------000--------------000-------------000------------000-----------0000--------0000000----000000000-------000000------------------------------------------", 16, 16, 1, pX, pY + 4, _R, _G, _B); //Outline
		}
		if (_Orient == 2) //Left <---
		{
			DrawFromOneZero("------------------------------------------000000-------000000000----000000000000---0000000000000--00000000000000-000000000000000-000000000000000--00000000000000---0000000000000----000000000000-------000000000----------000000--------------------------------", 16, 16, 1, pX + 8, pY + 4, (int)(_R * 0.75), (int)(_G * 0.75), (int)(_B * 0.75)); //Fill
			DrawFromOneZero("------------------------------------------000000-------000000000----0000000--------0000-----------000------------000-------------000--------------000--------------0000-------------000000-------------000000000----------000000--------------------------------", 16, 16, 1, pX + 8, pY + 4, _R, _G, _B); //Outline
		}
		if (_Orient == 3) //Down v
		{
			DrawFromOneZero("--000000000000----000000000000----000000000000----000000000000----000000000000----000000000000-----0000000000------0000000000------0000000000-------00000000--------00000000--------00000000---------000000-----------0000-------------00-----------------------", 16, 16, 1, pX + 4, pY, (int)(_R * 0.75), (int)(_G * 0.75), (int)(_B * 0.75)); //Fill
			DrawFromOneZero("--00--------00----00--------00----00--------00----00--------00----00--------00----00--------00-----00------00------00------00------00------00-------00----00--------00----00--------000--000---------000000-----------0000-------------00-----------------------", 16, 16, 1, pX + 4, pY, _R, _G, _B); //Outline
		}
		if (_Orient == 4) //Up ^
		{
			DrawFromOneZero("-----------------------00-------------0000-----------000000---------00000000--------00000000--------00000000-------0000000000------0000000000------0000000000-----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000--", 16, 16, 1, pX + 4, pY + 8, (int)(_R * 0.75), (int)(_G * 0.75), (int)(_B * 0.75)); //Fill
			DrawFromOneZero("-----------------------00-------------0000-----------000000---------000--000--------00----00--------00----00-------00------00------00------00------00------00-----00--------00----00--------00----00--------00----00--------00----00--------00----00--------00--", 16, 16, 1, pX + 4, pY + 8, _R, _G, _B); //Outline
		}
		
	}
	if (_Type == 1) //Body of ship
	{
		if (_Orient == 1 || _Orient == 2) //If horizontal
		{
			DrawBlock(_X, _Y + 6, 24, 12, (int)(_R * 0.75), (int)(_G * 0.75), (int)(_B * 0.75)); //Fill
			DrawBlock(_X, _Y + 6, 24, 2, _R, _G, _B); //1st Line 
			DrawBlock(_X, _Y + 16, 24, 2, _R, _G, _B); //2nd Line
		}
		if (_Orient == 3 || _Orient == 4) //If vertical
		{
			DrawBlock(_X +6, _Y, 12, 24, (int)(_R * 0.75), (int)(_G * 0.75), (int)(_B * 0.75)); //Fill
			DrawBlock(_X +6, _Y, 2, 24, _R, _G, _B); //1st Line
			DrawBlock(_X + 16, _Y, 2, 24, _R, _G, _B); //2nd Line
		}
	}
	if (_Type == 2) //Stern of ship
	{
		if (_Orient == 1) //Right --->
		{
			DrawFromOneZero("------------------------------------000000000000---0000000000000--00000000000000--00000000000000-000000000000000-000000000000000-000000000000000-000000000000000--00000000000000--00000000000000---0000000000000----000000000000--------------------------------", 16, 16, 1, _X + 8, _Y + 4, (int)(_R * 0.75), (int)(_G * 0.75), (int)(_B * 0.75)); //Fill
			DrawFromOneZero("------------------------------------000000000000---0000000000000--000-------------00-------------000-------------00--------------00--------------000--------------00--------------000--------------0000000000000----000000000000--------------------------------", 16, 16, 1, _X + 8, _Y + 4, _R, _G, _B); //Outline
		}
		if (_Orient == 2) //Left <---
		{
			DrawFromOneZero("--------------------------------000000000000----0000000000000---00000000000000--00000000000000--000000000000000-000000000000000-000000000000000-000000000000000-00000000000000--00000000000000--0000000000000---000000000000------------------------------------", 16, 16, 1, _X, _Y + 4, (int)(_R * 0.75), (int)(_G * 0.75), (int)(_B * 0.75)); //Fill
			DrawFromOneZero("--------------------------------000000000000----0000000000000--------------000--------------00--------------000--------------00--------------00-------------000-------------00-------------000--0000000000000---000000000000------------------------------------", 16, 16, 1, _X, _Y + 4, _R, _G, _B); //Outline
		}
		if (_Orient == 3) //Down v
		{
			DrawFromOneZero("----------------------0000----------00000000-------0000000000-----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000--", 16, 16, 1, _X + 4, _Y + 8, (int)(_R * 0.75), (int)(_G * 0.75), (int)(_B * 0.75)); //Fill
			DrawFromOneZero("----------------------0000----------00000000-------0000--0000-----000------000----00--------00----00--------00----00--------00----00--------00----00--------00----00--------00----00--------00----00--------00----00--------00----00--------00----00--------00--", 16, 16, 1, _X + 4, _Y + 8, _R, _G, _B); //Outline
		}
		if (_Orient == 4) //Up ^
		{
			DrawFromOneZero("--000000000000----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000----000000000000-----0000000000-------00000000----------0000----------------------", 16, 16, 1, _X + 4, _Y, (int)(_R * 0.75), (int)(_G * 0.75), (int)(_B * 0.75)); //Fill
			DrawFromOneZero("--00--------00----00--------00----00--------00----00--------00----00--------00----00--------00----00--------00----00--------00----00--------00----00--------00----00--------00----000------000-----0000--0000-------00000000----------0000----------------------", 16, 16, 1, _X + 4, _Y, _R, _G, _B); //Outline
		}
	}
}