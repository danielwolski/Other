#include "Plant.h"
#include "OrganismMaker.h"

void Plant::action()
{
	if (rand() % 100 < 30) Sawing();
}

void Plant::collision(Organism* other) {}

bool Plant::is_animal()
{
	return false;
}

Plant::Plant(OrganismType organism_type, World* world, Point position, int turaUrodzenia, int str, int inicjatywa)
	:Organism(organism_type, world, position, turaUrodzenia, str, inicjatywa)
{
	direction = new bool[4]{ true,true,true,true };
}

void Plant::Sawing()
{
	Point tmp1Point = this->draw_free_position(position);
	if (tmp1Point == position) return;
	else {
		Organism* tmpOrganism = organisms_maker::create_new_organism(organism_type, this->world, tmp1Point);
		Commentator::add_comment("New plant grows " + tmpOrganism->organism_to_string());
		world->add_organism(tmpOrganism);
	}
}

Plant::~Plant() {}
