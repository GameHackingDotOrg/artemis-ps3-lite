#ifndef GLOBALS_HPP_
#define GLOBALS_HPP_

#include <Mini2D/Mini2D.hpp>
#include <Mini2D/Image.hpp>
#include <Mini2D/Font.hpp>
#include <Mini2D/Units.hpp>

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

#include "comfortaa_regular_ttf.h"			// 
#include "comfortaa_bold_ttf.h"				// 
#include "comfortaa_light_ttf.h"			// 



#define LocToScreen(loc) 			loc.X *= _mini->MAXW; loc.Y *= _mini->MAXH;
#define DimToScreen(dim) 			dim *= _mini->MAXW;
#define LocToScreen2(loc, mini) 	loc.X *= mini->MAXW; loc.Y *= mini->MAXH;
#define DimToScreen2(dim, mini) 	dim *= mini->MAXW;

#define MENU_SELECTED 				0x000000FF
#define MENU_UNSELECTED 			0x00000040

extern Image * TEX_BGIMG;
extern Image * TEX_CHEAT;
extern Image * TEX_CIRCLE_ERROR_DARK;
extern Image * TEX_CIRCLE_ERROR_LIGHT;
extern Image * TEX_CIRCLE_LOADING_BG;
extern Image * TEX_CIRCLE_LOADING_SEEK;
extern Image * TEX_EDIT_ICO_ADD;
extern Image * TEX_EDIT_ICO_DEL;
extern Image * TEX_EDIT_SHADOW;
extern Image * TEX_FOOTER_ICO_CIRCLE;
extern Image * TEX_FOOTER_ICO_CROSS;
extern Image * TEX_FOOTER_ICO_LT;
extern Image * TEX_FOOTER_ICO_RT;
extern Image * TEX_FOOTER_ICO_SQUARE;
extern Image * TEX_FOOTER_ICO_TRIANGLE;
extern Image * TEX_HEADER_DOT;
extern Image * TEX_HEADER_ICO_ABT;
extern Image * TEX_HEADER_ICO_CHT;
extern Image * TEX_HEADER_ICO_OPT;
extern Image * TEX_HEADER_ICO_XMB;
extern Image * TEX_HEADER_LINE;
extern Image * TEX_HELP;
extern Image * TEX_MARK_ARROW;
extern Image * TEX_MARK_LINE;
extern Image * TEX_OPT_OFF;
extern Image * TEX_OPT_ON;
extern Image * TEX_SCROLL_BG;
extern Image * TEX_SCROLL_LOCK;
extern Image * TEX_TITLESCR_ICO_ABT;
extern Image * TEX_TITLESCR_ICO_CHT;
extern Image * TEX_TITLESCR_ICO_OPT;
extern Image * TEX_TITLESCR_ICO_XMB;
extern Image * TEX_TITLESCR_LOGO;

extern Font * FONT_COMFORTAA_REGULAR;
extern Font * FONT_COMFORTAA_BOLD;
extern Font * FONT_COMFORTAA_LIGHT;

extern Vector2 FONT_SMALL;
extern Vector2 FONT_MEDIUM;
extern Vector2 FONT_LARGE;

extern Vector2 LOC_CENTER;
extern Vector2 DIM_FULL;

#endif /* GLOBALS_HPP_ */
