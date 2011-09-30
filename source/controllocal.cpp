#include "controllocal.h"

void ControlLocal::_set_input(Input* const i){
	if (_input == i){
		return;
	}

	if (_input){
		_input->disable();
	}
	_input = i;
	if (_input){
		_input->enable();
	}
}


void ControlLocal::_terminate_input(){
	_input->reset();
	_set_input(NULL);
}

void ControlLocal::_free_input(Input* const i) const{
	delete _input;
}

void ControlLocal::_set_display(Display* const* d){
	if (_display == d){
		return;
	}

	for (size_t i = 0; _display && _display[i] != NULL; ++i){
		_display[i]->disable();
	}
	_display = d;
	for (size_t i = 0; _display && _display[i] != NULL; ++i){
		_display[i]->enable();
	}
}

void ControlLocal::_terminate_display(){
	_set_display(NULL);
}

void ControlLocal::_free_display(Display* const* d) const{
	for (size_t i = 0; d[i] != NULL; ++i){
		delete d[i];
	}
}

Input::Response ControlLocal::_hand_select(){
	_set_input(_input_hand);
	_set_display(_display_hand);
	_display_hand.card->update(_player->hand().at(_input_hand->cursor()), _input_hand->flipped());
	_display_hand.hand->update(_player->hand(), _input_hand->cursor(), _input_hand->flipped());
	//_display_hand.player->update


	Input::Response r = _input->get();
	if (r != Input::wait){
		_terminate_input();
	}
	
	return r;
}

ControlLocal::ControlLocal(Player& player) : Control(player), _input(NULL), _display(NULL),
	_input_hand(new InputContainer(player.hand())),
	_input_cancel(new InputCancel()),
	_display_hand{
		new DisplayPlayerOverview(0, 0, 0, 32, 1, player),
		new DisplayContainer(0, 0, 1, 32, 21, player.hand()), 
		new DisplayCard(1, 0, 0, 32, 24, player.hand().at(0), false),
		NULL
	}
{
	_set_display(_display_hand);
}

ControlLocal::~ControlLocal(){
	_free_input(_input_hand);
	_free_display(_display_hand);
}

Input::Response ControlLocal::standard(){
	return _hand_select();
}

Input::Response ControlLocal::powerup(){
	return _hand_select();
}

Input::Response ControlLocal::combo(){
	return _hand_select();
}

Input::Response ControlLocal::followup(){
	return _hand_select();
}

Input::Response ControlLocal::waiting(){
	_set_input(_input_cancel);
	_set_display(_display_hand);

	Input::Response r = _input->get();
	if (r != Input::wait){
		_terminate_input();
	}

	return r;
}
