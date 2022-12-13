#pragma once
#include "Organism.h"

class Animal : public Organism
{
public:
	virtual void action() override;
	virtual void collision(Organism* other) override;
	bool is_animal() override;
	virtual ~Animal();

	int get_move_range();
	void set_move_range(int move_range);
	double get_chance_of_moving();
	void set_chance_of_moving(double chance_to_move);
protected:
	int move_range;
	double chance_to_move;

	Animal(OrganismType organism_type, World* world, Point position, int birth_turn, int str, int initiative);
	virtual Point move();
	virtual void breeding(Organism* other);
};