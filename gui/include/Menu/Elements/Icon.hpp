/*
 * Icon.cpp
 *
 *
 *  A simple class for drawing an Image with a label under it.
 */

#ifndef ICON_HPP_
#define ICON_HPP_

#include <Mini2D/Mini.hpp>					// Mini class
#include <Mini2D/Image.hpp>					// Image class
#include <Mini2D/Font.hpp>					// Font class
#include <Mini2D/Units.hpp>					// Vector2

namespace Menu {
	namespace Elements {

		class Icon {
		public:
			Mini2D::Vector2 Location;		// Location of Icon
			Mini2D::Vector2 Dimension;		// Size of Icon
			Mini2D::Vector2 LabelOffset;	// Offset from Location
			float FontSize;					// Font size of label

			/*
			 * Icon Constructor
			 *
			 * icon:
			 *		Image to draw
			 * label:
			 *		String to print under image
			 */
			Icon(Mini2D::Image * icon, const std::wstring& label);

			~Icon();

			/*
			 * Draw:
			 *		Draws the image and label with the supplied color
			 *
			 * Font:
			 *		Font to use for printing the label
			 * RGBA:
			 *		Color
			 */
			void Draw(Mini2D::Font * font, unsigned int RGBA = 0x000000FF);

		private:
			Mini2D::Image * _icon;			// Image to draw
			const std::wstring& _label;		// String to draw under _icon
		};
	}
}

#endif /* ICON_HPP_ */
