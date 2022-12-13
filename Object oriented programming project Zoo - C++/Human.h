#pragma once
#include "Animal.h"

#define MOVE_RANGE_HUMAN 1
#define CHANCE_TO_MOVE_HUMAN 1
#define STR_HUMAN 5
#define INITIATIVE_HUMAN 4

class Human : public Animal
{
public:
	Human(World* world, Point position, int turaUrodzenia);
	~Human();
	void action() override;
	string organism_type_to_string() override;

	class Skill
	{
	public:
		Skill();
		void check_condition();
		void activate();
		void deactivate();

		bool get_is_active();
		void set_is_active(bool is_active);
		bool get_can_be_activated();
		void set_can_be_activated(bool can_be_activated);
		int get_duration();
		void set_duration(int duration);
		int get_cooldown();
		void set_cooldown(int cooldown);

	protected:
		bool can_be_activated;
		bool is_active;
		int duration;
		int cooldown;
	};

	Direction get_direction();
	void set_direction(Direction move_direction);
	Skill* get_skill();
	void drink();

protected:
	Direction move_direction;
	Skill* skill;
	Point move() override;
	void Magical_Potion();
};