/*
 * WindowManager.cpp
 *
 * 
 *  WindowManager draws the active Window and any parent Windows it may hover over.
 *  It handles all Window transitions.
 */

#include "Menu/WindowManager.hpp"			// WindowManager class

namespace Menu {

	static long uniqueCounter = 0;

	WindowManager::WindowManager() : _activeWindow(-1) {

	}

	WindowManager::~WindowManager() {
		
		// Delete all of our windows
		for(std::vector<IMenu *>::iterator it = _windows.begin(); it != _windows.end(); it++)
			if ((*it))
				delete *it;

		// Clear vector
		_windows.clear();
	}

	// Draws the active window (and any windows it hovers over)
	// Returns true when the main window is closed (signalling to close the app)
	bool WindowManager::Draw(float deltaTime) {

		IMenu * window = getWindowById(_activeWindow);

		if (!window)
			return false;

		// Find new active window if current is inactive
		if (window->State == WINDOW_STATE_INACTIVE) {

			// Set window to previous Window
			// The previous Window opened the current (inactive) Window
			window = getWindowById(window->PreviousID);
			
			// Remove inactive window from _windows
			removeWindowById(_activeWindow);

			// If new window is invalid, we must be closing the entire app
			if (!window)
				return true;

			// Set _activeWindow
			_activeWindow = window->ID;

			// Set WindowState to WINDOW_STATE_OPENING
			window->State = WINDOW_STATE_OPENING;
		}

		// Draw all windows
		recursiveDrawWindows(window, deltaTime);

		return false;
	}

	// Forwards the pad data to the active Window
	void WindowManager::Pad(int port, padData * pData) {

		IMenu * window = getWindowById(_activeWindow);

		if (!window)
			return;

		// Send pad input to active window
		window->Pad(port, *pData);
	}

	// Set WindowState of Window with ID 'id' to WINDOW_STATE_OPENING
	bool WindowManager::OpenWindow(long id) {

		// Iterate through _windows
		// If a Window's ID matches 'id' then make it active
		for(std::vector<IMenu *>::iterator it = _windows.begin(); it != _windows.end(); it++) {
			if ((*it)->ID == id) {
				(*it)->State = WINDOW_STATE_OPENING;
				_activeWindow = id;
				return true;
			}
		}

		return false;
	}

	// Set WindowState of Window with ID 'id' to WINDOW_STATE_CLOSING
	bool WindowManager::CloseWindow(long id) {

		// Iterate through _windows
		// If a Window's ID matches 'id' then set its state to WINDOW_STATE_CLOSING
		for(std::vector<IMenu *>::iterator it = _windows.begin(); it != _windows.end(); it++) {
			if ((*it)->ID == id) {
				(*it)->State = WINDOW_STATE_CLOSING;
				return true;
			}
		}

		return false;
	}

	// Add Window to _windows
	long WindowManager::AddWindow(Menu::IMenu * window) {

		if (!window)
			return -1;

		// Make sure this window isn't already added
		for(std::vector<IMenu *>::iterator it = _windows.begin(); it != _windows.end(); it++)
			if (*it == window)
				return -2;

		// Set the ID and add to _windows
		window->ID = uniqueCounter++;
		_windows.push_back(window);

		return window->ID;
	}

	// Returns the Window given an ID
	IMenu * WindowManager::getWindowById(long id) {

		// Iterate through _windows
		// If a Window's ID matches 'id' then return the pointer to the Window
		for(std::vector<IMenu *>::iterator it = _windows.begin(); it != _windows.end(); it++) {
			if ((*it)->ID == id)
				return *it;
		}

		return NULL;
	}

	// Removes the window from _windows given an ID
	void WindowManager::removeWindowById(long id) {

		// Iterate through _windows
		// If a Window's ID matches 'id' then delete that Window and remove it from _windows
		for(std::vector<IMenu *>::iterator it = _windows.begin(); it != _windows.end(); it++) {
			if ((*it)->ID == id) {
				delete *it;
				_windows.erase(it);
				return;
			}
		}
	}

	// Draws the previous window if the current window is a submenu
	// It will draw multiple layers of submenus
	void WindowManager::recursiveDrawWindows(IMenu * window, float deltaTime) {

		if (window->PreviousID >= 0 && window->IsSubmenu())
			recursiveDrawWindows(getWindowById(window->PreviousID), deltaTime);

		window->Draw(deltaTime);
	}
}
