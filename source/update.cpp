#include "update.h"

#include "turn.h"

touchPosition stylus;
uint32 keyDown;
bool killbit = 0;

#ifdef TEXTMODE
	//PrintConsole console[2];
	//PrintConsole console_top;
	//PrintConsole console_bottom;
#endif//TEXTMODE

void update(){
	scanKeys();
	touchRead(&stylus);
	keyDown = keysDownRepeat();

	//Play::get_state()->run();
	
	swiWaitForVBlank();
}

