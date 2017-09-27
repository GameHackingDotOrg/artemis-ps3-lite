/*
 * IMenu.hpp
 *
 *
 *  All menus must inherit this interface and implement its virtual methods.
 */

#ifndef IMENU_HPP_
#define IMENU_HPP_

#include <Mini2D/Mini.hpp>
#include <Mini2D/Image.hpp>
#include <Mini2D/Units.hpp>

namespace Menu
{
	enum WindowState
	{
		WINDOW_STATE_INACTIVE = 0,  // Window not actively drawn
		WINDOW_STATE_CLOSING,       // Window is closing
		WINDOW_STATE_ACTIVE,        // Window is active
		WINDOW_STATE_OPENING        // Window is opening
	};

	class IMenu
	{
	public:

		// Deconstructor
		virtual ~IMenu() { }

		// State of the Window (IMenu instance)
		virtual const WindowState& State() const = 0;
  		virtual void State(const WindowState& newState) = 0;

  		// Unique identifier of the Window
  		virtual const long& Id() const = 0;
  		virtual void Id(const long& newId) = 0;

  		// Unique identifier of the Window that opened this Window
  		virtual const long& PreviousId() const = 0;
  		virtual void PreviousId(const long& newPreviousId) = 0;

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
