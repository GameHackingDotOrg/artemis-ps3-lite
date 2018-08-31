/*
 * ProgressMenu.cpp
 *
 *
 *  
 */

#include "Menu/IMenu.hpp"
#include "Menu/Menus.hpp"
#include "Globals.hpp"
#include "IO/UTF8.hpp"
#include <math.h>

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
	_detailKey(0),
	_callback(callback),
	_userData(userData),
	_length(length),
	_index(0),
	_failed(false)
	{
		if (!_mini || !_windowManager || !_windowManager->GetLocale())
			return;

		// Set dimensions
		_dimWheel.Set(0.1, 0.1);

		// Set locations
		_locGeneric.Set(0.5, 0.35);
		_locWheel.Set(0.5, 0.5);
		_locPercent.Set(0.5, 0.5);
		_locDetail.Set(0.5, 0.65);


		// Translate location and dimension to screen space
		LOC_TO_SCREEN(_locGeneric, _mini);
		LOC_TO_SCREEN(_locWheel, _mini);
		LOC_TO_SCREEN(_locPercent, _mini);
		LOC_TO_SCREEN(_locDetail, _mini);

		DIM_TO_SCREEN(_dimWheel, _mini);
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
		int rgba = _failed ? 0x9D000000 : 0x1A000000, a = 0x00;
		
		if (!TEX_BGIMG || !TEX_CIRCLE_LOADING_BG || !TEX_CIRCLE_ERROR_DARK || !TEX_CIRCLE_LOADING_SEEK || !_windowManager || !_windowManager->GetLocale() || !(font = _windowManager->GetFont()))
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

		// Draw Generic message
		font->TextAlign = Font::PRINT_ALIGN_CENTER;
		font->ForeColor = rgba | a;
		font->PrintLine(_windowManager->GetLocale()->GetValue(_failed ? LOCALE_PRG_GENERIC_ERROR : LOCALE_PRG_GENERIC), NULL, _locGeneric, FONT_MEDIUM);

		// Draw Wheel
		if (!_failed)
		{
			TEX_CIRCLE_LOADING_BG->DrawRegion.Location.Set(_locWheel);
			TEX_CIRCLE_LOADING_BG->DrawRegion.Dimension.Set(_dimWheel);
			TEX_CIRCLE_LOADING_BG->Draw(rgba | a);

			TEX_CIRCLE_LOADING_SEEK->DrawRegion.Location.Set(_locWheel);
			TEX_CIRCLE_LOADING_SEEK->DrawRegion.Dimension.Set(_dimWheel);
			TEX_CIRCLE_LOADING_SEEK->DrawRegion.RectangleAngle = fmod(TEX_CIRCLE_LOADING_SEEK->DrawRegion.RectangleAngle - (deltaTime * 100), 360.0);
			TEX_CIRCLE_LOADING_SEEK->Draw(rgba | a);

			// Draw Percent message
			font->PrintFormat(_locPercent, FONT_MEDIUM, false, false, 10, L"%.0f%c", 100 * (float)_index / (float)(_length <= 0 ? 1 : _length), '\045');
		}
		else 
		{
			TEX_CIRCLE_ERROR_DARK->DrawRegion.Location.Set(_locWheel);
			TEX_CIRCLE_ERROR_DARK->DrawRegion.Dimension.Set(_dimWheel);
			TEX_CIRCLE_ERROR_DARK->Draw(0xE4E4E400 | a);
		}

		// Draw Detail message
		if (_detailKey)
			font->PrintLine(_windowManager->GetLocale()->GetValue(*_detailKey), NULL, _locDetail, FONT_MEDIUM);

		// Increment
		if (_index < _length && !_failed && _callback)
		{
			_failed = !_callback(_index++, _length, &_detailKey, _userData);
		}
		else if (!_failed && _callback)
		{
			// Success, exit to proper window
			if (State() == WINDOW_STATE_ACTIVE)
				_windowManager->CloseWindow(Id());
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
