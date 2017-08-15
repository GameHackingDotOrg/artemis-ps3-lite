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
		Start(Mini2D * mini, WindowManager * windowManager, long prevId);
		~Start();

		virtual void Draw(float deltaTime);
		virtual void Pad(int port, padData pData);
		virtual bool IsSubmenu();

	private:
		Mini2D * _mini;
		WindowManager * _windowManager;

		// Icons
		Elements::Icon * _iconLogo;
		Elements::Icon * _iconXmb;
		Elements::Icon * _iconCht;
		Elements::Icon * _iconOpt;
		Elements::Icon * _iconAbt;

		// Locations
		Vector2 _locLogo;
		Vector2 _locXmb;
		Vector2 _locCht;
		Vector2 _locOpt;
		Vector2 _locAbt;
		Vector2 _locLink;

		// Dimensions
		Vector2 _dimIco;
		Vector2 _dimLogo;

		Vector2 _fontIco;
		
		// Selected index
		int _selectedIndex;
	};
}

#endif /* MENUS_HPP_ */