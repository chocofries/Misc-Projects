#pragma once

#ifndef __PIXELART_H__
#define __PIXELART_H__

void DrawBlock(int _X, int _Y, int sizeX, int sizeY, int _R, int _G, int _B);
void DrawGrid(int _GridSize, int _X, int _Y, int _R, int _G, int _B);
void DrawFromOneZero(char _MyDraw[], int _Width, int _Height, int _PixSize, int _X, int _Y, int _R, int _G, int _B); //Draws pixels based on 1's or 0's
void DrawAlphabet(int _Letter, int _AlphaSize, int _X, int _Y, int _R, int _G, int _B);
void DrawNumber(int _Number, int _NumberSize, int _X, int _Y, int _R, int _G, int _B);
void DrawShipPart(int _Type, int _Orient, int _X, int _Y, int _R, int _G, int _B); //Draws bow, stern, or body of ship, with orientation
void DrawHit(int _Type, int _X, int _Y, int _R, int _G, int _B, int _Xoff);


#endif // !__PIXELART_H__
