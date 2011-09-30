#ifndef H_HAND
#define H_HAND

#include "card.h"
#include "rules.h"
#include "debug.h"

class Hand : public CardContainerOrdered<rule::max_handsize>{
	unsigned char _lastremoved;
	//unsigned char _lastremoved;

	//void _compact();
	//bool _uncompacted() const;
public:

	Hand(){}
	~Hand(){}

	//void remove(unsigned char i);
	//const Card& at(unsigned char i);

	//void push(const Card& c);
	//const Card& pop();
	//const Card& peek() const;

	virtual void insert(unsigned char i, const Card& c);
	virtual void remove(unsigned char i);

	void reinsert(const Card& c);

	void draw(CardContainerBase& deck);
};


#endif//H_HAND
