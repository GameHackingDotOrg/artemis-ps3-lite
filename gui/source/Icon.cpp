
#include "Menu/Elements/Icon.hpp"


namespace Menu
{
	namespace Elements {

		Icon::Icon(Image * icon, Font * font, std::wstring label) : _icon(icon), _font(font), _label(label) {
			Location.X = 0;
			Location.Y = 0;

			Dimension.X = 0;
			Dimension.Y = 0;

			FontSize.X = 0;
			FontSize.Y = 0;

			LabelOffset.X = 0;
			LabelOffset.Y = 0;
		}

		Icon::~Icon() {
			_icon = NULL;
			_font = NULL;
		}

		void Icon::Draw(unsigned int RGBA) {
			// We're just gonna move the label under the image and add the FontSize.Y for some extra buffering
			// This is mostly arbitrary
			// But I like the look of it and it scales well
			Vector2 textLoc = Location + Vector2(0, (Dimension.Y * 0.5) + FontSize.Y);

			if (!_icon || !_font)
				return;

			// Draw the image
			_icon->DrawRegion.Location.Set(Location);
			_icon->DrawRegion.Dimension.Set(Dimension);
			_icon->Draw(RGBA);

			// Print the label
			_font->TextAlign = Font::PRINT_ALIGN_CENTER;
			_font->ForeColor = RGBA;
			_font->PrintLine(NULL, &_label, NULL, textLoc + LabelOffset, FontSize);
		}
	}
}
