#include "ellipse.h"

CEllipse::CEllipse(COLORREF _penColor, COLORREF _brushColor, int _penStyle, int _brushStyle, int _X, int _Y, int _width)
{
	this->m_iPenColor = _penColor;
	this->m_iFillColor = _brushColor;
	this->m_iPenStyle = _penStyle;
	this->m_iBrushStyle = _brushStyle;
	this->m_iStartX = _X;
	this->m_iStartY = _Y;
	this->m_iEndX = _X;
	this->m_iEndY = _Y;
	this->m_iWidth = _width;
}

CEllipse::CEllipse()
{

}

CEllipse::~CEllipse()
{

}

void CEllipse::Draw(HDC _hdc)
{
	if (m_visible == true)
	{
		HPEN peint_pen;

		if (m_onion == false)
		{
			peint_pen = CreatePen(m_iPenStyle, m_iWidth, m_iPenColor);
		}
		else
		{
			peint_pen = CreatePen(PS_DOT, 1, m_iPenColor);
		}
		HPEN old_pen = static_cast<HPEN>(SelectObject(_hdc, peint_pen));

		HBRUSH peint_brush;
		if (m_onion == false)
		{
			if (m_iBrushStyle == -1)
			{
				peint_brush = CreateSolidBrush(m_iFillColor);
			}
			else
			{
				peint_brush = CreateHatchBrush(m_iBrushStyle, m_iFillColor);
			}
		}
		else
		{
			peint_brush = CreateHatchBrush(HS_BDIAGONAL, m_iFillColor);
		}
		HBRUSH old_brush = static_cast<HBRUSH>(SelectObject(_hdc, peint_brush));

		Ellipse(_hdc, m_iStartX, m_iStartY, m_iEndX, m_iEndY);

		SelectObject(_hdc, old_brush);
		SelectObject(_hdc, old_pen); // Restore old pen.
		DeleteObject(peint_brush);
		DeleteObject(peint_pen); // Delete the new pen.
	}
}

void CEllipse::SetColor(COLORREF _newColor)
{

}