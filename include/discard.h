#ifndef H_DISCARD
#define H_DISCARD

#include "card.h"
#include "rules.h"

class Discard : public CardContainer<rule::max_discardsize>{
public:
	Discard();
	~Discard(){}
};

#endif//H_DISCARD
