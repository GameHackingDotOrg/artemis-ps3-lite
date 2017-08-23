/*
 * main.cpp
 *
 *
 *  The program start.
 *
 *  Video and sound are initialized, data is loaded, and drawing starts.
 *  Also contains methods for dpad acceleration and other pad effects.
 */

#include <stdio.h>							// printf()
#include <io/pad.h>							// Pad stuff

#include <Mini2D/Mini.hpp>					// Mini
#include <Mini2D/Image.hpp>					// Image class from Mini2D
#include <Mini2D/Font.hpp>					// Font class from Mini2D

#include "Menu/IMenu.hpp"					// IMenu interface declaration
#include "Menu/Menus.hpp"					// Declaration of all menus
#include "Menu/WindowManager.hpp"			// WindowManager declaration
#include "Globals.hpp"						// Images, Fonts

using namespace Mini2D;

// Mini2D instance
Mini * mini = NULL;

// WindowManager instance
Menu::WindowManager * windowManager = NULL;

// Pad related variables
padData psuedoPadData[MAX_PORT_NUM];
float dpadIgnore = 0;
unsigned long dpadIgnoreState = 0;
int doExit = 0;

// Mini2D Callbacks
int drawUpdate(float deltaTime, unsigned long frame);
void padUpdate(int changed, int port, padData pData);
void exit();

// Misc methods
void padCopy(padData * destination, padData * source, bool copyDpadOnly);
void loadData(Mini2D::Mini * mini);
void unloadData();

// Program Start
int main(s32 argc, const char* argv[]) {

	// Initialize Mini2D
	mini = new Mini((Mini::PadCallback_f)&padUpdate, (Mini::DrawCallback_f)&drawUpdate, (Mini::ExitCallback_f)&exit);

	// Load our textures
	loadData(mini);

	// Initialize our Window Manager with a fresh instance of the Start Menu
	windowManager = new Menu::WindowManager(mini);
	windowManager->OpenWindow(windowManager->AddWindow(new Menu::Start(mini, windowManager, -1)));

	// Here we set the deadzone of the analog sticks
	// The clear color
	// Enable alpha blending
	// And begin the draw loop (which will call our padUpdate and drawUpdate callbacks regularly)
	mini->SetAnalogDeadzone(15);
	mini->SetClearColor(0x23B2D7FF);
	mini->SetAlphaState(1);
	mini->BeginDrawLoop();

	// Unload and exit the application
	exit();

	return 0;
}

// Called every frame to draw contents onto screen
int drawUpdate(float deltaTime, unsigned long frame) {

	// Decrement dpadIgnore timer
	if (dpadIgnore >= 0)
		dpadIgnore -= deltaTime;

	// Draw active Window
	if (windowManager->Draw(deltaTime))
		return -1;

	return doExit;
}

// Processes pad and forwards the result to the window manager
void padUpdate(int changed, int port, padData pData) {

	// If L3 and R3 are pressed, close Artemis Lite
	if (pData.BTN_L3 && pData.BTN_R3 && (changed & Mini::BTN_CHANGED_L3 || changed & Mini::BTN_CHANGED_R3))
		doExit = -1;

	// If the psuedoPadData isn't initialized, copy data from pData
	if (psuedoPadData[port].len == 0)
		memcpy(&psuedoPadData[port], &pData, sizeof(padData));

	// Determine if dpad is in use or not
	if (changed & (Mini::BTN_CHANGED_UP | Mini::BTN_CHANGED_DOWN | Mini::BTN_CHANGED_LEFT | Mini::BTN_CHANGED_RIGHT)) {
		dpadIgnoreState = pData.BTN_UP || pData.BTN_DOWN || pData.BTN_LEFT || pData.BTN_RIGHT;
		dpadIgnore = 0;
	}

	// Disable dpad input
	psuedoPadData[port].BTN_UP = 0;
	psuedoPadData[port].BTN_DOWN = 0;
	psuedoPadData[port].BTN_LEFT = 0;
	psuedoPadData[port].BTN_RIGHT = 0;

	// If we have a dpad held down, then pass dpad values everytime dpadIgnore hits <= 0
	// Otherwise if no dpad button is held down, then just copy everything
	if (dpadIgnoreState && dpadIgnore <= 0) {
		// Copy the dpad data from pData to our buffer
		padCopy(&psuedoPadData[port], &pData, 1);

		// Increment the state
		dpadIgnoreState++;

		// Here, we have developing stages of scrolling speed
		// From 1 - 6, we send the dpad 4 times a second; lasting a total of 1.5 seconds
		// From 6 - 20, we send the dpad 10 times a second; lasting a total of 1.5 seconds
		// From 20 - Infinity, we send the dpad 40 times a second
		dpadIgnore = dpadIgnoreState > 20 ? 0.025 : (dpadIgnoreState > 6 ? 0.1 : 0.25);
	}
	else if (!dpadIgnoreState) {
		padCopy(&psuedoPadData[port], &pData, 0);


	}

	// Forward pad to active Window
	windowManager->Pad(port, &psuedoPadData[port]);
}

// Unload and exit
void exit() {

	printf("Artemis Lite::Exiting\n");

	if (windowManager) {
		delete windowManager;
		windowManager = NULL;
	}

	unloadData();

	if (mini) {
		delete mini;
		mini = NULL;
	}

	exit(0);
}

// Copies the pad data from source to destination
void padCopy(padData * destination, padData * source, bool copyDpadOnly) {

	if (!source || !destination)
		return;

	// Copy only the dpad values from source
	if (copyDpadOnly) {
		destination->BTN_UP = source->BTN_UP;
		destination->BTN_DOWN = source->BTN_DOWN;
		destination->BTN_LEFT = source->BTN_LEFT;
		destination->BTN_RIGHT = source->BTN_RIGHT;
		return;
	}

	// Copy entire struct
	memcpy(destination, source, sizeof(padData));
}

// Load textures, fonts
void loadData(Mini2D::Mini * mini) {

	// Load fonts
	FONT_DEFAULT = new Font(mini);
	FONT_DEFAULT->Load((void*)comfortaa_bold_ttf, comfortaa_bold_ttf_size, 48);

	// Initialize default variables
	LocToScreen2(LOC_CENTER, mini);
	LocToScreen2(DIM_FULL, mini);

	// Initialize font sizes
	FONT_SMALL *= mini->MAXW;
	FONT_MEDIUM *= mini->MAXW;
	FONT_LARGE *= mini->MAXW;

	// Load textures
	TEX_BGIMG = new Image(mini);
	TEX_BGIMG->Load((void*)bgimg_png, bgimg_png_size, Image::IMAGE_TYPE_PNG);

	TEX_CHEAT = new Image(mini);
	TEX_CHEAT->Load((void*)cheat_png, cheat_png_size, Image::IMAGE_TYPE_PNG);

	TEX_CIRCLE_ERROR_DARK = new Image(mini);
	TEX_CIRCLE_ERROR_DARK->Load((void*)circle_error_dark_png, circle_error_dark_png_size, Image::IMAGE_TYPE_PNG);

	TEX_CIRCLE_ERROR_LIGHT = new Image(mini);
	TEX_CIRCLE_ERROR_LIGHT->Load((void*)circle_error_light_png, circle_error_light_png_size, Image::IMAGE_TYPE_PNG);

	TEX_CIRCLE_LOADING_BG = new Image(mini);
	TEX_CIRCLE_LOADING_BG->Load((void*)circle_loading_bg_png, circle_loading_bg_png_size, Image::IMAGE_TYPE_PNG);

	TEX_CIRCLE_LOADING_SEEK = new Image(mini);
	TEX_CIRCLE_LOADING_SEEK->Load((void*)circle_loading_seek_png, circle_loading_seek_png_size, Image::IMAGE_TYPE_PNG);

	TEX_EDIT_ICO_ADD = new Image(mini);
	TEX_EDIT_ICO_ADD->Load((void*)edit_ico_add_png, edit_ico_add_png_size, Image::IMAGE_TYPE_PNG);

	TEX_EDIT_ICO_DEL = new Image(mini);
	TEX_EDIT_ICO_DEL->Load((void*)edit_ico_del_png, edit_ico_del_png_size, Image::IMAGE_TYPE_PNG);

	TEX_EDIT_SHADOW = new Image(mini);
	TEX_EDIT_SHADOW->Load((void*)edit_shadow_png, edit_shadow_png_size, Image::IMAGE_TYPE_PNG);

	TEX_FOOTER_ICO_CIRCLE = new Image(mini);
	TEX_FOOTER_ICO_CIRCLE->Load((void*)footer_ico_circle_png, footer_ico_circle_png_size, Image::IMAGE_TYPE_PNG);

	TEX_FOOTER_ICO_CROSS = new Image(mini);
	TEX_FOOTER_ICO_CROSS->Load((void*)footer_ico_cross_png, footer_ico_cross_png_size, Image::IMAGE_TYPE_PNG);

	TEX_FOOTER_ICO_LT = new Image(mini);
	TEX_FOOTER_ICO_LT->Load((void*)footer_ico_lt_png, footer_ico_lt_png_size, Image::IMAGE_TYPE_PNG);

	TEX_FOOTER_ICO_RT = new Image(mini);
	TEX_FOOTER_ICO_RT->Load((void*)footer_ico_rt_png, footer_ico_rt_png_size, Image::IMAGE_TYPE_PNG);

	TEX_FOOTER_ICO_SQUARE = new Image(mini);
	TEX_FOOTER_ICO_SQUARE->Load((void*)footer_ico_square_png, footer_ico_square_png_size, Image::IMAGE_TYPE_PNG);

	TEX_FOOTER_ICO_TRIANGLE = new Image(mini);
	TEX_FOOTER_ICO_TRIANGLE->Load((void*)footer_ico_triangle_png, footer_ico_triangle_png_size, Image::IMAGE_TYPE_PNG);

	TEX_HEADER_DOT = new Image(mini);
	TEX_HEADER_DOT->Load((void*)header_dot_png, header_dot_png_size, Image::IMAGE_TYPE_PNG);

	TEX_HEADER_ICO_ABT = new Image(mini);
	TEX_HEADER_ICO_ABT->Load((void*)header_ico_abt_png, header_ico_abt_png_size, Image::IMAGE_TYPE_PNG);

	TEX_HEADER_ICO_CHT = new Image(mini);
	TEX_HEADER_ICO_CHT->Load((void*)header_ico_cht_png, header_ico_cht_png_size, Image::IMAGE_TYPE_PNG);

	TEX_HEADER_ICO_OPT = new Image(mini);
	TEX_HEADER_ICO_OPT->Load((void*)header_ico_opt_png, header_ico_opt_png_size, Image::IMAGE_TYPE_PNG);

	TEX_HEADER_ICO_XMB = new Image(mini);
	TEX_HEADER_ICO_XMB->Load((void*)header_ico_xmb_png, header_ico_xmb_png_size, Image::IMAGE_TYPE_PNG);

	TEX_HEADER_LINE = new Image(mini);
	TEX_HEADER_LINE->Load((void*)header_line_png, header_line_png_size, Image::IMAGE_TYPE_PNG);

	TEX_HELP = new Image(mini);
	TEX_HELP->Load((void*)help_png, help_png_size, Image::IMAGE_TYPE_PNG);

	TEX_MARK_ARROW = new Image(mini);
	TEX_MARK_ARROW->Load((void*)mark_arrow_png, mark_arrow_png_size, Image::IMAGE_TYPE_PNG);

	TEX_MARK_LINE = new Image(mini);
	TEX_MARK_LINE->Load((void*)mark_line_png, mark_line_png_size, Image::IMAGE_TYPE_PNG);

	TEX_OPT_OFF = new Image(mini);
	TEX_OPT_OFF->Load((void*)opt_off_png, opt_off_png_size, Image::IMAGE_TYPE_PNG);

	TEX_OPT_ON = new Image(mini);
	TEX_OPT_ON->Load((void*)opt_on_png, opt_on_png_size, Image::IMAGE_TYPE_PNG);

	TEX_SCROLL_BG = new Image(mini);
	TEX_SCROLL_BG->Load((void*)scroll_bg_png, scroll_bg_png_size, Image::IMAGE_TYPE_PNG);

	TEX_SCROLL_LOCK = new Image(mini);
	TEX_SCROLL_LOCK->Load((void*)scroll_lock_png, scroll_lock_png_size, Image::IMAGE_TYPE_PNG);

	TEX_TITLESCR_ICO_ABT = new Image(mini);
	TEX_TITLESCR_ICO_ABT->Load((void*)titlescr_ico_abt_png, titlescr_ico_abt_png_size, Image::IMAGE_TYPE_PNG);

	TEX_TITLESCR_ICO_CHT = new Image(mini);
	TEX_TITLESCR_ICO_CHT->Load((void*)titlescr_ico_cht_png, titlescr_ico_cht_png_size, Image::IMAGE_TYPE_PNG);

	TEX_TITLESCR_ICO_OPT = new Image(mini);
	TEX_TITLESCR_ICO_OPT->Load((void*)titlescr_ico_opt_png, titlescr_ico_opt_png_size, Image::IMAGE_TYPE_PNG);

	TEX_TITLESCR_ICO_XMB = new Image(mini);
	TEX_TITLESCR_ICO_XMB->Load((void*)titlescr_ico_xmb_png, titlescr_ico_xmb_png_size, Image::IMAGE_TYPE_PNG);

	TEX_TITLESCR_LOGO = new Image(mini);
	TEX_TITLESCR_LOGO->Load((void*)titlescr_logo_png, titlescr_logo_png_size, Image::IMAGE_TYPE_PNG);

	TEX_TITLESCR_LABEL = new Image(mini);
	TEX_TITLESCR_LABEL->Load((void*)titlescr_label_png, titlescr_label_png_size, Image::IMAGE_TYPE_PNG);

	TEX_TITLESCR_LINK = new Image(mini);
	TEX_TITLESCR_LINK->Load((void*)titlescr_link_png, titlescr_link_png_size, Image::IMAGE_TYPE_PNG);

	// Load custom characters into font
	FONT_DEFAULT->AddChar(CHAR_CROSS, TEX_FOOTER_ICO_CROSS, 4);
	FONT_DEFAULT->AddChar(CHAR_SQUARE, TEX_FOOTER_ICO_SQUARE, 4);
	FONT_DEFAULT->AddChar(CHAR_TRIANGLE, TEX_FOOTER_ICO_TRIANGLE, 4);
	FONT_DEFAULT->AddChar(CHAR_CIRCLE, TEX_FOOTER_ICO_CIRCLE, 4);
	FONT_DEFAULT->AddChar(CHAR_LEFT, TEX_FOOTER_ICO_LT, 4);
	FONT_DEFAULT->AddChar(CHAR_RIGHT, TEX_FOOTER_ICO_RT, 4);
}

// Unload textures, fonts
void unloadData() {

	if (FONT_DEFAULT) {
		delete FONT_DEFAULT;
		FONT_DEFAULT = NULL;
	}

	if (TEX_BGIMG) {
		delete TEX_BGIMG;
		TEX_BGIMG = NULL;
	}

	if (TEX_CHEAT) {
		delete TEX_CHEAT;
		TEX_CHEAT = NULL;
	}

	if (TEX_CIRCLE_ERROR_DARK) {
		delete TEX_CIRCLE_ERROR_DARK;
		TEX_CIRCLE_ERROR_DARK = NULL;
	}

	if (TEX_CIRCLE_ERROR_LIGHT) {
		delete TEX_CIRCLE_ERROR_LIGHT;
		TEX_CIRCLE_ERROR_LIGHT = NULL;
	}

	if (TEX_CIRCLE_LOADING_BG) {
		delete TEX_CIRCLE_LOADING_BG;
		TEX_CIRCLE_LOADING_BG = NULL;
	}

	if (TEX_CIRCLE_LOADING_SEEK) {
		delete TEX_CIRCLE_LOADING_SEEK;
		TEX_CIRCLE_LOADING_SEEK = NULL;
	}

	if (TEX_EDIT_ICO_ADD) {
		delete TEX_EDIT_ICO_ADD;
		TEX_EDIT_ICO_ADD = NULL;
	}

	if (TEX_EDIT_ICO_DEL) {
		delete TEX_EDIT_ICO_DEL;
		TEX_EDIT_ICO_DEL = NULL;
	}

	if (TEX_EDIT_SHADOW) {
		delete TEX_EDIT_SHADOW;
		TEX_EDIT_SHADOW = NULL;
	}

	if (TEX_FOOTER_ICO_CIRCLE) {
		delete TEX_FOOTER_ICO_CIRCLE;
		TEX_FOOTER_ICO_CIRCLE = NULL;
	}

	if (TEX_FOOTER_ICO_CROSS) {
		delete TEX_FOOTER_ICO_CROSS;
		TEX_FOOTER_ICO_CROSS = NULL;
	}

	if (TEX_FOOTER_ICO_LT) {
		delete TEX_FOOTER_ICO_LT;
		TEX_FOOTER_ICO_LT = NULL;
	}

	if (TEX_FOOTER_ICO_RT) {
		delete TEX_FOOTER_ICO_RT;
		TEX_FOOTER_ICO_RT = NULL;
	}

	if (TEX_FOOTER_ICO_SQUARE) {
		delete TEX_FOOTER_ICO_SQUARE;
		TEX_FOOTER_ICO_SQUARE = NULL;
	}

	if (TEX_FOOTER_ICO_TRIANGLE) {
		delete TEX_FOOTER_ICO_TRIANGLE;
		TEX_FOOTER_ICO_TRIANGLE = NULL;
	}

	if (TEX_HEADER_DOT) {
		delete TEX_HEADER_DOT;
		TEX_HEADER_DOT = NULL;
	}

	if (TEX_HEADER_ICO_ABT) {
		delete TEX_HEADER_ICO_ABT;
		TEX_HEADER_ICO_ABT = NULL;
	}

	if (TEX_HEADER_ICO_CHT) {
		delete TEX_HEADER_ICO_CHT;
		TEX_HEADER_ICO_CHT = NULL;
	}

	if (TEX_HEADER_ICO_OPT) {
		delete TEX_HEADER_ICO_OPT;
		TEX_HEADER_ICO_OPT = NULL;
	}

	if (TEX_HEADER_ICO_XMB) {
		delete TEX_HEADER_ICO_XMB;
		TEX_HEADER_ICO_XMB = NULL;
	}

	if (TEX_HEADER_LINE) {
		delete TEX_HEADER_LINE;
		TEX_HEADER_LINE = NULL;
	}

	if (TEX_HELP) {
		delete TEX_HELP;
		TEX_HELP = NULL;
	}

	if (TEX_MARK_ARROW) {
		delete TEX_MARK_ARROW;
		TEX_MARK_ARROW = NULL;
	}

	if (TEX_MARK_LINE) {
		delete TEX_MARK_LINE;
		TEX_MARK_LINE = NULL;
	}

	if (TEX_OPT_OFF) {
		delete TEX_OPT_OFF;
		TEX_OPT_OFF = NULL;
	}

	if (TEX_OPT_ON) {
		delete TEX_OPT_ON;
		TEX_OPT_ON = NULL;
	}

	if (TEX_SCROLL_BG) {
		delete TEX_SCROLL_BG;
		TEX_SCROLL_BG = NULL;
	}

	if (TEX_SCROLL_LOCK) {
		delete TEX_SCROLL_LOCK;
		TEX_SCROLL_LOCK = NULL;
	}

	if (TEX_TITLESCR_ICO_ABT) {
		delete TEX_TITLESCR_ICO_ABT;
		TEX_TITLESCR_ICO_ABT = NULL;
	}

	if (TEX_TITLESCR_ICO_CHT) {
		delete TEX_TITLESCR_ICO_CHT;
		TEX_TITLESCR_ICO_CHT = NULL;
	}

	if (TEX_TITLESCR_ICO_OPT) {
		delete TEX_TITLESCR_ICO_OPT;
		TEX_TITLESCR_ICO_OPT = NULL;
	}

	if (TEX_TITLESCR_ICO_XMB) {
		delete TEX_TITLESCR_ICO_XMB;
		TEX_TITLESCR_ICO_XMB = NULL;
	}

	if (TEX_TITLESCR_LOGO) {
		delete TEX_TITLESCR_LOGO;
		TEX_TITLESCR_LOGO = NULL;
	}

	if (TEX_TITLESCR_LABEL) {
		delete TEX_TITLESCR_LABEL;
		TEX_TITLESCR_LABEL = NULL;
	}

	if (TEX_TITLESCR_LINK) {
		delete TEX_TITLESCR_LINK;
		TEX_TITLESCR_LINK = NULL;
	}
}
