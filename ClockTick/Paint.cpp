#include "stdafx.h"
#include "ClockTick.h"
#include "Paint.h"
#include <Math.h>

extern MYDATA gData;
extern TIMEZONE_INFO timezoneInfo[25];

void DrawClockS(HDC &hdc, RECT &rect, int num, int zone)
{
	if (zone < -12 || zone > 12 || num > gData.num_clock)
		return;

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	HFONT hFont = CreateFontIndirect(&gData.TextFont);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 0, 0));

	SYSTEMTIME tm;
	GetLocalTime(&tm);

	short hour = tm.wHour;
	short minute = tm.wMinute;
	short second = tm.wSecond;

	hour += (zone - 8);
	if (hour > 24)
		hour -= 24;
	else if (hour < 0)
		hour += 24;

	TCHAR a[150];
	if (tm.wMinute < 10)
	{
		if (tm.wSecond < 10)
		{
			wsprintf(a, _T("ClockID:%d\nTimeZone:%d\nArea:%s\nTime:%d:0%d:0%d"), num, zone, timezoneInfo[zone + 12].areaname, hour, minute, second);
		}
		else
		{
			wsprintf(a, _T("ClockID:%d\nTimeZone:%d\nArea:%s\nTime:%d:0%d:%d"), num, zone, timezoneInfo[zone + 12].areaname, hour, minute, second);
		}
	}
	else
	{
		if (tm.wSecond < 10)
		{
			wsprintf(a, _T("ClockID:%d\nTimeZone:%d\nArea:%s\nTime:%d:%d:0%d"), num, zone, timezoneInfo[zone + 12].areaname, hour, minute, second);
		}
		else
		{
			wsprintf(a, _T("ClockID:%d\nTimeZone:%d\nArea:%s\nTime:%d:%d:%d"), num, zone, timezoneInfo[zone + 12].areaname, hour, minute, second);
		}
	}

	DrawText(hdc, a, _tcsclen(a), &rect, DT_LEFT | DT_TOP);

	POINT point;
	HPEN pen1 = CreatePen(PS_SOLID, 9, RGB(0, 0, 0));
	SelectObject(hdc, pen1);
	point.x = (rect.left + rect.right) / 2;
	point.y = (rect.top + rect.bottom) / 2;
	int R = 0;
	if (width >= height)
		R = height / 2 - 10;
	else
		R = width / 2 - 10;
	Ellipse(hdc, point.x - R, point.y - R, point.x + R, point.y + R);

	POINT p0, p1;
	HPEN pen2 = CreatePen(PS_SOLID, 6, RGB(0, 0, 0));
	SelectObject(hdc, pen2);
	for (int i = 0; i < 12; i++)
	{
		p0.x = (long)(point.x + R * sin(PI / 6 * i)*1.00f);
		p0.y = (long)(point.y - R * cos(PI / 6 * i)*1.00f);
		p1.x = (long)(point.x + R * sin(PI / 6 * i)*0.9f);
		p1.y = (long)(point.y - R * cos(PI / 6 * i)*0.9f);

		MoveToEx(hdc, p0.x, p0.y, NULL);
		LineTo(hdc, p1.x, p1.y);
	}

	HPEN pen3 = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, pen3);
	for (int i = 0; i < 60; i++)
	{
		p0.x = (long)(point.x + R * sin(PI / 30 * i)*1.00f);
		p0.y = (long)(point.y - R * cos(PI / 30 * i)*1.00f);
		p1.x = (long)(point.x + R * sin(PI / 30 * i)*0.95f);
		p1.y = (long)(point.y - R * cos(PI / 30 * i)*0.95f);

		MoveToEx(hdc, p0.x, p0.y, NULL);
		LineTo(hdc, p1.x, p1.y);
	}

	HPEN pen4 = CreatePen(PS_SOLID, 8, gData.colorHour);
	SelectObject(hdc, pen4);
	p0.x = (long)(point.x*1.00f);
	p0.y = (long)(point.y*1.00f);
	p1.x = (long)(point.x + R * sin(PI / 6 * (hour + ((double)minute / 60)))*0.6f);
	p1.y = (long)(point.y - R * cos(PI / 6 * (hour + ((double)minute / 60)))*0.6f);
	MoveToEx(hdc, p0.x, p0.y, NULL);
	LineTo(hdc, p1.x, p1.y);

	HPEN pen5 = CreatePen(PS_SOLID, 6, gData.colorMinute);
	SelectObject(hdc, pen5);
	p0.x = (long)(point.x*1.00f);
	p0.y = (long)(point.y*1.00f);
	p1.x = (long)(point.x + R * sin(PI / 30 * (minute + (double)(second / 60)))*0.8f);
	p1.y = (long)(point.y - R * cos(PI / 30 * (minute + (double)(second / 60)))*0.8f);
	MoveToEx(hdc, p0.x, p0.y, NULL);
	LineTo(hdc, p1.x, p1.y);

	HPEN pen6 = CreatePen(PS_SOLID, 2, gData.colorSecond);
	SelectObject(hdc, pen6);
	p0.x = (long)(point.x*1.00f);
	p0.y = (long)(point.y*1.00f);
	p1.x = (long)(point.x + R * sin(PI / 30 * second)*0.9f);
	p1.y = (long)(point.y - R * cos(PI / 30 * second)*0.9f);
	MoveToEx(hdc, p0.x, p0.y, NULL);
	LineTo(hdc, p1.x, p1.y);

	DeleteObject(pen1);
	DeleteObject(pen2);
	DeleteObject(pen3);
	DeleteObject(pen4);
	DeleteObject(pen5);
	DeleteObject(pen6);
	DeleteObject(hFont);
}

void DrawClockA(HDC &hdc, RECT &rect)
{
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	//ÄÚ´æDC
	HBITMAP bmp = CreateCompatibleBitmap(hdc, width, height);
	HDC dcMem = CreateCompatibleDC(hdc);
	SelectObject(dcMem, bmp);
	//±³¾°ÑÕÉ«
	HBRUSH bkbrush = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(dcMem, &rect, bkbrush);
	SetBkMode(dcMem, TRANSPARENT);

	unsigned char Pattern_Display = 0x00;
	if (gData.num_clock == 1)
	{
		Pattern_Display = 0x00;
	}
	else
	{
		Pattern_Display = gData.num_clock / 2 + gData.num_clock % 2;
	}

	switch (Pattern_Display)
	{
	case 0x00:
		DrawClockS(dcMem, rect, 1, gData.nTimeZone[0]);
		break;
	case 0x01:
		for (int i = 0; i < 2; i++)
		{
			RECT rect_cube = { rect.left + width / 2 * i,rect.top,rect.left + width / 2 * (i + 1),rect.bottom };
			DrawClockS(dcMem, rect_cube, i + 1, gData.nTimeZone[i]);
		}
		break;
	case 0x02:
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
			{
				RECT rect_cube = { rect.left + width / 2 * j,rect.top + height / 2 * i,rect.left + width / 2 * (j + 1),rect.top + height / 2 * (i + 1) };
				DrawClockS(dcMem, rect_cube, 2 * i + j + 1, gData.nTimeZone[2 * i + j]);
			}
		break;
	case 0x03:
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 3; j++)
			{
				RECT rect_cube = { rect.left + width / 3 * j,rect.top + height / 2 * i,rect.left + width / 3 * (j + 1),rect.top + height / 2 * (i + 1) };
				DrawClockS(dcMem, rect_cube, 3 * i + j + 1, gData.nTimeZone[3 * i + j]);
			}
		break;
	case 0x04:
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 4; j++)
			{
				RECT rect_cube = { rect.left + width / 4 * j,rect.top + height / 2 * i,rect.left + width / 4 * (j + 1),rect.top + height / 2 * (i + 1) };
				DrawClockS(dcMem, rect_cube, 4 * i + j + 1, gData.nTimeZone[4 * i + j]);
			}
		break;
	case 0x05:
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 5; j++)
			{
				RECT rect_cube = { rect.left + width / 5 * j,rect.top + height / 2 * i,rect.left + width / 5 * (j + 1),rect.top + height / 2 * (i + 1) };
				DrawClockS(dcMem, rect_cube, 5 * i + j + 1, gData.nTimeZone[5 * i + j]);
			}
		break;
	default:
		DrawClockS(dcMem, rect, 1, gData.nTimeZone[0]);
		break;
	}

	BitBlt(hdc, 0, 0, width, height, dcMem, 0, 0, SRCCOPY);
	DeleteObject(bkbrush);
	DeleteObject(bmp);
	DeleteObject(dcMem);
}
