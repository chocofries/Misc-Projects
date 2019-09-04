/***********************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2018 Media Design School

File Name   :   AnimPaint
Description :   Painting & Animation Software
Author      :   John (Zheng Yu) Bu
Mail        :   zheng.yu5315@mediadesign.school.nz
********************/

#ifndef __STAMP_H__
#define __STAMP_H__

#include <Windows.h>

#include "shape.h"
class CStamp : public IShape
{
public:
	CStamp();
	CStamp(HINSTANCE hInstance, HWND _hwnd, wchar_t* filename, int _startX, int _startY, int _endX, int _endY, bool _isForLoad);
	virtual ~CStamp();

	virtual void Draw(HDC _hdc);
	void SetStartX(int _iX);
	void SetStartY(int _iY);
	void SetFileName(wchar_t _filename);

private:
	int sX;
	int sY;
	bool m_isForLoad; //If this stamp is used by the load function
	HBITMAP m_hBitMap;
	BITMAP m_bitmapStructure;
	HWND m_hwnd;
};

#endif