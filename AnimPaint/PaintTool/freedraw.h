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

#ifndef __FREEDRAW_H__
#define __FREEDRAW_H__

//	Library Includes
#include <windows.h>
#include <windowsx.h>
#include <vector>

#include "shape.h"

class CFreeDraw : public IShape
{
public:
	CFreeDraw(int _iStyle, int _iWidth, COLORREF _newColor, int _iStartX, int _iStartY);
	CFreeDraw();
	virtual ~CFreeDraw();

	virtual void Draw(HDC _hdc);
	void SetWidth(int _iNewWidth);
	void AddLine(int _iStartX, int _iStartY);

private:

	int m_iStyle;
	int m_iWidth;
	int pointDist;
	bool nextPoint;
	COLORREF m_Color;
	std::vector<IShape*> m_lines;
	IShape* currentLine;
};

#endif