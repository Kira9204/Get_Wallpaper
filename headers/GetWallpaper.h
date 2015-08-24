#ifndef GetWallpaper_H
#define GetWallpaper_H
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
#include <wx/app.h>
#include <wx/image.h>

// ----------------------------------------------------------------------------
//   Declarations
// ----------------------------------------------------------------------------

class GetWallpaper : public wxApp
{
public:
	// Overrides base class initialization virtuals
	// This is called during application startup and is a good place for application initialization
	virtual bool OnInit();
};

#endif
