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

#include <Mini2D/Mini2D.hpp>				// Mini2D class
#include <Mini2D/Image.hpp>					// Image class
#include <Mini2D/Units.hpp>					// RectangleF, Vector2

#include "Menu/IMenu.hpp"					// IMenu declaration

namespace Menu {

	class WindowManager {
	public:

		// Contructors
		WindowManager();
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
	private:
		std::vector<IMenu *> _windows;		// Collection of Windows
		long _activeWindow;					// ID of the active Window

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
