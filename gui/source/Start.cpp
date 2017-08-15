/*
 * Start.cpp
 *
 * 
 *  Start is the initial menu displayed to the user.
 *  It displays the base icons to navigate throughout Artemis Lite.
 */

#include "Menu/IMenu.hpp"					// IMenu declaration
#include "Menu/Menus.hpp"					// Start declaration
#include "Menu/Elements/Icon.hpp"			// Icon declaration
#include "Globals.hpp"						// Images, LocToScreen(), DimToScreen(), LOC_CENTER, DIM_FULL, Font Sizes

namespace Menu
{
	//---------------------------------------------------------------------------
	// Text
	//---------------------------------------------------------------------------
	static std::wstring textLogo = 				L"Playstation 3 Hacking System";
	static std::wstring textLink = 				L"www.gamehacking.org/artemis";
	static std::wstring textXmb = 				L"Start Game";
	static std::wstring textCht = 				L"Cheats";
	static std::wstring textOpt = 				L"Options";
	static std::wstring textAbt = 				L"About";

	//---------------------------------------------------------------------------
	// Constructor and Deconstructor
	//---------------------------------------------------------------------------
	Start::Start(Mini2D * mini, WindowManager * windowManager, long prevId) : _mini(mini), _windowManager(windowManager), _windowState(WINDOW_STATE_INACTIVE), _id(-1), _previousId(prevId), _selectedIndex(0) {

		if (!_mini || !_windowManager)
			return;

		// Define out icon font size
		_fontIco = FONT_SMALL * 2;

		// Set locations
		_locLogo.Set(0.5, 0.25);
		_locXmb.Set(0.3, 0.6);
		_locCht.Set(0.433, 0.6);
		_locOpt.Set(0.558, 0.6);
		_locAbt.Set(0.7, 0.6);
		_locLink.Set(0.5, 0.96);

		_dimIco.Set(0.09375, 0.075);
		_dimLogo.Set(0.6, 0.105);

		// Initialize our icons
		_iconLogo = new Elements::Icon(TEX_TITLESCR_LOGO,    FONT_COMFORTAA_LIGHT, textLogo);
		_iconXmb  = new Elements::Icon(TEX_TITLESCR_ICO_XMB, FONT_COMFORTAA_BOLD,  textXmb);
		_iconCht  = new Elements::Icon(TEX_TITLESCR_ICO_CHT, FONT_COMFORTAA_BOLD,  textCht);
		_iconOpt  = new Elements::Icon(TEX_TITLESCR_ICO_OPT, FONT_COMFORTAA_BOLD,  textOpt);
		_iconAbt  = new Elements::Icon(TEX_TITLESCR_ICO_ABT, FONT_COMFORTAA_BOLD,  textAbt);

		// Translate location and dimension to screen space
		LocToScreen(_locLogo);
		LocToScreen(_locXmb);
		LocToScreen(_locCht);
		LocToScreen(_locOpt);
		LocToScreen(_locAbt);
		LocToScreen(_locLink);

		DimToScreen(_dimIco);
		DimToScreen(_dimLogo);
	}

	Start::~Start() {

		// Delete all our allocations
		if (_iconXmb) {
			delete _iconXmb;
			_iconXmb = NULL;
		}

		if (_iconCht) {
			delete _iconXmb;
			_iconXmb = NULL;
		}

		if (_iconOpt) {
			delete _iconOpt;
			_iconOpt = NULL;
		}

		if (_iconAbt) {
			delete _iconAbt;
			_iconAbt = NULL;
		}
	}

	//---------------------------------------------------------------------------
	// Getters and Setters
	//---------------------------------------------------------------------------
	const WindowState& Start::State() const {
		return _windowState;
	}

	void Start::State(const WindowState& newState) {
		_windowState = newState;
	}

	const long& Start::Id() const {
		return _id;
	}

	void Start::Id(const long& newId) {
		_id = newId;
	}

	const long& Start::PreviousId() const {
		return _previousId;
	}

	void Start::PreviousId(const long& newPreviousId) {
		_previousId = newPreviousId;
	}

	//---------------------------------------------------------------------------
	// Draw() and Pad()
	//---------------------------------------------------------------------------
	void Start::Draw(float deltaTime) {

		if (!TEX_BGIMG || !_iconLogo || !_iconXmb || !_iconCht || !_iconOpt || !_iconAbt)
			return;

		// For now we aren't going to have open/closing animations
		// We can just set these to ACTIVE and INACTIVE immediately
		if (State() == WINDOW_STATE_OPENING)
			State(WINDOW_STATE_ACTIVE);
		if (State() == WINDOW_STATE_CLOSING)
			State(WINDOW_STATE_INACTIVE);

		// Draw Background
		TEX_BGIMG->DrawRegion.Location.Set(LOC_CENTER);
		TEX_BGIMG->DrawRegion.Dimension.Set(DIM_FULL);
		TEX_BGIMG->Draw();

		// Print icons
		_iconLogo->Location.Set(_locLogo);
		_iconLogo->Dimension.Set(_dimLogo);
		_iconLogo->FontSize.Set(FONT_MEDIUM);
		_iconLogo->Draw();

		_iconXmb->Location.Set(_locXmb);
		_iconXmb->Dimension.Set(_dimIco);
		_iconXmb->FontSize.Set(_fontIco);
		_iconXmb->Draw(_selectedIndex == 0 ? MENU_SELECTED : MENU_UNSELECTED);

		_iconCht->Location.Set(_locCht);
		_iconCht->Dimension.Set(_dimIco);
		_iconCht->FontSize.Set(_fontIco);
		_iconCht->Draw(_selectedIndex == 1 ? MENU_SELECTED : MENU_UNSELECTED);

		_iconOpt->Location.Set(_locOpt);
		_iconOpt->Dimension.Set(_dimIco);
		_iconOpt->FontSize.Set(_fontIco);
		_iconOpt->LabelOffset.Set(0.01 * _mini->MAXW, 0);
		_iconOpt->Draw(_selectedIndex == 2 ? MENU_SELECTED : MENU_UNSELECTED);

		_iconAbt->Location.Set(_locAbt);
		_iconAbt->Dimension.Set(_dimIco);
		_iconAbt->FontSize.Set(_fontIco);
		_iconAbt->Draw(_selectedIndex == 3 ? MENU_SELECTED : MENU_UNSELECTED);

		// Print link
		FONT_COMFORTAA_LIGHT->TextAlign = Font::PRINT_ALIGN_BOTTOMCENTER;
		FONT_COMFORTAA_LIGHT->PrintLine(NULL, &textLink, NULL, _locLink, FONT_SMALL * 2.5);
	}

	void Start::Pad(int port, padData pData) {

		// Scroll through the list of icons
		if (pData.BTN_LEFT && !pData.BTN_RIGHT) {
			_selectedIndex--;
			if (_selectedIndex < 0)
				_selectedIndex = 3;
		}
		else if (pData.BTN_RIGHT && !pData.BTN_LEFT) {
			_selectedIndex++;
			if (_selectedIndex > 3)
				_selectedIndex = 0;
		}
	}

	//---------------------------------------------------------------------------
	// Misc
	//---------------------------------------------------------------------------
	bool Start::IsSubmenu() {
		return false;
	}

}
