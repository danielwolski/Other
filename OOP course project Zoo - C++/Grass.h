#pragma once
#include "Plant.h"

#define STR_GRASS 0
#define INITIATIVE_GRASS 0

class Grass : public Plant
{
public:
	Grass(World* world, Point position, int birth_turn);
	string organism_type_to_string() override;
};

