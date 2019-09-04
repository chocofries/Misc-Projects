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


#ifndef __ELLIPSE_H__
#define __ELLIPSE_H__

//	Library Includes
#include <windows.h>
#include <windowsx.h>

#include "shape.h"

class CEllipse : public IShape
{
public:
	CEllipse(COLORREF _penColor, COLORREF _brushColor, int _penStyle, int _brushStyle, int _X, int _Y, int _width);
	CEllipse();
	virtual ~CEllipse();

	virtual void Draw(HDC _hdc);
	void SetColor(COLORREF _newColor);

private:
	int m_iPenStyle;
	int m_iWidth;
	int m_iFill;
	int m_iBrushStyle;
	COLORREF m_iPenColor;
	COLORREF m_iFillColor;
};

#endif