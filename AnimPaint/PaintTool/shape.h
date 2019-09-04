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


#ifndef __SHAPE_H__
#define __SHAPE_H__

//	Library Includes
#include <windows.h>
#include <windowsx.h>

class IShape
{
public:
	IShape();
	virtual ~IShape(){}

	virtual void Draw(HDC _hdc) = 0;

	void SetStartX(int _iStartX);
	void SetEndX(int _iEndX);
	void SetStartY(int _iStartX);
	void SetEndY(int _iStartX);
	void DoThing(bool _DoIt, int _DoNum);
	void SetOnion(bool _onion);
	void SetShapeNum(int _Num);
	void SetVisible(bool _isVisible);

protected:
	int m_iStartX;
	int m_iEndX;
	int m_iStartY;
	int m_iEndY;
	int m_shapeNum; //The order of the shape in the list
	bool m_DoIt_1;
	bool m_DoIt_2;
	bool m_DoIt_3;
	bool m_visible; //If the shape will be drawn
	bool m_onion; //If it should be drawn as onion
};

#endif