#include "turn.h"

#include "input.h"

void Game::play_turn() const{
	dprint("New Turn\n");

	play_draw();

	play_standard();

	play_powerup();
}

void Game::play_draw() const{
	dprint("Draw Phase\n");

	_controls[0]->player().draw();
	_controls[1]->player().draw();
}

void Game::play_powerup() const{
	dprint("Powerup phase\n");

	Input::Response r0[rule::max_powerup] = {Input::wait, Input::wait, Input::wait, Input::wait};
	unsigned int n0 = 0;
	Input::Response r1[rule::max_powerup] = {Input::wait, Input::wait, Input::wait, Input::wait};
	unsigned int n1 = 0;

	while (1){
		update();

		if (r0[n0] == Input::wait){
			r0[n0] = _controls[0]->powerup();

			if (r0[n0] == Input::cancel){
				r0[n0] = Input::wait;
				if (n0){
					_controls[0]->player().hand().reinsert(*r0[--n0].card);
					r0[n0] = Input::wait;
				}
			}else
			// If not full/capped
			if (n0 < rule::max_powerup && r0[n0] != Input::wait){
				// Increment card count
				++n0;
				// If nocard, essentially break from the if statement
				if (r0[n0 - 1] != Input::nocard){
					const Card& c0 = *r0[n0 - 1].card;
					// Discarded card must be the same rank as the first
					if (c0.rank() != r0[0].card->rank()){
						// WARN
						dprint("WARNING: powerup must be of the same rank\n");
						--n0;
						_controls[0]->player().hand().reinsert(c0);
						r0[n0] = Input::wait;
						//break;
					}
				}
			}
		}

		if (r1[n1] == Input::wait){
			r1[n1] = _controls[1]->powerup();

			if (r1[n1] == Input::cancel){
				r1[n1] = Input::wait;
				if (n1){
					_controls[1]->player().hand().reinsert(*r1[--n1].card);
					r1[n1] = Input::wait;
				}
			}else
			// If not full/capped
			if (n1 < rule::max_powerup && r1[n1] != Input::wait){
				// Increment card count
				++n1;
				// If nocard, essentially break from the if statement
				if (r1[n1 - 1] != Input::nocard){
					const Card& c1 = *r1[n1 - 1].card;
					// Discarded card must be the same rank as the first
					if (c1.rank() != r1[0].card->rank()){
						// WARN
						dprint("WARNING: powerup must be of the same rank\n");
						--n1;
						_controls[1]->player().hand().reinsert(c1);
						r1[n1] = Input::wait;
						//break;
					}
				}
			}
		}

		// Resolve once nocard or full
		if ((n0 == rule::max_powerup || r0[n0] == Input::nocard) && (n1 == rule::max_powerup || r1[n1] == Input::nocard)){
			// Search for 1 less than the number of cards discarded
			for (unsigned int i = 0; i < n0 - 1 - (r0[n0] == Input::nocard); ++i){
				// Search discard first
				if (!_controls[0]->player().discard().search(_controls[0]->player().hand(), Card::Ace)){
					// If none left in discard, search the deck
					if (!_controls[0]->player().deck().search(_controls[0]->player().hand(), Card::Ace)){
						// None in deck either, exit early
						break;
					}
				}
			}
			for (unsigned int i = 0; i < n1 - 1 - (r1[n1] == Input::nocard); ++i){
				if (!_controls[1]->player().discard().search(_controls[1]->player().hand(), Card::Ace)){
					if (!_controls[1]->player().deck().search(_controls[1]->player().hand(), Card::Ace)){
						break;
					}
				}
			}
			break;
		}
	}
}

void Game::play_standard() const{
	dprint("Combat phase\n");

	Input::Response r0 = Input::wait;
	Input::Response r1 = Input::wait;
	while (1){
		update();


		if (r0 == Input::wait){
			r0 = _controls[0]->standard();
			// On nocard, allow other player to choose another card
			if (r0 == Input::nocard){
				if (r1 != Input::nocard){
					_controls[1]->player().hand().reinsert(*r1.card);
					r1 = Input::wait;
				}
			}
		}else{
			// Allow cancelling selection if waiting for other player
			if (_controls[0]->waiting() == Input::cancel){
				if (r0 != Input::nocard){
					_controls[0]->player().hand().reinsert(*r0.card);
				}
				r0 = Input::wait;
			}
		}
		if (r1 == Input::wait){
			r1 = _controls[1]->standard();

			if (r1 == Input::nocard){
				if (r0 != Input::nocard){
					_controls[0]->player().hand().reinsert(*r0.card);
					r0 = Input::wait;
				}
			}
		}else{
			if (_controls[1]->waiting() == Input::cancel){
				if (r1 != Input::nocard){
					_controls[1]->player().hand().reinsert(*r1.card);
				}
				r1 = Input::wait;
			}
		}
		// TODO message_type exit
		// Resolve action once both players are ready
		if (r0 != Input::wait && r1 != Input::wait){
			// Map sides and players for easier reference
			const Side& s0 = r0.card->side(r0.message);
			const Side& s1 = r1.card->side(r1.message);
			Player& p0 = _controls[0]->player();
			Player& p1 = _controls[1]->player();

			switch (s0.type()){
			case Side::Attack:
				switch (s1.type()){
				case Side::Attack:
					match_attack_attack(p0, r0, p1, r1);
					break;
				case Side::Block:
					match_attack_block(p0, r0, p1, r1);
					break;
				case Side::Burst:
					match_attack_burst(p0, r0, p1, r1);
					break;
				case Side::Dodge:
					match_attack_dodge(p0, r0, p1, r1);
					break;
				case Side::Throw:
					match_attack_throw(p0, r0, p1, r1);
					break;
				default:
					match_attack_other(p0, r0, p1, r1);
				}
				break;
			case Side::Block:
				switch (s1.type()){
				case Side::Attack:
					match_attack_block(p1, r1, p0, r0);
					break;
				case Side::Block:
					match_block_block(p0, r0, p1, r1);
					break;
				case Side::Burst:
					match_block_burst(p0, r0, p1, r1);
					break;
				case Side::Dodge:
					match_block_dodge(p0, r0, p1, r1);
					break;
				case Side::Throw:
					match_block_throw(p0, r0, p1, r1);
					break;
				default:
					match_block_other(p0, r0, p1, r1);
					break;
				}
				break;
			case Side::Burst:
				switch (s1.type()){
				case Side::Attack:
					match_attack_burst(p1, r1, p0, r0);
					break;
				case Side::Block:
					match_block_burst(p1, r1, p0, r0);
					break;
				case Side::Burst:
					match_burst_burst(p0, r0, p1, r1);
					break;
				case Side::Dodge:
					match_burst_dodge(p0, r0, p1, r1);
					break;
				case Side::Throw:
					match_burst_throw(p0, r0, p1, r1);
					break;
				default:
					match_burst_other(p0, r0, p1, r1);
					break;
				}
				break;
			case Side::Dodge:
				switch (s1.type()){
				case Side::Attack:
					match_attack_dodge(p1, r1, p0, r0);
					break;
				case Side::Block:
					match_block_dodge(p1, r1, p0, r0);
					break;
				case Side::Burst:
					match_burst_dodge(p1, r1, p0, r0);
					break;
				case Side::Dodge:
					match_dodge_dodge(p0, r0, p1, r1);
					break;
				case Side::Throw:
					match_dodge_throw(p0, r0, p1, r1);
					break;
				default:
					match_dodge_other(p0, r0, p1, r1);
					break;
				}
				break;
			case Side::Throw:
				switch (s1.type()){
				case Side::Attack:
					match_attack_throw(p1, r1, p0, r0);
					break;
				case Side::Block:
					match_block_throw(p1, r1, p0, r0);
					break;
				case Side::Burst:
					match_burst_throw(p1, r1, p0, r0);
					break;
				case Side::Dodge:
					match_dodge_throw(p1, r1, p0, r0);
					break;
				case Side::Throw:
					match_throw_throw(p0, r0, p1, r1);
					break;
				default:
					match_throw_other(p0, r0, p1, r1);
					break;
				}
				break;
			default:
				switch (s1.type()){
				case Side::Attack:
					match_attack_other(p1, r1, p0, r0);
					break;
				case Side::Block:
					match_block_other(p1, r1, p0, r0);
					break;
				case Side::Burst:
					match_burst_other(p1, r1, p0, r0);
					break;
				case Side::Dodge:
					match_dodge_other(p1, r1, p0, r0);
					break;
				case Side::Throw:
					match_throw_other(p1, r1, p0, r0);
					break;
				default:
					match_other_other(p0, r0, p1, r1);
					break;
				}
				break;
			}
			return;
		}
	}
}

void Game::play_combo(Control& ca, const Input::Response& starter) const{
	dprint("Combo phase\n");

	//TODO
}

void Game::match_attack_attack(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Attack v. Attack\n");

	const Side& sa = ra.card->side(ra.message);
	const Side& sb = rb.card->side(rb.message);

	if (sa.speed() < sb.speed()){
		pb.hurt(sa.damage());
		
		//return play_combo(0, ra); //FIXME
	}else if (sa.speed() > sb.speed()){
		pa.hurt(sb.damage());

		//return play_combo(1, rb); //FIXME
	}else{
		// Both attacks hit, but no combo
		pa.hurt(sb.damage());
		pb.hurt(sa.damage());
		
		return;
	}
}

void Game::match_attack_block(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Attack v. Block\n");
	
	const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	block_success(pb, rb, sa);

	return;
}

void Game::match_attack_burst(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Attack v. Burst\n");

	//const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	burst_success(pb, rb);

	return;
}

void Game::match_attack_dodge(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Attack v. Dodge\n");

	//const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	//return play_followup(); // FIXME
}

void Game::match_attack_throw(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Attack v. Throw\n");

	const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	pb.hurt(sa.damage());
		
	//return play_combo(0, ra); //FIXME
}

void Game::match_attack_other(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Attack v. None\n");

	const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	pb.hurt(sa.damage());
		
	//return play_combo(0, ra); //FIXME
}

void Game::match_block_block(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Block v. Block\n");

	//const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	block_return(pa, ra);
	block_return(pb, rb);

	return;
}

void Game::match_block_burst(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Block v. Burst\n");

	//const Side& sa = ra.card->side(ra.message);
	const Side& sb = rb.card->side(rb.message);

	block_success(pa, ra, sb);

	return;
}

void Game::match_block_dodge(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Block v. Dodge\n");

	//const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	block_return(pa, ra);

	return;
}

void Game::match_block_throw(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Block v. Throw\n");

	//const Side& sa = ra.card->side(ra.message);
	const Side& sb = rb.card->side(rb.message);

	pa.hurt(sb.damage());

	//return play_combo(); //FIXME
}

void Game::match_block_other(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Block v. None\n");

	//const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	block_return(pa, ra); // FIXME should be block_success

	return;
}

void Game::match_burst_burst(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Burst v. Burst\n");

	//const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	burst_success(pa, ra);
	burst_success(pb, rb);

	return;
}

void Game::match_burst_dodge(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Burst v. Dodge\n");

	//const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	//return play_followup(); //FIXME
}

void Game::match_burst_throw(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Burst v. Throw\n");

	//const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	burst_success(pa, ra);

	return;
}

void Game::match_burst_other(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Burst v. None\n");

	//const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	burst_success(pa, ra);

	return;
}

void Game::match_dodge_dodge(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Dodge v. Dodge\n");

	//const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	return;
}

void Game::match_dodge_throw(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Dodge v. Throw\n");

	//const Side& sa = ra.card->side(ra.message);
	const Side& sb = rb.card->side(rb.message);

	pa.hurt(sb.damage());

	//return play_combo(); //FIXME
}

void Game::match_dodge_other(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Dodge v. None\n");

	//const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	return;
}

void Game::match_throw_throw(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Throw v. Throw\n");

	const Side& sa = ra.card->side(ra.message);
	const Side& sb = rb.card->side(rb.message);

	if (sa.speed() < sb.speed()){
		pb.hurt(sa.damage());

		//return play_combo(); //FIXME
	}else if (sb.speed() < sa.speed()){
		pa.hurt(sb.damage());

		//return play_combo(); //FIXME
	}else{
		// FIXME
		// Does this work like attacks?
		pa.hurt(sb.damage());
		pb.hurt(sa.damage());

		return;
	}
}

void Game::match_throw_other(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("Throw v. None\n");

	const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	pb.hurt(sa.damage());

	//return play_combo(); // FIXME
}

void Game::match_other_other(Player& pa, Input::Response ra, Player& pb, Input::Response rb) const{
	dprint("None v. None\n");

	//const Side& sa = ra.card->side(ra.message);
	//const Side& sb = rb.card->side(rb.message);

	// I can't imagine this ever happening, but...
}

Game::Game(Control* control1, Control* control2) : _controls{control1, control2} {
	dprint("New Game\n");

	while (1){
		play_turn();
	}
}

