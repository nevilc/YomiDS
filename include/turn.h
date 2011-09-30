#ifndef H_TURN
#define H_TURN

#include <cstddef>
#include <stack>

#include "control.h"
#include "cardfilter.h"
#include "rules.h"
#include "update.h"
#include "debug.h"
#include "input.h"

class Game{
	Control* _controls[rule::max_players];

public:
	Game(Control* control1, Control* control2);

private:

	void play_turn() const;

	void play_draw() const;

	void play_powerup() const;

	void play_standard() const;
	void play_combo(Control& ca, const Input::Response& starter) const;
	void play_followup(Control& ca) const;

	void match_attack_attack(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_attack_block(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_attack_burst(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_attack_dodge(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_attack_throw(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_attack_other(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;

	void match_block_block(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_block_burst(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_block_dodge(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_block_throw(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_block_other(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;

	void match_burst_burst(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_burst_dodge(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_burst_throw(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_burst_other(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;

	void match_dodge_dodge(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_dodge_throw(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_dodge_other(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;

	void match_throw_throw(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;
	void match_throw_other(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;

	void match_other_other(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const;

	void block_return(Player& pa, Input::Response ra) const{
		pa.hand().reinsert(*ra.card);
	}

	void block_success(Player& pa, Input::Response ra, const Side& sb) const{
		pa.hurt(sb.blockdamage());
		block_return(pa, ra);
		pa.draw();
	}

	void burst_success(Player& pa, Input::Response ra) const{
		// Search for up to 2 aces
		// CHECK
		// Burst allows searching discard too, right?
		if (pa.deck().search(pa.hand(), Card::Ace)){
			if (!pa.deck().search(pa.hand(), Card::Ace)){
				pa.discard().search(pa.hand(), Card::Ace);
			}
			pa.deck().shuffle();
		}else if (pa.discard().search(pa.hand(), Card::Ace)){
			pa.discard().search(pa.hand(), Card::Ace);
		}
	}
};

#endif//H_TURN
