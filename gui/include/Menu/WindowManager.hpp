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
		WindowManager();
		~WindowManager();

		bool Draw(float deltaTime);
		void Pad(int port, padData * pData);

		bool OpenWindow(long id);
		bool CloseWindow(long id);
		long AddWindow(IMenu * window);
	private:
		std::vector<IMenu *> _windows;
		long _activeWindow;

		IMenu * getWindowById(long id);
		void removeWindowById(long id);
		void recursiveDrawWindows(IMenu * window, float deltaTime);
	};
}

#endif /* WINDOW_MANAGER_HPP_ */
