#include "stdafx.h"
#include "Print.h"
#include "Paint.h"
#include "ClockTick.h"

extern MYDATA gData;


void PrintClock(HWND hWnd)
{
	PRINTDLG pddlg;
	pddlg.lStructSize = sizeof(PRINTDLG);
	pddlg.hwndOwner = hWnd;
	pddlg.hDevMode = NULL;
	pddlg.hDevNames = NULL;
	pddlg.hDC = NULL;
	pddlg.Flags = PD_RETURNDC | PD_COLLATE;
	pddlg.nFromPage = START_PAGE_GENERAL;
	pddlg.nMinPage = 1;
	pddlg.nMaxPage = 1000;
	pddlg.nCopies = 1;
	pddlg.hInstance = 0;
	pddlg.lCustData = NULL;
	pddlg.lpfnPrintHook = NULL;
	pddlg.lpfnSetupHook = NULL;
	pddlg.lpPrintTemplateName = NULL;
	pddlg.lpSetupTemplateName = NULL;
	pddlg.hPrintTemplate = NULL;
	pddlg.hSetupTemplate = NULL;

	if (PrintDlg(&pddlg))
	{
		HDC hdcPrinter = pddlg.hDC;
		static DOCINFO di = { sizeof(DOCINFO), 0 };
		if (StartDoc(hdcPrinter, &di) > 0)
		{
			int pageWidth = GetDeviceCaps(hdcPrinter, HORZRES);
			int pageHeight = GetDeviceCaps(hdcPrinter, VERTRES);
			RECT rect = { 0, 0, pageWidth, pageHeight };
			for (int i = 0; i < gData.num_clock; i++)
			{
				if (StartPage(hdcPrinter) > 0)
				{
					DrawClockS(hdcPrinter, rect, i + 1, gData.nTimeZone[i]);
					EndPage(hdcPrinter);
				}
				else
				{
					if (pddlg.hDC != NULL) DeleteDC(pddlg.hDC);
					if (pddlg.hDevMode != NULL) GlobalFree(pddlg.hDevMode);
					if (pddlg.hDevNames != NULL) GlobalFree(pddlg.hDevNames);
				}
			}
			EndDoc(hdcPrinter);
		}
		DeleteDC(hdcPrinter);
	}
}
