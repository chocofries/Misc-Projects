#include "polygon.h"

CPolygon::CPolygon(int _iHatchStyle, COLORREF _FillColor, int _iPenStyle, COLORREF _PenColor, int _iPenWidth)
{
	this->m_iHatchStyle = _iHatchStyle;
	this->m_iFillColor = _FillColor;
	this->m_iPenStyle = _iPenStyle;
	this->m_iPenWidth = _iPenWidth;
	this->m_iPenColor = _PenColor;

	m_iStartX = -1;
	m_iStartY = -1;
	m_iEndX = -1;
	m_iEndY = -1;
	m_init = false;

	m_nPoints = sizeof(m_Poly) / (sizeof(m_Poly[0]));
	m_currentPoint = 0;
}

CPolygon::CPolygon()
{

}

CPolygon::~CPolygon()
{

}

void CPolygon::Draw(HDC _hdc)
{
	if (m_visible == true)
	{
		if (m_init == false) //If not yet initialized
		{
			if (m_iEndX > -1 && m_iEndY > -1)
			{
				for (int li = 0; li < m_nPoints; li++)
				{
					m_Poly[li] = { m_iEndX, m_iEndY };
				}
				m_init = true;
			}
		}

		int mx = m_iEndX;
		int my = m_iEndY;

		if (m_DoIt_1 == true) //If changing a point, then moving to new position
		{
			if (m_currentPoint < m_nPoints - 1)
			{
				m_currentPoint += 1;
				m_Poly[m_currentPoint] = { mx , my };

			}
			else
			{
				m_currentPoint = 0;
				m_Poly[0] = { mx , my };
			}
			m_DoIt_1 = false;
		}

		if (m_DoIt_2 == true) //If moving a single point to new position
		{
			m_Poly[m_currentPoint] = { mx , my };
			m_DoIt_2 = false;
		}

		HPEN peint_pen;
		if (m_onion == false) //If it is normal drawing
		{
			peint_pen = CreatePen(m_iPenStyle, m_iPenWidth, m_iPenColor);
		}
		else //If it is being drawn as an onion skin
		{
			peint_pen = CreatePen(PS_DOT, 1, m_iPenColor);
		}
		HPEN old_pen = static_cast<HPEN>(SelectObject(_hdc, peint_pen));

		HBRUSH peint_brush;
		if (m_onion == false) //If it is normal drawing
		{
			if (m_iHatchStyle == -1)
			{
				peint_brush = CreateSolidBrush(m_iFillColor);
			}
			else
			{
				peint_brush = CreateHatchBrush(m_iHatchStyle, m_iFillColor);
			}
		}
		else //If it is being drawn as an onion skin
		{
			peint_brush = CreateHatchBrush(HS_BDIAGONAL, m_iFillColor);
		}
		HBRUSH old_brush = static_cast<HBRUSH>(SelectObject(_hdc, peint_brush));

		Polygon(_hdc, m_Poly, m_nPoints);

		SelectObject(_hdc, old_brush);
		SelectObject(_hdc, old_pen); // Restore old pen.
		DeleteObject(peint_brush);
		DeleteObject(peint_pen); // Delete the new pen.
	}
}

void CPolygon::MovePoint(int _mx, int _my)
{
	if (m_currentPoint < m_nPoints-1)
	{
		m_Poly[m_currentPoint] = { _mx , _my};
	}
	else
	{
		m_Poly[0] = { _mx , _my };
		m_currentPoint = 0;
	}
}
