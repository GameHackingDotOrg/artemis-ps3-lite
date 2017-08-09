#include <math.h>

#include "Menu.hpp"
#include "Globals.hpp"

namespace Menu
{
	// Text
	static std::wstring TEXT_LOGO = 			L"Playstation 3 Hacking System";
	static std::wstring TEXT_LINK = 			L"www.gamehacking.org/artemis";
	static std::wstring TEXT_XMB = 				L"Start Game";
	static std::wstring TEXT_CHT = 				L"Cheats";
	static std::wstring TEXT_OPT = 				L"Options";
	static std::wstring TEXT_ABT = 				L"About";

	// Locations
	Vector2 TEX_TITLESCR_LOGO_LOC =				Vector2(0.5, 0.25);
	Vector2 TEX_TITLESCR_LOGO_DIM =				Vector2(0.6, 0.105);
	Vector2 TEX_TITLESCR_ICO_XMB_LOC =			Vector2(0.3, 0.6);
	Vector2 TEX_TITLESCR_ICO_CHT_LOC =			Vector2(0.433, 0.6);
	Vector2 TEX_TITLESCR_ICO_OPT_LOC =			Vector2(0.558, 0.6);
	Vector2 TEX_TITLESCR_ICO_ABT_LOC =			Vector2(0.7, 0.6);
	Vector2 TEX_TITLESCR_ICO_DIM =				Vector2(0.09375, 0.075);

	Vector2 TEXT_LOGO_LOC = 					Vector2(0.5, TEX_TITLESCR_LOGO_LOC.Y);
	Vector2 TEXT_LINK_LOC = 					Vector2(0.5, 0.96);
	Vector2 TEXT_TITLESCR_ICO_XMB_LOC =			Vector2(TEX_TITLESCR_ICO_XMB_LOC.X, 0);
	Vector2 TEXT_TITLESCR_ICO_CHT_LOC =			Vector2(TEX_TITLESCR_ICO_CHT_LOC.X, 0);
	Vector2 TEXT_TITLESCR_ICO_OPT_LOC =			Vector2(TEX_TITLESCR_ICO_OPT_LOC.X + 0.008, 0);
	Vector2 TEXT_TITLESCR_ICO_ABT_LOC =			Vector2(TEX_TITLESCR_ICO_ABT_LOC.X, 0);

	Vector2 FONT_ICON;
	
	// Selected index
	int selectedIndex = 0;

	Start::Start(Mini2D * mini, long id, long prevId) {
		if (!mini)
			return;

		_mini = mini;
		_id = id;
		_prevId = prevId;

		//
		FONT_ICON = FONT_SMALL * 2;

		// Setup each location and dimension
		TEX_TITLESCR_LOGO_LOC.X *= mini->MAXW; TEX_TITLESCR_LOGO_LOC.Y *= mini->MAXH;
		TEX_TITLESCR_LOGO_DIM *= mini->MAXW;

		TEX_TITLESCR_ICO_XMB_LOC.X *= mini->MAXW; TEX_TITLESCR_ICO_XMB_LOC.Y *= mini->MAXH;
		TEX_TITLESCR_ICO_CHT_LOC.X *= mini->MAXW; TEX_TITLESCR_ICO_CHT_LOC.Y *= mini->MAXH;
		TEX_TITLESCR_ICO_OPT_LOC.X *= mini->MAXW; TEX_TITLESCR_ICO_OPT_LOC.Y *= mini->MAXH;
		TEX_TITLESCR_ICO_ABT_LOC.X *= mini->MAXW; TEX_TITLESCR_ICO_ABT_LOC.Y *= mini->MAXH;
		TEX_TITLESCR_ICO_DIM *= mini->MAXW;

		// Setup the text locations
		// For the Y, we're just drawing under the associated image plus the size of the font
		// This way it all scales correctly if we have a 4:3 screen ratio
		TEXT_LOGO_LOC.X *= mini->MAXW; TEXT_LOGO_LOC.Y = TEX_TITLESCR_LOGO_LOC.Y + (TEX_TITLESCR_LOGO_DIM.Y * 0.5) + FONT_MEDIUM.Y;
		TEXT_TITLESCR_ICO_XMB_LOC.X *= mini->MAXW; TEXT_TITLESCR_ICO_XMB_LOC.Y = TEX_TITLESCR_ICO_XMB_LOC.Y + (TEX_TITLESCR_ICO_DIM.Y * 0.5) + FONT_ICON.Y;
		TEXT_TITLESCR_ICO_CHT_LOC.X *= mini->MAXW; TEXT_TITLESCR_ICO_CHT_LOC.Y = TEX_TITLESCR_ICO_CHT_LOC.Y + (TEX_TITLESCR_ICO_DIM.Y * 0.5) + FONT_ICON.Y;
		TEXT_TITLESCR_ICO_OPT_LOC.X *= mini->MAXW; TEXT_TITLESCR_ICO_OPT_LOC.Y = TEX_TITLESCR_ICO_OPT_LOC.Y + (TEX_TITLESCR_ICO_DIM.Y * 0.5) + FONT_ICON.Y;
		TEXT_TITLESCR_ICO_ABT_LOC.X *= mini->MAXW; TEXT_TITLESCR_ICO_ABT_LOC.Y = TEX_TITLESCR_ICO_ABT_LOC.Y + (TEX_TITLESCR_ICO_DIM.Y * 0.5) + FONT_ICON.Y;

		TEXT_LINK_LOC.X *= mini->MAXW; TEXT_LINK_LOC.Y *= mini->MAXH;
	}

	Start::~Start() {
		
	}

	void Start::Draw(float deltaTime) {
		if (!tex_bgimg || !tex_titlescr_logo)
			return;

		// Draw Background
		tex_bgimg->DrawRegion.Location.Set(CENTER_LOC);
		tex_bgimg->DrawRegion.Dimension.Set(FULL_DIM);
		tex_bgimg->Draw();

		// Draw Logo
		tex_titlescr_logo->DrawRegion.Location.Set(TEX_TITLESCR_LOGO_LOC);
		tex_titlescr_logo->DrawRegion.Dimension.Set(TEX_TITLESCR_LOGO_DIM);
		tex_titlescr_logo->Draw();

		// Print "Playstation 3 Hacking System"
		font_comfortaa_light->TextAlign = Font::PRINT_ALIGN_CENTER;
		font_comfortaa_light->PrintLine(NULL, &TEXT_LOGO, NULL, TEXT_LOGO_LOC, FONT_MEDIUM);

		// Print link
		font_comfortaa_light->TextAlign = Font::PRINT_ALIGN_BOTTOMCENTER;
		font_comfortaa_light->PrintLine(NULL, &TEXT_LINK, NULL, TEXT_LINK_LOC, FONT_SMALL * 2.5);


		// Draw Start Game
		tex_titlescr_ico_xmb->DrawRegion.Location.Set(TEX_TITLESCR_ICO_XMB_LOC);
		tex_titlescr_ico_xmb->DrawRegion.Dimension.Set(TEX_TITLESCR_ICO_DIM);
		tex_titlescr_ico_xmb->Draw();
		font_comfortaa_bold->TextAlign = Font::PRINT_ALIGN_CENTER;
		font_comfortaa_bold->PrintLine(NULL, &TEXT_XMB, NULL, TEXT_TITLESCR_ICO_XMB_LOC, FONT_ICON);

		// Draw Cheats
		tex_titlescr_ico_cht->DrawRegion.Location.Set(TEX_TITLESCR_ICO_CHT_LOC);
		tex_titlescr_ico_cht->DrawRegion.Dimension.Set(TEX_TITLESCR_ICO_DIM);
		tex_titlescr_ico_cht->Draw();
		font_comfortaa_bold->TextAlign = Font::PRINT_ALIGN_CENTER;
		font_comfortaa_bold->PrintLine(NULL, &TEXT_CHT, NULL, TEXT_TITLESCR_ICO_CHT_LOC, FONT_ICON);

		// Draw Options
		tex_titlescr_ico_opt->DrawRegion.Location.Set(TEX_TITLESCR_ICO_OPT_LOC);
		tex_titlescr_ico_opt->DrawRegion.Dimension.Set(TEX_TITLESCR_ICO_DIM);
		tex_titlescr_ico_opt->Draw();
		font_comfortaa_bold->TextAlign = Font::PRINT_ALIGN_CENTER;
		font_comfortaa_bold->PrintLine(NULL, &TEXT_OPT, NULL, TEXT_TITLESCR_ICO_OPT_LOC, FONT_ICON);

		// Draw About
		tex_titlescr_ico_abt->DrawRegion.Location.Set(TEX_TITLESCR_ICO_ABT_LOC);
		tex_titlescr_ico_abt->DrawRegion.Dimension.Set(TEX_TITLESCR_ICO_DIM);
		tex_titlescr_ico_abt->Draw();
		font_comfortaa_bold->TextAlign = Font::PRINT_ALIGN_CENTER;
		font_comfortaa_bold->PrintLine(NULL, &TEXT_ABT, NULL, TEXT_TITLESCR_ICO_ABT_LOC, FONT_ICON);
	}

	void Start::Pad(int changed, int port, padData pData) {

	}

	long Start::ID() {
		return _id;
	}
}
