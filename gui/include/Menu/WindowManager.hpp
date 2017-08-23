/*
 * WindowManager.hpp
 *
 *
 *  WindowManager draws the active Window and any parent Windows it may hover over.
 *  It handles all Window transitions.
 */

#ifndef WINDOW_MANAGER_HPP_
#define WINDOW_MANAGER_HPP_


#include <vector>							// std::vector<>

#include <Mini2D/Mini.hpp>					// Mini class
#include <Mini2D/Image.hpp>					// Image class
#include <Mini2D/Font.hpp>					// Font class
#include <Mini2D/Units.hpp>					// RectangleF, Vector2

#include "Menu/IMenu.hpp"					// IMenu declaration
#include "Config/Locale.hpp"				//
#include "Config/Config.hpp"				//

namespace Menu {

	class WindowManager {
	public:

		// Contructors
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
		Mini2D::Mini * _mini;
		std::vector<IMenu *> _windows;		// Collection of Windows
		long _activeWindow;					// ID of the active Window
		Config::Config * _config;			// Active config
		Config::Locale * _locale;			// Active locale
		Mini2D::Font * _font;				// Active font
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
