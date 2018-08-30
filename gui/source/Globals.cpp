/*
 * Globals.cpp
 *
 *
 *  Serves as a place for common methods and variables.
 */

#include <Mini2D/Mini.hpp>
#include <Mini2D/Image.hpp>
#include <Mini2D/Font.hpp>
#include <Mini2D/Units.hpp>
#include <Mini2D/Sound.hpp>

using namespace Mini2D;

Image * TEX_BGIMG;
Image * TEX_CHEAT;
Image * TEX_CIRCLE_ERROR_DARK;
Image * TEX_CIRCLE_ERROR_LIGHT;
Image * TEX_CIRCLE_LOADING_BG;
Image * TEX_CIRCLE_LOADING_SEEK;
Image * TEX_EDIT_ICO_ADD;
Image * TEX_EDIT_ICO_DEL;
Image * TEX_EDIT_SHADOW;
Image * TEX_FOOTER_ICO_CIRCLE;
Image * TEX_FOOTER_ICO_CROSS;
Image * TEX_FOOTER_ICO_LT;
Image * TEX_FOOTER_ICO_RT;
Image * TEX_FOOTER_ICO_SQUARE;
Image * TEX_FOOTER_ICO_TRIANGLE;
Image * TEX_HEADER_DOT;
Image * TEX_HEADER_ICO_ABT;
Image * TEX_HEADER_ICO_CHT;
Image * TEX_HEADER_ICO_OPT;
Image * TEX_HEADER_ICO_XMB;
Image * TEX_HEADER_LINE;
Image * TEX_HELP;
Image * TEX_MARK_ARROW;
Image * TEX_MARK_LINE;
Image * TEX_OPT_OFF;
Image * TEX_OPT_ON;
Image * TEX_SCROLL_BG;
Image * TEX_SCROLL_LOCK;
Image * TEX_TITLESCR_ICO_ABT;
Image * TEX_TITLESCR_ICO_CHT;
Image * TEX_TITLESCR_ICO_OPT;
Image * TEX_TITLESCR_ICO_XMB;
Image * TEX_TITLESCR_LOGO;
Image * TEX_TITLESCR_LABEL;
Image * TEX_TITLESCR_LINK;

Font * FONT_DEFAULT;

Sound * SND_BGM;

float FONT_SMALL =   0.0105;
float FONT_MEDIUM =  FONT_SMALL * 1.5;
float FONT_LARGE =   FONT_MEDIUM * 1.5;

Vector2 LOC_CENTER = Vector2(0.5, 0.5);
Vector2 DIM_FULL =   Vector2(1.0, 1.0);

std::wstring WSTRING_EMPTY = L"";

// Make sure to end the array with an empty wstring
std::wstring CONTRIBUTORS[] =
{
	L"Lazy Bastard",
	L"Berion",
	L"Daniel \"Dnawrkshp\" Gerendasy",
	L""
};

const char * CHEAT_DIRECTORIES[] = {
	ARTEMIS_PATH "Cheats/"
};
