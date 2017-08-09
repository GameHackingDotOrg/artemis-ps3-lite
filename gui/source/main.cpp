#include <stdio.h>
#include <io/pad.h>

#include <Mini2D/Mini2D.hpp>
#include <Mini2D/Image.hpp>
#include <Mini2D/Font.hpp>

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
void loadData(Mini2D * mini);
void unloadData();

int main(s32 argc, const char* argv[]) {

	// Initialize Mini2D
	mini = new Mini2D((Mini2D::PadCallback_f)&padUpdate, (Mini2D::DrawCallback_f)&drawUpdate, (Mini2D::ExitCallback_f)&exit);

	// Load our textures
	loadData(mini);

	// Initialize the main menu
	menuStart = new Menu::Start(mini, 1, 0);

	mini->SetAnalogDeadzone(15);
	mini->SetClearColor(0x23B2D7FF);
	mini->SetAlphaState(1);
	mini->BeginDrawLoop();

	unloadData();

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

// Load textures, fonts
void loadData(Mini2D * mini) {

	// Load fonts
	font_comfortaa_regular = new Font(mini);
	font_comfortaa_regular->Load((void*)comfortaa_regular_ttf, comfortaa_regular_ttf_size, 64, 64);

	font_comfortaa_bold = new Font(mini);
	font_comfortaa_bold->Load((void*)comfortaa_bold_ttf, comfortaa_bold_ttf_size, 64, 64);

	font_comfortaa_light = new Font(mini);
	font_comfortaa_light->Load((void*)comfortaa_light_ttf, comfortaa_light_ttf_size, 64, 64);

	// Initialize default variables
	CENTER_LOC.X *= mini->MAXW; CENTER_LOC.Y *= mini->MAXH;
	FULL_DIM.X *= mini->MAXW; FULL_DIM.Y *= mini->MAXH;

	// Initialize font sizes
	FONT_SMALL.X *= mini->MAXW; FONT_SMALL.Y *= mini->MAXH;
	FONT_MEDIUM.X *= mini->MAXW; FONT_MEDIUM.Y *= mini->MAXH;
	FONT_LARGE.X *= mini->MAXW; FONT_LARGE.Y *= mini->MAXH;

	// Load textures
	tex_bgimg = new Image(mini);
	tex_bgimg->Load((void*)bgimg_png, bgimg_png_size, Image::IMAGE_TYPE_PNG);

	tex_cheat = new Image(mini);
	tex_cheat->Load((void*)cheat_png, cheat_png_size, Image::IMAGE_TYPE_PNG);

	tex_circle_error_dark = new Image(mini);
	tex_circle_error_dark->Load((void*)circle_error_dark_png, circle_error_dark_png_size, Image::IMAGE_TYPE_PNG);

	tex_circle_error_light = new Image(mini);
	tex_circle_error_light->Load((void*)circle_error_light_png, circle_error_light_png_size, Image::IMAGE_TYPE_PNG);

	tex_circle_loading_bg = new Image(mini);
	tex_circle_loading_bg->Load((void*)circle_loading_bg_png, circle_loading_bg_png_size, Image::IMAGE_TYPE_PNG);

	tex_circle_loading_seek = new Image(mini);
	tex_circle_loading_seek->Load((void*)circle_loading_seek_png, circle_loading_seek_png_size, Image::IMAGE_TYPE_PNG);

	tex_edit_ico_add = new Image(mini);
	tex_edit_ico_add->Load((void*)edit_ico_add_png, edit_ico_add_png_size, Image::IMAGE_TYPE_PNG);

	tex_edit_ico_del = new Image(mini);
	tex_edit_ico_del->Load((void*)edit_ico_del_png, edit_ico_del_png_size, Image::IMAGE_TYPE_PNG);

	tex_edit_shadow = new Image(mini);
	tex_edit_shadow->Load((void*)edit_shadow_png, edit_shadow_png_size, Image::IMAGE_TYPE_PNG);

	tex_footer_ico_circle = new Image(mini);
	tex_footer_ico_circle->Load((void*)footer_ico_circle_png, footer_ico_circle_png_size, Image::IMAGE_TYPE_PNG);

	tex_footer_ico_cross = new Image(mini);
	tex_footer_ico_cross->Load((void*)footer_ico_cross_png, footer_ico_cross_png_size, Image::IMAGE_TYPE_PNG);

	tex_footer_ico_lt = new Image(mini);
	tex_footer_ico_lt->Load((void*)footer_ico_lt_png, footer_ico_lt_png_size, Image::IMAGE_TYPE_PNG);

	tex_footer_ico_rt = new Image(mini);
	tex_footer_ico_rt->Load((void*)footer_ico_rt_png, footer_ico_rt_png_size, Image::IMAGE_TYPE_PNG);

	tex_footer_ico_square = new Image(mini);
	tex_footer_ico_square->Load((void*)footer_ico_square_png, footer_ico_square_png_size, Image::IMAGE_TYPE_PNG);

	tex_footer_ico_triangle = new Image(mini);
	tex_footer_ico_triangle->Load((void*)footer_ico_triangle_png, footer_ico_triangle_png_size, Image::IMAGE_TYPE_PNG);

	tex_header_dot = new Image(mini);
	tex_header_dot->Load((void*)header_dot_png, header_dot_png_size, Image::IMAGE_TYPE_PNG);

	tex_header_ico_abt = new Image(mini);
	tex_header_ico_abt->Load((void*)header_ico_abt_png, header_ico_abt_png_size, Image::IMAGE_TYPE_PNG);

	tex_header_ico_cht = new Image(mini);
	tex_header_ico_cht->Load((void*)header_ico_cht_png, header_ico_cht_png_size, Image::IMAGE_TYPE_PNG);

	tex_header_ico_opt = new Image(mini);
	tex_header_ico_opt->Load((void*)header_ico_opt_png, header_ico_opt_png_size, Image::IMAGE_TYPE_PNG);

	tex_header_ico_xmb = new Image(mini);
	tex_header_ico_xmb->Load((void*)header_ico_xmb_png, header_ico_xmb_png_size, Image::IMAGE_TYPE_PNG);

	tex_header_line = new Image(mini);
	tex_header_line->Load((void*)header_line_png, header_line_png_size, Image::IMAGE_TYPE_PNG);

	tex_help = new Image(mini);
	tex_help->Load((void*)help_png, help_png_size, Image::IMAGE_TYPE_PNG);

	tex_mark_arrow = new Image(mini);
	tex_mark_arrow->Load((void*)mark_arrow_png, mark_arrow_png_size, Image::IMAGE_TYPE_PNG);

	tex_mark_line = new Image(mini);
	tex_mark_line->Load((void*)mark_line_png, mark_line_png_size, Image::IMAGE_TYPE_PNG);

	tex_opt_off = new Image(mini);
	tex_opt_off->Load((void*)opt_off_png, opt_off_png_size, Image::IMAGE_TYPE_PNG);

	tex_opt_on = new Image(mini);
	tex_opt_on->Load((void*)opt_on_png, opt_on_png_size, Image::IMAGE_TYPE_PNG);

	tex_scroll_bg = new Image(mini);
	tex_scroll_bg->Load((void*)scroll_bg_png, scroll_bg_png_size, Image::IMAGE_TYPE_PNG);

	tex_scroll_lock = new Image(mini);
	tex_scroll_lock->Load((void*)scroll_lock_png, scroll_lock_png_size, Image::IMAGE_TYPE_PNG);

	tex_titlescr_ico_abt = new Image(mini);
	tex_titlescr_ico_abt->Load((void*)titlescr_ico_abt_png, titlescr_ico_abt_png_size, Image::IMAGE_TYPE_PNG);

	tex_titlescr_ico_cht = new Image(mini);
	tex_titlescr_ico_cht->Load((void*)titlescr_ico_cht_png, titlescr_ico_cht_png_size, Image::IMAGE_TYPE_PNG);

	tex_titlescr_ico_opt = new Image(mini);
	tex_titlescr_ico_opt->Load((void*)titlescr_ico_opt_png, titlescr_ico_opt_png_size, Image::IMAGE_TYPE_PNG);

	tex_titlescr_ico_xmb = new Image(mini);
	tex_titlescr_ico_xmb->Load((void*)titlescr_ico_xmb_png, titlescr_ico_xmb_png_size, Image::IMAGE_TYPE_PNG);

	tex_titlescr_logo = new Image(mini);
	tex_titlescr_logo->Load((void*)titlescr_logo_png, titlescr_logo_png_size, Image::IMAGE_TYPE_PNG);


	printf("Artemis Lite::Loaded Textures\n");
}

// Unload textures, fonts
void unloadData() {
	if (font_comfortaa_regular) {
		delete font_comfortaa_regular;
		font_comfortaa_regular = NULL;
	}
	
	if (font_comfortaa_bold) {
		delete font_comfortaa_bold;
		font_comfortaa_bold = NULL;
	}
	
	if (font_comfortaa_light) {
		delete font_comfortaa_light;
		font_comfortaa_light = NULL;
	}


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