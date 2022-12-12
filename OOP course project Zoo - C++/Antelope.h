#pragma once
#include "Animal.h"

#define MOVE_RANGE_ANTELOPE 2
#define CHANCE_TO_MOVE_ANTELOPE 1
#define STR_ANTELOPE 4
#define INITIATIVE_ANTELOPE 4

class Antelope : public Animal
{
public:
	Antelope(World* world, Point position, int birth_turn);
	string organism_type_to_string() override;
	bool special_action_while_attack(Organism* attacker, Organism* victim) override;
};