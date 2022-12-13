#include "SowThistle.h"
#include "Symbols.h"
//#include "Kolory.h"

#define ATTEMPTS 3

void Sow_Thistle::action()
{
	for (int i = 0; i < ATTEMPTS; i++) {
		if (rand() % 100 < 30)	
			Sawing();
	}
}

Sow_Thistle::Sow_Thistle(World* world, Point position, int birth_turn)
	:Plant(OrganismType::SOW_THISTLE, world, position, birth_turn, STR_SOW_THISTLE, INITIATIVE_SOW_THISTLE)
{
	this->symbol = SOW_THISTLE_SYMBOL;
}

string Sow_Thistle::organism_type_to_string()
{
	return "Sow Thistle";
}
