/*
 * Globals.hpp
 *
 *
 *  Serves as a place for common methods and variables.
 *  The variables referenced in here with 'extern' are defined in Globals.cpp to avoid duplication when linking.
 */

#ifndef GLOBALS_HPP_
#define GLOBALS_HPP_

#include <Mini2D/Mini.hpp>					// Mini class
#include <Mini2D/Image.hpp>					// Image class
#include <Mini2D/Font.hpp>					// Font class
#include <Mini2D/Units.hpp>					// Vector2

// Textures
#include "bgimg_png.h"						//
#include "cheat_png.h"						//
#include "circle_error_dark_png.h"			//
#include "circle_error_light_png.h"			//
#include "circle_loading_bg_png.h"			//
#include "circle_loading_seek_png.h"		//
#include "edit_ico_add_png.h"				//
#include "edit_ico_del_png.h"				//
#include "edit_shadow_png.h"				//
#include "footer_ico_circle_png.h"			//
#include "footer_ico_cross_png.h"			//
#include "footer_ico_lt_png.h"				//
#include "footer_ico_rt_png.h"				//
#include "footer_ico_square_png.h"			//
#include "footer_ico_triangle_png.h"		//
#include "header_dot_png.h"					//
#include "header_ico_abt_png.h"				//
#include "header_ico_cht_png.h"				//
#include "header_ico_opt_png.h"				//
#include "header_ico_xmb_png.h"				//
#include "header_line_png.h"				//
#include "help_png.h"						//
#include "mark_arrow_png.h"					//
#include "mark_line_png.h"					//
#include "opt_off_png.h"					//
#include "opt_on_png.h"						//
#include "scroll_bg_png.h"					//
#include "scroll_lock_png.h"				//
#include "titlescr_ico_abt_png.h"			//
#include "titlescr_ico_cht_png.h"			//
#include "titlescr_ico_opt_png.h"			//
#include "titlescr_ico_xmb_png.h"			//
#include "titlescr_logo_png.h"				//
#include "titlescr_label_png.h"				//
#include "titlescr_link_png.h"				//

#include "comfortaa_bold_ttf.h"				//


/*
 * LocToScreen:
 *		Multiplies a Vector2's X and Y by _mini->MAXW and _mini->MAXH respectively
 *
 * loc:
 *		Vector2 to scale
 */
#define LocToScreen(loc) 			loc.X *= _mini->MAXW; loc.Y *= _mini->MAXH;

/*
 * DimToScreen:
 *		Multiplies a Vector2's X and Y by _mini->MAXW
 *
 * dim:
 *		Vector2 to scale
 */
#define DimToScreen(dim) 			dim *= _mini->MAXW;

/*
 * LocToScreen2:
 *		Multiplies a Vector2's X and Y by the max screen width and height respectively
 *
 * loc:
 *		Vector2 to scale
 * mini:
 *		Mini2D instance
 */
#define LocToScreen2(loc, mini) 	loc.X *= mini->MAXW; loc.Y *= mini->MAXH;

/*
 * LocToScreen2:
 *		Multiplies a Vector2's X and Y by the max screen width
 *
 * dim:
 *		Vector2 to scale
 * mini:
 *		Mini2D instance
 */
#define DimToScreen2(dim, mini) 			dim *= mini->MAXW;


#define MENU_SELECTED 						0x000000FF
#define MENU_UNSELECTED 					0x00000040

#define CHAR_CROSS							(wchar_t)0x0010
#define CHAR_TRIANGLE						(wchar_t)0x0011
#define CHAR_CIRCLE							(wchar_t)0x0012
#define CHAR_SQUARE							(wchar_t)0x0013
#define CHAR_LEFT							(wchar_t)0x0014
#define CHAR_RIGHT							(wchar_t)0x0015

const std::wstring START_XMB_ICON =			L"START_XMB_ICON";
const std::wstring START_CHT_ICON =			L"START_CHT_ICON";
const std::wstring START_OPT_ICON =			L"START_OPT_ICON";
const std::wstring START_ABT_ICON =			L"START_ABT_ICON";

extern Mini2D::Image * TEX_BGIMG;
extern Mini2D::Image * TEX_CHEAT;
extern Mini2D::Image * TEX_CIRCLE_ERROR_DARK;
extern Mini2D::Image * TEX_CIRCLE_ERROR_LIGHT;
extern Mini2D::Image * TEX_CIRCLE_LOADING_BG;
extern Mini2D::Image * TEX_CIRCLE_LOADING_SEEK;
extern Mini2D::Image * TEX_EDIT_ICO_ADD;
extern Mini2D::Image * TEX_EDIT_ICO_DEL;
extern Mini2D::Image * TEX_EDIT_SHADOW;
extern Mini2D::Image * TEX_FOOTER_ICO_CIRCLE;
extern Mini2D::Image * TEX_FOOTER_ICO_CROSS;
extern Mini2D::Image * TEX_FOOTER_ICO_LT;
extern Mini2D::Image * TEX_FOOTER_ICO_RT;
extern Mini2D::Image * TEX_FOOTER_ICO_SQUARE;
extern Mini2D::Image * TEX_FOOTER_ICO_TRIANGLE;
extern Mini2D::Image * TEX_HEADER_DOT;
extern Mini2D::Image * TEX_HEADER_ICO_ABT;
extern Mini2D::Image * TEX_HEADER_ICO_CHT;
extern Mini2D::Image * TEX_HEADER_ICO_OPT;
extern Mini2D::Image * TEX_HEADER_ICO_XMB;
extern Mini2D::Image * TEX_HEADER_LINE;
extern Mini2D::Image * TEX_HELP;
extern Mini2D::Image * TEX_MARK_ARROW;
extern Mini2D::Image * TEX_MARK_LINE;
extern Mini2D::Image * TEX_OPT_OFF;
extern Mini2D::Image * TEX_OPT_ON;
extern Mini2D::Image * TEX_SCROLL_BG;
extern Mini2D::Image * TEX_SCROLL_LOCK;
extern Mini2D::Image * TEX_TITLESCR_ICO_ABT;
extern Mini2D::Image * TEX_TITLESCR_ICO_CHT;
extern Mini2D::Image * TEX_TITLESCR_ICO_OPT;
extern Mini2D::Image * TEX_TITLESCR_ICO_XMB;
extern Mini2D::Image * TEX_TITLESCR_LOGO;
extern Mini2D::Image * TEX_TITLESCR_LABEL;
extern Mini2D::Image * TEX_TITLESCR_LINK;

extern Mini2D::Font * FONT_DEFAULT;

extern float FONT_SMALL;
extern float FONT_MEDIUM;
extern float FONT_LARGE;

extern Mini2D::Vector2 LOC_CENTER;
extern Mini2D::Vector2 DIM_FULL;

#endif /* GLOBALS_HPP_ */
