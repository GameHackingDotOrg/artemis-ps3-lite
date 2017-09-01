/*
 * Icon.cpp
 *
 *
 *  A simple class for drawing an Image with a label under it.
 */

#include "Menu/Elements/Icon.hpp"			// Icon class declaration

using namespace Mini2D;

namespace Menu
{
	namespace Elements {

		//---------------------------------------------------------------------------
		// Setup
		//---------------------------------------------------------------------------
		Icon::Icon(Image * icon, const std::wstring& label) : _icon(icon), _label(label) {

			// Set defaults
			Location.X = 0;
			Location.Y = 0;
			Dimension.X = 0;
			Dimension.Y = 0;
			LabelOffset.X = 0;
			LabelOffset.Y = 0;
			FontSize = 0;
		}

		//---------------------------------------------------------------------------
		// Clean clean
		//---------------------------------------------------------------------------
		Icon::~Icon() {

			_icon = NULL;
		}

		//---------------------------------------------------------------------------
		// Draw the Icon
		//---------------------------------------------------------------------------
		void Icon::Draw(Font * font, unsigned int RGBA) {

			// We're just gonna move the label under the image and add the FontSize for some extra buffering
			// This is mostly arbitrary
			// But I like the look of it and it scales well
			Vector2 textLoc = Location + Vector2(0, (Dimension.Y * 0.5) + FontSize);

			if (!_icon || !font)
				return;

			// Draw the image
			_icon->DrawRegion.Location.Set(Location);
			_icon->DrawRegion.Dimension.Set(Dimension);
			_icon->Draw(RGBA);

			// Print the label
			font->TextAlign = Font::PRINT_ALIGN_CENTER;
			font->ForeColor = RGBA;
			font->PrintLine(_label, NULL, textLoc + LabelOffset, FontSize);
		}
	}
}
