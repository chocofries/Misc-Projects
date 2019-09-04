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

#include <windows.h>   // Include all the windows headers.
#include <windowsx.h>  // Include useful macros.
#include <Commctrl.h>
#include <commdlg.h>
#include <tchar.h>
#include <string>

#include "resource.h"
#include "shape.h"
#include "freedraw.h"
#include "line.h"
#include "canvas.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polygon.h"
#include "stamp.h"
#include "backBuffer.h"

#define WINDOW_CLASS_NAME L"WINCLASS1"

//Global variables
HINSTANCE g_hInstance;
CCanvas* g_pCanvas = nullptr;
IShape* g_pShape = nullptr;
HMENU g_hMenu;
HIMAGELIST g_hImageList = NULL;
CBackBuffer* g_pBackBuffer = nullptr;
int g_mouseX, g_mouseY;

//Enum to declare the type of tool supported by the application.
enum ESHAPE
{
	FREEHAND = 0,
	LINESHAPE,
	RECTANGLESHAPE,
	ELLIPSESHAPE,
	POLYGONSHAPE,
	STAMP
};


void GameLoop()
{
	if (g_pCanvas != nullptr)
	{
		g_pCanvas->Draw(g_mouseX, g_mouseY);
	}
	//One frame of game logic occurs here...
}


//
//   FUNCTION: OnClose(HWND)
//
//   PURPOSE: Process the WM_CLOSE message
//
void OnClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
}

//
//   FUNCTION: OnInitTrackbarDialog(HWND, HWND, LPARAM)
//
//   PURPOSE: Process the WM_INITDIALOG message
//
BOOL OnInitPenWidthDialog(HWND _hwnd, HWND hWndFocus, LPARAM lParam)
{
	// Load and register Trackbar control class
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccx.dwICC = ICC_WIN95_CLASSES; // Or ICC_PROGRESS_CLASS

	// Create the Trackbar control
	RECT rc = { 20, 20, 250, 20 };
	HWND hTrackbar = CreateWindowEx(0, TRACKBAR_CLASS, 0,
		TBS_HORZ | TBS_NOTICKS | WS_CHILD | WS_VISIBLE,
		rc.left, rc.top, rc.right, rc.bottom,
		_hwnd, (HMENU)ID_PEN_WIDTH, g_hInstance, 0);

	// Set Trackbar range
	SendMessage(hTrackbar, TBM_SETRANGE, (g_pCanvas->GetPenWidth()), MAKELONG(0, 99));

	return TRUE;
}
//
//  FUNCTION: TrackbarDlgProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the Trackbar control dialog.
//
//
INT_PTR CALLBACK PenWidthDlgProc(HWND _hwnd, UINT _msg, WPARAM wParam, LPARAM lParam)
{
	static int scrollNum = g_pCanvas->GetPenWidth();

	HWND hTrackbar = GetDlgItem(_hwnd, ID_PEN_WIDTH);

	switch (_msg)
	{
		HANDLE_MSG(_hwnd, WM_INITDIALOG, OnInitPenWidthDialog);

		HANDLE_MSG(_hwnd, WM_CLOSE, OnClose);

	case WM_CREATE:
	{
		SendMessage(hTrackbar, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)(g_pCanvas->GetPenWidth()));
		return(0);
	}
	break;
	
	case WM_HSCROLL:
	{
		
		if (hTrackbar == (HWND)lParam)
		{
			int newPos = SendMessage(_hwnd, TBM_GETPOS, 0, 0);
			if (newPos != scrollNum)
			{
				SendMessage(hTrackbar, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)scrollNum);
			}
		}

		if (LOWORD(wParam) == TB_THUMBTRACK)
		{
			scrollNum = HIWORD(wParam)+1;
			g_pCanvas->SetPenWidth(scrollNum);
		}
		return(0);
	}
	break;
	default:
		return FALSE;
	}

	return 0;
}
#pragma endregion


#pragma region Updown
#define IDC_EDIT		2990
#define IDC_UPDOWN		2991
//
//   FUNCTION: OnInitUpdownDialog(HWND, HWND, LPARAM)
//
//   PURPOSE: Process the WM_INITDIALOG message
//
BOOL OnInitUpdownDialog(HWND _hwnd, HWND hWndFocus, LPARAM lParam)
{
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccx.dwICC = ICC_UPDOWN_CLASS;

	// Create an Edit control
	RECT rc = { 20, 20, 100, 24 };
	HWND hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", 0,
		WS_CHILD | WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
		_hwnd, (HMENU)IDC_EDIT, g_hInstance, 0);

	// Create the ComboBoxEx control
	SetRect(&rc, 20, 60, 180, 20);
	HWND hUpdown = CreateWindowEx(0, UPDOWN_CLASS, 0,
		UDS_ALIGNRIGHT | UDS_SETBUDDYINT | UDS_WRAP | WS_CHILD | WS_VISIBLE,
		rc.left, rc.top, rc.right, rc.bottom,
		_hwnd, (HMENU)IDC_UPDOWN, g_hInstance, 0);

	// Set Buddy
	SendMessage(hUpdown, UDM_SETBUDDY, (WPARAM)hEdit, 0);

	return TRUE;
}
//
//  FUNCTION: UpdownDlgProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the Updown control dialog.
//
//
INT_PTR CALLBACK UpdownDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_INITDIALOG, OnInitUpdownDialog);

	case WM_CREATE:
	{
		//g_pCanvas->Pause();
		return (0);
	}
	break;
	case WM_COMMAND:
	{
		//g_pCanvas->Pause();
		int fps = 1;
		wchar_t szBuf[260];
		GetDlgItemText(hWnd, IDC_EDIT, szBuf, 260 - 1);
		fps = _wtoi(szBuf);
		if(fps <= 0)
		{ 
			fps = 1;
		}
		if (fps > 100)
		{
			fps = 100;
		}
		//g_pCanvas->Pause();
		g_pCanvas->SetFPS(fps);
		//g_pCanvas->Pause();
		return(0);
	}
	break;
	case WM_CLOSE:
	{
		EndDialog(hWnd, 0);
		return(0);
	}
	default:
		return FALSE;	// Let system deal with msg
	}
	return 0;
}
#pragma endregion



LRESULT CALLBACK WindowProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	// This is the main message handler of the system.
	//PAINTSTRUCT ps; // Used in WM_PAINT.
	//HDC hdc;        // Handle to a device context.
	static ESHAPE currentShape = POLYGONSHAPE;
	static bool isDrawingPolygon;
	static bool penWidthDlg = false;
	static wchar_t* m_pBMPFileName; //Pointer to file name of the bmp to use as stamp
	static wchar_t m_BMPFileName;
	static int sX = 0, sY = 0, eX = 0, eY = 0;
	static int pointDist = 0;
	static wchar_t stampFN;
	
	switch (_msg)
	{
	case WM_CREATE:
	{
		g_pCanvas = new CCanvas;
		g_pCanvas->Initialise(_hwnd, 1400, 800);
		g_pBackBuffer = g_pCanvas->GetBackBuffer();
		// Do initialization stuff here.

		HICON hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(ID_MAIN_ICON));
		_ASSERTE(hIcon != 0);
		SendMessage(_hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

		// Return Success.
		return (0);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		case ID_FILE_EXIT:
		{
			g_pCanvas->Pause();
			PostQuitMessage(0);
			break;
		}
		case ID_HELP_ABOUT:
		{
			isDrawingPolygon = false;
			MessageBox(_hwnd, L"AnimPaint was developed by John Bu.\n\nMay, 2018.", L"About", MB_OK | MB_ICONINFORMATION);
			break;
		}
		case ID_SHOW_HUD:
		{
			isDrawingPolygon = false;
			if (g_pCanvas->GetShowHUD() == false)
			{
				g_pCanvas->SetShowHUD(true);
			}
			else
			{
				g_pCanvas->SetShowHUD(false);
			}
			break;
		}
		case ID_SHAPE_FREE:
		{
			currentShape = FREEHAND;
			break;
		}
		case ID_SHAPE_LINE:
		{
			currentShape = LINESHAPE;
			break;
		}
		case ID_SHAPE_R:
		{
			currentShape = RECTANGLESHAPE;
			break;
		}
		case ID_SHAPE_ELLIPSE:
		{
			currentShape = ELLIPSESHAPE;
			break;
		}
		case ID_SHAPE_POLYGON:
		{
			currentShape = POLYGONSHAPE;
			break;
		}
		case ID_ADD_STAMP:
		{
			OPENFILENAME ofn;			// common dialog box structure
			wchar_t wszFile[260];      // buffer for file name
			//HANDLE hf;					// file handle
			HWND nHw = _hwnd;

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = nHw;
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
				m_pBMPFileName = ofn.lpstrFile;
				wcscpy(&m_BMPFileName, m_pBMPFileName);
				wcscpy(&stampFN, m_pBMPFileName);
				currentShape = STAMP;
			}
			break;
		}
		case ID_PEN_WIDTH:
		{
			isDrawingPolygon = false;
			HWND hDlg = CreateDialog(g_hInstance,MAKEINTRESOURCE(IDD_TRACKBARDIALOG),_hwnd, PenWidthDlgProc);
			if (hDlg)
			{
				ShowWindow(hDlg, SW_SHOW);
			}
			break;
		}
		case ID_PEN_S_SOLID:
		{
			isDrawingPolygon = false;
			g_pCanvas->SetPenStyle(PS_SOLID);
			break;
		}
		case ID_PEN_S_DASH:
		{
			isDrawingPolygon = false;
			g_pCanvas->SetPenStyle(PS_DASH);
			break;
		}
		case ID_PEN_S_DOT:
		{
			isDrawingPolygon = false;
			g_pCanvas->SetPenStyle(PS_DOT);
			break;
		}
		case ID_PEN_S_DASHDOT:
		{
			isDrawingPolygon = false;
			g_pCanvas->SetPenStyle(PS_DASHDOT);
			break;
		}
		case ID_PEN_S_DASHDOTDOT:
		{
			isDrawingPolygon = false;
			g_pCanvas->SetPenStyle(PS_DASHDOTDOT);
			break;
		}
		case ID_BS_SOLID:
		{
			isDrawingPolygon = false;
			g_pCanvas->SetBrushStyle(-1);
			break;
		}
		case ID_BS_DH_A:
		{
			isDrawingPolygon = false;
			g_pCanvas->SetBrushStyle(HS_BDIAGONAL);
			break;
		}
		case ID_BS_DH_B:
		{
			isDrawingPolygon = false;
			g_pCanvas->SetBrushStyle(HS_FDIAGONAL);
			break;
		}
		case ID_BS_HH:
		{
			isDrawingPolygon = false;
			g_pCanvas->SetBrushStyle(HS_HORIZONTAL);
			break;
		}
		case ID_BS_VH:
		{
			isDrawingPolygon = false;
			g_pCanvas->SetBrushStyle(HS_VERTICAL);
			break;
		}
		case ID_BS_DCH:
		{
			isDrawingPolygon = false;
			g_pCanvas->SetBrushStyle(HS_DIAGCROSS);
			break;
		}
		case ID_BS_CH:
		{
			isDrawingPolygon = false;
			g_pCanvas->SetBrushStyle(HS_CROSS);
			break;
		}
		case ID_PEN_COLOR:
		{
			isDrawingPolygon = false;
			static CHOOSECOLOR ccColour = { 0 };	// common dialog box structure 
			static COLORREF acrCustClr[8];			// array of custom colors 

			ccColour.lStructSize = sizeof(ccColour);
			ccColour.hwndOwner = NULL;
			ccColour.hInstance = NULL;
			ccColour.lpCustColors = (LPDWORD) acrCustClr;
			ccColour.rgbResult = g_pCanvas->GetPenColour();
			ccColour.Flags = CC_ANYCOLOR | CC_RGBINIT | CC_FULLOPEN;
			ccColour.lCustData = NULL;
			ccColour.lpfnHook = NULL;
			ccColour.lpTemplateName = NULL;
			
			if (ChooseColor(&ccColour) == TRUE)
			{
				g_pCanvas->SetPenColour(ccColour.rgbResult);
			}
			break;
		}
		case ID_BRUSH_COLOR:
		{
			isDrawingPolygon = false;
			static CHOOSECOLOR ccColour = { 0 };	// common dialog box structure 
			static COLORREF acrCustClr[8];			// array of custom colors 

			ccColour.lStructSize = sizeof(ccColour);
			ccColour.hwndOwner = NULL;
			ccColour.hInstance = NULL;
			ccColour.lpCustColors = (LPDWORD)acrCustClr;
			ccColour.rgbResult = g_pCanvas->GetBrushColour();
			ccColour.Flags = CC_ANYCOLOR | CC_RGBINIT | CC_FULLOPEN;
			ccColour.lCustData = NULL;
			ccColour.lpfnHook = NULL;
			ccColour.lpTemplateName = NULL;

			if (ChooseColor(&ccColour) == TRUE)
			{
				g_pCanvas->SetBrushColour(ccColour.rgbResult);
			}
			break;
		}
		case ID_FILE_NEW:
		{
			isDrawingPolygon = false;
			g_pCanvas->DeleteAllFrames();
			g_pCanvas->UndoAll();
			g_pCanvas->FlushRedo();
			break;
		}
		case ID_FILE_OPEN:
		{
			isDrawingPolygon = false;
			g_pCanvas->Load(_hwnd,g_pShape,g_pCanvas);
			break;
		}
		case ID_FILE_SAVE:
		{
			isDrawingPolygon = false;
			g_pCanvas->Save(_hwnd);
		break;
		}
		case ID_FILE_ANIM:
		{
			isDrawingPolygon = false;
			g_pCanvas->SaveAnimation(_hwnd);
			break;
		}
		case ID_EDIT_UNDO:
		{
			isDrawingPolygon = false;
			g_pCanvas->Undo();
		}
		break;
		case ID_EDIT_REDO:
		{
			isDrawingPolygon = false;
			g_pCanvas->Redo();
		}
		break;
		case ID_ANIM_ADD:
		{
			isDrawingPolygon = false;
			g_pCanvas->AddFrame();
		}
		break;
		case ID_ANIM_DELETE:
		{
			isDrawingPolygon = false;
			g_pCanvas->DeleteFrame();
		}
		break;
		case ID_ANIM_NEXT:
		{
			isDrawingPolygon = false;
			g_pCanvas->NextFrame();
		}
		break;
		case ID_ANIM_PREV:
		{
			isDrawingPolygon = false;
			g_pCanvas->PrevFrame();
		}
		break;
		case ID_ANIM_PLAY:
		{
			isDrawingPolygon = false;
			g_pCanvas->PlayPause();
		}
		break;
		case ID_ANIM_OPTION:
		{
			isDrawingPolygon = false;
			HWND hDlg = CreateDialog(g_hInstance,
				MAKEINTRESOURCE(IDD_ANIMDIALOG),
				_hwnd, UpdownDlgProc);
			if (hDlg)
			{     
				ShowWindow(hDlg, SW_SHOW);
			}
		}
		break;
		case ID_ANIM_ONION:
		{
			isDrawingPolygon = false;
			g_pCanvas->ToggleOnion();
		}
		break;
		default:
			break;
		}
		return(0);
	}
	break;
	case WM_MOVE:
	{
		return(0);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int mouseX = g_mouseX;
		int mouseY = g_mouseY;

		if (currentShape != POLYGONSHAPE)
		{
			isDrawingPolygon = false;
		}

		switch (currentShape)
		{
		case FREEHAND:
		{
			g_pShape = new CFreeDraw(g_pCanvas->GetPenStyle(), g_pCanvas->GetPenWidth(), g_pCanvas->GetPenColour(), mouseX, mouseY);
			g_pShape->SetStartX(mouseX);
			g_pShape->SetStartY(mouseY);
			g_pShape->SetEndX(mouseX);
			g_pShape->SetEndY(mouseY);
			g_pCanvas->AddShape(g_pShape);
			break;
		}
		case LINESHAPE:
		{
			g_pShape = new CLine(g_pCanvas->GetPenStyle(),g_pCanvas->GetPenWidth(), g_pCanvas->GetPenColour(), mouseX, mouseY);
			g_pShape->SetStartX(mouseX);
			g_pShape->SetStartY(mouseY);
			g_pShape->SetEndX(mouseX);
			g_pShape->SetEndY(mouseY);
			g_pCanvas->AddShape(g_pShape);
			break;
		}
		case RECTANGLESHAPE:
		{
			g_pShape = new CRectangle(g_pCanvas->GetBrushStyle(), g_pCanvas->GetBrushColour(), g_pCanvas->GetPenStyle(), g_pCanvas->GetPenColour(), g_pCanvas->GetPenWidth(), mouseX, mouseY);
			g_pCanvas->AddShape(g_pShape);
			break;
		}
		case ELLIPSESHAPE:
		{
			g_pShape = new CEllipse(g_pCanvas->GetPenColour(), g_pCanvas->GetBrushColour(), g_pCanvas->GetPenStyle(), g_pCanvas->GetBrushStyle(), mouseX, mouseY, g_pCanvas->GetPenWidth());
			g_pCanvas->AddShape(g_pShape);
			break;
		}
		case POLYGONSHAPE:
		{
			if (isDrawingPolygon == false)
			{
				g_pShape = new CPolygon(g_pCanvas->GetBrushStyle(), g_pCanvas->GetBrushColour(), g_pCanvas->GetPenStyle(), g_pCanvas->GetPenColour(), g_pCanvas->GetPenWidth());
				g_pCanvas->AddShape(g_pShape);

				g_pShape->SetStartX(mouseX);
				g_pShape->SetStartY(mouseY);
				g_pShape->SetEndX(mouseX);
				g_pShape->SetEndY(mouseY);

				isDrawingPolygon = true;
			}
			break;
		}
		case STAMP:
		{
			g_pShape = new CStamp(NULL, _hwnd, &stampFN, mouseX, mouseY, mouseX, mouseY, false);
			g_pCanvas->AddStamp(g_pShape);
			
			break;
		}
		default:
			break;
		}
		return(0);
	}
	break;
	case WM_LBUTTONUP:
	{
		//Position of the mouse
		int mouseX = static_cast<int>(LOWORD(_lparam));
		int mouseY = static_cast<int>(HIWORD(_lparam));
		if (currentShape != POLYGONSHAPE)
		{
			g_pShape = nullptr;
			sX = 0;
			sY = 0;
			eX = 0;
			eY = 0;
			pointDist = 0;
		}
		else if (isDrawingPolygon == true) //If the current shape is polygon and isDrawingPolygon is true
		{
			g_pShape->SetEndX(mouseX);
			g_pShape->SetEndY(mouseY);
			g_pShape->DoThing(true, 1); //Change a point to the new position
		}

		return(0);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		if (g_pShape != nullptr)
		{
			g_pShape = nullptr;
			isDrawingPolygon = false;
		}
		return(0);
	}
	break;
	case WM_MOUSEMOVE:
	{
		//Position of the mouse
		int mouseX = static_cast<int>(LOWORD(_lparam));
		int mouseY = static_cast<int>(HIWORD(_lparam));
		g_mouseX = mouseX;
		g_mouseY = mouseY;

		//Get button state
		int buttons = static_cast<int>(_wparam);

		//Test if left button is down while moving
		if (buttons & MK_LBUTTON)
		{
			if (sX == 0 && sY == 0 && eX == 0 && eY == 0)
			{
				sX = mouseX;
				sY = mouseY;
				eX = mouseX;
				eY = mouseY;
			}

			if (g_pShape != nullptr)
			{
				if (currentShape != FREEHAND)
				{
					g_pShape->SetEndX(mouseX);
					g_pShape->SetEndY(mouseY);
					//InvalidateRect(_hwnd, NULL, TRUE);
					if (currentShape == POLYGONSHAPE && isDrawingPolygon == true)
					{
						if (pointDist > 8)
						{
							sX = eX;
							sY = eY;
							eX = mouseX;
							eY = mouseY;
							g_pShape->SetEndX(eX);
							g_pShape->SetEndY(eY);
							g_pShape->DoThing(true, 1); //Change to a new point
							g_pShape->DoThing(true, 2); //Move point to a new position
							pointDist = 0;
						}
						else
						{
							eX = mouseX;
							eY = mouseY;
							g_pShape->SetEndX(eX);
							g_pShape->SetEndY(eY);
							pointDist = (int)sqrt(((eX - sX)*(eX - sX)) + ((eY - sY)*(eY - sY)));
						}
					}
				}
				else //If it is the freehand tool
				{
					if (pointDist > 8)
					{
						sX = eX;
						sY = eY;
						eX = mouseX;
						eY = mouseY;
						//New FreeDraw Line
						g_pShape->SetStartX(sX);
						g_pShape->SetStartY(sY);
						g_pShape->DoThing(true, 1); //Do the AddLine Function of the freehand draw
						pointDist = 0;
					}
					else
					{
						eX = mouseX;
						eY = mouseY;
						g_pShape->SetEndX(eX);
						g_pShape->SetEndY(eY);
						pointDist = (int)sqrt(((eX - sX)*(eX - sX)) + ((eY - sY)*(eY - sY)));
					}
				}
				
			}
		}

		//Test if right button is down while moving
		if (buttons & MK_RBUTTON)
		{
			//Do something
			if (g_pShape != nullptr)
			{
				g_pShape = nullptr;
				isDrawingPolygon = false;
			}
		}

		return(0);
	}
	break;
	case WM_KEYDOWN:
	{
		switch (_wparam)
		{
		case 0x59: //Y
		{
			SendMessage(_hwnd, WM_COMMAND, ID_EDIT_REDO, NULL);
			break;
		}
		case 0x5A: //Z
		{
			SendMessage(_hwnd, WM_COMMAND, ID_EDIT_UNDO, NULL);
			break;
		}
		case 0x53: //S
		{
			SendMessage(_hwnd, WM_COMMAND, ID_FILE_SAVE, NULL);
			break;
		}
		case 0x4F: //O
		{
			SendMessage(_hwnd, WM_COMMAND, ID_FILE_OPEN, NULL);
			break;
		}
		case 0x4E: //N
		{
			SendMessage(_hwnd, WM_COMMAND, ID_FILE_NEW, NULL);
			break;
		}
		case 0x48: //H for enable/disable HUD
		{
			isDrawingPolygon = false;
			SendMessage(_hwnd, WM_COMMAND, ID_SHOW_HUD, NULL);
			break;
		}
		case 0x42: //B for brush colour change
		{
			isDrawingPolygon = false;
			SendMessage(_hwnd, WM_COMMAND, ID_BRUSH_COLOR, NULL);
			break;
		}
		case 0x50: //P for pen colour change
		{
			isDrawingPolygon = false;
			SendMessage(_hwnd, WM_COMMAND, ID_PEN_COLOR, NULL);
			break;
		}
		case 0x49: //I for pen width change
		{
			isDrawingPolygon = false;
			SendMessage(_hwnd, WM_COMMAND, ID_PEN_WIDTH, NULL);
			break;
		}
		case 0x46: //F for free draw
		{
			SendMessage(_hwnd, WM_COMMAND, ID_SHAPE_FREE,NULL);
			break;
		}
		case 0x4C: //L for Line shape
		{
			SendMessage(_hwnd, WM_COMMAND, ID_SHAPE_LINE, NULL);
			break;
		}
		case 0x52: //R for Rectangle shape
		{
			SendMessage(_hwnd, WM_COMMAND, ID_SHAPE_R, NULL);
			break;
		}
		case 0x45: //E for Ellipse shape
		{
			SendMessage(_hwnd, WM_COMMAND, ID_SHAPE_ELLIPSE, NULL);
			break;
		}
		case 0x47: //G for Polygon shape
		{
			SendMessage(_hwnd, WM_COMMAND, ID_SHAPE_POLYGON, NULL);
			break;
		}
		case 0x4D: //M for add stamp
		{
			SendMessage(_hwnd, WM_COMMAND, ID_ADD_STAMP, NULL);
			break;
		}
		case 0x4B:
		{
			SendMessage(_hwnd, WM_COMMAND, ID_ANIM_ADD, NULL);
			break;
		}
		case VK_DELETE:
		{
			SendMessage(_hwnd, WM_COMMAND, ID_ANIM_DELETE, NULL);
			break;
		}
		case VK_RIGHT: //Right Arrow for next frame
		{
			SendMessage(_hwnd, WM_COMMAND, ID_ANIM_NEXT, NULL);
			break;
		}
		case VK_LEFT: //Left Arrow for next frame
		{
			SendMessage(_hwnd, WM_COMMAND, ID_ANIM_PREV, NULL);
			break;
		}
		case VK_SPACE: //Spacebar to play/pause
		{
			SendMessage(_hwnd, WM_COMMAND, ID_ANIM_PLAY, NULL);
			break;
		}
		case 0x4A: //J to open animation options
		{
			SendMessage(_hwnd, WM_COMMAND, ID_ANIM_OPTION, NULL);
			break;
		}
		case 0x41: //A to save the animation
		{
			SendMessage(_hwnd, WM_COMMAND, ID_FILE_ANIM, NULL);
			break;
		}
		case 0x55: //A to save the animation
		{
			SendMessage(_hwnd, WM_COMMAND, ID_ANIM_ONION, NULL);
			break;
		}
		default:
			break;
		}
		return(0);
	}
	break;
	case WM_CLOSE:
	{
		g_pCanvas->Pause();
		g_pCanvas->SetTerminating();
		delete g_pCanvas;
	}
	case WM_DESTROY:
	{
		g_pCanvas->Pause();
		g_pCanvas->SetTerminating();
		//delete g_pCanvas;
		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);

		// Return success.
		return (0);
	}
	break;

		default:break;
	} // End switch.

	  // Process any messages that we did not take care of...

	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}


int WINAPI WinMain(HINSTANCE _hInstance,
	HINSTANCE _hPrevInstance,
	LPSTR _lpCmdLine,
	int _nCmdShow)
{
	WNDCLASSEX winclass; // This will hold the class we create.
	HWND hwnd;           // Generic window handle.
	g_hMenu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1));
	MSG msg;             // Generic message.

	g_hInstance = _hInstance;
	// First fill in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground =
		static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		return (0);
	}

	// create the window
	hwnd = CreateWindowEx(NULL, // Extended style.
		WINDOW_CLASS_NAME,      // Class.
		L"AnimPaint 0.0.1",   // Title.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100,                    // Initial x,y.
		1400, 800,                // Initial width, height.
		NULL,                   // Handle to parent.
		g_hMenu,                   // Handle to menu.
		_hInstance,             // Instance of this application.
		NULL);                  // Extra creation parameters.

	if (!(hwnd))
	{
		return (0);
	}

	// Enter main event loop
	while (true)
	{
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Test if this is a quit.
			if (msg.message == WM_QUIT)
			{
				if (g_pCanvas != nullptr)
				{
					g_pCanvas->Pause();
				}
				break;
			}
			// Translate any accelerator keys.
			TranslateMessage(&msg);
			// Send the message to the window proc.
			DispatchMessage(&msg);
		}

		// Main game processing goes here
		
		GameLoop(); //One frame of game logic occurs here...
	}

	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}