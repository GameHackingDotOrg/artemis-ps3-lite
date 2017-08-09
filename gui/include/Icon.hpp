
#ifndef ICON_HPP_
#define ICON_HPP_

#include <Mini2D/Mini2D.hpp>
#include <Mini2D/Image.hpp>
#include <Mini2D/Font.hpp>
#include <Mini2D/Units.hpp>

namespace Menu {

	class Icon {
	public:
		Vector2 Location;
		Vector2 Dimension;
		Vector2 FontSize;

		Icon(Image * icon, Font * font, std::wstring label);
		~Icon();

		void Draw(unsigned int RGBA = 0xFFFFFFFF);

	private:
		Image * _icon;
		Font * _font;
		std::wstring _label;
	};

}

#endif /* ICON_HPP_ */
