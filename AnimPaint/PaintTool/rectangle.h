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

#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

//	Library Includes
#include <windows.h>
#include <windowsx.h>
#include "shape.h"


enum EBRUSHSTYLE
{
	NOSTYLE = -1,
	SOLID,
	HATCH
};

class CRectangle : public IShape
{
public:
	CRectangle(int _iHatchStyle, COLORREF _FillColor, int _iPenStyle, COLORREF _PenColor,int _iPenWidth, int _X, int _Y);
	CRectangle();
	virtual ~CRectangle();

	virtual void Draw(HDC _hdc);
	void SetBrushStyle(EBRUSHSTYLE _brushStyle);
	void SetFillColor(COLORREF _newColor);
	void SetPenStyle (int _iPenStyle);
	void SetPenColor(COLORREF _newColor);
	void SetHatchStyle(int _iHatchStyle);

private:
	EBRUSHSTYLE m_iBrushStyle;
	int m_iHatchStyle;
	COLORREF m_iFillColor;
	int m_iPenStyle;
	int m_iPenColor;
	int m_iPenWidth;
	COLORREF m_Color;
};

#endif