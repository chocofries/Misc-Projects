#include "line.h"

CLine::CLine(int _iStyle, int _iWidth, COLORREF _newColor, int _iStartX, int _iStartY)
{
	this->m_iStyle = _iStyle;
	this->m_iWidth = _iWidth;
	this->m_Color = _newColor;
	this->m_iStartX = _iStartX;
	this->m_iStartY = _iStartY;
}

CLine::CLine()
{

}

CLine::~CLine()
{

}

void CLine::Draw(HDC _hdc)
{
	if (m_visible == true)
	{
		HPEN peint_pen;
		if (m_onion == false)
		{
			peint_pen = CreatePen(m_iStyle, m_iWidth, m_Color);
		}
		else
		{
			peint_pen = CreatePen(PS_DOT, 1, m_Color);
		}
		HPEN old_pen = static_cast<HPEN>(SelectObject(_hdc, peint_pen));

		MoveToEx(_hdc, m_iStartX, m_iStartY, NULL);
		LineTo(_hdc, m_iEndX, m_iEndY);

		SelectObject(_hdc, old_pen); // Restore old pen.
		DeleteObject(peint_pen); // Delete the new pen.
	}
}

void CLine::SetWidth(int _iNewWidth)
{

}