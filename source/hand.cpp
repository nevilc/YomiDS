#include "hand.h"

#include <nds.h>

void Hand::insert(unsigned char i, const Card& c){
	_lastremoved = -1;
	CardContainerOrdered::insert(i, c);
}

void Hand::remove(unsigned char i){
	_lastremoved = i;
	CardContainerOrdered::remove(i);
}

void Hand::reinsert(const Card& c){
	sassert(_lastremoved != -1, "Attempting invalid reinsert");

	insert(_lastremoved, c);

	//_lastremoved = -1;
}

/*
void Hand::_compact(){
	dprint("Compacting Hand");
	for (unsigned char i = _lastremoved; i < size(); ++i){
		_cardarray()[i] = _cardarray()[i + 1];
	}
	_lastremoved = _maxsize();
}

bool Hand::_uncompacted() const{
	return _lastremoved == _maxsize();
}

Hand::Hand() : _lastremoved(_maxsize()){

}

void Hand::remove(unsigned char i){
	// "remove" the card, but leave it where it is
	// If the next card added is the same card, restore
	// the "removed" card
	if (_uncompacted()){
		_compact();
	}

	_lastremoved = i;

}

const Card& Hand::at(unsigned char i){
	//TODO
}

void Hand::push(const Card& c){
	//TODO
}

const Card& Hand::pop(){
	//
}

const Card& Hand::peek() const{
	//TODO
}
*/

void Hand::draw(CardContainerBase& deck){
	push(deck.pop());
}


