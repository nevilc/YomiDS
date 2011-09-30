#include "input.h"

#include "debug.h"

LinkedList* Input::_instances;

Input::Response Input::wait{nullptr, Response::wait};
Input::Response Input::nocard{nullptr, Response::nocard};
Input::Response Input::cancel{nullptr, Response::cancel};
Input::Response Input::exit{nullptr, Response::exit};

Input::Input(){
	dprint("New Input");
}

void Input::disable(){
	_enabled = false;
}

void Input::enable(){
	_enabled = true;
}

InputContainer::InputContainer(CardContainerBase& container_) : _container(&container_), _handpos(0), _flipped(0){

}

Input::Response InputContainer::get(){
	if (keyDown & KEY_LEFT){
		if (_handpos == 0){
			_handpos = _container->size() - 1;
		}else{
			--_handpos;
		}
	}
	if (keyDown & KEY_RIGHT){
		if (_handpos == _container->size() - 1){
			_handpos = 0;
		}else{
			++_handpos;
		}
	}

	if (keyDown & KEY_A){
		Card const* c = &_container->at(_handpos);
		_container->remove(_handpos);

		reset();
		return Response{c, Response::message_type(_flipped)};
	}
	if (keyDown & KEY_X){
		_flipped = !_flipped;
	}
	if (keyDown & KEY_Y){
		reset();
		return nocard;
	}
	if (keyDown & KEY_B){
		reset();
		return cancel;
	}


	return wait;
}

void InputContainer::reset(){
	_handpos = 0;
	_flipped = 0;
}

unsigned char InputContainer::cursor() const{
	return _handpos;
}

bool InputContainer::flipped() const{
	return _flipped;
}

Input::Response InputCancel::get(){
	if (keyDown & KEY_B){
		return Input::cancel;
	}
	return Input::wait;
}
