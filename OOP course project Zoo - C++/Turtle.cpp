#include "Turtle.h"
#include "Commentator.h"
#include "Symbols.h"
//#include "Kolory.h"

Turtle::Turtle(World* world, Point position, int turaUrodzenia)
	:Animal(OrganismType::TURTLE, world, position, turaUrodzenia, STR_TURTLE, INITIATIVE_TURTLE)
{
	this->move_range = MOVE_RANGE_TURTLE;
	this->chance_to_move = CHANCE_TO_MOVE_TURTLE;
	this->symbol = TURTLE_SYMBOL;
}

string Turtle::organism_type_to_string()
{
	return "Turtle";
}

bool Turtle::special_action_while_attack(Organism* attacker, Organism* victim)
{
	if (this == victim) {
		if (attacker->get_str() < 5 && attacker->is_animal()) {
			Commentator::add_comment(organism_to_string() + " defends himself from " + attacker->organism_to_string() + " attack");
			return true;
		}
		else return false;
	}
	else if (this == attacker) {
		if (attacker->get_str() >= victim->get_str()) return false;
		else {
			if (victim->get_str() < 5 && victim->is_animal()) {
				Commentator::add_comment(organism_to_string() + " defends himself from " + victim->organism_to_string() + " attack");
				return true;
			}
			else return false;
		}
	}
}