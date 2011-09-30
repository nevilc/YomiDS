#ifndef H_DECK
#define H_DECK

#include <cstdarg>
#include <cstdlib>

#include <nds.h>

#include "card.h"
#include "rules.h"

class Deck : public CardContainer<rule::max_decksize>{
public:
	Deck();
	Deck(Card const* const* cardlist);
	~Deck(){}
	// Does this make me a bad person?
	/*	
	#define CC(num) const Card& CC##num
	Deck(	CC( 0), CC( 1), CC( 2), CC( 3), CC( 4), CC( 5), CC( 6), CC( 7),
			CC( 8), CC( 9), CC(10), CC(11), CC(12), CC(13), CC(14), CC(15),
			CC(16), CC(17), CC(18), CC(19), CC(20), CC(21), CC(22), CC(23),
			CC(24), CC(25), CC(26), CC(27), CC(28), CC(29), CC(30), CC(31),
			CC(32), CC(33), CC(34), CC(35), CC(36), CC(37), CC(38), CC(39),
			CC(40), CC(41), CC(42), CC(43), CC(44), CC(45), CC(46), CC(47),
			CC(48), CC(49), CC(50), CC(51), CC(52), CC(53)) : _cards{
				&CC0, &CC1, &CC2, &CC3, &CC4, &CC5, &CC6, &CC7,
				&CC8, &CC9, &CC10, &CC11, &CC12, &CC13, &CC14, &CC15,
				&CC16, &CC17, &CC18, &CC19, &CC20, &CC21, &CC22, &CC23,
				&CC24, &CC25, &CC26, &CC27, &CC28, &CC29, &CC30, &CC31,
				&CC32, &CC33, &CC34, &CC35, &CC36, &CC37, &CC38, &CC39,
				&CC40, &CC41, &CC42, &CC43, &CC44, &CC45, &CC46, &CC47,
				&CC48, &CC49, &CC50, &CC51, &CC52, &CC53}, _size(rule::max_decksize){}

	// Yes, yes it does
	// (Why do I go out of the way to make optimizations the compiler likely will effectively do anyways)
	#undef CC
	*/

	void shuffle();
};


#endif//H_DECK
