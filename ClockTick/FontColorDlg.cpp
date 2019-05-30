#include "stdafx.h"
#include "FontColorDlg.h"
#include "ClockTick.h"
#include "resource.h"

extern MYDATA gData;
extern HINSTANCE hInst;

INT_PTR CALLBACK FontColorProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	static COLORREF dwCustColors[16] = { 0 };
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON_FONT)
		{
			gData.TextFont = ChooseMyFont(hDlg, hInst, gData.TextFont);
			return (INT_PTR)TRUE;
		}

		if (LOWORD(wParam) == IDC_BUTTON_COLOR1)
		{
			gData.colorHour = ChooseMyColor(hDlg, hInst, gData.colorHour);
			return (INT_PTR)TRUE;
		}

		if (LOWORD(wParam) == IDC_BUTTON_COLOR2)
		{
			gData.colorMinute = ChooseMyColor(hDlg, hInst, gData.colorMinute);
			return (INT_PTR)TRUE;
		}

		if (LOWORD(wParam) == IDC_BUTTON_COLOR3)
		{
			gData.colorSecond = ChooseMyColor(hDlg, hInst, gData.colorSecond);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

LOGFONT ChooseMyFont(HWND hWnd, HINSTANCE hInst, LOGFONT font)
{
	CHOOSEFONT stChooseFont;
	ZeroMemory(&stChooseFont, sizeof(CHOOSEFONT));
	stChooseFont.lStructSize = sizeof(CHOOSEFONT);
	stChooseFont.hwndOwner = hWnd;
	stChooseFont.lpLogFont = &font;
	stChooseFont.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
	stChooseFont.nFontType = SCREEN_FONTTYPE;

	stChooseFont.iPointSize = 0;
	stChooseFont.rgbColors = RGB(0, 0, 0);
	stChooseFont.lCustData = 0L;
	stChooseFont.lpfnHook = (LPCFHOOKPROC)NULL;
	stChooseFont.lpTemplateName = (LPTSTR)NULL;
	stChooseFont.hInstance = hInst;
	stChooseFont.lpszStyle = (LPTSTR)NULL;
	stChooseFont.nSizeMin = 0;
	stChooseFont.nSizeMax = 0;

	// Display the CHOOSEFONT common-dialog box. 
	if (ChooseFont(&stChooseFont))
		return *(stChooseFont.lpLogFont);
	else
		return font;
}

COLORREF ChooseMyColor(HWND hWnd, HINSTANCE hInst, COLORREF colorDefault)
{
	COLORREF acrCustClr[16] = { 0 };

	CHOOSECOLOR stChooseColor;
	ZeroMemory(&stChooseColor, sizeof(CHOOSECOLOR));
	stChooseColor.Flags = CC_RGBINIT | CC_FULLOPEN | CC_ANYCOLOR;
	stChooseColor.lStructSize = sizeof(CHOOSECOLOR);
	stChooseColor.hwndOwner = hWnd;
	stChooseColor.lpCustColors = acrCustClr;
	stChooseColor.rgbResult = colorDefault;

	// Display the CHOOSECOLOR common-dialog box. 
	if (ChooseColor(&stChooseColor))
		return stChooseColor.rgbResult;
	else
		return colorDefault;
}
