#pragma once
#include "Animal.h"

#define MOVE_RANGE_SHEEP 1
#define CHANCE_TO_MOVE_SHEEP 1
#define STR_SHEEP 4
#define INITIATIVE_SHEEP 4

class Sheep : public Animal
{
public:
	Sheep(World* world, Point position, int birth_turn);
	string organism_type_to_string() override;
	~Sheep();
};

