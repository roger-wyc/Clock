#pragma once

#include <Windows.h>

HANDLE CreateMyFile(LPTSTR lpszFileName);
BOOL WriteMyFile(HANDLE hFile, LPVOID lpData, DWORD dwSize);
BOOL ReadMyFile(HANDLE hFile, LPVOID lpData, DWORD dwSize);
void FreeMyFile(HANDLE hFile);
DWORD GetMyFileSize(HANDLE hFile);
