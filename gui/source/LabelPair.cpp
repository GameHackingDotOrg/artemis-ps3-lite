/*
 * LabelPair.cpp
 *
 *
 *  A class for drawing a label with another label directly under it.
 *	This is especially handy in the About menu.
 */

#include "Menu/Elements/LabelPair.hpp"

using namespace Mini2D;

namespace Menu
{
	namespace Elements
	{
		//---------------------------------------------------------------------------
		// Setup
		//---------------------------------------------------------------------------
		LabelPair::LabelPair(const std::wstring& top, const std::wstring& bottom) :
		_top(top),
		_bottom(bottom)
		{
			// Set defaults
			Location.X = 0;
			Location.Y = 0;
			FontSizeTop = 0;
			FontSizeBottom = 0;
		}

		//---------------------------------------------------------------------------
		// Clean clean
		//---------------------------------------------------------------------------
		LabelPair::~LabelPair()
		{

		}

		//---------------------------------------------------------------------------
		// Draw the LabelPair
		//---------------------------------------------------------------------------
		void LabelPair::Draw(Font * fontTop, Mini2D::Font * fontBottom, unsigned int RGBA, float yBuffer)
		{
			// We're just gonna move the label under the image and add the FontSize for some extra buffering
			// This is mostly arbitrary
			// But I like the look of it and it scales well
			Vector2 locBottom = Location + Vector2(0, (FontSizeTop * 0.5) + (FontSizeBottom * 0.5) + yBuffer);

			if (!fontTop)
				return;

			// Draw the labels
			fontTop->TextAlign = Font::PRINT_ALIGN_CENTER;
			fontTop->ForeColor = RGBA;
			fontTop->PrintLine(_top, NULL, Location, FontSizeTop);

			if (fontBottom)
			{
				fontBottom->TextAlign = Font::PRINT_ALIGN_CENTER;
				fontBottom->ForeColor = RGBA;
				fontBottom->PrintLine(_bottom, NULL, locBottom, FontSizeBottom);
			}
			else
			{
				fontTop->PrintLine(_bottom, NULL, locBottom, FontSizeBottom);
			}

		}
	}
}
