#ifndef GUI_H
#define GUI_H
/////////////////////////////////////////////////////////////////////////////
// Name:        GUI.h
// Encoding:	UTF-8
//
// Purpose:     Main Application GUI
//
// Author:      Erik Welander
// Modified:    2015-08-16
// Copyright:   Erik Welander
// Licence:     Creative Commons "by-nc-nd"
/////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
//==========WxWidgets segment=========
#include <wx/wx.h>

//==========Windows headers==========
#include <windows.h>
#include <Lmcons.h>

//==========Application headers===========
#include "libSys.h"
#include <vector>
#include <exception>

// ----------------------------------------------------------------------------
//   Declarations
// ----------------------------------------------------------------------------
using std::string;
using std::vector;
using std::exception;

class GUI : public wxFrame
{
	public:
		GUI(wxWindow* parent, wxWindowID id = -1);
	private:
		static const long ID_menuAbout, ID_menuQuit;
		static const wxString m_title,
							  m_version;
		wxPanel *panel;
		wxMenuBar *m_menuBar;
		wxMenu *m_menuOptions;
		wxMenu *m_menuInfo;
		wxBoxSizer* boxSizer;

		int imageSizeX, imageSizeY;
		int numImages;
		vector<string> imageStrings;

		void initVars();
		void initGUI(wxWindow* parent, wxWindowID id);
		void onButtonClick(wxCommandEvent& event);
		void onMenuAbout(wxCommandEvent& event);
		void onMenuQuit(wxCommandEvent& event);
		DECLARE_EVENT_TABLE()
};

#endif