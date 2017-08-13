#include <math.h>

#include "Menu/Menus.hpp"
#include "Menu/Elements/Icon.hpp"
#include "Globals.hpp"

namespace Menu
{
	// Text
	static std::wstring textLogo = 				L"Playstation 3 Hacking System";
	static std::wstring textLink = 				L"www.gamehacking.org/artemis";
	static std::wstring textXmb = 				L"Start Game";
	static std::wstring textCht = 				L"Cheats";
	static std::wstring textOpt = 				L"Options";
	static std::wstring textAbt = 				L"About";

	// Icons
	Elements::Icon * iconLogo;
	Elements::Icon * iconXmb;
	Elements::Icon * iconCht;
	Elements::Icon * iconOpt;
	Elements::Icon * iconAbt;

	// Locations
	Vector2 locLogo =							Vector2(0.5, 0.25);
	Vector2 locXmb =							Vector2(0.3, 0.6);
	Vector2 locCht =							Vector2(0.433, 0.6);
	Vector2 locOpt =							Vector2(0.558, 0.6);
	Vector2 locAbt =							Vector2(0.7, 0.6);
	Vector2 locLINK = 							Vector2(0.5, 0.96);

	Vector2 dimIco =							Vector2(0.09375, 0.075);
	Vector2 dimLogo =							Vector2(0.6, 0.105);

	Vector2 fontIco;
	
	// Selected index
	int selectedIndex = 0;

	Start::Start(Mini2D * mini, long id, long prevId) {
		if (!mini)
			return;

		_mini = mini;
		_id = id;
		_prevId = prevId;

		// Define out icon font size
		fontIco = FONT_SMALL * 2;

		// Initialize our icons
		iconLogo = new Elements::Icon(TEX_TITLESCR_LOGO, FONT_COMFORTAA_LIGHT, textLogo);
		iconXmb  = new Elements::Icon(TEX_TITLESCR_ICO_XMB, FONT_COMFORTAA_BOLD, textXmb);
		iconCht  = new Elements::Icon(TEX_TITLESCR_ICO_CHT, FONT_COMFORTAA_BOLD, textCht);
		iconOpt  = new Elements::Icon(TEX_TITLESCR_ICO_OPT, FONT_COMFORTAA_BOLD, textOpt);
		iconAbt  = new Elements::Icon(TEX_TITLESCR_ICO_ABT, FONT_COMFORTAA_BOLD, textAbt);

		// Translate location and dimension to screen space
		LocToScreen(locLogo);
		LocToScreen(locXmb);
		LocToScreen(locCht);
		LocToScreen(locOpt);
		LocToScreen(locAbt);
		LocToScreen(locLINK);

		DimToScreen(dimIco);
		DimToScreen(dimLogo);
	}

	Start::~Start() {
		// Unload all our allocations

		if (iconXmb) {
			delete iconXmb;
			iconXmb = NULL;
		}

		if (iconCht) {
			delete iconXmb;
			iconXmb = NULL;
		}

		if (iconOpt) {
			delete iconOpt;
			iconOpt = NULL;
		}

		if (iconAbt) {
			delete iconAbt;
			iconAbt = NULL;
		}
	}

	void Start::Draw(float deltaTime) {
		if (!TEX_BGIMG || !iconLogo || !iconXmb || !iconCht || !iconOpt || !iconAbt)
			return;

		// Draw Background
		TEX_BGIMG->DrawRegion.Location.Set(LOC_CENTER);
		TEX_BGIMG->DrawRegion.Dimension.Set(DIM_FULL);
		TEX_BGIMG->Draw();

		// Print icons
		iconLogo->Location.Set(locLogo);
		iconLogo->Dimension.Set(dimLogo);
		iconLogo->FontSize.Set(FONT_MEDIUM);
		iconLogo->Draw();

		iconXmb->Location.Set(locXmb);
		iconXmb->Dimension.Set(dimIco);
		iconXmb->FontSize.Set(fontIco);
		iconXmb->Draw(selectedIndex == 0 ? MENU_SELECTED : MENU_UNSELECTED);

		iconCht->Location.Set(locCht);
		iconCht->Dimension.Set(dimIco);
		iconCht->FontSize.Set(fontIco);
		iconCht->Draw(selectedIndex == 1 ? MENU_SELECTED : MENU_UNSELECTED);

		iconOpt->Location.Set(locOpt);
		iconOpt->Dimension.Set(dimIco);
		iconOpt->FontSize.Set(fontIco);
		iconOpt->LabelOffset.Set(0.01 * _mini->MAXW, 0);
		iconOpt->Draw(selectedIndex == 2 ? MENU_SELECTED : MENU_UNSELECTED);

		iconAbt->Location.Set(locAbt);
		iconAbt->Dimension.Set(dimIco);
		iconAbt->FontSize.Set(fontIco);
		iconAbt->Draw(selectedIndex == 3 ? MENU_SELECTED : MENU_UNSELECTED);

		// Print link
		FONT_COMFORTAA_LIGHT->TextAlign = Font::PRINT_ALIGN_BOTTOMCENTER;
		FONT_COMFORTAA_LIGHT->PrintLine(NULL, &textLink, NULL, locLINK, FONT_SMALL * 2.5);
	}

	void Start::Pad(int changed, int port, padData pData) {
		if (pData.BTN_LEFT && !pData.BTN_RIGHT) {
			selectedIndex--;
			if (selectedIndex < 0)
				selectedIndex = 3;
		}
		else if (pData.BTN_RIGHT && !pData.BTN_LEFT) {
			selectedIndex++;
			if (selectedIndex > 3)
				selectedIndex = 0;
		}
	}

	long Start::ID() {
		return _id;
	}
}
