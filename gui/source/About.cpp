/*
 * About.cpp
 *
 *
 *  This menu displays information about Project Artemis and Artemis PS3 Lite.
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
	About::About(Mini * mini, WindowManager * windowManager, long prevId) :
	_mini(mini),
	_windowManager(windowManager),
	_windowState(WINDOW_STATE_INACTIVE),
	_id(-1),
	_previousId(prevId),
	_windowFrameLabel(IO::UTF8::ToUTF32("v" ARTEMIS_VERSION))
	{
		if (!_mini || !_windowManager || !_windowManager->GetLocale())
			return;

		// Initialize our elements
		_windowFrame = new Elements::WindowFrame(_mini, TEX_HEADER_ICO_ABT, _windowManager->GetLocale()->GetValue(LOCALE_GEN_ABOUT), _windowFrameLabel);
		_lpThank = new Elements::LabelPair(_windowManager->GetLocale()->GetValue(LOCALE_ABT_THANKS), _windowManager->GetLocale()->GetValue(LOCALE_ABT_ARTEMIS));
		_lpLearn = new Elements::LabelPair(_windowManager->GetLocale()->GetValue(LOCALE_ABT_LEARN), GENERAL_ARTEMIS_LINK);
		_lpContribute = new Elements::LabelPair(_windowManager->GetLocale()->GetValue(LOCALE_ABT_CONTRIBUTE), GENERAL_GITHUB_LINK);

		// Set locations
		_lpThank->Location.Set(0.5, 0.135);
		_lpLearn->Location.Set(0.5, 0.925);
		_lpContribute->Location.Set(0.5, 0.275);
		_locContributors.Set(0.5, 0.4);

		// Set font sizes
		_lpThank->FontSizeTop = FONT_LARGE;
		_lpThank->FontSizeBottom = FONT_MEDIUM;
		_lpLearn->FontSizeTop = FONT_MEDIUM;
		_lpLearn->FontSizeBottom = FONT_SMALL;
		_lpContribute->FontSizeTop = FONT_MEDIUM;
		_lpContribute->FontSizeBottom = FONT_SMALL;

		// Translate to screen space
		LOC_TO_SCREEN(_lpThank->Location, _mini);
		LOC_TO_SCREEN(_lpLearn->Location, _mini);
		LOC_TO_SCREEN(_lpContribute->Location, _mini);
		LOC_TO_SCREEN(_locContributors, _mini);
	}

	//---------------------------------------------------------------------------
	// Clean up
	//---------------------------------------------------------------------------
	About::~About()
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
		int x = 0;
		Vector2 locContributors = Vector2(_locContributors.X, _locContributors.Y + (FONT_MEDIUM * 1.25));

		if (!TEX_BGIMG || !_windowManager || !_windowManager->GetLocale() || !(font = _windowManager->GetFont()))
			return;

		// For now we aren't going to have open/closing animations
		// We can just set these to ACTIVE and INACTIVE immediately
		if (State() == WINDOW_STATE_OPENING)
			State(WINDOW_STATE_ACTIVE);
		if (State() == WINDOW_STATE_CLOSING)
			State(WINDOW_STATE_INACTIVE);

		// Draw the window frame first
		_windowFrame->Draw(font);

		// Draw our label pairs
		_lpThank->Draw(font, font, 0x000000FF, _lpThank->FontSizeBottom * 0.25);
		_lpContribute->Draw(font, FONT_DEFAULT, 0x000000FF, _lpContribute->FontSizeBottom * 0.25);
		_lpLearn->Draw(font, FONT_DEFAULT, 0x000000FF, _lpLearn->FontSizeBottom * 0.25);

		// Finally we can draw our contributors list
		font->PrintLine(_windowManager->GetLocale()->GetValue(LOCALE_ABT_CONTRIBUTORS), NULL, _locContributors, FONT_MEDIUM);

		// Loop through the array and print name
		while (CONTRIBUTORS[x] != L"")
		{
			// Draw name
			FONT_DEFAULT->TextAlign = Font::PRINT_ALIGN_CENTER;
			FONT_DEFAULT->ForeColor = 0x000000FF;
			FONT_DEFAULT->PrintLine(CONTRIBUTORS[x], NULL, locContributors, FONT_SMALL);

			// Increment
			locContributors.Y += FONT_SMALL * 1.25;
			x++;
		}
	}

	//---------------------------------------------------------------------------
	// Close the window if Circle is pressed
	//---------------------------------------------------------------------------
	void About::Pad(int port, padData pData)
	{
		// Scroll through the list of icons
		if (pData.BTN_CIRCLE)
			_windowManager->CloseWindow(Id());
	}

	//---------------------------------------------------------------------------
	// Tells the WindowManager that this is not drawn on top of the previous window
	//---------------------------------------------------------------------------
	bool About::IsSubmenu()
	{
		return false;
	}

}
