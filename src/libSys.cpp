/////////////////////////////////////////////////////////////////////////////
// Name:        GetWallpaper.cpp
// Encoding:	UTF-8
//
// Purpose:     Get Wallpaper main application file.
//
// Author:      Erik Welander (mail@erikwelander.se)
// Modified:    2015-08-15
// Copyright:   Erik Welander
// Licence:     Creative Commons "by-nc-nd"
/////////////////////////////////////////////////////////////////////////////
#include "../headers/libSys.h"

BYTE* libSys::readRegKey(const HKEY root, const string key, const string name) throw(std::exception)
{
	HKEY hKey;
	BYTE buffer[BYTE_BUFFER];

	if (ERROR_SUCCESS == RegOpenKeyExA(root, key.c_str(), 0, KEY_READ, &hKey))
	{
		DWORD dwType = REG_BINARY, dwSize = sizeof(buffer);
		if (ERROR_SUCCESS == RegQueryValueExA(hKey, name.c_str(), NULL, &dwType, buffer, &dwSize))
		{
			RegCloseKey(hKey);
			return buffer;
		}
	}
	throw std::exception("Could not open registry key!");
}

string libSys::byteToString(const BYTE* data, const int offset)
{
	std::stringstream ss;
	int consequtiveZeroes = 0;
	for (int i = offset; i < BYTE_BUFFER; i++)
	{
		if (consequtiveZeroes > 1)
		{
			break;
		}

		int number = data[i];
		if (number > 1)
		{
			ss << (char)data[i];
			consequtiveZeroes = 0;
		}
		else
		{
			++consequtiveZeroes;
		}
	}
	return ss.str();
}

LPWSTR libSys::stringToLPCTSTR(const string& str)
{
	LPWSTR ws = new wchar_t[str.size() + 1]; // +1 for zero at the end
	copy(str.begin(), str.end(), ws);
	ws[str.size()] = 0; // zero at the end
	return ws;
}

void libSys::runSilentCMD(const string command)
{
	ShellExecute(NULL, TEXT("open"), TEXT("cmd"), stringToLPCTSTR("/Q /C " + command), NULL, SW_HIDE);
}