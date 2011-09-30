#ifndef H_INPUT
#define H_INPUT

#include "card.h"
#include "update.h"

class Input{
public:
	static LinkedList* _instances;

	struct Response{
		enum message_type{
			top = 0,
			bottom = 1,
			wait,
			nocard,
			cancel,
			exit
		};

		const Card* card;
		message_type message;

		//bool side; // If card is nullptr, true indicates no card, false no response

		// Checks for exact equality
		// Even a burst and flipped burst will not be considered equal, nor will
		// two of the same card of different suits
		bool operator==(const Response& other) const{
			return card == other.card && message == other.message;
		}
		bool operator!=(const Response& other) const{
			return !operator==(other);
		}
	};
	static Response wait;
	static Response nocard;
	static Response cancel;
	static Response exit;

private:
	bool _enabled;

public:
	Input();
	virtual ~Input(){}

	void disable();
	void enable();

	virtual Response get() = 0;

	virtual void reset() = 0;
};

class InputContainer : public Input{
	CardContainerBase* _container;

	unsigned char _handpos;
	bool _flipped;

public:
	InputContainer(CardContainerBase& container_);
	~InputContainer(){}

	Response get();

	void reset();

	unsigned char cursor() const;
	bool flipped() const;
};

class InputCancel : public Input{
public:
	Response get();

	void reset(){}
};	

#endif//H_INPUT
