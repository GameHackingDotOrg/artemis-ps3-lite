/*
 * Start.cpp
 *
 *
 *  Start is the initial menu displayed to the user.
 *  It displays the base icons to navigate throughout Artemis Lite.
 */

#include "Menu/IMenu.hpp"
#include "Menu/Menus.hpp"
#include "Menu/Elements/Icon.hpp"
#include "Globals.hpp"

using namespace Mini2D;

namespace Menu
{
	//---------------------------------------------------------------------------
	// Setup all menu variables
	//---------------------------------------------------------------------------
	Start::Start(Mini * mini, WindowManager * windowManager, long prevId) :
	_mini(mini),
	_windowManager(windowManager),
	_windowState(WINDOW_STATE_INACTIVE),
	_id(-1),
	_previousId(prevId),
	_selectedIndex(0)
	{
		if (!_mini || !_windowManager)
			return;

		// Define our icon font size
		_fontIco = FONT_MEDIUM;

		// Set dimensions
		_dimIco.Set(0.09375, 0.075);
		_dimLogo.Set(0.6, 0.105);
		_dimLabel.Set(0.425, 0.025);
		_dimLink.Set(0.3, 0.02);

		// Set locations
		_locLogo.Set(0.5, 0.25);
		_locLabel.Set(0.5, _dimLabel.Y);
		_locLink.Set(0.5, 0.96);
		_locXmb.Set(0.3, 0.6);
		_locCht.Set(0.433, 0.6);
		_locOpt.Set(0.558, 0.6);
		_locAbt.Set(0.7, 0.6);

		// Initialize our icons
		_iconXmb  = new Elements::Icon(TEX_TITLESCR_ICO_XMB, _windowManager->GetLocale()->GetValue(LOCALE_GEN_LAUNCH));
		_iconCht  = new Elements::Icon(TEX_TITLESCR_ICO_CHT, _windowManager->GetLocale()->GetValue(LOCALE_GEN_CHEATS));
		_iconOpt  = new Elements::Icon(TEX_TITLESCR_ICO_OPT, _windowManager->GetLocale()->GetValue(LOCALE_GEN_OPTIONS));
		_iconAbt  = new Elements::Icon(TEX_TITLESCR_ICO_ABT, _windowManager->GetLocale()->GetValue(LOCALE_GEN_ABOUT));

		// Translate location and dimension to screen space
		LOC_TO_SCREEN(_locLogo, _mini);
		LOC_TO_SCREEN(_locLabel, _mini);
		LOC_TO_SCREEN(_locLink, _mini);
		LOC_TO_SCREEN(_locXmb, _mini);
		LOC_TO_SCREEN(_locCht, _mini);
		LOC_TO_SCREEN(_locOpt, _mini);
		LOC_TO_SCREEN(_locAbt, _mini);

		DIM_TO_SCREEN(_dimIco, _mini);
		DIM_TO_SCREEN(_dimLogo, _mini);
		DIM_TO_SCREEN(_dimLabel, _mini);
		DIM_TO_SCREEN(_dimLink, _mini);

		// Move the description label down below the logo
		_locLabel.Y += _locLogo.Y + _dimLogo.Y * 0.5;
	}

	//---------------------------------------------------------------------------
	// Clean up
	//---------------------------------------------------------------------------
	Start::~Start()
	{
		// Delete all our allocations
		if (_iconXmb)
		{
			delete _iconXmb;
			_iconXmb = NULL;
		}

		if (_iconCht)
		{
			delete _iconXmb;
			_iconXmb = NULL;
		}

		if (_iconOpt)
		{
			delete _iconOpt;
			_iconOpt = NULL;
		}

		if (_iconAbt)
		{
			delete _iconAbt;
			_iconAbt = NULL;
		}
	}

	//---------------------------------------------------------------------------
	// Getters and Setters
	//---------------------------------------------------------------------------
	const WindowState& Start::State() const
	{
		return _windowState;
	}

	void Start::State(const WindowState& newState)
	{
		_windowState = newState;
	}

	const long& Start::Id() const
	{
		return _id;
	}

	void Start::Id(const long& newId)
	{
		_id = newId;
	}

	const long& Start::PreviousId() const
	{
		return _previousId;
	}

	void Start::PreviousId(const long& newPreviousId)
	{
		_previousId = newPreviousId;
	}

	//---------------------------------------------------------------------------
	// Draws the menu
	//---------------------------------------------------------------------------
	void Start::Draw(float deltaTime)
	{
		Font * font;

		if (!TEX_BGIMG || !_iconXmb || !_iconCht || !_iconOpt || !_iconAbt || !_windowManager || !_windowManager->GetLocale() || !_windowManager->GetFont())
			return;

		font = _windowManager->GetFont();

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

		// Draw logo and logo label
		TEX_TITLESCR_LOGO->DrawRegion.Location.Set(_locLogo);
		TEX_TITLESCR_LOGO->DrawRegion.Dimension.Set(_dimLogo);
		TEX_TITLESCR_LOGO->Draw(0x000000FF);

		TEX_TITLESCR_LABEL->DrawRegion.Location.Set(_locLabel);
		TEX_TITLESCR_LABEL->DrawRegion.Dimension.Set(_dimLabel);
		TEX_TITLESCR_LABEL->Draw(0x000000FF);

		// Print icons
		_iconXmb->Location.Set(_locXmb);
		_iconXmb->Dimension.Set(_dimIco);
		_iconXmb->FontSize = _fontIco;
		_iconXmb->LabelOffset.Set(0.0025 * _mini->MAXW, 0);
		_iconXmb->Draw(font, _selectedIndex == 0 ? MENU_SELECTED : MENU_UNSELECTED);

		_iconCht->Location.Set(_locCht);
		_iconCht->Dimension.Set(_dimIco);
		_iconCht->FontSize = _fontIco;
		_iconCht->LabelOffset.Set(0.0025 * _mini->MAXW, 0);
		_iconCht->Draw(font, _selectedIndex == 1 ? MENU_SELECTED : MENU_UNSELECTED);

		_iconOpt->Location.Set(_locOpt);
		_iconOpt->Dimension.Set(_dimIco);
		_iconOpt->FontSize = _fontIco;
		_iconOpt->LabelOffset.Set(0.01 * _mini->MAXW, 0);
		_iconOpt->Draw(font, _selectedIndex == 2 ? MENU_SELECTED : MENU_UNSELECTED);

		_iconAbt->Location.Set(_locAbt);
		_iconAbt->Dimension.Set(_dimIco);
		_iconAbt->FontSize = _fontIco;
		_iconAbt->Draw(font, _selectedIndex == 3 ? MENU_SELECTED : MENU_UNSELECTED);

		// Print link
		TEX_TITLESCR_LINK->DrawRegion.Location.Set(_locLink);
		TEX_TITLESCR_LINK->DrawRegion.Dimension.Set(_dimLink);
		TEX_TITLESCR_LINK->Draw(0x000000FF);
	}

	//---------------------------------------------------------------------------
	// Updates the selected icon based on pad input
	//---------------------------------------------------------------------------
	void Start::Pad(int port, padData pData)
	{

		// Scroll through the list of icons
		if (pData.BTN_LEFT && !pData.BTN_RIGHT)
		{
			_selectedIndex--;
			if (_selectedIndex < 0)
				_selectedIndex = 3;
		}
		else if (pData.BTN_RIGHT && !pData.BTN_LEFT)
		{
			_selectedIndex++;
			if (_selectedIndex > 3)
				_selectedIndex = 0;
		}
		else if (pData.BTN_CROSS && State() == WINDOW_STATE_ACTIVE)
		{
			switch (_selectedIndex)
			{
				case 3:
					_windowManager->OpenWindow(_windowManager->AddWindow(new Menu::About(_mini, _windowManager, Id())));
					break;
			}
		}
	}

	//---------------------------------------------------------------------------
	// Tells the WindowManager that this is not drawn on top of the previous window
	//---------------------------------------------------------------------------
	bool Start::IsSubmenu()
	{
		return false;
	}

}
