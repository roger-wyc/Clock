// ClockTick.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ClockTick.h"
#include <Commdlg.h>
#include "Paint.h"
#include "PropertySheet.h"
#include "TimeZoneDlg.h"
#include "FontColorDlg.h"
#include "File.h"
#include "Print.h"
#pragma comment(lib, "comctl32.lib")	// for PropertySheet(LPCPROPSHEETHEADER header)

#define MAX_LOADSTRING 100
#define TIMER_ID       1

TIMEZONE_INFO timezoneInfo[TIMEZONE_NUM] = {	{ _T("West"),_T("West-12 West") }, { _T("Honululu"),_T("West-11 Honululu") }, {_T("Anchorage"),_T("West-10 Anchorage")}, {_T("Vancouver"),_T("West-9 Vancouver")},{_T("Los Angeles"),_T("West-8 Los Angeles")},
									{_T("Mexico City"),_T("West-7 Mexico City")},{_T("Chicago"),_T("West-6 Chicago")},{_T("New York"),_T("West-5 New York")},{_T("Brazilia"),_T("West-4 Brazilia")},{_T("Nuuk"),_T("West-3 Nuuk")},
									{_T("Reykjavik"),_T("West-2 Reykjavik")},{_T("Dakar"),_T("West-1 Dakar")},{_T("London"),_T("Mid-0 London")},{_T("Berlin"),_T("East-1 Berlin")},{_T("Athens"),_T("East-2 Athens")},
									{_T("Moscow"),_T("East-3 Moscow")},{_T("Dubai"),_T("East-4 Dubai")},{_T("Mumbai"),_T("East-5 Mumbai")},{_T("Kathmandu"),_T("East-6 Kathmandu")},{_T("Bankrk"),_T("East-7 Bankrk")},
									{_T("Beijing"),_T("East-8 Beijing")},{_T("Tokyo"),_T("East-9 Tokyo")},{_T("Sydney"),_T("East-10 Sydney")},{_T("Auckland"),_T("East-11 Auckland")},{_T("East"), _T("East-12 East")}
								};

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//User Variables:
MYDATA gData = { 0 };
BOOL bTimer = TRUE;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void SaveParameter(HWND hWnd);
void LoadParameter(HWND hWnd);

void Value_Init();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLOCKTICK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLOCKTICK));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLOCKTICK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLOCKTICK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	HMENU hmenu = GetMenu(hWnd);
	PAINTSTRUCT ps;
	HDC hdc;

    switch (message)
    {
    case WM_COMMAND:
        {
			wmId = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDM_START:
				SetTimer(hWnd, TIMER_ID, 1000, NULL);
				bTimer = TRUE;
				CheckMenuItem(hmenu, IDM_START, MF_CHECKED);
				CheckMenuItem(hmenu, IDM_STOP, MF_UNCHECKED);
				break;
			case IDM_STOP:
				KillTimer(hWnd, TIMER_ID);
				bTimer = FALSE;
				CheckMenuItem(hmenu, IDM_START, MF_UNCHECKED);
				CheckMenuItem(hmenu, IDM_STOP, MF_CHECKED);
				break;
			case IDM_SET:
				CreatePropertySheet(hWnd, hInst);
				break;
			case IDM_LOAD:
				LoadParameter(hWnd);			
				break;
			case IDM_SAVE:
				SaveParameter(hWnd);
				break;
			case IDM_PRINT:
				PrintClock(hWnd);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			RECT rt;
			GetClientRect(hWnd, &rt);  //获取当前窗口位置
			DrawClockA(hdc, rt);
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CREATE:
		Value_Init();
		SetTimer(hWnd, TIMER_ID, 1000, NULL);
		bTimer = TRUE;
		CheckMenuItem(hmenu, IDM_START, MF_CHECKED);
		CheckMenuItem(hmenu, IDM_STOP, MF_UNCHECKED);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_CLOSE:
		if (IDYES == MessageBox(hWnd, _T("Are you sure to Exit？"), _T("Exit"), MB_YESNOCANCEL))
		{
			KillTimer(hWnd, TIMER_ID);
			DestroyWindow(hWnd);
		}
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void Value_Init()
{
	gData.num_clock = 4;

	for (int i = 0; i < 10; i++)
	{
		gData.nTimeZone[i] = 8;
	}
	gData.colorHour = RGB(255, 0, 0);
	gData.colorMinute = RGB(0, 0, 255);
	gData.colorSecond = RGB(0, 0, 0);
}

void SaveParameter(HWND hWnd)
{
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH] = { 0 };
	SAVE_INFO buffer = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = _T("Dat File(*.dat)\0*.Dat\0All(*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrDefExt = _T(".dat");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn))
	{
		HANDLE hf = CreateFile(ofn.lpstrFile, GENERIC_WRITE, 0, (LPSECURITY_ATTRIBUTES)NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);

		buffer.savenum_clock = gData.num_clock;
		for (int i = 0; i < 10; i++)
		{
			buffer.savenTimeZone[i] = gData.nTimeZone[i];
		}
		buffer.savecolorHour = gData.colorHour;
		buffer.savecolorMinute = gData.colorMinute;
		buffer.savecolorSecond = gData.colorSecond;
		buffer.savefontheight = gData.TextFont.lfHeight;
		buffer.savefontweight = gData.TextFont.lfWeight;
		for (int i = 0; i < 32; i++)
			buffer.savefontname[i] = gData.TextFont.lfFaceName[i];

		WriteMyFile(hf, &buffer, sizeof(SAVE_INFO));
		FreeMyFile(hf);
	}
}

void LoadParameter(HWND hWnd)
{
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH] = { 0 };
	SAVE_INFO buffer = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = _T("Dat File(*.dat)\0*.Dat\0All(*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrDefExt = _T(".dat");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn))
	{
		HANDLE hf = CreateMyFile(ofn.lpstrFile);
		bool bret = ReadMyFile(hf, &buffer, sizeof(SAVE_INFO));
		if (bret)
		{
			gData.num_clock = buffer.savenum_clock;
			for (int i = 0; i < 10; i++)
			{
				gData.nTimeZone[i] = buffer.savenTimeZone[i];
			}
			gData.colorHour = buffer.savecolorHour;
			gData.colorMinute = buffer.savecolorMinute;
			gData.colorSecond = buffer.savecolorSecond;
			gData.TextFont.lfHeight = buffer.savefontheight;
			gData.TextFont.lfWeight = buffer.savefontweight;
			for (int i = 0; i < 32; i++)
				gData.TextFont.lfFaceName[i] = buffer.savefontname[i];
			InvalidateRect(hWnd, NULL, FALSE);
		}
		FreeMyFile(hf);
	}
}
