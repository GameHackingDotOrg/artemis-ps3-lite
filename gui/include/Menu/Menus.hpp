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
#include "Menu/Elements/LabelPair.hpp"
#include "Menu/Elements/WindowFrame.hpp"
#include "Menu/WindowManager.hpp"
#include "Cheats/GameList.hpp"

namespace Menu
{

	// Displays a progress wheel and uses a callback to increment
	class ProgressMenu : public IMenu
	{
	public:

		// Callback function type
		//  void* represents userData
		//  long represents the total number of increments
		//  long represents the current index
		//  Returns false if failed
		typedef bool (*IncrementCallback_t)(void*,unsigned long,unsigned long);

		/*
		 * ProgressMenu Constructor
		 *
		 * mini:
		 *		Instance of Mini2D
		 * windowManager:
		 *		Instance of WindowManager
		 * prevId:
		 *		The 64-bit id of the Window opening this new Window
		 */
		ProgressMenu(Mini2D::Mini * mini, WindowManager * windowManager, long successId, long failId, IncrementCallback_t callback, void * userData, unsigned long length);
		~ProgressMenu();

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

		// Unique identifier of the Window
		long _id;

		// Unique identifier of the Window to open if this succeeds
		long _previousId;

		// Unique identifier of the Window to open if this fails
		long _failId;

		// Window frame instance
		Elements::WindowFrame * _windowFrame;

		// Animation time
		float _animationTime;

		// Callback arguments
		IncrementCallback_t _callback;
		void * _userData;
		unsigned long _length;
		unsigned long _index;
		bool _failed;
	};

	// Lists controller mapping for a specific menu
	class HelpMenu : public IMenu
	{
	public:

		/*
		 * HelpMenu Constructor
		 *
		 * mini:
		 *		Instance of Mini2D
		 * windowManager:
		 *		Instance of WindowManager
		 * prevId:
		 *		The 64-bit id of the Window opening this new Window
		 */
		HelpMenu(Mini2D::Mini * mini, WindowManager * windowManager, long prevId, int mCross = 0, int mCirc = 0, int mTri = 0, int mSqr = 0, int mR1 = 0, int mL1 = 0, int mStart = 0, int mSel = 0, int mNav = 0);
		~HelpMenu();

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

		// Unique identifier of the Window
		long _id;

		// Unique identifier of the Window that opened this Window
		long _previousId;

		// Window frame instance
		Elements::WindowFrame * _windowFrame;

		// Animation time
		float _animationTime;

		// LOCALE_HLP array indicies for each mappable button
		int _mCross, _mCirc, _mTri, _mSqr, _mR1, _mL1, _mStart, _mSel, _mNav;


		// Draws the mapping at the specified location
		void drawMap(Mini2D::Font * font, float fontSize, float x, float y, int map, unsigned int RGBA);
	};

	class StartMenu : public IMenu
	{
	public:

		/*
		 * StartMenu Constructor
		 *
		 * mini:
		 *		Instance of Mini2D
		 * windowManager:
		 *		Instance of WindowManager
		 * prevId:
		 *		The 64-bit id of the Window opening this new Window
		 */
		StartMenu(Mini2D::Mini * mini, WindowManager * windowManager, long prevId);
		~StartMenu();

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

		// Unique identifier of the Window
		long _id;

		// Unique identifier of the Window that opened this Window
		long _previousId;

		// Animation time
		float _animationTime;

		// Icons
		Elements::Icon * _iconXmb;
		Elements::Icon * _iconCht;
		Elements::Icon * _iconOpt;
		Elements::Icon * _iconAbt;

		// Locations
		Mini2D::Vector2 _locLogo;
		Mini2D::Vector2 _locLabel;
		Mini2D::Vector2 _locLink;
		Mini2D::Vector2 _locXmb;
		Mini2D::Vector2 _locCht;
		Mini2D::Vector2 _locOpt;
		Mini2D::Vector2 _locAbt;

		// Dimensions
		Mini2D::Vector2 _dimIco;
		Mini2D::Vector2 _dimLogo;
		Mini2D::Vector2 _dimLabel;
		Mini2D::Vector2 _dimLink;

		// Font size of label for disc, cheats, gears, and question mark icons
		float _fontIco;

		// Actively selected icon
		int _selectedIndex;

		// Collection of games and their cheats
		Cheats::GameList * _gameList;
	};

	class AboutMenu : public IMenu
	{
	public:

		/*
		 * AboutMenu Constructor
		 *
		 * mini:
		 *		Instance of Mini2D
		 * windowManager:
		 *		Instance of WindowManager
		 * prevId:
		 *		The 64-bit id of the Window opening this new Window
		 */
		AboutMenu(Mini2D::Mini * mini, WindowManager * windowManager, long prevId);
		~AboutMenu();

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

		// Unique identifier of the Window
		long _id;

		// Unique identifier of the Window that opened this Window
		long _previousId;

		// Window frame instance
		Elements::WindowFrame * _windowFrame;

		// WindowFrame label
		std::wstring _windowFrameLabel;

		// Animation time
		float _animationTime;

		// Label Pairs
		Elements::LabelPair * _lpThank;
		Elements::LabelPair * _lpLearn;
		Elements::LabelPair * _lpContribute;

		// Locations
		Mini2D::Vector2 _locThank;
		Mini2D::Vector2 _locLearn;
		Mini2D::Vector2 _locContribute;
		Mini2D::Vector2 _locContributors;
	};

	// Loads and lists games we have cheats for
	class GameListMenu : public IMenu
	{
	public:

		/*
		 * GameListMenu Constructor
		 *
		 * mini:
		 *		Instance of Mini2D
		 * windowManager:
		 *		Instance of WindowManager
		 * prevId:
		 *		The 64-bit id of the Window opening this new Window
		 */
		GameListMenu(Mini2D::Mini * mini, WindowManager * windowManager, long prevId);
		~GameListMenu();

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

		// Unique identifier of the Window
		long _id;

		// Unique identifier of the Window that opened this Window
		long _previousId;

		// Window frame instance
		Elements::WindowFrame * _windowFrame;

		// Animation time
		float _animationTime;
	};
}

#endif /* MENUS_HPP_ */
