#include "deck.h"

Deck::Deck(Card const* const* cardlist){
	// Slightly inefficient, but infinitely more sane than the previous solution
	for (unsigned int i = 0; i < rule::max_decksize; ++i){
		push(*cardlist[i]);
	}
}

void Deck::shuffle(){
	for (unsigned char i = 0; i < size(); ++i){
		Card const* swap = _cardarray()[i];
		unsigned char pos = rand() % size();
		_cardarray()[i] = _cardarray()[pos];
		_cardarray()[pos] = swap;
	}
}
