#include "stdafx.h"

#include <windowsx.h>
#include "TimeZoneDlg.h"
#include "ClockTick.h"
#include "resource.h"

extern MYDATA gData;
extern HINSTANCE hInst;
extern TIMEZONE_INFO timezoneInfo[TIMEZONE_NUM];

UINT temp_numclock;
int temp_nTimeZone[CLOCK_MAX];

INT_PTR CALLBACK TimeZoneProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		Value_Get();
		InitClockCountComBo(hDlg);
		InitTimeZoneComBo(hDlg);
		InitListView(hDlg);	

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON_SETNUM)
		{
			HWND hnum = GetDlgItem(hDlg, IDC_COMBO_CLOCKCOUNT);
			int id = (int)SendMessage(hnum, CB_GETCURSEL, 0, 0L);
			temp_numclock = id + 1;
			for (int i = id + 1; i < 10; i++)
			{
				temp_nTimeZone[i] = 8;
			}

			HWND hlist = GetDlgItem(hDlg, IDC_LIST);
			RefreshListView(hDlg, hlist);
			Value_Set();

			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON_SETTIMEZONE)
		{
			HWND htime = GetDlgItem(hDlg, IDC_COMBO_TIMEZONE);
			HWND hlist = GetDlgItem(hDlg, IDC_LIST);
			int id = (int)SendMessage(htime, CB_GETCURSEL, 0, 0L);
			int row = SendMessage(hlist, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
			if (row < 0 || id < 0)
				return (INT_PTR)FALSE;

			LV_ITEM lvitem = { 0 };
			lvitem.mask = LVIF_TEXT;
			lvitem.pszText = (LPWSTR)timezoneInfo[id].zonename;
			lvitem.iItem = row;
			lvitem.iSubItem = 1;
			SendMessage(hlist, LVM_SETITEM, 0, LPARAM(&lvitem));
			temp_nTimeZone[row] = id - 12;
			Value_Set();

			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void InitClockCountComBo(HWND hDlg)
{
	HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO_CLOCKCOUNT);
	ComboBox_ResetContent(hComboBox);
	for (int i = 0; i < CLOCK_MAX; i++)
	{
		TCHAR tszClockCount[MAX_PATH] = { 0 };
		_itow_s(i + 1, tszClockCount, MAX_PATH, 10);
		ComboBox_AddString(hComboBox, tszClockCount);
	}
	SendMessage(hComboBox, CB_SETCURSEL, (WPARAM)(gData.num_clock - 1), 0);
}

void InitTimeZoneComBo(HWND hDlg)
{
	HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO_TIMEZONE);
	ComboBox_ResetContent(hComboBox);
	for (int i = 0; i < TIMEZONE_NUM; i++)
	{
		TCHAR tszTimeZone[MAX_PATH] = { 0 };
		memcpy(tszTimeZone, timezoneInfo[i].zonename, MAX_PATH);
		ComboBox_AddString(hComboBox, tszTimeZone);
	}
	SendMessage(hComboBox, CB_SETCURSEL, (WPARAM)(TIMEZONE_NUM/2), 0);
}

void InitListView(HWND hDlg)
{
	HWND hlist = GetDlgItem(hDlg, IDC_LIST);
	ListView_SetExtendedListViewStyle(hlist, ListView_GetExtendedListViewStyle(hlist) | LVS_EX_FULLROWSELECT);
	// SendMessage(hlist, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES);

	LVCOLUMN lvc = { 0 };
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
	lvc.fmt = LVCFMT_CENTER;
	lvc.cchTextMax = 50;
	lvc.pszText = NULL;

	lvc.cx = 80;
	lvc.iSubItem = 0;  // _T("ID");
	ListView_InsertColumn(hlist, LV_COLUMN_CLOCKID, &lvc);
	lvc.cx = 200;	
	lvc.iSubItem = 1;  // _T("TimeZone");
	ListView_InsertColumn(hlist, LV_COLUMN_TIMEZONE, &lvc);

	RefreshListView(hDlg, hlist);
}

void RefreshListView(HWND hDlg, HWND hlist)
{
	ListView_DeleteAllItems(hlist);
	for (int i = 0; i < temp_numclock; i++)
	{
		TCHAR tszID[MAX_PATH] = { 0 };
		_itow_s(i + 1, tszID, MAX_PATH, 10);
		InsertRow(hlist, i, tszID, (LPARAM)&temp_nTimeZone[i]);

		TCHAR tszTimeZone[MAX_PATH] = { 0 };
		memcpy(tszTimeZone, timezoneInfo[temp_nTimeZone[i]+12].zonename, MAX_PATH);
		SetRow(hlist, i, tszTimeZone, LV_COLUMN_TIMEZONE);
	}
}

void InsertRow(HWND hCtrl, INT iItem, LPTSTR lpszText, LPARAM lParam)
{
	LV_ITEM lvitem;
	ZeroMemory(&lvitem, sizeof(LV_ITEM));

	lvitem.mask = LVIF_TEXT | LVIF_PARAM;
	lvitem.iItem = iItem;
	lvitem.pszText = lpszText;
	lvitem.iSubItem = 0;
	lvitem.cchTextMax = MAX_PATH;
	lvitem.lParam = lParam;

	ListView_InsertItem(hCtrl, &lvitem);
}

void SetRow(HWND hCtrl, INT iItem, LPTSTR lpszText, INT iSubItem)
{
	LVITEM item;
	ZeroMemory(&item, sizeof(LVITEM));

	item.iItem = iItem;
	item.mask = LVIF_TEXT;
	item.pszText = lpszText;
	item.iSubItem = iSubItem;
	item.cchTextMax = lstrlen(item.pszText);

	ListView_SetItem(hCtrl, &item);
}

void Value_Get()
{
	temp_numclock = gData.num_clock;
	for (int i = 0; i < CLOCK_MAX; i++)
	{
		temp_nTimeZone[i]= gData.nTimeZone[i];
	}
}

void Value_Set()
{
	gData.num_clock = temp_numclock;
	for (int i = 0; i < CLOCK_MAX; i++)
	{
		gData.nTimeZone[i] = temp_nTimeZone[i];
	}
}
