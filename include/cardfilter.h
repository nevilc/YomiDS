#ifndef H_CARDFILTER
#define H_CARDFILTER

#include "card.h"

class CardFilter{
public:
	enum Match{		None	= 0x0,
					Top		= 0x1,
					Bottom	= 0x2,
					Both	= 0x4
	};

protected:
	virtual bool _filter(Card const* card, Match match) = 0;
public:
	
	Match filter(Card const*const*& start, Card const*const* end){
		while (start != end){
			if (_filter(*start, Top)){
				if (_filter(*start, Bottom)){
					return Both;
				}
				return Top;
			}else{
				if (_filter(*start, Bottom)){
					return Bottom;
				}
			}
			++start;
		}
		return None;
	}
};

class CardFilterAttribute : public CardFilter{
protected:
	Card::Suit _suits;
	Card::Rank _ranks;

	Side::Type _types;
	Side::Tag _tags;

	virtual bool _filter(Card const* card, Match match) = 0;

	CardFilterAttribute(Card::Suit suits_, Card::Rank ranks_, Side::Type types_, Side::Tag tags_) : _suits(suits_), _ranks(ranks_), _types(types_), _tags(tags_){}
public:
};

class CardFilterNumeric : public CardFilter{
protected:
	unsigned char _speed;
	unsigned char _combopoints;
	unsigned char _damage;
	unsigned char _blockdamage;
	unsigned char _bonusdamage;
	unsigned char _bonuslimit;
	unsigned char _extracost;

	static const unsigned char _max = -1;
	static const unsigned char _min = 0;

	virtual bool _filter(Card const* card, Match match) = 0;

	CardFilterNumeric(unsigned char speed_, unsigned char combopoints_, unsigned char damage_, unsigned char blockdamage_, unsigned char bonusdamage_, unsigned char bonuslimit_, unsigned char extracost_) : _speed(speed_), _combopoints(combopoints_), _damage(damage_), _blockdamage(blockdamage_), _bonusdamage(bonusdamage_), _extracost(extracost_){}
public:
};

class Upperbound : public CardFilterNumeric{
	virtual bool _filter(Card const* card, Match match){
		Side const* s = &card->side(match == Bottom);
		return s->speed() <= _speed && s->combopoints() <= _combopoints && s->damage() <= _damage && s->blockdamage() <= _blockdamage && s->bonusdamage() <= _bonusdamage && s->bonuslimit() <= _bonuslimit && s->extracost() <= _extracost;
	}
public:
	Upperbound(unsigned char speed_ = _max, unsigned char combopoints_ = _max, unsigned char damage_ = _max, unsigned char blockdamage_ = _max, unsigned char bonusdamage_ = _max, unsigned char bonuslimit_ = _max, unsigned char extracost_ = _max) : CardFilterNumeric(speed_, combopoints_, damage_, blockdamage_, bonusdamage_, bonuslimit_, extracost_){}
};

class Lowerbound : public CardFilterNumeric{
	virtual bool _filter(Card const* card, Match match){
		Side const* s = &card->side(match == Bottom);
		return s->speed() >= _speed && s->combopoints() >= _combopoints && s->damage() >= _damage && s->blockdamage() >= _blockdamage && s->bonusdamage() >= _bonusdamage && s->bonuslimit() >= _bonuslimit && s->extracost() >= _extracost;
	}
public:
	Lowerbound(unsigned char speed_ = _min, unsigned char combopoints_ = _min, unsigned char damage_ = _min, unsigned char blockdamage_ = _min, unsigned char bonusdamage_ = _min, unsigned char bonuslimit_ = _min, unsigned char extracost_ = _min) : CardFilterNumeric(speed_, combopoints_, damage_, blockdamage_, bonusdamage_, bonuslimit_, extracost_){}
};

class Whitelist : public CardFilterAttribute{
	bool _filter(Card const* card, Match match){
		Side const* s = &card->side(match == Bottom);
		return card->suit() & _suits || card->rank() & _ranks || s->type() & _types || s->tags() & _tags;
	}
public:
	Whitelist(Card::Suit suits_, Card::Rank ranks_, Side::Type types_, Side::Tag tags_) : CardFilterAttribute(suits_, ranks_, types_, tags_){}
};

class Blacklist : public CardFilterAttribute{
	bool _filter(Card const* card, Match match){
		Side const* s = &card->side(match == Bottom);
		return !(card->suit() & _suits || card->rank() & _ranks || s->type() & _types || s->tags() & _tags);
	}
public:
	Blacklist(Card::Suit suits_ = Card::Suit(0), Card::Rank ranks_ = Card::Rank(0), Side::Type types_ = Side::Type(0), Side::Tag tags_ = Side::Tag(0)) : CardFilterAttribute(suits_, ranks_, types_, tags_){}
};

#endif//H_CARDFILTER
