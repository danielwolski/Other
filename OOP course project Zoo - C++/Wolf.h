#pragma once
#include "Animal.h"


#define MOVE_RANGE_WOLF 1
#define CHANCE_TO_MOVE_WOLF 1
#define STR_WOLF 9
#define INITIATIVE_WOLF 5

class Wolf : public Animal
{
public:
	Wolf(World* world, Point position, int birth_turn);
	string organism_type_to_string() override;
};