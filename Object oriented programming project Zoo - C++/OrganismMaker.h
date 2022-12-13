#pragma once
#include "AllClasses.h"

class organisms_maker
{
public:
	static Organism* create_new_organism(Organism::OrganismType organism_type, World* world, Point position);
};