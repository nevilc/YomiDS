#include "card.h"

#include <cstdio>

#include "aec.h"
#include "crc.h"

void Side::print(unsigned char x, unsigned char y) const{
	ansi::setcursor(x, y);
	switch(type()){
	case Attack:
		printf("Attack");
		break;
	case Dodge:
		printf("Dodge");
		break;
	case Block:
		printf("Block");
		break;
	case Throw:
		printf("Throw");
		break;
	case Burst:
		printf("Gold Burst");
		break;
	default:
		// ERROR
		sassert(false, "Unknown type");
		break;
	}
	printf(" ");
	if (name()[0] != '\0'){
		printf("%s ", name());
	}
	if (damage()){
		printf("%u", damage());
		if (bonusdamage()){
			printf("+%u", bonusdamage());
		}
		if (blockdamage()){
			printf("/%u", blockdamage());
		}
		printf(" ");
	}
	
	//printf("\n");
}

void Side::fullprint() const{
	int n = 0;
	switch(type()){
	case Attack:
		printf("Attack%n", &n);
		break;
	case Dodge:
		printf("Dodge%n", &n);
		break;
	case Block:
		printf("Block%n", &n);
		break;
	case Throw:
		printf("Throw%n", &n);
		break;
	case Burst:
		printf("Gold Burst%n", &n);
		break;
	default:
		// ERROR
		sassert(false, "Unknown type");
		break;
	}
	
	// Max line + 1
	char* c = new char[33];
	char* ctemp = new char[33];
	c[0] = '\0';

	if (name()[0] != '\0'){
		sprintf(ctemp, "%s", name());
		strcat(c, ctemp);
	}
	if (damage()){
		sprintf(ctemp, " %u", damage());
		strcat(c, ctemp);
		if (bonusdamage()){
			sprintf(ctemp, "+%u", bonusdamage());
			strcat(c, ctemp);
		}
		if (blockdamage()){
			sprintf(ctemp, "(%u)", blockdamage());
			strcat(c, ctemp);
		}
	}
	size_t clen;
	clen = 32 - n - strlen(c);
	for (size_t i = 0; i < clen; ++i){
		printf("%c", ' ');
	}
	printf("%s", c);

	delete[] c;
	delete[] ctemp;

	if (type() == Attack || type() == Throw){
		printf("[@%i.%i", speed()/10, speed()-speed()/10);
		if (combopoints() >= 1){
			printf("|");
			if (combopoints() >= 4){
				printf(":");
			}else{
				printf("'");
			}
			if (combopoints() >= 2){
				if (combopoints() >= 5){
					printf(":");
				}else{
					printf("'");
				}
				if (combopoints() >= 3){
					if (combopoints() >= 6){
						printf(":");
					}else{
						printf("'");
					}
				}
			}
		}
	
		if (isStarter()){
			printf("|Starter");
		}
		if (isLinker()){
			printf("|Linker");
		}
		if (isEnder()){
			printf("|Ender");
		}
		if (isCantCombo()){
			printf("|Can't Combo");
		}

		if (isKnockdown()){
			printf("|%%");
		}
		printf("]");
	
		printf("\n");
	}

	switch(type()){
	case Attack:
		// Combo text?
		break;
	case Throw:
		printf("Combos into any normal attack, Linker, or Ender.");
		if (isKnockdown()){
			printf(" Knocks down if this throw ends your combo.");
		}
		printf("\n");
		break;
	case Block:
		printf("When you block an attack or Joker, draw a card. Return this to your hand unless you were thrown or hit by a knockdown mixup.\n");
		break;
	case Dodge:
		printf("When you dodge an attack or Joker, you may hit back with any single attack or throw. (It becomes an ender.)\n");
		break;
	case Burst:
		printf("Beats attacks and throws. On hit: search for up to two Aces.\n");
		break;
	};

}

void Card::print(unsigned char x, unsigned char y, bool flipped) const{
	ansi::setcursor(x, y);
	printf(" ");
	
	switch(rank()){
	case Card::Two:
		printf("2");
		break;
	case Card::Three:
		printf("3");
		break;
	case Card::Four:
		printf("4");
		break;
	case Card::Five:
		printf("5");
		break;
	case Card::Six:
		printf("6");
		break;
	case Card::Seven:
		printf("7");
		break;
	case Card::Eight:
		printf("8");
		break;
	case Card::Nine:
		printf("9");
		break;
	case Card::Ten:
		printf("10");
		break;
	case Card::Jack:
		printf("J");
		break;
	case Card::Queen:
		printf("Q");
		break;
	case Card::King:
		printf("K");
		break;
	case Card::Ace:
		printf("A");
		break;
	case Card::Joker:
		printf("Joker");
		break;
	default:
		// ERROR
		sassert(false, "Unknown rank");
		break;
	}
	switch(suit()){
	case Card::Heart:
		printf("\x03");
		break;
	case Card::Diamond:
		printf("\x04");
		break;
	case Card::Club:
		printf("\x05");
		break;
	case Card::Spade:
		printf("\x06");
		break;
	case Card::None:
		break;
	default:
		// ERROR
		sassert(false, "Unknown suit");
		break;
	}
	
	side(flipped).print(x, y + 1);

	side(!flipped).print(x, y + 2);
}
void Card::fullprint(unsigned char x, unsigned char y, bool flipped) const{
	ansi::setcursor(x, y);
	printf(" ");
	
	switch(rank()){
	case Card::Two:
		printf("2");
		break;
	case Card::Three:
		printf("3");
		break;
	case Card::Four:
		printf("4");
		break;
	case Card::Five:
		printf("5");
		break;
	case Card::Six:
		printf("6");
		break;
	case Card::Seven:
		printf("7");
		break;
	case Card::Eight:
		printf("8");
		break;
	case Card::Nine:
		printf("9");
		break;
	case Card::Ten:
		printf("10");
		break;
	case Card::Jack:
		printf("Jack");
		break;
	case Card::Queen:
		printf("Queen");
		break;
	case Card::King:
		printf("King");
		break;
	case Card::Ace:
		printf("Ace");
		break;
	case Card::Joker:
		printf("Joker");
		break;
	default:
		// ERROR
		sassert(false, "Unknown rank");
		break;
	}

	switch(suit()){
	case Card::Heart:
		printf(" of Hearts");
		break;
	case Card::Diamond:
		printf(" of Diamonds");
		break;
	case Card::Club:
		printf(" of Clubs");
		break;
	case Card::Spade:
		printf(" of Spades");
		break;
	case Card::None:
		break;
	default:
		// ERROR
		sassert(false, "Unknown suit");
		break;
	}
	
	ansi::setcursor(x, y + 1);
	
	side(flipped).fullprint();
	printf("----------------\n");
	side(!flipped).fullprint();
}

void Card::drawZoom() const{
	//TODO
}

CardContainerBase::CardContainerBase() : _size(0){

}

unsigned char CardContainerBase::size() const{
	return _size;
}

void CardContainerBase::remove(unsigned char i){
	sassertf(i < size(), "Attempting to remove card %u from container of size %u", i, size());

	// Removes the card by swapping it with the last card and decreasing the size by one
	_cardarray()[i] = _cardarray()[--_size];
}

const Card& CardContainerBase::at(unsigned char i) const{
	sassertf(i < size(), "Attempting to access card %u from container of size %u", i, size());

	return *_cardarray()[i];
}

void CardContainerBase::push(const Card& c){
	sassertf(size() != _maxsize(), "CardContainer exceeding max size of %u", _maxsize());

	_cardarray()[_size++] = &c;
}

const Card& CardContainerBase::pop(){
	sassert(size(), "Attempting to pop empty CardContainer");

	return *_cardarray()[--_size];
}

const Card& CardContainerBase::peek() const{
	sassert(size(), "Attempting to peek empty CardContainer");

	return *_cardarray()[_size - 1];
}

unsigned int CardContainerBase::hash() const{
	return crc(_cardarray(), size() * sizeof(Card const *), 0);
}

bool CardContainerBase::search(CardContainerBase& dest, Card::Rank rank){
	// Transfers first card of the rank(if found) to dest, then swaps
	// the found with the last card, removing it by decreasing size

	// This alters the order of the discard, but it is fast, and (I believe)
	// no abilities are based on the order of any card containers (with the 
	// exception of Deck, which is shuffled anyways)
	for (unsigned char i = 0; i < _size; ++i){
		if (_cardarray()[i]->rank() == rank){
			dest.push(*_cardarray()[i]);
			remove(i);
			return true;
		}
	}
	return false;
}
