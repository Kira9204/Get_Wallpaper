/////////////////////////////////////////////////////////////////////////////
// Name:        GetWallpaper.cpp
// Encoding:	UTF-8
//
// Purpose:     Get Wallpaper main application file.
//
// Author:      Erik Welander (mail@erikwelander.se)
// Modified:    2015-08-16
// Copyright:   Erik Welander
// Licence:     Creative Commons "by-nc-nd"
/////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#include "headers/GetWallpaper.h"
#include "headers/GUI.h"
IMPLEMENT_APP(GetWallpaper);

bool GetWallpaper::OnInit()
{
	bool wxsOK = true;
	wxInitAllImageHandlers();
	if (wxsOK)
	{
		GUI* Frame = new GUI(0);
		Frame->Show();
		SetTopWindow(Frame);
	}
	return wxsOK;

}
