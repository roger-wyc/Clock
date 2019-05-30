#include "stdafx.h"
#include "File.h"

HANDLE CreateMyFile(LPTSTR lpszFileName)
{
	return CreateFile(lpszFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
}

BOOL WriteMyFile(HANDLE hFile, LPVOID lpData, DWORD dwSize)
{
	DWORD dwWriteSize = 0;
	return WriteFile(hFile, lpData, dwSize, &dwWriteSize, NULL);
}

BOOL ReadMyFile(HANDLE hFile, LPVOID lpData, DWORD dwSize)
{
	DWORD dwReadSize = 0;
	return ReadFile(hFile, lpData, dwSize, &dwReadSize, NULL);
}

void FreeMyFile(HANDLE hFile)
{
	if (hFile != INVALID_HANDLE_VALUE)
		CloseHandle(hFile);
}

DWORD GetMyFileSize(HANDLE hFile)
{
	return GetFileSize(hFile, NULL);
}
