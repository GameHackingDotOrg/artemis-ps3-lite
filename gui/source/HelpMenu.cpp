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
	HelpMenu::HelpMenu(Mini * mini, WindowManager * windowManager, long prevId, int mCross, int mCirc, int mTri, int mSqr, int mR1, int mL1, int mStart, int mSel, int mNav) :
	_mini(mini),
	_windowManager(windowManager),
	_windowState(WINDOW_STATE_INACTIVE),
	_id(-1),
	_previousId(prevId),
	_animationTime(0),
	_mCross(mCross),
	_mCirc(mCirc),
	_mTri(mTri),
	_mSqr(mSqr),
	_mR1(mR1),
	_mL1(mL1),
	_mStart(mStart),
	_mSel(mSel),
	_mNav(mNav)
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
		int rgba = 0xFFECDE00, a = 0x00;

		if (!TEX_HELP || !_windowManager || !_windowManager->GetLocale() || !(font = _windowManager->GetFont()))
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

		// Draw controller
		TEX_HELP->DrawRegion.Location.Set(0.5 * _mini->MAXW, 0.5 * _mini->MAXH);
		TEX_HELP->DrawRegion.Dimension.Set((_mini->MAXH * (float)TEX_HELP->GetWidth()) / (float)TEX_HELP->GetHeight(), _mini->MAXH);
		TEX_HELP->Draw(0xFFFFFF00 | a);

		// Draw mappings
		drawMap(font, FONT_MEDIUM, 0.53101851, 454.5/1080.0, _mNav, rgba | a);
		drawMap(font, FONT_MEDIUM, 0.87407407, 324.5/1080.0, _mSel, rgba | a);
		drawMap(font, FONT_MEDIUM, 0.87361111, 739.5/1080.0, _mStart, rgba | a);
		drawMap(font, FONT_MEDIUM, 1.23657407, 324.5/1080.0, _mR1, rgba | a);
		drawMap(font, FONT_MEDIUM, 0.61342592, 269.5/1080.0, _mL1, rgba | a);
		drawMap(font, FONT_MEDIUM, 1.08981481, 738.5/1080.0, _mCross, rgba | a);
		drawMap(font, FONT_MEDIUM, 1.17222222, 643.5/1080.0, _mCirc, rgba | a);
		drawMap(font, FONT_MEDIUM, 1.30555555, 436.5/1080.0, _mTri, rgba | a);
		drawMap(font, FONT_MEDIUM, 1.04120370, 324.5/1080.0, _mSqr, rgba | a);
	}

	void HelpMenu::drawMap(Font * font, float fontSize, float x, float y, int map, unsigned int RGBA)
	{
		Vector2 drawLoc = Vector2(x * _mini->MAXH, (y * _mini->MAXH) - (fontSize * 0.6));

		font->TextAlign = Font::PRINT_ALIGN_TOPCENTER;
		font->ForeColor = RGBA;
		font->PrintLine(_windowManager->GetLocale()->GetValue(LOCALE_HLP[map]), NULL, drawLoc, fontSize);
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
