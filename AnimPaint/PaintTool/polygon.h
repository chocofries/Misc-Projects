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

#ifndef __POLYGON_H__
#define __POLYGON_H__

//	Library Includes
#include <windows.h>
#include <windowsx.h>

#include "shape.h"

class CPolygon : public IShape
{
public:
	CPolygon(int _iHatchStyle, COLORREF _FillColor, int _iPenStyle, COLORREF _PenColor, int _iPenWidth);
	CPolygon();
	virtual ~CPolygon();

	virtual void Draw(HDC _hdc);
	void MovePoint(int _mx, int _my);

private:
	COLORREF m_iFillColor;
	COLORREF m_iPenColor;
	POINT* m_pPointList;
	POINT m_Poly[1024];
	bool m_init;
	int m_currentPoint;
	int m_nPoints;
	int m_iHatchStyle;
	int m_iFillStyle;
	int m_iPenStyle;
	int m_iPenWidth;
};

#endif