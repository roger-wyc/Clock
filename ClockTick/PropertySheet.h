#pragma once

#include <Windows.h>
#include <Commdlg.h>

INT_PTR CreatePropertySheet(HWND hWnd, HINSTANCE hInst);
int CALLBACK PropSheetProc(HWND hWnd, UINT message, LPARAM lParam);
