#include <stdio.h>
#include <io/pad.h>

#include <Mini2D/Mini2D.hpp>
#include <Mini2D/Image.hpp>

#include "Menu.hpp"
#include "Globals.hpp"

// Data
#include "background_music_mp3_bin.h"

// 
Mini2D * mini = NULL;
Menu::Start * menuStart = NULL;
int doExit = 0;

// 
int drawUpdate(float deltaTime, unsigned long frame);
void padUpdate(int changed, int port, padData pData);
void exit();

// 
void LoadTextures(Mini2D * mini);
void UnloadTextures();

int main(s32 argc, const char* argv[]) {

	// Initialize Mini2D
	mini = new Mini2D((Mini2D::PadCallback_f)&padUpdate, (Mini2D::DrawCallback_f)&drawUpdate, (Mini2D::ExitCallback_f)&exit);

	// Load our textures
	LoadTextures(mini);

	// Initialize the main menu
	menuStart = new Menu::Start(mini, 1, 0);

	mini->SetAnalogDeadzone(15);
	mini->SetClearColor(0x23B2D7FF);
	mini->SetAlphaState(1);
	mini->BeginDrawLoop();

	UnloadTextures();

	return 0;
}

int drawUpdate(float deltaTime, unsigned long frame) {
	menuStart->Draw(deltaTime);
	return doExit;
}

void padUpdate(int changed, int port, padData pData) {
	if (pData.BTN_L3 && pData.BTN_R3 && (changed & Mini2D::BTN_CHANGED_L3 || changed & Mini2D::BTN_CHANGED_R3))
		doExit = -1;

	menuStart->Pad(changed, port, pData);
}

void exit() {
	printf("Artemis Lite::Exiting\n");

	if (menuStart) {
		delete menuStart;
		menuStart = NULL;
	}

	if (mini) {
		delete mini;
		mini = NULL;
	}
}

// Load textures
void LoadTextures(Mini2D * mini) {
	Vector2 center = Vector2(0.5 * mini->MAXW, 0.5 * mini->MAXH);
	
	// Initialize locations
	TEX_BGIMG_LOC.X *= mini->MAXW; TEX_BGIMG_LOC.Y *= mini->MAXH; 
	TEX_BGIMG_DIM.X *= mini->MAXW; TEX_BGIMG_DIM.Y *= mini->MAXH;

	TEX_CHEAT_LOC.X *= mini->MAXW; TEX_CHEAT_LOC.Y *= mini->MAXH; 
	TEX_CHEAT_DIM.X *= mini->MAXW; TEX_CHEAT_DIM.Y *= mini->MAXH;

	TEX_CIRCLE_ERROR_DARK_LOC.X *= mini->MAXW; TEX_CIRCLE_ERROR_DARK_LOC.Y *= mini->MAXH; 
	TEX_CIRCLE_ERROR_DARK_DIM.X *= mini->MAXW; TEX_CIRCLE_ERROR_DARK_DIM.Y *= mini->MAXH;

	TEX_CIRCLE_ERROR_LIGHT_LOC.X *= mini->MAXW; TEX_CIRCLE_ERROR_LIGHT_LOC.Y *= mini->MAXH; 
	TEX_CIRCLE_ERROR_LIGHT_DIM.X *= mini->MAXW; TEX_CIRCLE_ERROR_LIGHT_DIM.Y *= mini->MAXH;

	TEX_CIRCLE_LOADING_BG_LOC.X *= mini->MAXW; TEX_CIRCLE_LOADING_BG_LOC.Y *= mini->MAXH; 
	TEX_CIRCLE_LOADING_BG_DIM.X *= mini->MAXW; TEX_CIRCLE_LOADING_BG_DIM.Y *= mini->MAXH;

	TEX_CIRCLE_LOADING_SEEK_LOC.X *= mini->MAXW; TEX_CIRCLE_LOADING_SEEK_LOC.Y *= mini->MAXH; 
	TEX_CIRCLE_LOADING_SEEK_DIM.X *= mini->MAXW; TEX_CIRCLE_LOADING_SEEK_DIM.Y *= mini->MAXH;

	TEX_EDIT_ICO_ADD_LOC.X *= mini->MAXW; TEX_EDIT_ICO_ADD_LOC.Y *= mini->MAXH; 
	TEX_EDIT_ICO_ADD_DIM.X *= mini->MAXW; TEX_EDIT_ICO_ADD_DIM.Y *= mini->MAXH;

	TEX_EDIT_ICO_DEL_LOC.X *= mini->MAXW; TEX_EDIT_ICO_DEL_LOC.Y *= mini->MAXH; 
	TEX_EDIT_ICO_DEL_DIM.X *= mini->MAXW; TEX_EDIT_ICO_DEL_DIM.Y *= mini->MAXH;

	TEX_EDIT_SHADOW_LOC.X *= mini->MAXW; TEX_EDIT_SHADOW_LOC.Y *= mini->MAXH; 
	TEX_EDIT_SHADOW_DIM.X *= mini->MAXW; TEX_EDIT_SHADOW_DIM.Y *= mini->MAXH;

	TEX_FOOTER_ICO_CIRCLE_LOC.X *= mini->MAXW; TEX_FOOTER_ICO_CIRCLE_LOC.Y *= mini->MAXH; 
	TEX_FOOTER_ICO_CIRCLE_DIM.X *= mini->MAXW; TEX_FOOTER_ICO_CIRCLE_DIM.Y *= mini->MAXH;

	TEX_FOOTER_ICO_CROSS_LOC.X *= mini->MAXW; TEX_FOOTER_ICO_CROSS_LOC.Y *= mini->MAXH; 
	TEX_FOOTER_ICO_CROSS_DIM.X *= mini->MAXW; TEX_FOOTER_ICO_CROSS_DIM.Y *= mini->MAXH;

	TEX_FOOTER_ICO_LT_LOC.X *= mini->MAXW; TEX_FOOTER_ICO_LT_LOC.Y *= mini->MAXH; 
	TEX_FOOTER_ICO_LT_DIM.X *= mini->MAXW; TEX_FOOTER_ICO_LT_DIM.Y *= mini->MAXH;

	TEX_FOOTER_ICO_RT_LOC.X *= mini->MAXW; TEX_FOOTER_ICO_RT_LOC.Y *= mini->MAXH; 
	TEX_FOOTER_ICO_RT_DIM.X *= mini->MAXW; TEX_FOOTER_ICO_RT_DIM.Y *= mini->MAXH;

	TEX_FOOTER_ICO_SQUARE_LOC.X *= mini->MAXW; TEX_FOOTER_ICO_SQUARE_LOC.Y *= mini->MAXH; 
	TEX_FOOTER_ICO_SQUARE_DIM.X *= mini->MAXW; TEX_FOOTER_ICO_SQUARE_DIM.Y *= mini->MAXH;

	TEX_FOOTER_ICO_TRIANGLE_LOC.X *= mini->MAXW; TEX_FOOTER_ICO_TRIANGLE_LOC.Y *= mini->MAXH; 
	TEX_FOOTER_ICO_TRIANGLE_DIM.X *= mini->MAXW; TEX_FOOTER_ICO_TRIANGLE_DIM.Y *= mini->MAXH;

	TEX_HEADER_DOT_LOC.X *= mini->MAXW; TEX_HEADER_DOT_LOC.Y *= mini->MAXH; 
	TEX_HEADER_DOT_DIM.X *= mini->MAXW; TEX_HEADER_DOT_DIM.Y *= mini->MAXH;

	TEX_HEADER_ICO_ABT_LOC.X *= mini->MAXW; TEX_HEADER_ICO_ABT_LOC.Y *= mini->MAXH; 
	TEX_HEADER_ICO_ABT_DIM.X *= mini->MAXW; TEX_HEADER_ICO_ABT_DIM.Y *= mini->MAXH;

	TEX_HEADER_ICO_CHT_LOC.X *= mini->MAXW; TEX_HEADER_ICO_CHT_LOC.Y *= mini->MAXH; 
	TEX_HEADER_ICO_CHT_DIM.X *= mini->MAXW; TEX_HEADER_ICO_CHT_DIM.Y *= mini->MAXH;

	TEX_HEADER_ICO_OPT_LOC.X *= mini->MAXW; TEX_HEADER_ICO_OPT_LOC.Y *= mini->MAXH; 
	TEX_HEADER_ICO_OPT_DIM.X *= mini->MAXW; TEX_HEADER_ICO_OPT_DIM.Y *= mini->MAXH;

	TEX_HEADER_ICO_XMB_LOC.X *= mini->MAXW; TEX_HEADER_ICO_XMB_LOC.Y *= mini->MAXH; 
	TEX_HEADER_ICO_XMB_DIM.X *= mini->MAXW; TEX_HEADER_ICO_XMB_DIM.Y *= mini->MAXH;

	TEX_HEADER_LINE_LOC.X *= mini->MAXW; TEX_HEADER_LINE_LOC.Y *= mini->MAXH; 
	TEX_HEADER_LINE_DIM.X *= mini->MAXW; TEX_HEADER_LINE_DIM.Y *= mini->MAXH;

	TEX_HELP_LOC.X *= mini->MAXW; TEX_HELP_LOC.Y *= mini->MAXH; 
	TEX_HELP_DIM.X *= mini->MAXW; TEX_HELP_DIM.Y *= mini->MAXH;

	TEX_MARK_ARROW_LOC.X *= mini->MAXW; TEX_MARK_ARROW_LOC.Y *= mini->MAXH; 
	TEX_MARK_ARROW_DIM.X *= mini->MAXW; TEX_MARK_ARROW_DIM.Y *= mini->MAXH;

	TEX_MARK_LINE_LOC.X *= mini->MAXW; TEX_MARK_LINE_LOC.Y *= mini->MAXH; 
	TEX_MARK_LINE_DIM.X *= mini->MAXW; TEX_MARK_LINE_DIM.Y *= mini->MAXH;

	TEX_OPT_OFF_LOC.X *= mini->MAXW; TEX_OPT_OFF_LOC.Y *= mini->MAXH; 
	TEX_OPT_OFF_DIM.X *= mini->MAXW; TEX_OPT_OFF_DIM.Y *= mini->MAXH;

	TEX_OPT_ON_LOC.X *= mini->MAXW; TEX_OPT_ON_LOC.Y *= mini->MAXH; 
	TEX_OPT_ON_DIM.X *= mini->MAXW; TEX_OPT_ON_DIM.Y *= mini->MAXH;

	TEX_SCROLL_BG_LOC.X *= mini->MAXW; TEX_SCROLL_BG_LOC.Y *= mini->MAXH; 
	TEX_SCROLL_BG_DIM.X *= mini->MAXW; TEX_SCROLL_BG_DIM.Y *= mini->MAXH;

	TEX_SCROLL_LOCK_LOC.X *= mini->MAXW; TEX_SCROLL_LOCK_LOC.Y *= mini->MAXH; 
	TEX_SCROLL_LOCK_DIM.X *= mini->MAXW; TEX_SCROLL_LOCK_DIM.Y *= mini->MAXH;

	TEX_TITLESCR_ICO_ABT_LOC.X *= mini->MAXW; TEX_TITLESCR_ICO_ABT_LOC.Y *= mini->MAXH; 
	TEX_TITLESCR_ICO_ABT_DIM.X *= mini->MAXW; TEX_TITLESCR_ICO_ABT_DIM.Y *= mini->MAXH;

	TEX_TITLESCR_ICO_CHT_LOC.X *= mini->MAXW; TEX_TITLESCR_ICO_CHT_LOC.Y *= mini->MAXH; 
	TEX_TITLESCR_ICO_CHT_DIM.X *= mini->MAXW; TEX_TITLESCR_ICO_CHT_DIM.Y *= mini->MAXH;

	TEX_TITLESCR_ICO_OPT_LOC.X *= mini->MAXW; TEX_TITLESCR_ICO_OPT_LOC.Y *= mini->MAXH; 
	TEX_TITLESCR_ICO_OPT_DIM.X *= mini->MAXW; TEX_TITLESCR_ICO_OPT_DIM.Y *= mini->MAXH;

	TEX_TITLESCR_ICO_XMB_LOC.X *= mini->MAXW; TEX_TITLESCR_ICO_XMB_LOC.Y *= mini->MAXH; 
	TEX_TITLESCR_ICO_XMB_DIM.X *= mini->MAXW; TEX_TITLESCR_ICO_XMB_DIM.Y *= mini->MAXH;

	TEX_TITLESCR_LOGO_LOC.X *= mini->MAXW; TEX_TITLESCR_LOGO_LOC.Y *= mini->MAXH; 
	TEX_TITLESCR_LOGO_DIM.X *= mini->MAXW; TEX_TITLESCR_LOGO_DIM.Y *= mini->MAXH;
	

	// Load textures
	tex_bgimg = new Image(mini);
	tex_bgimg->Load((void*)bgimg_png, bgimg_png_size, Image::IMAGE_TYPE_PNG);
	tex_bgimg->DrawRegion.Location.Set(TEX_BGIMG_LOC);
	tex_bgimg->DrawRegion.Dimension.Set(TEX_BGIMG_DIM);

	tex_cheat = new Image(mini);
	tex_cheat->Load((void*)cheat_png, cheat_png_size, Image::IMAGE_TYPE_PNG);
	tex_cheat->DrawRegion.Location.Set(center);
	tex_cheat->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_circle_error_dark = new Image(mini);
	tex_circle_error_dark->Load((void*)circle_error_dark_png, circle_error_dark_png_size, Image::IMAGE_TYPE_PNG);
	tex_circle_error_dark->DrawRegion.Location.Set(center);
	tex_circle_error_dark->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_circle_error_light = new Image(mini);
	tex_circle_error_light->Load((void*)circle_error_light_png, circle_error_light_png_size, Image::IMAGE_TYPE_PNG);
	tex_circle_error_light->DrawRegion.Location.Set(center);
	tex_circle_error_light->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_circle_loading_bg = new Image(mini);
	tex_circle_loading_bg->Load((void*)circle_loading_bg_png, circle_loading_bg_png_size, Image::IMAGE_TYPE_PNG);
	tex_circle_loading_bg->DrawRegion.Location.Set(center);
	tex_circle_loading_bg->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_circle_loading_seek = new Image(mini);
	tex_circle_loading_seek->Load((void*)circle_loading_seek_png, circle_loading_seek_png_size, Image::IMAGE_TYPE_PNG);
	tex_circle_loading_seek->DrawRegion.Location.Set(center);
	tex_circle_loading_seek->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_edit_ico_add = new Image(mini);
	tex_edit_ico_add->Load((void*)edit_ico_add_png, edit_ico_add_png_size, Image::IMAGE_TYPE_PNG);
	tex_edit_ico_add->DrawRegion.Location.Set(center);
	tex_edit_ico_add->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_edit_ico_del = new Image(mini);
	tex_edit_ico_del->Load((void*)edit_ico_del_png, edit_ico_del_png_size, Image::IMAGE_TYPE_PNG);
	tex_edit_ico_del->DrawRegion.Location.Set(center);
	tex_edit_ico_del->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_edit_shadow = new Image(mini);
	tex_edit_shadow->Load((void*)edit_shadow_png, edit_shadow_png_size, Image::IMAGE_TYPE_PNG);
	tex_edit_shadow->DrawRegion.Location.Set(center);
	tex_edit_shadow->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_footer_ico_circle = new Image(mini);
	tex_footer_ico_circle->Load((void*)footer_ico_circle_png, footer_ico_circle_png_size, Image::IMAGE_TYPE_PNG);
	tex_footer_ico_circle->DrawRegion.Location.Set(center);
	tex_footer_ico_circle->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_footer_ico_cross = new Image(mini);
	tex_footer_ico_cross->Load((void*)footer_ico_cross_png, footer_ico_cross_png_size, Image::IMAGE_TYPE_PNG);
	tex_footer_ico_cross->DrawRegion.Location.Set(center);
	tex_footer_ico_cross->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_footer_ico_lt = new Image(mini);
	tex_footer_ico_lt->Load((void*)footer_ico_lt_png, footer_ico_lt_png_size, Image::IMAGE_TYPE_PNG);
	tex_footer_ico_lt->DrawRegion.Location.Set(center);
	tex_footer_ico_lt->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_footer_ico_rt = new Image(mini);
	tex_footer_ico_rt->Load((void*)footer_ico_rt_png, footer_ico_rt_png_size, Image::IMAGE_TYPE_PNG);
	tex_footer_ico_rt->DrawRegion.Location.Set(center);
	tex_footer_ico_rt->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_footer_ico_square = new Image(mini);
	tex_footer_ico_square->Load((void*)footer_ico_square_png, footer_ico_square_png_size, Image::IMAGE_TYPE_PNG);
	tex_footer_ico_square->DrawRegion.Location.Set(center);
	tex_footer_ico_square->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_footer_ico_triangle = new Image(mini);
	tex_footer_ico_triangle->Load((void*)footer_ico_triangle_png, footer_ico_triangle_png_size, Image::IMAGE_TYPE_PNG);
	tex_footer_ico_triangle->DrawRegion.Location.Set(center);
	tex_footer_ico_triangle->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_header_dot = new Image(mini);
	tex_header_dot->Load((void*)header_dot_png, header_dot_png_size, Image::IMAGE_TYPE_PNG);
	tex_header_dot->DrawRegion.Location.Set(center);
	tex_header_dot->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_header_ico_abt = new Image(mini);
	tex_header_ico_abt->Load((void*)header_ico_abt_png, header_ico_abt_png_size, Image::IMAGE_TYPE_PNG);
	tex_header_ico_abt->DrawRegion.Location.Set(center);
	tex_header_ico_abt->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_header_ico_cht = new Image(mini);
	tex_header_ico_cht->Load((void*)header_ico_cht_png, header_ico_cht_png_size, Image::IMAGE_TYPE_PNG);
	tex_header_ico_cht->DrawRegion.Location.Set(center);
	tex_header_ico_cht->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_header_ico_opt = new Image(mini);
	tex_header_ico_opt->Load((void*)header_ico_opt_png, header_ico_opt_png_size, Image::IMAGE_TYPE_PNG);
	tex_header_ico_opt->DrawRegion.Location.Set(center);
	tex_header_ico_opt->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_header_ico_xmb = new Image(mini);
	tex_header_ico_xmb->Load((void*)header_ico_xmb_png, header_ico_xmb_png_size, Image::IMAGE_TYPE_PNG);
	tex_header_ico_xmb->DrawRegion.Location.Set(center);
	tex_header_ico_xmb->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_header_line = new Image(mini);
	tex_header_line->Load((void*)header_line_png, header_line_png_size, Image::IMAGE_TYPE_PNG);
	tex_header_line->DrawRegion.Location.Set(center);
	tex_header_line->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_help = new Image(mini);
	tex_help->Load((void*)help_png, help_png_size, Image::IMAGE_TYPE_PNG);
	tex_help->DrawRegion.Location.Set(center);
	tex_help->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_mark_arrow = new Image(mini);
	tex_mark_arrow->Load((void*)mark_arrow_png, mark_arrow_png_size, Image::IMAGE_TYPE_PNG);
	tex_mark_arrow->DrawRegion.Location.Set(center);
	tex_mark_arrow->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_mark_line = new Image(mini);
	tex_mark_line->Load((void*)mark_line_png, mark_line_png_size, Image::IMAGE_TYPE_PNG);
	tex_mark_line->DrawRegion.Location.Set(center);
	tex_mark_line->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_opt_off = new Image(mini);
	tex_opt_off->Load((void*)opt_off_png, opt_off_png_size, Image::IMAGE_TYPE_PNG);
	tex_opt_off->DrawRegion.Location.Set(center);
	tex_opt_off->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_opt_on = new Image(mini);
	tex_opt_on->Load((void*)opt_on_png, opt_on_png_size, Image::IMAGE_TYPE_PNG);
	tex_opt_on->DrawRegion.Location.Set(center);
	tex_opt_on->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_scroll_bg = new Image(mini);
	tex_scroll_bg->Load((void*)scroll_bg_png, scroll_bg_png_size, Image::IMAGE_TYPE_PNG);
	tex_scroll_bg->DrawRegion.Location.Set(center);
	tex_scroll_bg->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_scroll_lock = new Image(mini);
	tex_scroll_lock->Load((void*)scroll_lock_png, scroll_lock_png_size, Image::IMAGE_TYPE_PNG);
	tex_scroll_lock->DrawRegion.Location.Set(center);
	tex_scroll_lock->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_titlescr_ico_abt = new Image(mini);
	tex_titlescr_ico_abt->Load((void*)titlescr_ico_abt_png, titlescr_ico_abt_png_size, Image::IMAGE_TYPE_PNG);
	tex_titlescr_ico_abt->DrawRegion.Location.Set(center);
	tex_titlescr_ico_abt->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_titlescr_ico_cht = new Image(mini);
	tex_titlescr_ico_cht->Load((void*)titlescr_ico_cht_png, titlescr_ico_cht_png_size, Image::IMAGE_TYPE_PNG);
	tex_titlescr_ico_cht->DrawRegion.Location.Set(center);
	tex_titlescr_ico_cht->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_titlescr_ico_opt = new Image(mini);
	tex_titlescr_ico_opt->Load((void*)titlescr_ico_opt_png, titlescr_ico_opt_png_size, Image::IMAGE_TYPE_PNG);
	tex_titlescr_ico_opt->DrawRegion.Location.Set(center);
	tex_titlescr_ico_opt->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_titlescr_ico_xmb = new Image(mini);
	tex_titlescr_ico_xmb->Load((void*)titlescr_ico_xmb_png, titlescr_ico_xmb_png_size, Image::IMAGE_TYPE_PNG);
	tex_titlescr_ico_xmb->DrawRegion.Location.Set(center);
	tex_titlescr_ico_xmb->DrawRegion.Dimension.Set(mini->MAXW, mini->MAXH);

	tex_titlescr_logo = new Image(mini);
	tex_titlescr_logo->Load((void*)titlescr_logo_png, titlescr_logo_png_size, Image::IMAGE_TYPE_PNG);
	tex_titlescr_logo->DrawRegion.Location.Set(TEX_TITLESCR_LOGO_LOC);
	tex_titlescr_logo->DrawRegion.Dimension.Set(TEX_TITLESCR_LOGO_DIM);


	printf("Artemis Lite::Loaded Textures\n");
}

// Unload textures
void UnloadTextures() {
	if (tex_bgimg) {
		delete tex_bgimg;
		tex_bgimg = NULL;
	}

	if (tex_cheat) {
		delete tex_cheat;
		tex_cheat = NULL;
	}

	if (tex_circle_error_dark) {
		delete tex_circle_error_dark;
		tex_circle_error_dark = NULL;
	}

	if (tex_circle_error_light) {
		delete tex_circle_error_light;
		tex_circle_error_light = NULL;
	}

	if (tex_circle_loading_bg) {
		delete tex_circle_loading_bg;
		tex_circle_loading_bg = NULL;
	}

	if (tex_circle_loading_seek) {
		delete tex_circle_loading_seek;
		tex_circle_loading_seek = NULL;
	}

	if (tex_edit_ico_add) {
		delete tex_edit_ico_add;
		tex_edit_ico_add = NULL;
	}

	if (tex_edit_ico_del) {
		delete tex_edit_ico_del;
		tex_edit_ico_del = NULL;
	}

	if (tex_edit_shadow) {
		delete tex_edit_shadow;
		tex_edit_shadow = NULL;
	}

	if (tex_footer_ico_circle) {
		delete tex_footer_ico_circle;
		tex_footer_ico_circle = NULL;
	}

	if (tex_footer_ico_cross) {
		delete tex_footer_ico_cross;
		tex_footer_ico_cross = NULL;
	}

	if (tex_footer_ico_lt) {
		delete tex_footer_ico_lt;
		tex_footer_ico_lt = NULL;
	}

	if (tex_footer_ico_rt) {
		delete tex_footer_ico_rt;
		tex_footer_ico_rt = NULL;
	}

	if (tex_footer_ico_square) {
		delete tex_footer_ico_square;
		tex_footer_ico_square = NULL;
	}

	if (tex_footer_ico_triangle) {
		delete tex_footer_ico_triangle;
		tex_footer_ico_triangle = NULL;
	}

	if (tex_header_dot) {
		delete tex_header_dot;
		tex_header_dot = NULL;
	}

	if (tex_header_ico_abt) {
		delete tex_header_ico_abt;
		tex_header_ico_abt = NULL;
	}

	if (tex_header_ico_cht) {
		delete tex_header_ico_cht;
		tex_header_ico_cht = NULL;
	}

	if (tex_header_ico_opt) {
		delete tex_header_ico_opt;
		tex_header_ico_opt = NULL;
	}

	if (tex_header_ico_xmb) {
		delete tex_header_ico_xmb;
		tex_header_ico_xmb = NULL;
	}

	if (tex_header_line) {
		delete tex_header_line;
		tex_header_line = NULL;
	}

	if (tex_help) {
		delete tex_help;
		tex_help = NULL;
	}

	if (tex_mark_arrow) {
		delete tex_mark_arrow;
		tex_mark_arrow = NULL;
	}

	if (tex_mark_line) {
		delete tex_mark_line;
		tex_mark_line = NULL;
	}

	if (tex_opt_off) {
		delete tex_opt_off;
		tex_opt_off = NULL;
	}

	if (tex_opt_on) {
		delete tex_opt_on;
		tex_opt_on = NULL;
	}

	if (tex_scroll_bg) {
		delete tex_scroll_bg;
		tex_scroll_bg = NULL;
	}

	if (tex_scroll_lock) {
		delete tex_scroll_lock;
		tex_scroll_lock = NULL;
	}

	if (tex_titlescr_ico_abt) {
		delete tex_titlescr_ico_abt;
		tex_titlescr_ico_abt = NULL;
	}

	if (tex_titlescr_ico_cht) {
		delete tex_titlescr_ico_cht;
		tex_titlescr_ico_cht = NULL;
	}

	if (tex_titlescr_ico_opt) {
		delete tex_titlescr_ico_opt;
		tex_titlescr_ico_opt = NULL;
	}

	if (tex_titlescr_ico_xmb) {
		delete tex_titlescr_ico_xmb;
		tex_titlescr_ico_xmb = NULL;
	}

	if (tex_titlescr_logo) {
		delete tex_titlescr_logo;
		tex_titlescr_logo = NULL;
	}
}