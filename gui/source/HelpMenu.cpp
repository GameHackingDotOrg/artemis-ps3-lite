/*
 * HelpMenu.cpp
 *
 *
 *  This menu displays controller mappings
 */

#include "Menu/IMenu.hpp"
#include "Menu/Menus.hpp"
#include "Globals.hpp"
#include "IO/UTF8.hpp"

using namespace Mini2D;

namespace Menu
{
	//---------------------------------------------------------------------------
	// Setup all menu variables
	//---------------------------------------------------------------------------
	HelpMenu::HelpMenu(Mini * mini, WindowManager * windowManager, long prevId) :
	_mini(mini),
	_windowManager(windowManager),
	_windowState(WINDOW_STATE_INACTIVE),
	_id(-1),
	_previousId(prevId),
	_animationTime(0)
	{
		if (!_mini || !_windowManager || !_windowManager->GetLocale())
			return;
	}

	//---------------------------------------------------------------------------
	// Clean up
	//---------------------------------------------------------------------------
	HelpMenu::~HelpMenu()
	{

	}

	//---------------------------------------------------------------------------
	// Getters and Setters
	//---------------------------------------------------------------------------
	const WindowState& HelpMenu::State() const
	{
		return _windowState;
	}

	void HelpMenu::State(const WindowState& newState)
	{
		_windowState = newState;
	}

	const long& HelpMenu::Id() const
	{
		return _id;
	}

	void HelpMenu::Id(const long& newId)
	{
		_id = newId;
	}

	const long& HelpMenu::PreviousId() const
	{
		return _previousId;
	}

	void HelpMenu::PreviousId(const long& newPreviousId)
	{
		_previousId = newPreviousId;
	}

	//---------------------------------------------------------------------------
	// Draws the menu
	//---------------------------------------------------------------------------
	void HelpMenu::Draw(float deltaTime)
	{
		Font * font;
		int rgba = 0x1A000000, a = 0x00;

		if (!TEX_BGIMG || !_windowManager || !_windowManager->GetLocale() || !(font = _windowManager->GetFont()))
			return;


		// Set rgba based on window state and how long we've been in that state
		switch (State())
		{
			case WINDOW_STATE_OPENING:
				a = ANI_TIME_TO_A(_animationTime, MENU_ANIMATION_DURATION);

				if ((_animationTime += deltaTime) > MENU_ANIMATION_DURATION)
					State(WINDOW_STATE_ACTIVE);
				break;
			case WINDOW_STATE_CLOSING:
				a = ANI_TIME_TO_A(MENU_ANIMATION_DURATION - _animationTime, MENU_ANIMATION_DURATION);

				if ((_animationTime += deltaTime) > MENU_ANIMATION_DURATION)
					State(WINDOW_STATE_INACTIVE);
				break;
			case WINDOW_STATE_ACTIVE:
			case WINDOW_STATE_INACTIVE:
				_animationTime = 0;
				a = 0xFF;
				break;
		}
	}

	//---------------------------------------------------------------------------
	// Close the window if Circle is pressed
	//---------------------------------------------------------------------------
	void HelpMenu::Pad(int port, padData pData)
	{
		// Scroll through the list of icons
		if (pData.BTN_CIRCLE)
			_windowManager->CloseWindow(Id());
	}

	//---------------------------------------------------------------------------
	// Tells the WindowManager that this is not drawn on top of the previous window
	//---------------------------------------------------------------------------
	bool HelpMenu::IsSubmenu()
	{
		return true;
	}

}
