#include "Belladonna.h"
#include "Commentator.h"
#include "Symbols.h"
//#include "Kolory.h"

Belladonna::Belladonna(World* world, Point position, int birth_turn)
	:Plant(OrganismType::BELLADONNA, world, position, birth_turn, STR_BELLADONNA, INITIATIVE_BELLADONNA)
{
	this->symbol = BELLADONNA_SYMBOL;
}

void Belladonna::action()
{
	if (rand() % 100 < 5) Sawing();
}

string Belladonna::organism_type_to_string()
{
	return "Belladonna";
}

bool Belladonna::special_action_while_attack(Organism* attacker, Organism* victim)
{
	Commentator::add_comment(attacker->organism_to_string() + " ate " + this->organism_to_string());
	if (attacker->get_str() >= 99) {
		world->delete_organism(this);
		Commentator::add_comment(attacker->organism_to_string() + " destroys Belladonna");
	}
	if (attacker->is_animal()) {
		world->delete_organism(attacker);
		Commentator::add_comment(attacker->organism_to_string() + " dies from Belladonna");
	}
	return true;
}

