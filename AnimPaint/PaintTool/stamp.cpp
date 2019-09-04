#include "stamp.h"

CStamp::CStamp()
{

}
CStamp::CStamp(HINSTANCE hInstance, HWND _hwnd, wchar_t* filename, int _startX, int _startY, int _endX, int _endY, bool _isForLoad)
{
	this->m_hBitMap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	this->m_iStartX = _startX;
	this->m_iStartY = _startY;
	this->m_iEndX = _endX;
	this->m_iEndY = _endY;
	this->m_hwnd = _hwnd;
	this->sX = m_iStartX;
	this->sY = m_iStartY;
	this->m_isForLoad = _isForLoad;
}
CStamp::~CStamp()
{
	DeleteObject(m_hBitMap);
}

void CStamp::Draw(HDC _hdc)
{
	if (m_visible == true && m_onion == false)
	{
		HDC windowDC = _hdc;
		HDC bitDC = CreateCompatibleDC(windowDC);

		GetObject(m_hBitMap, sizeof(BITMAP), &m_bitmapStructure);
		HBITMAP oldBM = static_cast<HBITMAP>(SelectObject(bitDC, m_hBitMap));
		int width =  m_bitmapStructure.bmWidth;
		int height = m_bitmapStructure.bmHeight;
		
		RECT _rect;
		GetClientRect(m_hwnd, &_rect);

		if (m_isForLoad == true)
		{
			BitBlt(windowDC,0,0, width, height, bitDC, 0,0, SRCCOPY);
		}
		else
		{
			StretchBlt(windowDC, sX, sY, m_iEndX - sX, m_iEndY - sY, bitDC, 0, 0, width, height, SRCCOPY);
		}

		SelectObject(bitDC, oldBM);
		DeleteDC(bitDC);
		ReleaseDC(m_hwnd, windowDC);
	}
}
void CStamp::SetStartX(int _iX)
{
	this->m_iStartX = _iX;
}
void CStamp::SetStartY(int _iY)
{
	this->m_iStartY = _iY;
}

void CStamp::SetFileName(wchar_t _filename)
{
	wchar_t fName = _filename;
	this->m_hBitMap = (HBITMAP)LoadImage(NULL, &fName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}