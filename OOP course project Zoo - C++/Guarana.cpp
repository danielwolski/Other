#include "Guarana.h"
#include "Commentator.h"
#include "Symbols.h"
//#include "Kolory.h"

Guarana::Guarana(World* world, Point position, int turaUrodzenia)
	:Plant(OrganismType::GUARANA, world, position, turaUrodzenia, STR_GUARANA, INITIATIVE_GUARANA)
{
	this->symbol = GUARANA_SYMBOL;
}

string Guarana::organism_type_to_string()
{
	return "Guarana";
}

bool Guarana::special_action_while_attack(Organism* attacker, Organism* victim)
{
	Point tmpPosition = this->position;
	world->delete_organism(this);
	attacker->make_move(tmpPosition);
	Commentator::add_comment(attacker->organism_to_string() + " ate " + this->organism_to_string()
		+ "  and increased strength by  " + to_string(STR_INCREASE));
	attacker->SetSila(attacker->get_str() + STR_INCREASE);
	return true;
}
