/*
 * WindowManager.cpp
 *
 *
 *  WindowManager draws the active Window and any parent Windows it may hover over.
 *  It handles all Window transitions.
 */

#include "Menu/WindowManager.hpp"
#include "IO/UTF8.hpp"
#include "Globals.hpp"

using namespace Mini2D;

namespace Menu {

	static long uniqueCounter = 0;

	//---------------------------------------------------------------------------
	// Load up the config, locale, and font
	//---------------------------------------------------------------------------
	WindowManager::WindowManager(Mini * mini) : _mini(mini), _activeWindow(-1) {

		if (!_mini) {
			printf("Artemis Lite::WindowManager::Invalid Mini\n");
			return;
		}

		_config = new Config::Config("artemis-ps3-lite.cfg");
		_locale = NULL;
		_font = NULL;
		_texturePointer = _mini->TexturePointer;

		Update();
	}

	//---------------------------------------------------------------------------
	// Clean up
	//---------------------------------------------------------------------------
	WindowManager::~WindowManager() {

		// Delete all of our windows
		for(std::vector<IMenu *>::iterator it = _windows.begin(); it != _windows.end(); it++)
			if ((*it))
				delete *it;

		// Clear vector
		_windows.clear();

		// Delete our config
		if (_config) {
			delete _config;
			_config = NULL;
		}

		// Delete our config
		if (_locale) {
			delete _locale;
			_locale = NULL;
		}

		if (_font && _font != FONT_DEFAULT) {
			delete _font;
			_font = NULL;

			// Reset RSX texture pointer to before the last font was loaded
			// This allows us to reuse the memory
			_mini->TexturePointer = _texturePointer;
		}
	}

	//---------------------------------------------------------------------------
	// Draws the active window (and any windows it hovers over)
	// Returns true when the main window is closed (signalling to close the app)
	//---------------------------------------------------------------------------
	bool WindowManager::Draw(float deltaTime) {

		IMenu * window = getWindowById(_activeWindow);
		if (!window)
			return false;

		// Find new active window if current is inactive
		if (window->State() == WINDOW_STATE_INACTIVE) {

			// Set window to previous Window
			// The previous Window opened the current (inactive) Window
			window = getWindowById(window->PreviousId());

			// Remove inactive window from _windows
			removeWindowById(_activeWindow);

			// If new window is invalid, we must be closing the entire app
			if (!window)
				return true;

			// Set _activeWindow
			_activeWindow = window->Id();

			// Set WindowState to WINDOW_STATE_OPENING
			window->State(WINDOW_STATE_OPENING);
		}

		// Draw all windows
		recursiveDrawWindows(window, deltaTime);

		return false;
	}

	//---------------------------------------------------------------------------
	// Forwards the pad data to the active Window
	//---------------------------------------------------------------------------
	void WindowManager::Pad(int port, padData * pData) {

		IMenu * window = getWindowById(_activeWindow);
		if (!window)
			return;

		// Send pad input to active window
		window->Pad(port, *pData);
	}

	//---------------------------------------------------------------------------
	// Set WindowState of Window with ID 'id' to WINDOW_STATE_OPENING
	//---------------------------------------------------------------------------
	bool WindowManager::OpenWindow(long id) {

		// Iterate through _windows
		// If a Window's ID matches 'id' then make it active
		for(std::vector<IMenu *>::iterator it = _windows.begin(); it != _windows.end(); it++) {
			if ((*it)->Id() == id) {
				(*it)->State(WINDOW_STATE_OPENING);
				_activeWindow = id;
				return true;
			}
		}

		return false;
	}

	//---------------------------------------------------------------------------
	// Set WindowState of Window with ID 'id' to WINDOW_STATE_CLOSING
	//---------------------------------------------------------------------------
	bool WindowManager::CloseWindow(long id) {

		// Iterate through _windows
		// If a Window's ID matches 'id' then set its state to WINDOW_STATE_CLOSING
		for(std::vector<IMenu *>::iterator it = _windows.begin(); it != _windows.end(); it++) {
			if ((*it)->Id() == id) {
				(*it)->State(WINDOW_STATE_CLOSING);
				return true;
			}
		}

		return false;
	}

	//---------------------------------------------------------------------------
	// Add Window to _windows
	//---------------------------------------------------------------------------
	long WindowManager::AddWindow(Menu::IMenu * window) {

		if (!window)
			return -1;

		// Make sure this window isn't already added
		for(std::vector<IMenu *>::iterator it = _windows.begin(); it != _windows.end(); it++)
			if (*it == window)
				return -2;

		// Set the ID and add to _windows
		window->Id(uniqueCounter++);
		_windows.push_back(window);

		return window->Id();
	}

	//---------------------------------------------------------------------------
	// Update all settings from _config
	//---------------------------------------------------------------------------
	void WindowManager::Update() {
		std::wstring fontPath;

		if (_locale)
			delete _locale;

		if (_font && _font != FONT_DEFAULT) {
			delete _font;
			_font = NULL;

			// Reset RSX texture pointer to before the last font was loaded
			// This allows us to reuse the memory
			_mini->TexturePointer = _texturePointer;
		}

		_locale = new Config::Locale(_config->GetCString("translation"));
		if (_locale) {

			// Load FONT parameter from locale and attempt to load it
			// If it is set to 'default' then load the default font
			if ((fontPath = _locale->GetValue(L"FONT")) != L"default" && fontPath.size() > 0) {
				_font = new Font(_mini);
				if (_font->Load((char*)(ARTEMIS_PATH "Locales/" + IO::UTF8::FromUTF32(fontPath)).c_str(), 48) != Font::FONT_SUCCESS)
					printf("Artemis Lite::WindowManager::Error loading font %s\n", IO::UTF8::FromUTF32(_locale->GetValue(L"FONT")).c_str());

				// Load custom characters into font
				_font->AddChar(CHAR_CROSS, TEX_FOOTER_ICO_CROSS, 4);
				_font->AddChar(CHAR_SQUARE, TEX_FOOTER_ICO_SQUARE, 4);
				_font->AddChar(CHAR_TRIANGLE, TEX_FOOTER_ICO_TRIANGLE, 4);
				_font->AddChar(CHAR_CIRCLE, TEX_FOOTER_ICO_CIRCLE, 4);
				_font->AddChar(CHAR_LEFT, TEX_FOOTER_ICO_LT, 4);
				_font->AddChar(CHAR_RIGHT, TEX_FOOTER_ICO_RT, 4);
			}
			else {
				_font = FONT_DEFAULT;
			}
		}
	}


	//---------------------------------------------------------------------------
	// Get Methods
	//---------------------------------------------------------------------------
	Config::Locale * WindowManager::GetLocale() {

		return _locale;
	}

	Config::Config * WindowManager::GetConfig() {

		return _config;
	}

	Font * WindowManager::GetFont() {

		return _font;
	}


	//---------------------------------------------------------------------------
	// Returns the Window given an ID
	//---------------------------------------------------------------------------
	IMenu * WindowManager::getWindowById(long id) {

		// Iterate through _windows
		// If a Window's ID matches 'id' then return the pointer to the Window
		for(std::vector<IMenu *>::iterator it = _windows.begin(); it != _windows.end(); it++) {
			if ((*it)->Id() == id)
				return *it;
		}

		return NULL;
	}

	//---------------------------------------------------------------------------
	// Removes the window from _windows given an ID
	//---------------------------------------------------------------------------
	void WindowManager::removeWindowById(long id) {

		// Iterate through _windows
		// If a Window's ID matches 'id' then delete that Window and remove it from _windows
		for(std::vector<IMenu *>::iterator it = _windows.begin(); it != _windows.end(); it++) {
			if ((*it)->Id() == id) {
				delete *it;
				_windows.erase(it);
				return;
			}
		}
	}

	//---------------------------------------------------------------------------
	// Draws the previous window if the current window is a submenu
	// It will draw multiple layers of submenus
	//---------------------------------------------------------------------------
	void WindowManager::recursiveDrawWindows(IMenu * window, float deltaTime) {

		if (window->PreviousId() >= 0 && window->IsSubmenu())
			recursiveDrawWindows(getWindowById(window->PreviousId()), deltaTime);

		window->Draw(deltaTime);
	}
}
