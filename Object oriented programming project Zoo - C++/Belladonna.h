#pragma once
#include "Plant.h"


#define STR_BELLADONNA 99
#define INITIATIVE_BELLADONNA 0

class Belladonna : public Plant
{
public:
	Belladonna(World* world, Point position, int birth_turn);
	void action() override;
	string organism_type_to_string() override;
	bool special_action_while_attack(Organism* attacker, Organism* victim) override;
};