#pragma once
#include <Windows.h>
#include <Commdlg.h>
#include <commctrl.h>

#define LV_COLUMN_CLOCKID	0
#define LV_COLUMN_TIMEZONE	1
#define LV_COLUMN_NUM		2

void Value_Get();
void Value_Set();

INT_PTR CALLBACK TimeZoneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void InitClockCountComBo(HWND hDlg);
void InitTimeZoneComBo(HWND hDlg);
void InitListView(HWND hDlg);
void RefreshListView(HWND hDlg, HWND hlist);
void InsertRow(HWND hCtrl, INT iItem, LPTSTR lpszText, LPARAM lParam);
void SetRow(HWND hCtrl, INT iItem, LPTSTR lpszText, INT iSubItem);
