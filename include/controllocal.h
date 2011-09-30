#ifndef H_CONTROLLOCAL
#define H_CONTROLLOCAL

#include <nds.h>

#include "control.h"
#include "input.h"
#include "display.h"
#include "aec.h"
#include "update.h"
#include "debug.h"

class ControlLocal : public Control{

	Input::Response _select_hand();

	Input* _input;
	Display* const* _display;

	InputContainer* const _input_hand;
	InputCancel* const _input_cancel;
	
	// NONX pointer sizes may vary
	struct{
		DisplayPlayerOverview* const player;
		DisplayContainer* const hand;
		DisplayCard* const card;
		Display* const end;
		
		operator Display* const *() const{
			return reinterpret_cast<Display* const *>(&player);
		}
	} _display_hand;


	void _set_display(Display* const* d);
	void _terminate_display();
	void _free_display(Display* const* d) const;

	void _set_input(Input* const i);
	void _terminate_input();
	void _free_input(Input* const i) const;

	Input::Response _hand_select();

public:
	ControlLocal(Player& player);
	virtual ~ControlLocal();

	virtual Input::Response standard();
	virtual Input::Response powerup();
	virtual Input::Response combo();
	virtual Input::Response followup();
	virtual Input::Response waiting();
};

#endif//H_CONTROLLOCAL
