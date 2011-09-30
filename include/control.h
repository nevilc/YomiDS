#ifndef H_CONTROL
#define H_CONTROL

#include "player.h"
#include "input.h"

class Control{
protected:
	Player* _player;
public:
	

	Control(Player& player) : _player(&player){}

	virtual ~Control(){}

	//virtual CardDirected read();
	//virtual Response read();

	virtual Input::Response standard() = 0;
	virtual Input::Response powerup() = 0;
	virtual Input::Response combo() = 0;
	virtual Input::Response followup() = 0;
	virtual Input::Response waiting() = 0;

	Player& player(){
		return *_player;
	}
};

#endif//H_CONTROL
