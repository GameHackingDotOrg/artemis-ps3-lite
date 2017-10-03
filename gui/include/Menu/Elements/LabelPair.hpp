/*
 * LabelPair.hpp
 *
 *
 *  A class for drawing a label with another label directly under it.
 *	This is especially handy in the About menu.
 */

#ifndef LABELPAIR_HPP_
#define LABELPAIR_HPP_

#include <Mini2D/Mini.hpp>
#include <Mini2D/Image.hpp>
#include <Mini2D/Font.hpp>
#include <Mini2D/Units.hpp>

namespace Menu
{
	namespace Elements
	{
		class LabelPair
		{
		public:

			// Location of top label
			Mini2D::Vector2 Location;

			// Font sizes
			float FontSizeTop;
			float FontSizeBottom;

			/*
			 * Icon Constructor
			 *
			 * icon:
			 *		Image to draw
			 * label:
			 *		String to print under image
			 */
			LabelPair(const std::wstring& top, const std::wstring& bottom);
			~LabelPair();

			/*
			 * Draw:
			 *		Draws the labels with the supplied color
			 *
			 * fontTop:
			 *		Font to use for printing the top label
			 * fontBottom:
			 *		Font to use for printing the bottom label
			 * RGBA:
			 *		Color
			 * yBuffer:
			 *		Y Offset from bottom label's default drawing location
			 */
			void Draw(Mini2D::Font * fontTop, Mini2D::Font * fontBottom = NULL, unsigned int RGBA = 0x000000FF, float yBuffer = 0);

		private:

			// Top label
			const std::wstring& _top;

			// Bottom label
			const std::wstring& _bottom;
		};
	}
}

#endif /* LABELPAIR_HPP_ */
