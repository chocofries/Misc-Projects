#include "shape.h"

IShape::IShape()
{
	m_DoIt_1 = false;
	m_DoIt_2 = false;
	m_DoIt_3 = false;
	m_visible = true;
}

void IShape::SetStartX(int _iStartX)
{
	if (this != nullptr)
	{
		m_iStartX = _iStartX;
	}
}

void IShape::SetEndX(int _iEndX)
{
	if (this != nullptr)
	{
		m_iEndX = _iEndX;
	}
}

void IShape::SetStartY(int _iStartY)
{
	if (this != nullptr)
	{
		m_iStartY = _iStartY;
	}
}

void IShape::SetEndY(int _iEndY)
{
	if (this != nullptr)
	{
		m_iEndY = _iEndY;
	}
}

void IShape::DoThing(bool _DoIt, int _DoNum)
{
	if (this != nullptr)
	{
		switch (_DoNum)
		{
		case 1:
			m_DoIt_1 = _DoIt;
			break;
		case 2:
			m_DoIt_2 = _DoIt;
			break;
		case 3:
			m_DoIt_3 = _DoIt;
			break;
		}
	}
}

void IShape::SetOnion(bool _onion)
{
	if (this != nullptr)
	{
		m_onion = _onion;
	}
}

void IShape::SetShapeNum(int _Num)
{
	if (this != nullptr)
	{
		m_shapeNum = _Num;
	}
}

void IShape::SetVisible(bool _isVisible)
{
	if (this != nullptr)
	{
		m_visible = _isVisible;
	}
}
