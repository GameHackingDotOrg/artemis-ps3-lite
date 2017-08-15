

#ifndef IMENU_HPP_
#define IMENU_HPP_

#include <Mini2D/Mini2D.hpp>				// Mini2D class
#include <Mini2D/Image.hpp>					// Image class
#include <Mini2D/Units.hpp>					// RectangleF, Vector2

namespace Menu {

	class IMenu
	{
	public:
		enum WindowState {
			WINDOW_STATE_INACTIVE = 0,		// Window not actively drawn
			WINDOW_STATE_CLOSING,			// Window is closing
			WINDOW_STATE_ACTIVE,			// Window is active
			WINDOW_STATE_OPENING			// Window is opening
		};

		WindowState State;					// State of the Window (IMenu instance)
		long ID;							// Unique identifier of the Window
		long PreviousID;					// Unique identifier of the Window that opened this Window

		virtual ~IMenu() { }

		// Draws the menu
		virtual void Draw(float deltaTime) = 0;

		// Process controller inputs
		virtual void Pad(int port, padData pData) = 0;

		// Returns true if the window is drawn over the previous window
		virtual bool IsSubmenu() = 0;
	};
}

#endif /* IMENU_HPP_ */