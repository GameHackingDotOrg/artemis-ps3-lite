/*
 * Icon.hpp
 *
 *
 *  A simple class for drawing an Image with a label under it.
 */

#ifndef ICON_HPP_
#define ICON_HPP_

#include <Mini2D/Mini.hpp>
#include <Mini2D/Image.hpp>
#include <Mini2D/Font.hpp>
#include <Mini2D/Units.hpp>

namespace Menu
{
	namespace Elements
	{
		class Icon
		{
		public:

			// Location of Icon
			Mini2D::Vector2 Location;

			// Size of Icon
			Mini2D::Vector2 Dimension;

			// Offset from Location
			Mini2D::Vector2 LabelOffset;

			// Font size of label
			float FontSize;

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

			// Image to draw
			Mini2D::Image * _icon;

			// String to draw under _icon
			const std::wstring& _label;
		};
	}
}

#endif /* ICON_HPP_ */
