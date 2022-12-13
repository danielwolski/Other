#include "Animal.h"
#include "Commentator.h"
#include "OrganismMaker.h"

void Animal::action()
{
	for (int i = 0; i < move_range; i++) {
		Point future_position = move();

		if (world->check_if_free(future_position)
			&& world->whats_on_pos(future_position) != this) {
			collision(world->whats_on_pos(future_position));
			break;
		}
		else if (world->whats_on_pos(future_position) != this) make_move(future_position);
	}
}

void Animal::collision(Organism* other)
{
	if (organism_type == other->get_organism_type()) {
		if (rand() % 100 < 50)  breeding(other);
	}

	else {
		if (other->special_action_while_attack(this, other)) 
			return;
		if (special_action_while_attack(this, other)) 
			return;

		if (str >= other->get_str()) 
		{
			world->delete_organism(other);
			make_move(other->get_position());
			Commentator::add_comment(organism_to_string() + " kills " + other->organism_to_string());
		}
		else 
		{
			world->delete_organism(this);
			Commentator::add_comment(other->organism_to_string() + " kills " + organism_to_string());
		}
	}
}

int Animal::get_move_range()
{
	return move_range;
}

void Animal::set_move_range(int move_range)
{
	this->move_range = move_range;
}

double Animal::get_chance_of_moving()
{
	return chance_to_move;
}

void Animal::set_chance_of_moving(double chance_to_move)
{
	this->chance_to_move = chance_to_move;
}

bool Animal::is_animal()
{
	return true;
}

Animal::~Animal()
{
}

Animal::Animal(OrganismType organism_type, World* world, Point position, int age, int str, int initiative)
	:Organism(organism_type, world, position, age, str, initiative)
{
	direction = new bool[4]{ true,true,true,true };
	was_breeding = false;
}

Point Animal::move()
{
	if (rand() % 100 >= (int)(chance_to_move * 100)) return position;
	else return draw_any_position(position);
}

void Animal::breeding(Organism* other)
{
	if (this->was_breeding || other->get_was_breeding()) 
		return;
	Point tmp1Point = this->draw_free_position(position);
	if (tmp1Point == position) 
	{
		Point tmp2Point = other->draw_free_position(other->get_position());

		if (tmp2Point == other->get_position()) 
			return;
		else 
		{
			Organism* tmpOrganism = organisms_maker::create_new_organism(organism_type, this->world, tmp2Point);
			Commentator::add_comment("Born " + tmpOrganism->organism_to_string());
			world->add_organism(tmpOrganism);
			was_breeding = true;
			other->set_was_breeding(true);
		}
	}
	else 
	{
		Organism* tmpOrganism = organisms_maker::create_new_organism(organism_type, this->world, tmp1Point);
		Commentator::add_comment("Born " + tmpOrganism->organism_to_string());
		world->add_organism(tmpOrganism);
		was_breeding = true;
		other->set_was_breeding(true);
	}
}