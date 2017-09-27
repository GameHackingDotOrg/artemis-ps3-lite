/*
 * Menus.hpp
 *
 *
 *  Contains all the declarations of classes inheriting the IMenu interface.
 */

#ifndef MENUS_HPP_
#define MENUS_HPP_

#include <Mini2D/Mini.hpp>
#include <Mini2D/Image.hpp>
#include <Mini2D/Units.hpp>

#include "Menu/IMenu.hpp"
#include "Menu/Elements/Icon.hpp"
#include "Menu/Elements/WindowFrame.hpp"
#include "Menu/WindowManager.hpp"

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
		Start(Mini2D::Mini * mini, WindowManager * windowManager, long prevId);

		~Start();

		// Getters and Setters
		virtual const WindowState& State() const;
  		virtual void State(const WindowState& newState);

  		virtual const long& Id() const;
  		virtual void Id(const long& newId);

  		virtual const long& PreviousId() const;
  		virtual void PreviousId(const long& newPreviousId);

		// Implementations of pure virtual methods from IMenu
		virtual void Draw(float deltaTime);
		virtual void Pad(int port, padData pData);
		virtual bool IsSubmenu();

	private:
		Mini2D::Mini * _mini;				// Mini2D instance
		WindowManager * _windowManager;		// Manager of the Windows

		WindowState _windowState;			// State of the Window
		long _id;							// Unique identifier of the Window
		long _previousId;					// Unique identifier of the Window that opened this Window

		// Icons
		Elements::Icon * _iconXmb;			// Disc icon
		Elements::Icon * _iconCht;			// Cheats icon
		Elements::Icon * _iconOpt;			// Gears icon
		Elements::Icon * _iconAbt;			// Question mark icon

		// Locations
		Mini2D::Vector2 _locLogo;			// Location of Artemis logo on screen
		Mini2D::Vector2 _locLabel;			// Location of Artemis logo label on screen
		Mini2D::Vector2 _locLink;			// Location of Artemis web link on screen
		Mini2D::Vector2 _locXmb;			// Location of _iconXmb on screen
		Mini2D::Vector2 _locCht;			// Location of _iconCht on screen
		Mini2D::Vector2 _locOpt;			// Location of _iconOpt on screen
		Mini2D::Vector2 _locAbt;			// Location of _iconAbt on screen

		// Dimensions
		Mini2D::Vector2 _dimIco;			// Size of disc, cheats, gears, and question mark icons
		Mini2D::Vector2 _dimLogo;			// Size of Artemis logo icon
		Mini2D::Vector2 _dimLabel;			// Size of Artemis logo label
		Mini2D::Vector2 _dimLink;			// Size of Artemis page link

		float _fontIco;						// Font size of label for disc, cheats, gears, and question mark icons


		int _selectedIndex;					// Actively selected icon
	};

	class About : public IMenu {
	public:

		/*
		 * About Constructor
		 *
		 * mini:
		 *		Instance of Mini2D
		 * windowManager:
		 *		Instance of WindowManager
		 * prevId:
		 *		The 64-bit id of the Window opening this new Window
		 */
		About(Mini2D::Mini * mini, WindowManager * windowManager, long prevId);

		~About();

		// Getters and Setters
		virtual const WindowState& State() const;
  		virtual void State(const WindowState& newState);

  		virtual const long& Id() const;
  		virtual void Id(const long& newId);

  		virtual const long& PreviousId() const;
  		virtual void PreviousId(const long& newPreviousId);

		// Implementations of pure virtual methods from IMenu
		virtual void Draw(float deltaTime);
		virtual void Pad(int port, padData pData);
		virtual bool IsSubmenu();

	private:
		// Mini2D instance
		Mini2D::Mini * _mini;

		// Manager of the Windows
		WindowManager * _windowManager;

		// State of the Window
		WindowState _windowState;

		// Window frame instance
		Elements::WindowFrame * _windowFrame;

		// Unique identifier of the Window
		long _id;

		// Unique identifier of the Window that opened this Window
		long _previousId;

		// WindowFrame label
		std::wstring _windowFrameLabel;

		// Locations
		Mini2D::Vector2 _locHeaderLine;
		Mini2D::Vector2 _locHeaderLogo;
		Mini2D::Vector2 _locHeaderLeft;
		Mini2D::Vector2 _locHeaderRight;
		Mini2D::Vector2 _locThank;
		Mini2D::Vector2 _locThankFoot;

		// Dimensions
		Mini2D::Vector2 _dimHeaderLine;
		Mini2D::Vector2 _dimHeaderLogo;

		// Font size
		float _fontHeaderLeft;
		float _fontHeaderRight;
	};
}

#endif /* MENUS_HPP_ */
