#include <windows.h>
#include <tchar.h>
#include <iostream>

int _tmain()
{
	DWORD dwRet;
	HKEY hKey;

	dwRet = RegOpenKeyEx(
		HKEY_CURRENT_USER,
		_T("Control Panel\\Desktop"),
		NULL,
		KEY_QUERY_VALUE,
		&hKey);
	if (dwRet != ERROR_SUCCESS)
	{
		std::clog
			<< "Error: RegOpenKeyEx:"
			<< " dwRet=" << dwRet
			<< " GetLastError=" << GetLastError() << "\n";
		return 1;
	}

	const DWORD SIZE = 1024;
	TCHAR szValue[SIZE] = _T("");
	DWORD dwValue = SIZE;
	DWORD dwType = 0;
	dwRet = RegQueryValueEx(
		hKey,
		_T("Wallpaper"),
		NULL,
		&dwType,
		(LPBYTE)&szValue,
		&dwValue);
	if (dwRet != ERROR_SUCCESS)
	{
		std::clog
			<< "Error: RegQueryValueEx:"
			<< " dwRet=" << dwRet
			<< " GetLastError=" << GetLastError() << "\n";
		return 1;
	}
	if (dwType != REG_SZ)
	{
		std::clog << "Value not a string\n";
		return 1;
	}

#ifdef _UNICODE
	std::wcout << "szValue=" << szValue << "\n";
#else
	std::cout << "szValue=" << szValue << "\n";
#endif

	RegCloseKey(hKey);
	hKey = NULL;
}