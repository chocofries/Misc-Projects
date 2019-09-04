#include "rectangle.h"


CRectangle::CRectangle(int _iHatchStyle, COLORREF _FillColor, int _iPenStyle, COLORREF _PenColor, int _iPenWidth, int _X, int _Y)
{
	this->m_iHatchStyle = _iHatchStyle;
	this->m_Color = _FillColor;
	this->m_iPenStyle = _iPenStyle;
	this->m_iPenWidth = _iPenWidth;
	this->m_iPenColor = _PenColor;
	this->m_iStartX = _X;
	this->m_iStartY = _Y;
	this->m_iEndX = _X;
	this->m_iEndY = _Y;
}

CRectangle::CRectangle()
{

}

CRectangle::~CRectangle()
{

}

void CRectangle::Draw(HDC _hdc)
{
	if (m_visible == true)
	{
		HPEN peint_pen;
		if (m_onion == false)
		{
			peint_pen = CreatePen(m_iPenStyle, m_iPenWidth, m_iPenColor);
		}
		else
		{
			peint_pen = CreatePen(PS_DOT, 1, m_iPenColor);
		}
		HPEN old_pen = static_cast<HPEN>(SelectObject(_hdc, peint_pen));

		HBRUSH peint_brush;
		if (m_onion == false)
		{
			if (m_iHatchStyle == -1)
			{
				peint_brush = CreateSolidBrush(m_Color);
			}
			else
			{
				peint_brush = CreateHatchBrush(m_iHatchStyle, m_Color);
			}
		}
		else
		{
			peint_brush = CreateHatchBrush(HS_BDIAGONAL, m_Color);
		}
		HBRUSH old_brush = static_cast<HBRUSH>(SelectObject(_hdc, peint_brush));


		RECT tempRect = { m_iStartX, m_iStartY, m_iEndX, m_iEndY };

		FillRect(_hdc, &tempRect, peint_brush);
		Rectangle(_hdc, m_iStartX, m_iStartY, m_iEndX, m_iEndY);

		SelectObject(_hdc, old_pen); // Restore old pen.
		DeleteObject(peint_pen); // Delete the new pen.
		SelectObject(_hdc, old_brush);
		DeleteObject(peint_brush);
	}
}

void CRectangle::SetBrushStyle(EBRUSHSTYLE _brushStyle)
{

}

void CRectangle::SetFillColor(COLORREF _newColor)
{

}

void CRectangle::SetPenStyle(int _iPenStyle)
{

}

void CRectangle::SetPenColor(COLORREF _newColor)
{

}

void CRectangle::SetHatchStyle(int _iHatchStyle)
{

}