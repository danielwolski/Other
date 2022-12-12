#pragma once
#include "Animal.h"

#define MOVE_RANGE_TURTLE 1
#define CHANCE_TO_MOVE_TURTLE 0.25
#define STR_TURTLE 2
#define INITIATIVE_TURTLE 1

class Turtle : public Animal
{
public:
	Turtle(World* world, Point position, int turaUrodzenia);
	string organism_type_to_string() override;
	bool special_action_while_attack(Organism* atakujacy, Organism* ofiara) override;
};