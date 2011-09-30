#ifndef H_UPDATE
#define H_UPDATE

#include <nds.h>

#include "options.h"

// These globals should be moved somewhere more fitting
extern touchPosition stylus;
extern uint32 keyDown;
extern bool killbit;

#ifdef TEXTMODE
	//extern PrintConsole console[2];
	//extern PrintConsole console_top;
	//extern PrintConsole console_bottom;
#endif//TEXTMODE

void update();

#endif
