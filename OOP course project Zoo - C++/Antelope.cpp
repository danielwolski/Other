#include "Antelope.h"
#include "Commentator.h"
#include "Symbols.h"
//#include "Kolory.h"


Antelope::Antelope(World* world, Point position, int turaUrodzenia)
	:Animal(OrganismType::ANTYLOPA, world, position, turaUrodzenia, STR_ANTELOPE, INITIATIVE_ANTELOPE)
{
	this->move_range = MOVE_RANGE_ANTELOPE;
	this->chance_to_move = CHANCE_TO_MOVE_ANTELOPE;
	//this->kolor = RED;
	this->symbol = ANTELOPE_SYMBOL;
}

string Antelope::organism_type_to_string()
{
	return "Antelope";
}

bool Antelope::special_action_while_attack(Organism* atakujacy, Organism* ofiara)
{
	if (rand() % 100 < 50) {
		if (this == atakujacy) {
			Commentator::add_comment(organism_to_string() + " ucieka od " + ofiara->organism_to_string());
			make_move(draw_free_position(ofiara->get_position()));
		}
		else if (this == ofiara) {
			Commentator::add_comment(organism_to_string() + " ucieka od " + atakujacy->organism_to_string());
			Point tmpPozycja = this->position;
			make_move(draw_free_position(this->position));
			if (position == tmpPozycja) {
				world->delete_organism(this);
				Commentator::add_comment(atakujacy->organism_to_string() + " zabija " + organism_to_string());
			}
			atakujacy->make_move(tmpPozycja);
		}
		return true;
	}
	else return false;
}