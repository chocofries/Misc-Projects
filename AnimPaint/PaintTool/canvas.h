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

#ifndef __CANVAS_H__
#define __CANVAS_H__

//	Library Includes
#include <windows.h>
#include <windowsx.h>
#include <vector>
#include <time.h>
#include "backBuffer.h"
#include "frame.h"

typedef enum
{
	LINE = 0,
	BOX,
	ELLIPSE,
	MAX_SHAPE
}EShape;

class IShape; //Forward Declaration
class CLine;
class CStamp;
class CBackBuffer;

class CCanvas
{
public:
	CCanvas();
	~CCanvas();
	bool Initialise(HWND _hwnd, int _iWidth, int _iHeight);
	CBackBuffer* GetBackBuffer();
	bool Draw(int mouseX, int mouseY);
	void Save(HWND _hwnd);
	void SaveAnimation(HWND _hwnd);
	void Load(HWND _hwnd, IShape* _gShape, CCanvas* _gCanvas);
	void AddShape(IShape* _shape);
	void AddStamp(IShape* _stamp);
	void SetPenColour(COLORREF _colour);
	void SetPenWidth(int _width);
	void SetPenStyle(int _style);
	void SetBrushColour(COLORREF _colour);
	void SetBrushStyle(int _style);
	int GetPenWidth() const;
	int GetPenStyle() const;
	COLORREF GetPenColour() const;
	COLORREF GetBrushColour() const;
	int GetBrushStyle() const;
	bool GetShowHUD() const;
	void SetShowHUD(bool _show);
	void SetFPS(int _fps);
	void Undo();
	void Redo();
	void UndoAll(); //Puts all shapes into redo vector
	void FlushRedo(); //Deletes shapes in the redo vector;
	void SetStampFileName(wchar_t _fileName);
	void AddFrame();
	void DeleteFrame();
	void DeleteAllFrames();
	void NextFrame();
	void PrevFrame();
	void PlayPause();
	void Pause();
	void SetTerminating();
	void ToggleOnion();
	
private:
	CBackBuffer* m_pBackBuffer; // A canvas has a backbuffer.
	CBackBuffer backBuffer;

	std::vector<Frame*> m_frames; //Vector that stores the animation frames
	Frame* currentFrame; //Pointer to the current frame being drawn
	Frame* onionSkin; //Pointer to the onion skin frame
	int frameIndex; //Index of the current frame
	bool animIsPlaying; //If the animation is playing or not

	HWND hwnd;
	int penWidth, penStyle, brushStyle; //Width & Style
	COLORREF penColour; //Pen Colour
	COLORREF brushColour; //Brush Colour
	HDC hdc_b;
	bool showHUD; //Whether or not the hud should be shown
	bool isSaving;
	bool terminating;
	wchar_t stampFileName;

	int frameSpeed;
	double timeCounter;
	clock_t nowTime;
	clock_t prevTime;
	bool drawOnion;
};

#endif