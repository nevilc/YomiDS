#include "display.h"

LinkedList* Display::_instances = NULL;

#ifdef TEXTMODE
PrintConsole Display::_console[2];
#endif//TEXTMODE

void Display::init(){
	consoleInit(&_console[0], 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, 0, 1);
	consoleInit(&_console[1], 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, 1, 1);
}

void Display::drawall(){
	for (LinkedList* i = _instances; i != NULL; i = i->next){
		reinterpret_cast<Display*>(i->data)->draw();
	}
}

void Display::set_window() const{
	consoleSelect(&_console[_screen]);
	consoleSetWindow(&_console[_screen], x(), y(), w(), h());
}

Display::Display(bool screen_, unsigned char x_, unsigned char y_, unsigned char w_, unsigned char h_) : _screen(screen_), _x(x_), _y(y_), _w(w_), _h(h_), _dirty(true), _enabled(false){	
	dprint("New Display");

	_instances = linkedlistAdd(_instances ? &_instances : NULL, reinterpret_cast<void*>(this));
	// ERROR
	sassert(_instances != NULL, "Insufficient memory for LinkedList");
}

Display::~Display(){
	for (LinkedList* i = _instances; i != NULL; i = i->next){
		if (i->data == this){
			// if removing the first element, manually set _instances to the next node
			if (i == _instances){
				_instances = _instances->next;
			}
			linkedlistRemove(i);
			return;
		}
	}
	// ERROR
	sassert(false, "Display* not found");
}

unsigned char Display::x() const{
	return _x;
}

unsigned char Display::y() const{
	return _y;
}

unsigned char Display::w() const{
	return _w;
}

unsigned char Display::h() const{
	return _h;
}

bool Display::screen() const{
	return _screen;
}

void Display::enable(){
	_enabled = true;
	_dirty = true;
}

void Display::disable(){
	_enabled = false;
	set_window();
	ansi::clear();
}

void Display::draw(){
	if (_enabled){
		if (_dirty){
			set_window();
			ansi::clear();
			_draw();
			_dirty = false;
		}
	}
}

void Display::move(unsigned char x_, unsigned char y_){
	// Clear current area, move, then mark dirty
	set_window();
	ansi::clear();
	_x = x_;
	_y = y_;
	_dirty = true;
}

void Display::resize(unsigned char w_, unsigned char h_){
	// Clear current area, resize, then mark dirty
	set_window();
	ansi::clear();
	_w = w_;
	_h = h_;
	_dirty = true;
}

void DisplayContainer::_draw() const{
	#ifdef TEXTMODE

	for (unsigned int i = 0; i < h() / 3 && i < _container->size(); ++i){
		//ansi::setcursor(0, i * 3);
		_container->at(_viewpos + i).print(0, i * 3, _flipped);
	}

	// Print an arrow by the current selection
	ansi::setcursor(0, (_handpos - _viewpos) * 3);
	printf("\x10");
	
	#else//GFX
	#endif
}

DisplayContainer::DisplayContainer(bool screen_, unsigned char x_, unsigned char y_, unsigned char w_, unsigned char h_, const CardContainerBase& container_) : Display(screen_, x_, y_, w_, h_), _container(&container_), _handpos(0), _viewpos(0), _flipped(false){

}

void DisplayContainer::update(const CardContainerBase& container, unsigned char handpos, bool flipped){
	int hash;
	if ((hash = container.hash()) != _lasthash || _handpos != handpos || _flipped != flipped  || _container != &container){
		dprintf("%x / %x", _lasthash, container.hash());
		_lasthash = hash;
		
		_dirty = true;

		_container = &container;
		_handpos = handpos;
		_flipped = flipped;
		// Lock view if there aren't enough cards to scroll
		if (_container->size() <= h() / 3){
			_viewpos = 0;
		}else{
			// follow _handpos when decreasing
			_viewpos = _viewpos <= _handpos ? _viewpos : _handpos;
			// follow _handpos when increasing
			_viewpos = _viewpos >= _handpos - h() / 3 + 1 ? _viewpos : _handpos - h() / 3 + 1;

			// prevent _viewpos from scrolling past last card
			_viewpos = _viewpos <= _container->size() - h() / 3 ? _viewpos : _container->size() - h() / 3;
		}
	}


}

void DisplayPlayerOverview::_draw() const{
	printf("[%s %u/%u] %u cards", _player->fighter().name(), _player->hp(), _player->fighter().hp(), _player->hand().size());
}

DisplayPlayerOverview::DisplayPlayerOverview(bool screen_, unsigned char x_, unsigned char y_, unsigned char w_, unsigned char h_, const Player& player_) : Display(screen_, x_, y_, w_, h_), _player(&player_){

}

void DisplayPlayerOverview::update(const Player& player){
	if (_player != &player){
		_dirty = true;
		_player = &player;
	}
}


void DisplayCard::_draw() const{
	_card->fullprint(_x, _y, _flipped);
}

DisplayCard::DisplayCard(bool screen_, unsigned char x_, unsigned char y_, unsigned char w_, unsigned char h_, const Card& card_, bool flipped_) : Display(screen_, x_, y_, w_, h_), _card(&card_), _flipped(flipped_){

}

void DisplayCard::update(const Card& card, bool flipped){
	if (_card != &card || _flipped != flipped){
		_dirty = true;
		_card = &card;
		_flipped = flipped;
	}
}


