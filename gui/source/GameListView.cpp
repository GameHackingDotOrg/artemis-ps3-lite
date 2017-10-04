/*
 * GameListView.cpp
 *
 *
 *  This menu loads and then displays the games list
 */

#include "Menu/IMenu.hpp"
#include "Menu/Menus.hpp"
#include "Menu/Elements/LabelPair.hpp"
#include "Globals.hpp"
#include "IO/UTF8.hpp"

using namespace Mini2D;

namespace Menu
{
	//---------------------------------------------------------------------------
	// Setup all menu variables
	//---------------------------------------------------------------------------
	GameListView::GameListView(Mini * mini, WindowManager * windowManager, long prevId) :
	_mini(mini),
	_windowManager(windowManager),
	_windowState(WINDOW_STATE_INACTIVE),
	_id(-1),
	_previousId(prevId),
	_animationTime(0)
	{
		if (!_mini || !_windowManager || !_windowManager->GetLocale())
			return;

		// Initialize our elements
		_windowFrame = new Elements::WindowFrame(_mini, TEX_HEADER_ICO_ABT, _windowManager->GetLocale()->GetValue(LOCALE_GEN_CHEATS), _windowManager->GetLocale()->GetValue(LOCALE_CHT_GAMELIST));
	}

	//---------------------------------------------------------------------------
	// Clean up
	//---------------------------------------------------------------------------
	GameListView::~GameListView()
	{
		if (_windowFrame)
		{
			delete _windowFrame;
			_windowFrame = NULL;
		}
	}

	//---------------------------------------------------------------------------
	// Getters and Setters
	//---------------------------------------------------------------------------
	const WindowState& GameListView::State() const
	{
		return _windowState;
	}

	void GameListView::State(const WindowState& newState)
	{
		_windowState = newState;
	}

	const long& GameListView::Id() const
	{
		return _id;
	}

	void GameListView::Id(const long& newId)
	{
		_id = newId;
	}

	const long& GameListView::PreviousId() const
	{
		return _previousId;
	}

	void GameListView::PreviousId(const long& newPreviousId)
	{
		_previousId = newPreviousId;
	}

	//---------------------------------------------------------------------------
	// Draws the menu
	//---------------------------------------------------------------------------
	void GameListView::Draw(float deltaTime)
	{
		Font * font;
		int x = 0, rgba = 0x1A000000, a = 0x00;

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

		// Draw the window frame first
		_windowFrame->Draw(font, rgba | a);
	}

	//---------------------------------------------------------------------------
	// Close the window if Circle is pressed
	//---------------------------------------------------------------------------
	void GameListView::Pad(int port, padData pData)
	{
		// Scroll through the list of icons
		if (pData.BTN_CIRCLE)
			_windowManager->CloseWindow(Id());
	}

	//---------------------------------------------------------------------------
	// Tells the WindowManager that this is not drawn on top of the previous window
	//---------------------------------------------------------------------------
	bool GameListView::IsSubmenu()
	{
		return false;
	}

}
