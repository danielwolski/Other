#include "Human.h"
#include "Commentator.h"
#include "Symbols.h"
//#include "Kolory.h"

#define SKILL_DURATION 10
#define MAGICAL_POTION_STR_BOOST 10
#define SKILL_COOLDOWN 15


Human::Human(World* world, Point position, int birth_turn)
	:Animal(OrganismType::HUMAN, world, position, birth_turn, STR_HUMAN, INITIATIVE_HUMAN)
{
	this->move_range = MOVE_RANGE_HUMAN;
	this->chance_to_move = CHANCE_TO_MOVE_HUMAN;
	skill = new Skill();
	move_direction = Direction::NO_DIRECTION;
	//this->kolor = 10;
	this->symbol = HUMAN_SYMBOL;
}


void Human::action()
{
	if (skill->get_is_active()) {
		Commentator::add_comment(organism_to_string() + " Magical Potion is active: (Turns left: " + to_string(skill->get_duration()) + ")");
		Commentator::comment();
	}

	for (int i = 0; i < move_range; i++) {
		Point position = move();


		if (world->check_if_free(position) && world->whats_on_pos(position) != this) 
		{
			collision(world->whats_on_pos(position));
			if (skill->get_is_active())
				Magical_Potion();
			break;
		}
		else if (world->whats_on_pos(position) != this) 
			make_move(position);

		if (skill->get_is_active()) 
			Magical_Potion();
	}
	move_direction = Direction::NO_DIRECTION;
	skill->check_condition();
}

string Human::organism_type_to_string()
{
	return "Human";
}

Organism::Direction Human::get_direction()
{
	return move_direction;
}

void Human::set_direction(Direction move_direction)
{
	this->move_direction = move_direction;
}

Human::Skill* Human::get_skill()
{
	return skill;
}

Point Human::move()
{
	int x = position.GetX();
	int y = position.GetY();
	draw_any_position(position);//BLOKUJE KIERUNKI NIEDOZWOLONE PRZY GRANICY SWIATU
	if (is_direction_blocked(move_direction)) return position;
	else {
		Point position;
		if (move_direction == Direction::DOL) return Point(x, y + 1);
		if (move_direction == Direction::GORA) return Point(x, y - 1);
		if (move_direction == Direction::LEWO) return Point(x - 1, y);
		if (move_direction == Direction::PRAWO) return Point(x + 1, y);
		if (move_direction == Direction::NO_DIRECTION) return Point(x, y);
	}
}

void Human::Magical_Potion()
{
		Human::str--;
}

Human::Skill::Skill()
{
	cooldown = 0;
	duration = 0;
	is_active = false;
	can_be_activated = true;
}

bool Human::Skill::get_is_active()
{
	return is_active;
}

void Human::Skill::set_is_active(bool is_active)
{
	this->is_active = is_active;
}

bool Human::Skill::get_can_be_activated()
{
	return can_be_activated;
}

void Human::Skill::set_can_be_activated(bool can_be_activated)
{
	this->can_be_activated = can_be_activated;
}

int Human::Skill::get_duration()
{
	return duration;
}

void Human::Skill::set_duration(int duration)
{
	this->duration = duration;
}

int Human::Skill::get_cooldown()
{
	return cooldown;
}

void Human::Skill::set_cooldown(int cooldown)
{
	this->cooldown = cooldown;
}

void Human::Skill::check_condition()
{
	if (cooldown > 0) 
		cooldown--;

	if (duration > 0) 
		duration--;

	if (duration == 0) 
		deactivate();

	if (cooldown == 0) 
		can_be_activated = true;
}

void Human::Skill::activate()
{
	if (cooldown == 0) 
	{
		is_active = true;
		can_be_activated = false;
		cooldown = SKILL_COOLDOWN;
		duration = SKILL_DURATION;
	}
	else if (cooldown > 0)
		cout << "You will be able to drink Magic Potion after" << cooldown << " turns" << endl;
}

void Human::drink()
{
	Human::str = Human::str + MAGICAL_POTION_STR_BOOST;
}

void Human::Skill::deactivate()
{
	is_active = false;
}

Human::~Human() 
{
}
