

#ifndef MENU_HPP_
#define MENU_HPP_

#include <Mini2D/Mini2D.hpp>				// Mini2D class
#include <Mini2D/Image.hpp>					// Image class
#include <Mini2D/Units.hpp>					// RectangleF, Vector2

namespace Menu {

	class IMenu
	{
	public:
		long State;								// Whether or not the menu is opening, closing, or idle

		virtual ~IMenu() { }

		// Draws the menu
		virtual void Draw(float deltaTime) = 0;

		// Process controller inputs
		virtual void Pad(int changed, int port, padData pData) = 0;

		// Returns the ID of this menu instance
		virtual long ID() = 0;

	protected:
		Mini2D * _mini;
		long  _id;
		long _prevId;
	};

	class Start : public IMenu {
	public:
		Start(Mini2D * mini, long id, long prevId);
		~Start();

		virtual void Draw(float deltaTime);
		virtual void Pad(int changed, int port, padData pData);
		virtual long ID();

	private:
	};
}

#endif /* MENU_HPP_ */