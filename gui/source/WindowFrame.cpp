/*
 * WindowFrame.cpp
 *
 *
 *  Draws the header and footer.
 */

#include "Menu/Elements/WindowFrame.hpp"
#include "Globals.hpp"

using namespace Mini2D;

namespace Menu
{
	namespace Elements
	{
		//---------------------------------------------------------------------------
		// Setup
		//---------------------------------------------------------------------------
		WindowFrame::WindowFrame(Mini * mini, Image * logo, const std::wstring& title, const std::wstring& label,
			Mini2D::Vector2 center, Mini2D::Vector2 size) :
		_mini(mini),
		_logo(logo),
		_title(title),
		_label(label)
		{
			if (!_mini || !_logo)
				return;

			// Copy over the container location and size
			_locContainer = center;
			_dimContainer = size;

			// Place logo on the top left of the container
			_locLogo.Set(_locContainer.X - (_dimContainer.X * 0.47), _locContainer.Y - (_dimContainer.Y * 0.425));
			_dimLogo.Set(_dimContainer * 0.035);

			// Translate the logo size and location to screen space
			LOC_TO_SCREEN(_locLogo, _mini);
			DIM_TO_SCREEN(_dimLogo, _mini);

			// Place the header line on the right end of the logo
			_locLine.Set(_locLogo.X + (_dimLogo.X * 0.45), _locLogo.Y);

			// Have the line end close to the end of the container
			_locXLineStop = (_locContainer.X + (_dimContainer.X * 0.47)) * _mini->MAXW;

			// Place title above line and to the right of the logo
			_locTitle.Set(_locLogo.X + (_dimLogo.X * 0.5), _locLogo.Y - (_dimLogo.Y * 0.2));

			// Place label above line right before line end
			_locLabel.Set(_locXLineStop - TEX_HEADER_DOT->GetWidth() * 0.5, _locTitle.Y);
		}

		//---------------------------------------------------------------------------
		// Clean clean
		//---------------------------------------------------------------------------
		WindowFrame::~WindowFrame()
		{
			_mini = NULL;
			_logo = NULL;
		}

		//---------------------------------------------------------------------------
		// Draw the WindowFrame
		//---------------------------------------------------------------------------
		void WindowFrame::Draw(Font * font)
		{
			if (!_mini || !_logo || !font)
				return;

			// Draw Background
			TEX_BGIMG->DrawRegion.Location.Set(_locContainer * Vector2(_mini->MAXW, _mini->MAXH));
			TEX_BGIMG->DrawRegion.Dimension.Set(_dimContainer * Vector2(_mini->MAXW, _mini->MAXH));
			TEX_BGIMG->Draw();

			// Draw the header line
			TEX_HEADER_LINE->DrawRegion.Location.Set(_locLine);
			TEX_HEADER_LINE->DrawRegion.Location.X += (_locXLineStop - _locLine.X) * 0.5;
			TEX_HEADER_LINE->DrawRegion.Dimension.Set(Vector2(_locXLineStop - _locLine.X, TEX_HEADER_LINE->GetHeight()));
			TEX_HEADER_LINE->Draw();

			// Draw header dot at end of line
			TEX_HEADER_DOT->DrawRegion.Location.Set(Vector2(_locXLineStop, _locLine.Y));
			TEX_HEADER_DOT->DrawRegion.Dimension.Set(Vector2(TEX_HEADER_DOT->GetWidth(), TEX_HEADER_DOT->GetHeight()));
			TEX_HEADER_DOT->Draw();

			// Draw the logo
			_logo->DrawRegion.Location.Set(_locLogo);
			_logo->DrawRegion.Dimension.Set(_dimLogo);
			_logo->Draw(0x000000FF);

			// Draw the title
			font->TextAlign = Font::PRINT_ALIGN_BOTTOMLEFT;
			font->ForeColor = 0x000000FF;
			font->PrintLine(_title, NULL, _locTitle, FONT_SMALL * 2);

			// Draw the label
			font->TextAlign = Font::PRINT_ALIGN_BOTTOMRIGHT;
			font->ForeColor = 0x000000FF;
			font->PrintLine(_label, NULL, _locLabel, FONT_SMALL);
		}
	}
}
