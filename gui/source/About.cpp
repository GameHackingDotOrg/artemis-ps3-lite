/*
 * About.cpp
 *
 *
 *  This menu displays information about Project Artemis and Artemis PS3 Lite.
 */

#include "Menu/IMenu.hpp"
#include "Menu/Menus.hpp"
#include "Menu/Elements/Icon.hpp"
#include "Globals.hpp"
#include "IO/UTF8.hpp"

using namespace Mini2D;

namespace Menu {

	//---------------------------------------------------------------------------
	// Setup all menu variables
	//---------------------------------------------------------------------------
	About::About(Mini * mini,
		WindowManager * windowManager,
		long prevId) :
	_mini(mini),
	_windowManager(windowManager),
	_windowState(WINDOW_STATE_INACTIVE),
	_id(-1),
	_previousId(prevId),
	_windowFrameLabel(IO::UTF8::ToUTF32("v" ARTEMIS_VERSION))
	{
		if (!_mini || !_windowManager || !_windowManager->GetLocale())
			return;

		_windowFrame = new Elements::WindowFrame(_mini, TEX_HEADER_ICO_ABT, _windowManager->GetLocale()->GetValue(LOCALE_GEN_ABOUT), _windowFrameLabel);
	}

	//---------------------------------------------------------------------------
	// Clean up
	//---------------------------------------------------------------------------
	About::~About()
	{
		if (_windowFrame) {
			delete _windowFrame;
			_windowFrame = NULL;
		}
	}

	//---------------------------------------------------------------------------
	// Getters and Setters
	//---------------------------------------------------------------------------
	const WindowState& About::State() const
	{
		return _windowState;
	}

	void About::State(const WindowState& newState)
	{
		_windowState = newState;
	}

	const long& About::Id() const
	{
		return _id;
	}

	void About::Id(const long& newId)
	{
		_id = newId;
	}

	const long& About::PreviousId() const
	{
		return _previousId;
	}

	void About::PreviousId(const long& newPreviousId)
	{
		_previousId = newPreviousId;
	}

	//---------------------------------------------------------------------------
	// Draws the menu
	//---------------------------------------------------------------------------
	void About::Draw(float deltaTime)
	{
		Font * font;

		if (!TEX_BGIMG || !_windowManager || !_windowManager->GetLocale() || !_windowManager->GetFont())
			return;

		font = _windowManager->GetFont();

		// For now we aren't going to have open/closing animations
		// We can just set these to ACTIVE and INACTIVE immediately
		if (State() == WINDOW_STATE_OPENING)
			State(WINDOW_STATE_ACTIVE);
		if (State() == WINDOW_STATE_CLOSING)
			State(WINDOW_STATE_INACTIVE);

		_windowFrame->Draw(font);
	}

	//---------------------------------------------------------------------------
	// Updates the selected icon based on pad input
	//---------------------------------------------------------------------------
	void About::Pad(int port,
		padData pData)
	{
		// Scroll through the list of icons
		if (pData.BTN_CIRCLE) {
			_windowManager->CloseWindow(Id());
		}
	}

	//---------------------------------------------------------------------------
	// Tells the WindowManager that this is not drawn on top of the previous window
	//---------------------------------------------------------------------------
	bool About::IsSubmenu()
	{
		return false;
	}

}
