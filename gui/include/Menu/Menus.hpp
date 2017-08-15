/*
 * Menus.hpp
 *
 * 
 *  Contains all the class declarations inheriting the IMenu interface.
 */

#ifndef MENUS_HPP_
#define MENUS_HPP_

#include <Mini2D/Mini2D.hpp>				// Mini2D class
#include <Mini2D/Image.hpp>					// Image class
#include <Mini2D/Units.hpp>					// RectangleF, Vector2

#include "Menu/IMenu.hpp"					// IMenu declaration
#include "Menu/Elements/Icon.hpp"			// Icon declaration
#include "Menu/WindowManager.hpp"			// WindowManager class

namespace Menu {

	class Start : public IMenu {
	public:

		/*
		 * Start Constructor
		 *		
		 * mini:
		 *		Instance of Mini2D
		 * windowManager:
		 *		Instance of WindowManager
		 * prevId:
		 *		The 64-bit id of the Window opening this new Window
		 */
		Start(Mini2D * mini, WindowManager * windowManager, long prevId);

		~Start();

		// Implementations of pure virtual methods from IMenu
		virtual void Draw(float deltaTime);
		virtual void Pad(int port, padData pData);
		virtual bool IsSubmenu();

	private:
		Mini2D * _mini;						// Mini2D instance
		WindowManager * _windowManager;		// Manager of the Windows

		// Icons
		Elements::Icon * _iconLogo;			// Artemis logo icon
		Elements::Icon * _iconXmb;			// Disc icon
		Elements::Icon * _iconCht;			// Cheats icon
		Elements::Icon * _iconOpt;			// Gears icon
		Elements::Icon * _iconAbt;			// Question mark icon

		// Locations
		Vector2 _locLogo;					// Location of _iconLogo on screen
		Vector2 _locXmb;					// Location of _iconXmb on screen
		Vector2 _locCht;					// Location of _iconCht on screen
		Vector2 _locOpt;					// Location of _iconOpt on screen
		Vector2 _locAbt;					// Location of _iconAbt on screen
		Vector2 _locLink;					// Location of Artemis web link on screen

		// Dimensions
		Vector2 _dimIco;					// Size of disc, cheats, gears, and question mark icons
		Vector2 _dimLogo;					// Size of Artemis logo icon

		Vector2 _fontIco;					// Font size of label for disc, cheats, gears, and question mark icons
		

		int _selectedIndex;					// Actively selected icon
	};
}

#endif /* MENUS_HPP_ */