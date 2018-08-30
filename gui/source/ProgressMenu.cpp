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
	ProgressMenu::ProgressMenu(Mini * mini, WindowManager * windowManager, long successId, long failId, IncrementCallback_t callback, void * userData, unsigned long length) :
	_mini(mini),
	_windowManager(windowManager),
	_windowState(WINDOW_STATE_INACTIVE),
	_id(-1),
	_previousId(successId),
	_failId(failId),
	_animationTime(0),
	_callback(callback),
	_userData(userData),
	_length(length),
	_index(0),
	_failed(false)
	{
		if (!_mini || !_windowManager || !_windowManager->GetLocale())
			return;
	}

	//---------------------------------------------------------------------------
	// Clean up
	//---------------------------------------------------------------------------
	ProgressMenu::~ProgressMenu()
	{

	}

	//---------------------------------------------------------------------------
	// Getters and Setters
	//---------------------------------------------------------------------------
	const WindowState& ProgressMenu::State() const
	{
		return _windowState;
	}

	void ProgressMenu::State(const WindowState& newState)
	{
		_windowState = newState;
	}

	const long& ProgressMenu::Id() const
	{
		return _id;
	}

	void ProgressMenu::Id(const long& newId)
	{
		_id = newId;
	}

	const long& ProgressMenu::PreviousId() const
	{
		return _previousId;
	}

	void ProgressMenu::PreviousId(const long& newPreviousId)
	{
		_previousId = newPreviousId;
	}

	//---------------------------------------------------------------------------
	// Draws the menu
	//---------------------------------------------------------------------------
	void ProgressMenu::Draw(float deltaTime)
	{
		Font * font;
		int rgba = 0xFFECDE00, a = 0x00;

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

		// Draw Background
		TEX_BGIMG->DrawRegion.Location.Set(LOC_CENTER);
		TEX_BGIMG->DrawRegion.Dimension.Set(DIM_FULL);
		TEX_BGIMG->Draw();


		if (_index > _length && !_failed && _callback)
		{
			_failed = !_callback(_userData, _length, _index++);
		}
	}

	//---------------------------------------------------------------------------
	// Close the window if Circle is pressed
	//---------------------------------------------------------------------------
	void ProgressMenu::Pad(int port, padData pData)
	{
		// Force close this menu and open the 'fail' window
		if (pData.BTN_CIRCLE)
		{
			// If they are the same we don't need to close the success window too (that would error)
			if (_failId != PreviousId())
			{
				// Close the success window and set the new PreviousId to the fail window's id
				_windowManager->CloseWindow(PreviousId());
				PreviousId(_failId);
			}

			// Close this window (which will open the fail window)
			_windowManager->CloseWindow(Id());
		}
	}

	//---------------------------------------------------------------------------
	// Tells the WindowManager that this is not drawn on top of the previous window
	//---------------------------------------------------------------------------
	bool ProgressMenu::IsSubmenu()
	{
		return true;
	}

}
