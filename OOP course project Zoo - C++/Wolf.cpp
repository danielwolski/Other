#include "Wolf.h"
#include "Symbols.h"


Wolf::Wolf(World* world, Point position, int birth_turn)
	:Animal(OrganismType::WOLF, world, position, birth_turn, STR_WOLF, INITIATIVE_WOLF)
{
	this->move_range = MOVE_RANGE_WOLF;
	this->chance_to_move = CHANCE_TO_MOVE_WOLF;
	this->symbol = WOLF_SYMBOL;
}

string Wolf::organism_type_to_string()
{
	return "Wolf";
}
