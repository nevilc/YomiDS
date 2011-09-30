#ifndef H_CONTROLAI
#define H_CONTROLAI

#include <cstdlib>

#include "control.h"
#include "ai.h"

class ControlAI : public Control{

public:
	ControlAI(Player& player) : Control(player){}

	virtual Input::Response standard(){
		// TODO

		// TEST
		// return a random card, valid or not
		int cpos = rand() % player().hand().size();
		bool side = bool(rand() % 2);

		Card const* c = &player().hand().at(cpos);
		player().hand().remove(cpos);
		return Input::Response{c, Input::Response::message_type(side)};

		return Input::wait;
	}

	virtual Input::Response powerup(){
		return Input::nocard;
	}

	virtual Input::Response combo(){
		return Input::nocard;
	}

	virtual Input::Response followup(){
		return Input::nocard;
	}

	virtual Input::Response waiting(){
		return Input::wait;
	}
};

#endif//H_CONTROLAI
