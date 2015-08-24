#ifndef libSys_H
#define libSys_H
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

#include <Windows.h>
#include <string>
#include <sstream>
#include <exception>
using std::string;

namespace libSys
{
	const int BYTE_BUFFER = 2048;
	BYTE* readRegKey(HKEY root, string key, string name);
	string byteToString(const BYTE* data, const int offset);
	LPWSTR stringToLPCTSTR(const string& str);
	void runSilentCMD(const string command);
}


#endif