#pragma once
#include "Plant.h"

#define STR_GUARANA 0
#define INITIATIVE_GUARANA 0
#define STR_INCREASE 3

class Guarana : public Plant
{
public:
	Guarana(World* world, Point position, int birth_turn);;
	string organism_type_to_string() override;
	bool special_action_while_attack(Organism* attacker, Organism* victim) override;
};
