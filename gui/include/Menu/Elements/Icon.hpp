/*
 * Icon.cpp
 *
 * 
 *  A simple class for drawing an Image with a label under it.
 */

#ifndef ICON_HPP_
#define ICON_HPP_

#include <Mini2D/Mini2D.hpp>				// Mini2D class
#include <Mini2D/Image.hpp>					// Image class
#include <Mini2D/Font.hpp>					// Font class
#include <Mini2D/Units.hpp>					// Vector2

namespace Menu {
	namespace Elements {

		class Icon {
		public:
			Vector2 Location;				// Location of Icon
			Vector2 Dimension;				// Size of Icon
			Vector2 FontSize;				// Font size of label
			Vector2 LabelOffset;			// Offset from Location

			/*
			 * Icon Constructor
			 *		
			 * icon:
			 *		Image to draw
			 * font:
			 *		Font to use for label
			 * label:
			 *		String to print under image
			 */
			Icon(Image * icon, Font * font, std::wstring label);

			~Icon();

			/*
			 * Draw:
			 *		Draws the image and label with the supplied color
			 *		
			 * RGBA:
			 *		Color
			 */
			void Draw(unsigned int RGBA = 0x000000FF);

		private:
			Image * _icon;					// Image to draw
			Font * _font;					// Font to draw label with
			std::wstring _label;			// String to draw under _icon
		};
	}
}

#endif /* ICON_HPP_ */
