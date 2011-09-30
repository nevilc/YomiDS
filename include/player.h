#ifndef H_PLAYER
#define H_PLAYER

#include "hand.h"
#include "deck.h"
#include "discard.h"
#include "fighter.h"

#include <cstdio>

class Player{
	const Fighter* _fighter;
	Deck _deck;
	Hand _hand;
	Discard _discard;

	unsigned char _hp;

public:
	const Fighter& fighter() const{
		return *_fighter;
	}

	unsigned char hp() const{
		return _hp;
	}
	Deck& deck(){
		return _deck;
	}
	const Deck& deck() const{
		return _deck;
	}
	Hand& hand(){
		return _hand;
	}
	const Hand& hand() const{
		return _hand;
	}
	Discard& discard(){
		return _discard;
	}
	const Discard& discard() const{
		return _discard;
	}
	void hurt(unsigned char amt){
		if (amt >= _hp){
			// TODO die
		}else{
			_hp -= amt;
		}
	}

	void draw(){
		_hand.draw(_deck);
	}

	Player(Fighter& fighter_) : _fighter(&fighter_), _deck(fighter_.deck()), _hand(), _discard(), _hp(fighter_.hp()){

		// Shuffle
		_deck.shuffle();
		// Draw starting hand
		// Subtract one from starting hand to compensate for the initial draw that should be skipped first turn
		for (unsigned int i = 0; i < rule::initial_handsize - 1; ++i){
			hand().draw(deck());
		}
	}
};

#endif//H_PLAYER
