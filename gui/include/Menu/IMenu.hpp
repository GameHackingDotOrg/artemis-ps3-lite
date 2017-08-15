/*
 * IMenu.hpp
 *
 * 
 *  All menus must inherit this interface and implement its methods and variables.
 */

#ifndef IMENU_HPP_
#define IMENU_HPP_

#include <Mini2D/Mini2D.hpp>				// Mini2D class
#include <Mini2D/Image.hpp>					// Image class
#include <Mini2D/Units.hpp>					// RectangleF, Vector2

namespace Menu {

	enum WindowState {
		WINDOW_STATE_INACTIVE = 0,			// Window not actively drawn
		WINDOW_STATE_CLOSING,				// Window is closing
		WINDOW_STATE_ACTIVE,				// Window is active
		WINDOW_STATE_OPENING				// Window is opening
	};

	class IMenu
	{
	public:

		WindowState State;					// State of the Window (IMenu instance)
		long ID;							// Unique identifier of the Window
		long PreviousID;					// Unique identifier of the Window that opened this Window

		// Deconstructor
		virtual ~IMenu() { }

		/*
		 * Draw:
		 *		Draws the Window
		 *		
		 * deltaTime:
		 *		Milliseconds since last frame
		 */
		virtual void Draw(float deltaTime) = 0;

		/*
		 * Pad:
		 *		Process controller input
		 *		
		 * port:
		 *		Which controller pData is coming from
		 * pData:
		 *		Pad information
		 */
		virtual void Pad(int port, padData pData) = 0;

		/*
		 * IsSubmenu:
		 *		Whether or not this Menu is a submenu
		 *		
		 * Return:
		 *		True if the Window is to bo drawn over the previous Window
		 */
		virtual bool IsSubmenu() = 0;
	};
}

#endif /* IMENU_HPP_ */