#include <atlstr.h>
#include <atlimage.h>
#include <string>
#include "canvas.h"
#include "shape.h"
#include "stamp.h"
#include "backBuffer.h"

CCanvas::CCanvas()
{
	penWidth = 1;
	penStyle = PS_SOLID;
	brushStyle = -1;
	penColour = BLACK_PEN;
	brushColour = RGB(200,200,200);
	showHUD = true;
	isSaving = false;
	currentFrame = new Frame();
	m_frames.push_back(currentFrame);
	timeCounter = 0;
	nowTime = clock();
	prevTime = nowTime;
	animIsPlaying = false;
	frameSpeed = 12;
	terminating = false;
	drawOnion = true;
}
CCanvas::~CCanvas()
{

}

bool CCanvas::Initialise(HWND _hwnd, int _iWidth, int _iHeight)
{
	this->hwnd = _hwnd;
	backBuffer.Initialise(hwnd, _iWidth, _iHeight);
	return false;
}

CBackBuffer* CCanvas::GetBackBuffer()
{
	return (m_pBackBuffer);
}

bool CCanvas::Draw(int mouseX, int mouseY)
{
	HDC hdc = GetDC(hwnd);
	hdc_b = backBuffer.GetBFDC();
	//Do drawing 
	backBuffer.Clear();
	if (terminating == false)
	{
		frameIndex = std::find(m_frames.begin(), m_frames.end(), currentFrame) - m_frames.begin();
		if (frameIndex >= 1)
		{
			onionSkin = m_frames.at(frameIndex-1);
		}
		else
		{
			onionSkin = currentFrame;
		}
	}
	else
	{
		frameIndex = 0;
	}

	nowTime = clock();
	timeCounter += (double)(nowTime - prevTime);
	prevTime = nowTime;

	if (animIsPlaying == true && isSaving == false)
	{
		if (timeCounter > (double)(CLOCKS_PER_SEC/ frameSpeed))
		{
			timeCounter -= (double)(CLOCKS_PER_SEC/ frameSpeed);
			NextFrame();
		}
	}
	else
	{
		timeCounter = 0;
	}

	if (terminating == false)
	{
		//Draw Onion Skin
		if (animIsPlaying == false && isSaving == false && drawOnion == true)
		{
			for (IShape * shape : onionSkin->GetShapeVector()) //Draws all the shapes in the current onion skin vector
			{
				shape->SetOnion(true);
				shape->Draw(hdc_b);
			}
		}

		for (IShape * shape : currentFrame->GetShapeVector()) //Draws all the shapes in the current frame's shape vector
		{
			shape->SetOnion(false);
			shape->Draw(hdc_b);
		}
	}

	if (penStyle != PS_SOLID)
	{
		penWidth = 1;
	}
	
	if (showHUD == true && isSaving == false)
	{
		TCHAR text[256];
		swprintf_s(text, 256, L"Mouse X: %d", mouseX);
		TextOut(hdc_b, 40, 30, text, wcslen(text));
		swprintf_s(text, 256, L"Mouse Y: %d", mouseY);
		TextOut(hdc_b, 40, 50, text, wcslen(text));
		swprintf_s(text, 256, L"Shapes: %d", currentFrame->GetShapeVector().size());
		TextOut(hdc_b, 40, 70, text, wcslen(text));
		swprintf_s(text, 256, L"Pen Width: %d", penWidth);
		TextOut(hdc_b, 40, 90, text, wcslen(text));
		swprintf_s(text, 256, L"Total Frames: %d", m_frames.size());
		TextOut(hdc_b, 40, 130, text, wcslen(text));
		swprintf_s(text, 256, L"Current Frame: %d", frameIndex+1);
		TextOut(hdc_b, 40, 150, text, wcslen(text));
		swprintf_s(text, 256, L"Animation FPS: %d", frameSpeed);
		TextOut(hdc_b, 40, 170, text, wcslen(text));
	}
	backBuffer.Present();

	ReleaseDC(hwnd, hdc);
	return false;
}

void CCanvas::Save(HWND _hwnd)
{
	animIsPlaying = false;
	isSaving = true;
	bool preHudState = showHUD;
	showHUD = false;
	OPENFILENAME ofn;			// common dialog box structure
	wchar_t wszFile[260];      // buffer for file name

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = _hwnd;
	ofn.lpstrFile = wszFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(wszFile);
	ofn.lpstrFilter = L".bmp\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	RECT rect = { 0 };

	HDC theDC = GetDC(_hwnd);

	GetWindowRect(_hwnd, &rect);
	ATL::CImage* image_ = new CImage();
	image_->Create((rect.right - rect.left) - 16, (rect.bottom - rect.top) - 8, 32);

	Draw(0,0);

	HDC device_context_handle = image_->GetDC();
	BitBlt(device_context_handle, 0, 0, rect.right, rect.bottom, hdc_b, 0, 0, SRCCOPY);

	if (GetSaveFileName(&ofn) == TRUE)
	{
		std::wstring ws = (ofn.lpstrFile);
		ws += std::wstring(L".bmp");

		image_->Save(ws.c_str(), Gdiplus::ImageFormatBMP);
		image_->ReleaseDC();

		delete image_;
	}

	ReleaseDC(_hwnd, theDC);
	isSaving = false;
	showHUD = preHudState;
}

void CCanvas::SaveAnimation(HWND _hwnd)
{
	animIsPlaying = false;
	isSaving = true;
	bool preHudState = showHUD;
	showHUD = false;
	OPENFILENAME ofn;			// common dialog box structure
	wchar_t wszFile[260];      // buffer for file name

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = _hwnd;
	ofn.lpstrFile = wszFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(wszFile);
	ofn.lpstrFilter = L".bmp\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	RECT rect = { 0 };
	HDC theDC = GetDC(_hwnd);
	int prevSpeed = frameSpeed;

	if (GetSaveFileName(&ofn) == TRUE)
	{
		currentFrame = m_frames.front();
		
		frameSpeed = 100;
		for (int fN = 0; fN < m_frames.size(); fN++)
		{
			GetWindowRect(_hwnd, &rect);
			ATL::CImage* image_ = new CImage();
			image_->Create((rect.right - rect.left)-16, (rect.bottom - rect.top)-8, 32);

			Draw(0, 0); //Draw the new frame

			HDC device_context_handle = image_->GetDC();
			BitBlt(device_context_handle, 0, 0, rect.right, rect.bottom, hdc_b, 0, 0, SRCCOPY); //Copy From the backBuffer

			std::wstring ws = (ofn.lpstrFile);

			ws += std::wstring(L"_");
			ws += std::to_wstring(fN+1);
			ws += std::wstring(L".bmp");

			image_->Save(ws.c_str(), Gdiplus::ImageFormatBMP);
			image_->ReleaseDC();
			delete image_;
			
			NextFrame();
		}
	}

	ReleaseDC(_hwnd, theDC);
	frameSpeed = prevSpeed;
	isSaving = false;
	showHUD = preHudState;
}

void CCanvas::Load(HWND _hwnd, IShape* _gShape, CCanvas* _gCanvas)
{
	if (isSaving == false)
	{
		animIsPlaying = false;
		OPENFILENAME ofn;			// common dialog box structure
		wchar_t wszFile[260];      // buffer for file name

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = _hwnd;
		ofn.lpstrFile = wszFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(wszFile);
		ofn.lpstrFilter = L"Bitmap File\0*.bmp\0All Files\0*\0\0";;
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST;

		// Display the Open dialog box. 
		if (GetOpenFileName(&ofn) == TRUE)
		{
			RECT _rect;
			GetClientRect(_hwnd, &_rect);

			_gShape = new CStamp(NULL, _hwnd, ofn.lpstrFile, 0, 0, _rect.right, _rect.bottom, true);
			UndoAll();
			AddShape(_gShape);
		}
	}
}

void CCanvas::AddShape(IShape* _shape) //Adds a shape to the shape vector
{
	if (isSaving == false)
	{
		animIsPlaying = false;
		(currentFrame->GetShapeVector()).push_back(_shape); //Add shape to the current frame's shape vector
		if (!currentFrame->GetRedoVector().empty())
		{
			FlushRedo();
		}
	}
}

void CCanvas::AddStamp(IShape* _stamp)
{
	if (isSaving == false)
	{
		animIsPlaying = false;
		IShape* tempStamp = _stamp;
		(currentFrame->GetShapeVector()).push_back(tempStamp); //Add shape to the current frame's shape vector
		if (!currentFrame->GetRedoVector().empty())
		{
			FlushRedo();
		}
	}
}

void CCanvas::SetPenColour(COLORREF _colour)
{
	if (this != nullptr)
	{
		this->penColour = _colour;
	}
}

void CCanvas::SetPenWidth(int _width)
{
	if (this != nullptr)
	{
		this->penWidth = _width;
	}
}

void CCanvas::SetPenStyle(int _style)
{
	if (this != nullptr)
	{
		this->penStyle = _style;
	}
}

void CCanvas::SetBrushColour(COLORREF _colour)
{
	if (this != nullptr)
	{
		this->brushColour = _colour;
	}
}

void CCanvas::SetBrushStyle(int _style)
{
	if (this != nullptr)
	{
		this->brushStyle = _style;
	}
}

int CCanvas::GetPenWidth() const
{
	if (this != nullptr)
	{
		return (this->penWidth);
	}
}

int CCanvas::GetPenStyle() const
{
	if (this != nullptr)
	{
		return (this->penStyle);
	}
}

COLORREF CCanvas::GetPenColour() const
{
	if (this != nullptr)
	{
		return (this->penColour);
	}
}

COLORREF CCanvas::GetBrushColour() const
{
	if (this != nullptr)
	{
		return (this->brushColour);
	}
}

int CCanvas::GetBrushStyle() const
{
	if (this != nullptr)
	{
		return (this->brushStyle);
	}
}

bool CCanvas::GetShowHUD() const
{
	if (this != nullptr)
	{
		return (this->showHUD);
	}
}

void CCanvas::SetShowHUD(bool _show)
{
	if (this != nullptr)
	{
		this->showHUD = _show;
	}
}

void CCanvas::SetFPS(int _fps)
{
	if (this != nullptr)
	{
		this->frameSpeed = _fps;
	}
}

void CCanvas::SetStampFileName(wchar_t _fileName)
{
	animIsPlaying = false;
	wchar_t fN = _fileName;
	if (this != nullptr)
	{
		this->stampFileName = fN;
	}
}

void CCanvas::Undo()
{
	animIsPlaying = false;
	if (!currentFrame->GetShapeVector().empty())
	{
		IShape* undoShape = (currentFrame->GetShapeVector().back());
		currentFrame->GetRedoVector().push_back(undoShape);
		undoShape->SetVisible(false);
		currentFrame->GetShapeVector().pop_back();
	}
}

void CCanvas::Redo()
{
	animIsPlaying = false;
	if (!currentFrame->GetRedoVector().empty())
	{
		IShape* redoShape = (currentFrame->GetRedoVector().back());
		currentFrame->GetShapeVector().push_back(redoShape);
		redoShape->SetVisible(true);
		currentFrame->GetRedoVector().pop_back();
	}
}

void CCanvas::UndoAll()
{
	animIsPlaying = false;
	while (!currentFrame->GetShapeVector().empty())
	{
		IShape* undoShape = (currentFrame->GetShapeVector().back());
		currentFrame->GetRedoVector().push_back(undoShape);
		undoShape->SetVisible(false);
		currentFrame->GetShapeVector().pop_back();
	}
}

void CCanvas::FlushRedo()
{
	animIsPlaying = false;
	while(!currentFrame->GetRedoVector().empty())
	{
		IShape* flushShape = (currentFrame->GetRedoVector().back());
		delete flushShape;
		currentFrame->GetRedoVector().pop_back();
	}
}

void CCanvas::AddFrame()
{
	animIsPlaying = false;
	currentFrame = new Frame();
	m_frames.push_back(currentFrame);
}

void CCanvas::DeleteFrame()
{
	animIsPlaying = false;
	if (m_frames.size() > 1)
	{
		Frame* deleteFrame = currentFrame;
		m_frames.erase(m_frames.begin() + (frameIndex));
		NextFrame();
		delete deleteFrame;
	}
}

void CCanvas::DeleteAllFrames()
{
	animIsPlaying = false;
	while (m_frames.size() > 1)
	{
		currentFrame = m_frames.front();
		Frame* deleteFrame = m_frames.back();
		m_frames.pop_back();
		delete deleteFrame;
	}
}

void CCanvas::NextFrame()
{
	if (terminating == false)
	{
		int itera = 0;
		for (std::vector<Frame*>::iterator itN = m_frames.begin(); itN <= m_frames.end(); itN++)
		{
			if (itN != m_frames.end()) //if the frame is not at the end
			{
				if (itera == frameIndex + 1)
				{
					currentFrame = *itN;
					return;
				}
				itera += 1;
			}
			else //if at the end of the frames
			{
				currentFrame = m_frames.at(0); //Set current frame to the first frame
				return;
			}
		}
	}
}

void CCanvas::PrevFrame()
{
	if (terminating == false)
	{
		int itero = m_frames.size() - 1;
		std::vector<Frame*>::reverse_iterator itP = m_frames.rbegin();
		for (; itP <= m_frames.rend(); itP++)
		{
			if (itP != m_frames.rend()) //if the frame is not at the begining
			{
				if (itero == (frameIndex - 1))
				{
					currentFrame = *itP;
					return;
				}
				itero -= 1;
			}
			else //if at the begining of the frames
			{
				currentFrame = m_frames.at(m_frames.size() - 1); //Set current frame to the last frame
				return;
			}
		}
	}
}

void CCanvas::PlayPause()
{
	if (animIsPlaying)
	{
		animIsPlaying = false;
		return;
	}
	else
	{
		animIsPlaying = true;
		return;
	}
}

void CCanvas::Pause()
{
	animIsPlaying = false;
}

void CCanvas::SetTerminating()
{
	terminating = true;
}

void CCanvas::ToggleOnion()
{
	if (drawOnion == false)
	{
		drawOnion = true;
		return;
	}
	else
	{
		drawOnion = false;
		return;
	}
}