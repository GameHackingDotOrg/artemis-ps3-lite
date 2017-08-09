
#include "Icon.hpp"


namespace Menu
{

	Icon::Icon(Image * icon, Font * font, std::wstring label) : _icon(icon), _font(font), _label(label) {

	}

	Icon::~Icon() {
		_icon = NULL;
		_font = NULL;
	}

	void Icon::Draw(unsigned int RGBA) {

	}

}
