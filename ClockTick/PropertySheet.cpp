#include "stdafx.h"
#include "PropertySheet.h"
#include "TimeZoneDlg.h"
#include "FontColorDlg.h"
#include "resource.h"

INT_PTR CreatePropertySheet(HWND hWnd, HINSTANCE hInst)
{
	TCHAR tszTitleTimeZone[MAX_PATH] = { 0 };
	TCHAR tszTitleFontColor[MAX_PATH] = { 0 };
	memcpy(tszTitleTimeZone, _T("Time Zone"), MAX_PATH);
	memcpy(tszTitleFontColor, _T("Font and Color"), MAX_PATH);

	PROPSHEETPAGE psp[2] = { 0 };
	psp[0].dwSize = sizeof(PROPSHEETPAGE);
	psp[0].dwFlags = PSP_USETITLE;
	psp[0].pszTitle = tszTitleTimeZone;
	psp[0].hInstance = hInst;
	psp[0].pfnDlgProc = TimeZoneProc;
	psp[0].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG_TIMESETTING);

	psp[1].dwSize = sizeof(PROPSHEETPAGE);
	psp[1].dwFlags = PSP_USETITLE;
	psp[1].pszTitle = tszTitleFontColor;
	psp[1].hInstance = hInst;
	psp[1].pfnDlgProc = FontColorProc;
	psp[1].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG_FONTCOLOR);

	PROPSHEETHEADER psh = { 0 };
	psh.dwSize = sizeof(PROPSHEETHEADER);
	psh.hInstance = hInst;
	psh.hwndParent = hWnd;
	psh.dwFlags = PSH_PROPSHEETPAGE | PSH_USECALLBACK;
	psh.ppsp = (LPCPROPSHEETPAGE)&psp;
	psh.nPages = sizeof(psp) / sizeof(PROPSHEETPAGE);
	psh.pfnCallback = PropSheetProc;

	return PropertySheet(&psh);
}

int CALLBACK PropSheetProc(HWND hWnd, UINT message, LPARAM lParam)
{
	switch (message)
	{
	case PSCB_INITIALIZED:
		break;
	default:
		break;
	}
	return 0;
}
