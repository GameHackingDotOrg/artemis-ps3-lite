/*
 * WindowManager.hpp
 *
 *
 *  WindowManager draws the active Window and any parent Windows it may hover over.
 *  It handles all Window transitions.
 */

#ifndef WINDOW_MANAGER_HPP_
#define WINDOW_MANAGER_HPP_


#include <vector>

#include <Mini2D/Mini.hpp>
#include <Mini2D/Image.hpp>
#include <Mini2D/Font.hpp>
#include <Mini2D/Units.hpp>

#include "Menu/IMenu.hpp"
#include "Config/Locale.hpp"
#include "Config/Config.hpp"

namespace Menu
{
	class WindowManager
	{
	public:

		/*
		 * Constructor
		 *
		 * mini:
		 *		Mini instance
		 */
		WindowManager(Mini2D::Mini * mini);
		~WindowManager();

		/*
		 * Draw:
		 *		Draws the Window and any Windows it hovers over
		 *
		 * deltaTime:
		 *		Milliseconds since last frame
		 */
		bool Draw(float deltaTime);

		/*
		 * Pad:
		 *		Forwards controller input to the active Window
		 *
		 * port:
		 *		Which controller pData is coming from
		 * pData:
		 *		Pad information
		 */
		void Pad(int port, padData * pData);

		/*
		 * OpenWindow:
		 *		Changes the active Window and sets the Window's state to OPENING
		 *
		 * id:
		 *		ID of the Window to open
		 *
		 * Return:
		 *		True if successful
		 */
		bool OpenWindow(long id);

		/*
		 * CloseWindow:
		 *		Sets the Window's state to CLOSING
		 *
		 * id:
		 *		ID of the Window to close
		 *
		 * Return:
		 *		True if successful
		 */
		bool CloseWindow(long id);

		/*
		 * AddWindow:
		 *		Sets the Window's state to CLOSING
		 *
		 * window:
		 *		New window
		 *
		 * Return:
		 *		-1	: window is NULL
		 *		-2	: window is already added
		 *		>=0	: ID of the new window
		 */
		long AddWindow(IMenu * window);

		/*
		 * Update:
		 *		Update the font and locale from _config
		 */
		void Update();

		/*
		 * GetLocale:
		 *		Get the current locale
		 */
		Config::Locale * GetLocale();

		/*
		 * GetConfig:
		 *		Get the current config
		 */
		Config::Config * GetConfig();

		/*
		 * GetFont:
		 *		Get the current font
		 */
		Mini2D::Font * GetFont();

	private:

		// Mini instance
		Mini2D::Mini * _mini;

		// Collection of Windows
		std::vector<IMenu *> _windows;

		// ID of the active Window
		long _activeWindow;

		// Active config
		Config::Config * _config;

		// Active locale
		Config::Locale * _locale;

		// Active font
		Mini2D::Font * _font;

		// RSX texture pointer
		// This is used to reuse RSX memory when we change locale and use a different font
		u32 * _texturePointer;

		// Returns the Window given an ID
		IMenu * getWindowById(long id);

		// Removes the window from _windows given an ID
		void removeWindowById(long id);

		// Draws the previous window if the current window is a submenu
		// It will draw multiple layers of submenus
		void recursiveDrawWindows(IMenu * window, float deltaTime);
	};
}

#endif /* WINDOW_MANAGER_HPP_ */
