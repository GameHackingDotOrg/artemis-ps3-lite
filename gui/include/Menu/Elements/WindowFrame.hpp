/*
 * WindowFrame.hpp
 *
 *
 *  Draws the header and footer.
 */

#ifndef WINDOWFRAME_HPP_
#define WINDOWFRAME_HPP_

#include <Mini2D/Mini.hpp>
#include <Mini2D/Image.hpp>
#include <Mini2D/Font.hpp>
#include <Mini2D/Units.hpp>

namespace Menu {
	namespace Elements {

		class WindowFrame {
		public:

			/*
			 * WindowFrame Constructor
			 *
			 * mini:
			 *		Instance of Mini
			 * logo:
			 *		Logo to draw in the top left corner
			 * title:
			 *		String to print next to the logo
			 * label:
			 *		String to print on the top right
			 * center:
			 *		Frame location
			 * size:
			 *		Frame size
			 */
			WindowFrame(Mini2D::Mini * mini,
				Mini2D::Image * logo,
				const std::wstring& title,
				const std::wstring& label,
				Mini2D::Vector2 center = Mini2D::Vector2(0.5, 0.5),
				Mini2D::Vector2 size = Mini2D::Vector2(1, 1));

			~WindowFrame();

			/*
			 * Draw:
			 *		Draws the window frame
			 *
			 * Font:
			 *		Font to use for printing the title and label
			 */
			void Draw(Mini2D::Font * font);

		private:

			// Mini instance
			Mini2D::Mini * _mini;

			// Logo to draw
			Mini2D::Image * _logo;

			// String to draw right of _logo
			const std::wstring& _title;

			// String to draw on the top right of the header
			const std::wstring& _label;

			// Locations
			Mini2D::Vector2 _locContainer;
			Mini2D::Vector2 _locLogo;
			Mini2D::Vector2 _locTitle;
			Mini2D::Vector2 _locLabel;
			Mini2D::Vector2 _locLine;

			// Dimensions
			Mini2D::Vector2 _dimLogo;
			Mini2D::Vector2 _dimContainer;

			// Header line X end
			float _locXLineStop;
		};
	}
}

#endif /* WINDOWFRAME_HPP_ */
