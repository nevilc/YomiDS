#ifndef H_CARD
#define H_CARD

#include <cstdlib>
#include <cstdio>

#include <nds.h>

#include "rules.h"
#include "debug.h"

class Side{
public:
	enum Type{	Attack		= 0x1, 
				Dodge		= 0x2, 
				Throw		= 0x4, 
				Block		= 0x8, 
				Burst		= 0x10
	};
	enum Tag{	None		= 0x0,
				Starter		= 0x1, 
				Ender		= 0x2, 
				Linker		= 0x4, 
				NoCombo		= 0x8,
				Knockdown	= 0x10, 

				Dragon		= 0x20,
				TimeSpiral	= 0x40
	};
private:
				
	Type _type;
	
	const char* _name;

	unsigned char _speed;
	unsigned char _combopoints;
	unsigned char _damage;
	unsigned char _blockdamage;
	unsigned char _bonusdamage;
	unsigned char _bonuslimit;
	unsigned char _extracost;
	
	Tag _tags;

public:
	Side(Type type_, const char* name_ = "", unsigned char speed_ = 0, 
		unsigned char combopoints_ = 0, unsigned char damage_ = 0, 
		unsigned char blockdamage_ = 0, unsigned char bonusdamage_ = 0, 
		unsigned char bonuslimit_ = 0, unsigned char extracost_ = 0, 
		Tag tags_ = None): 
		_type(type_), _name(name_), _speed(speed_), _combopoints(combopoints_), 
		_damage(damage_), _blockdamage(blockdamage_), _bonusdamage(bonusdamage_), 
		_bonuslimit(bonuslimit_), _extracost(extracost_), _tags(tags_){}

	Type type() const{
		return _type;
	}

	const char* name() const{
		return _name;
	}
	unsigned char speed() const{
		return _speed;
	}
	unsigned char combopoints() const{
		return _combopoints;
	}
	unsigned char damage() const{
		return _damage;
	}
	unsigned char blockdamage() const{
		return _blockdamage;
	}
	unsigned char bonusdamage() const{
		return _bonusdamage;
	}
	unsigned char bonuslimit() const{
		return _bonuslimit;
	}
	unsigned char extracost() const{
		return _extracost;
	}
	bool isStarter() const{
		return _tags & Starter;
	}
	bool isEnder() const{
		return _tags & Ender;
	}
	bool isLinker() const{
		return _tags & Linker;
	}
	bool isKnockdown() const{
		return _tags & Knockdown;
	}
	bool isCantCombo() const{
		return ((_type == Attack) || (_type == Throw)) && (_combopoints == 0);
	}

	bool isDragon() const{
		return _tags & Dragon;
	}

	Tag tags() const{
		return _tags;
	}

	void print(unsigned char x, unsigned char y) const;

	void fullprint() const;

};

class Card{
public:
	enum Suit{	None		= 0x0,
				Club		= 0x1,
				Diamond		= 0x2,
				Heart		= 0x3, 
				Spade		= 0x4};
	/*
	enum Rank{	NoCard		= 0x0,
				Ace			= 0x1, 
				Two         = 0x2, 
				Three		= 0x4, 
				Four		= 0x8, 
				Five		= 0x10,
				Six			= 0x20, 
				Seven		= 0x40, 
				Eight		= 0x80, 
				Nine		= 0x100, 
				Ten			= 0x200, 
				Jack		= 0x400, 
				Queen		= 0x800, 
				King		= 0x1000, 
				Joker		= 0x2000};
	*/
	enum Rank{	NoCard		= 0x0,
				Ace			= 0x1, 
				Two         = 0x2, 
				Three		= 0x3, 
				Four		= 0x4, 
				Five		= 0x5,
				Six			= 0x6, 
				Seven		= 0x7, 
				Eight		= 0x8, 
				Nine		= 0x9, 
				Ten			= 0xA, 
				Jack		= 0xB, 
				Queen		= 0xC, 
				King		= 0xD, 
				Joker		= 0xE};
private:

	Rank _rank;
	Suit _suit;

	Side const* _sides[rule::card_sides];

public:
	Card(Rank rank_, Suit suit_, const Side& top_, const Side& bottom_) : _rank(rank_), _suit(suit_), _sides{&top_, &bottom_}{}
	Card() : _rank(NoCard), _suit(None), _sides{NULL, NULL}{}

private:
	// Intellisense doesn't seem to recognise the next (non-constructor?) function after array initialization (g++ only),
	// So have it not recognise a fake function
	void _dummy_func();

public:

	const Side& side(bool side) const{
		// ERROR
		sassert(_sides[side] != NULL, "Dereferencing NULL side");
		return *_sides[side];
	}
	
	Suit suit() const{
		return _suit;
	}
	Rank rank() const{
		return _rank;
	}

	void print(unsigned char x, unsigned char y, bool flipped = 0) const;
	void fullprint(unsigned char x, unsigned char y, bool flipped = 0) const;

	void draw() const;
	void drawZoom() const;
};

class CardContainerBase{
private:

protected:
	unsigned char _size;

	virtual Card const** _cardarray() = 0;
	virtual Card const* const* _cardarray() const = 0;

	virtual unsigned char _maxsize() const = 0;

	//void _size(unsigned char s);

public:
	CardContainerBase();
	virtual ~CardContainerBase(){}

	// Property operations
	unsigned char size() const;

	// Random-access operations
	// Virtual to allow containers to preserve ordering at the expense of performance
	// And other such things (see Hand)
	//virtual void insert(unsigned char i, const Card& c);
	virtual void remove(unsigned char i);
	virtual const Card& at(unsigned char i) const;

	// Stack-style operations
	virtual void push(const Card& c);
	virtual const Card& pop();
	virtual const Card& peek() const;

	unsigned int hash() const;

	// Misc operations
	bool search(CardContainerBase& dest, Card::Rank rank);
};

template<unsigned char Tsize>
class CardContainer : public CardContainerBase{
private:
	Card const* _cards[Tsize];

protected:
	Card const** _cardarray();
	Card const* const* _cardarray() const;

	unsigned char _maxsize() const;

public:
	CardContainer();
	virtual ~CardContainer(){}
};

template<unsigned char Tsize>
Card const** CardContainer<Tsize>::_cardarray(){
	return _cards;
}

template<unsigned char Tsize>
Card const* const* CardContainer<Tsize>::_cardarray() const{
	return _cards;
}

template<unsigned char Tsize>
unsigned char CardContainer<Tsize>::_maxsize() const{
	return Tsize;
}

template<unsigned char Tsize>
CardContainer<Tsize>::CardContainer() : CardContainerBase(){
	
}

template<unsigned char Tsize>
class CardContainerOrdered : public CardContainer<Tsize>{
public:
	CardContainerOrdered() : CardContainer<Tsize>(){}

	virtual void insert(unsigned char i, const Card& c);
	virtual void remove(unsigned char i);
};

template<unsigned char Tsize>
void CardContainerOrdered<Tsize>::insert(unsigned char i, const Card& c){
	sassertf(i <= this->size(), "Attempting to insert card at position %u from container of size %u", i, this->size());
	
	// 'Clever' reverse iterating -- I both love and hate this
	for (unsigned char j = i; j --> 0 ;){
		this->_cardarray()[j + 1] = this->_cardarray()[j];
	}
	this->_cardarray()[i] = &c;
	++this->_size;
}

template<unsigned char Tsize>
void CardContainerOrdered<Tsize>::remove(unsigned char i){
	sassertf(i < this->size(), "Attempting to remove card %u from container of size %u", i, this->size());
	
	for (unsigned char j = i; j < this->size() - 1; ++j){
		this->_cardarray()[j] = this->_cardarray()[j + 1];
	}
	--this->_size;
}

#endif//H_CARD
