#ifndef H_RULES
#define H_RULES

namespace rule{
	// Although theoretically changable, due to the nature of the game, many assumptions are
	// made that rule::max_players will be 2
	const unsigned int max_players = 2;
	
	// To avoid the overhead of std::vector, hands are implemented just as fixed size arrays
	// Having a max hand size doesn't strictly follow the rules, but with a large enough max,
	// this should very rarely be an issue
	const unsigned int max_handsize = 14;
	
	// Starting handsize is seven, according to the official rules, but you can change it here
	// if you are so inclined
	const unsigned int initial_handsize = 7;

	// Again, while changable, some locations require a hardcoded 54 (specifically the Deck 
	// constructor) so changing this value is of little use
	const unsigned int max_decksize = 54;

	// The maximum discard size should be enough to hold the entire deck (although that is 
	// unlikely)
	const unsigned int max_discardsize = max_decksize;

	// The maximum combo limit is only for memory purposes, if you want to alter a fighter's
	// combo limit, you have to modify that definition.
	// This value should be equal to the combo points of the fighter with the most minus 1 (the
	// initial attack). So normally this value will be 5 (Valerie's 6 - 1 = 5)
	const unsigned int max_combo = 5;

	// Also necessarily hardcoded, with no reason to change anyways
	const unsigned int card_sides = 2;

	// Not hard coded, but there's little reason to change this
	// Could be used to cap to discarding pairs or triples for whatever reason
	const unsigned int max_powerup = 4;
}

#endif//H_RULES
