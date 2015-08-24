/////////////////////////////////////////////////////////////////////////////
// Name:        GUI.cpp
// Encoding:	UTF-8
// Purpose:     Main Application GUI
// Author:      Erik Welander
// Modified:    2015-08-16
// Copyright:   Erik Welander
// Licence:     Creative Commons "by-nc-nd"
/////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#include "../headers/GUI.h"

// ----------------------------------------------------------------------------
//   Declarations
// ----------------------------------------------------------------------------
const wxString GUI::m_version = _(" V2015-08-16");
const wxString GUI::m_title = _("GetWallpaper");
const long GUI::ID_menuAbout = wxNewId();
const long GUI::ID_menuQuit = wxNewId();

BEGIN_EVENT_TABLE(GUI, wxFrame)
END_EVENT_TABLE()

GUI::GUI(wxWindow* parent, wxWindowID id)
{
	initVars();
	initGUI(parent, id);
}
// ----------------------------------------------------------------------------
//   Private methods
// ----------------------------------------------------------------------------

void GUI::initVars()
{
	imageSizeX = 512;
	imageSizeY = 288;

	for (int i = 0; true; i++)
	{
		try
		{
			BYTE* registryValue = libSys::readRegKey(HKEY_CURRENT_USER, "Control Panel\\Desktop\\", "TranscodedImageCache_00" + std::to_string(i));
			imageStrings.push_back(libSys::byteToString(registryValue, 24));
		}
		catch (const std::exception& exception)
		{
			break;
		}
	}

	if (imageStrings.size() == 0)
	{
		try
		{
			BYTE* registryValue = libSys::readRegKey(HKEY_CURRENT_USER, "Control Panel\\Desktop\\", "TranscodedImageCache");
			imageStrings.push_back(libSys::byteToString(registryValue, 24));
		}
		catch (const std::exception& exception)
		{
			wxString message = _("No wallpapers detected!");
			message += _("\nThis program is designed to work with Windows 8.x and Windows 10.");
			wxMessageDialog dialog(NULL, message, m_title + m_version, wxOK | wxICON_INFORMATION);
			dialog.ShowModal();
			exit(1);
		}
	}
}

void GUI::initGUI(wxWindow* parent, wxWindowID id)
{
	Create(parent, wxID_ANY, m_title + m_version, wxDefaultPosition, wxDefaultSize, wxMINIMIZE_BOX | wxCLOSE_BOX | wxSYSTEM_MENU | wxCAPTION);
	SetIcon(wxICON(MYICON));

	m_menuBar = new wxMenuBar();

	m_menuOptions = new wxMenu();
	m_menuOptions->Append(ID_menuQuit, _("Quit\tALT+F4"));

	m_menuInfo = new wxMenu();
	m_menuInfo->Append(ID_menuAbout, _("About\tF1"));

	m_menuBar->Append(m_menuOptions, _("Options"));
	m_menuBar->Append(m_menuInfo, _("Information"));
	SetMenuBar(m_menuBar);

	boxSizer = new wxBoxSizer(wxHORIZONTAL);

	for (int i = 0; i < imageStrings.size(); i++)
	{
		wxString imgStr = wxString::From8BitData(imageStrings.at(i).c_str());
		wxImage* image = new wxImage(imgStr, wxBITMAP_TYPE_ANY, -1);
		image->Rescale(imageSizeX, imageSizeY);

		wxBitmap bitmap = wxBitmap(*image);
		wxBitmapButton* staticButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(bitmap), wxDefaultPosition, wxDefaultSize, 0);
		boxSizer->Add(staticButton, wxALL, 5);

		Connect(wxID_ANY+i, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&GUI::onButtonClick);
	}

	Connect(ID_menuAbout, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&GUI::onMenuAbout);
	Connect(ID_menuQuit, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&GUI::onMenuQuit);
	SetSizer(boxSizer);
	Layout();
	Fit();
}

void GUI::onButtonClick(wxCommandEvent& event)
{
	int id = event.GetId();
	id += 31999;

	libSys::runSilentCMD("explorer.exe " + imageStrings.at(id));
}

void GUI::onMenuAbout(wxCommandEvent& event)
{
	wxString message = _("GetWallpaper");
	message += _("\nVersion: " + m_version);
	message += _("\nAuthor: Erik Welander (Kira)");
	message += _("\nContact:");
	message += _("\nFacebook: https://www.facebook.com/erik.welander");
	message += _("\nEmail: mail@erikwelander.se");
	message += _("\nWeb: http://erikwelander.se/");
	message += _("\nLicence: Creative Commons \"by-nc-nd\"");
	message += _("\n\nThis program is designed for users with large amounts of wallpapers across several screens.");
	message += _("\nIt decodes the absolute path to all current wallpapers and presents them as scaled image buttons that opens the refering image in question.");
	wxMessageDialog dialog(NULL, message, m_title + m_version, wxOK | wxICON_INFORMATION);
	dialog.ShowModal();
}
void GUI::onMenuQuit(wxCommandEvent& event)
{
	exit(0);
}
