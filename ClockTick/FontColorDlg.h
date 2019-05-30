#pragma once
#include <Windows.h>
#include <Commdlg.h>
#include <commctrl.h>

INT_PTR CALLBACK FontColorProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

LOGFONT ChooseMyFont(HWND hWnd, HINSTANCE hInst, LOGFONT font);
COLORREF ChooseMyColor(HWND hWnd, HINSTANCE hInst, COLORREF colorDefault);
void DestroyMyFont(HFONT hFont);
void SaveFontColorData();