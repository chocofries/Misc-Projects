#include <math.h>
#include "freedraw.h"
#include "line.h"

CFreeDraw::CFreeDraw(int _iStyle, int _iWidth, COLORREF _newColor, int _iStartX, int _iStartY)
{
	this->m_iStyle = _iStyle;
	this->m_iWidth = _iWidth;
	this->m_Color = _newColor;
	this->m_iStartX = _iStartX;
	this->m_iStartY = _iStartY;
	this->pointDist = 0;
	nextPoint = false;
	currentLine = nullptr;
	AddLine(m_iStartX, m_iStartY);
}

CFreeDraw::CFreeDraw()
{

}

CFreeDraw::~CFreeDraw()
{
	while (!m_lines.empty())
	{
		IShape* deleteLine = m_lines.back();
		m_lines.pop_back();
		delete deleteLine;
	}
}

void CFreeDraw::Draw(HDC _hdc)
{
	if (m_DoIt_1 == true)
	{
		AddLine(m_iStartX, m_iStartY);
		currentLine->SetStartX(m_iStartX);
		currentLine->SetStartY(m_iStartY);
		m_DoIt_1 = false;
	}
	if (m_visible == true)
	{
		currentLine->SetEndX(m_iEndX);
		currentLine->SetEndY(m_iEndY);
		for (IShape * shape : m_lines) //Draws all the shapes in the shape's line vector
		{
			shape->SetOnion(m_onion);
			shape->Draw(_hdc);
		}
	}
}

void CFreeDraw::SetWidth(int _iNewWidth)
{
	this->m_iWidth = _iNewWidth;
}

void CFreeDraw::AddLine(int _iStartX, int _iStartY)
{
	currentLine = new CLine(m_iStyle, m_iWidth, m_Color, _iStartX, _iStartY);
	currentLine->SetStartX(_iStartX);
	currentLine->SetStartY(_iStartY);
	currentLine->SetEndX(m_iEndX);
	currentLine->SetEndY(m_iEndY);
	m_lines.push_back(currentLine);
}