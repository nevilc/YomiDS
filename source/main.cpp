#include <nds.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "nf_2d.h"

#include "options.h"

#include "player.h"
#include "turn.h"
#include "update.h"
#include "cardfilter.h"
#include "display.h"

#include "controllocal.h"
#include "controlai.h"

volatile unsigned int framecount = 0;
void vblank(){
	Display::drawall();
	++framecount;
}

int main(int argc, char** argv){
	irqSet(IRQ_VBLANK, &vblank);

	#ifdef TEXTMODE
		videoSetMode(MODE_0_2D);
		videoSetModeSub(MODE_0_2D);

		vramSetBankA(VRAM_A_MAIN_BG);
		vramSetBankC(VRAM_C_SUB_BG);
	#endif//TEXTMODE

	Display::init();

	keysSetRepeat(30, 12);

	srand(time(NULL));

	Player P1(FGrave);
	Player P2(FMidori);

	ControlLocal	C1(P1);
	ControlAI		C2(P2);

	//DisplayPlayerOverview a(0, 0, 0, 32, 1, P1);
	//DisplayContainer b(0, 0, 1, 32, 21, P1.hand());

	//DisplayCard c(1, 0, 0, 32, 24, P1.hand().at(0), false);

	Game(&C1, &C2);

	while(1){
		update();
	}
	return 0;
}
