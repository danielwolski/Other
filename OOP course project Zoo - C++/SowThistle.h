#pragma once
#include "Plant.h"

#define STR_SOW_THISTLE 0
#define INITIATIVE_SOW_THISTLE 0

class Sow_Thistle : public Plant
{
public:
	void action() override;
	Sow_Thistle(World* world, Point position, int turaUrodzenia);
	string organism_type_to_string() override;
};

