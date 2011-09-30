#ifndef H_DISPLAY
#define H_DISPLAY

#include <cstdio>
//#include <unordered_set>

#include <nds.h>


#include "options.h"
#include "update.h"
#include "aec.h"

#include "card.h"
#include "player.h"	

class Display{
protected:
	static LinkedList* _instances;

	#ifdef TEXTMODE
	static PrintConsole _console[2];
	#endif//TEXTMODE

	bool _screen;

	unsigned char _x;
	unsigned char _y;

	unsigned char _w;
	unsigned char _h;

	bool _dirty;

	bool _enabled;

	virtual void _draw() const = 0;
	//virtual void _haschanged() = 0;

	void set_window() const;
public:
	static void init();
	static void drawall();

	Display(bool screen_, unsigned char x_, unsigned char y_, unsigned char w_, unsigned char h_);
	virtual ~Display();

	unsigned char x() const;
	unsigned char y() const;

	unsigned char w() const;
	unsigned char h() const;

	bool screen() const;

	void enable();
	void disable();

	void draw();

	void move(unsigned char x_, unsigned char y_);
	void resize(unsigned char w_, unsigned char h_);
};

class DisplayContainer : public Display{
	const CardContainerBase* _container;
	unsigned int _lasthash;

	unsigned char _handpos;

	unsigned char _viewpos;
	bool _flipped;

	void _draw() const;

public:
	DisplayContainer(bool screen_, unsigned char x_, unsigned char y_, unsigned char w_, unsigned char h_, const CardContainerBase& container_);

	void update(const CardContainerBase& container, unsigned char handpos, bool flipped);
};

class DisplayPlayerOverview : public Display{
	const Player* _player;

	void _draw() const;

public:
	DisplayPlayerOverview(bool screen_, unsigned char x_, unsigned char y_, unsigned char w_, unsigned char h_, const Player& player_);

	unsigned char w() const;
	unsigned char h() const;

	void update(const Player& player);
};

class DisplayCard : public Display{
	const Card* _card;

	bool _flipped;

	void _draw() const;
public:
	DisplayCard(bool screen_, unsigned char x_, unsigned char y_, unsigned char w_, unsigned char h_, const Card& card_, bool flipped_);

	unsigned char w() const;
	unsigned char h() const;

	void update(const Card& card, bool flipped);
};



#endif//H_DISPLAY
