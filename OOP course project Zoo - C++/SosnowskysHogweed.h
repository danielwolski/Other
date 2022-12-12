#pragma once
#include "Plant.h"
 
#define STR_SOSNOWSKYS_HOGWEED 10
#define INITIATIVE_SOSNOWSKYS_HOGWEED 0

class SosnowskysHogweed : public Plant
{
public:
	void action() override;
	SosnowskysHogweed(World* world, Point position, int turaUrodzenia);
	string organism_type_to_string() override;
	bool special_action_while_attack(Organism* atakujacy, Organism* ofiara) override;
};

