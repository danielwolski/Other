#include "Sheep.h"
#include "Symbols.h"
//#include "Kolory.h"



Sheep::Sheep(World* world, Point position, int turaUrodzenia)
	:Animal(OrganismType::SHEEP, world, position, turaUrodzenia, STR_SHEEP, INITIATIVE_SHEEP)
{
	this->move_range = MOVE_RANGE_SHEEP;
	this->chance_to_move = CHANCE_TO_MOVE_SHEEP;
	//this->kolor = RED;
	this->symbol = SHEEP_SYMBOL;
}

string Sheep::organism_type_to_string()
{
	return "Sheep";
}

Sheep::~Sheep(){}
