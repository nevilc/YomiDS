#ifndef H_FIGHTER
#define H_FIGHTER

#include "deck.h"

class Fighter{
	const char* _name;
	const char* _description;

	unsigned char _maxcombo;

	unsigned char _attack;
	unsigned char _throw;
	unsigned char _block;
	unsigned char _dodge;
	
	const char* _abilityname;
	//Ability

	const char* _flavor;

	unsigned char _hp;

	Deck const* _deck;

public:
	Fighter(const char* name_, const char* description_, unsigned char maxcombo_, unsigned char attack_, unsigned char throw_, unsigned char block_, unsigned char dodge_, const char* abilityname_, const char* flavor_, unsigned char hp_, const Deck& deck_):
	  _name(name_), _description(description_), _maxcombo(maxcombo_), _attack(attack_), _throw(throw_), _block(block_), _dodge(dodge_), _abilityname(abilityname_), _flavor(flavor_), _hp(hp_), _deck(&deck_){}


	const char* name() const{
		return _name;
	}
	const char* description() const{
		return _description;
	}
	unsigned char maxcombo() const{
		return _maxcombo;
	}
	unsigned char attackrank() const{
		return _attack;
	}
	unsigned char throwrank() const{
		return _throw;
	}
	unsigned char dodgerank() const{
		return _dodge;
	}
	unsigned char hp() const{
		return _hp;
	}
	const char* abilityname() const{
		return _abilityname;
	}
	const char* flavor() const{
		return _flavor;
	}
	const Deck& deck() const{
		return *_deck;
	}
};

extern Fighter FGrave;
extern Fighter FMidori;
extern Fighter FRook;
extern Fighter FValerie;
extern Fighter FLum;
extern Fighter FJaina;
extern Fighter FSetsuki;


#endif//H_FIGHTER
