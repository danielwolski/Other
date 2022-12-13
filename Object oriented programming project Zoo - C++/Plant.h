#pragma once
#include "Organism.h"

class Plant : public Organism
{
public:
	virtual void action() override;
	bool is_animal() override;
	virtual ~Plant();
protected:
	Plant(OrganismType organism_type, World* world, Point position, int turaUrodzenia, int str, int inicjatywa);
	virtual void Sawing();
private:
	void collision(Organism* other) override;
	/*NIE JEST POTRZEBNA,
	patrz funkcje "special_action_while_attack()",
	ktora jest zdefiniowana u roznych roslin
	.*/
};