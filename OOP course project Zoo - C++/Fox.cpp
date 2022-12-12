#include "Fox.h"
#include "Symbols.h"
//#include "Kolory.h"

Fox::Fox(World* world, Point position, int birth_turn)
	:Animal(OrganismType::FOX, world, position, birth_turn, STR_FOX, INITIATIVE_FOX)
{
	this->move_range = MOVE_RANGE_FOX;
	this->chance_to_move = CHANCE_TO_MOVE_FOX;
	this->symbol = FOX_SYMBOL;
}

string Fox::organism_type_to_string()
{
	return "Fox";
}

Point Fox::draw_any_position(Point position)
{
	unlock_all_directions();
	int pozX = position.GetX();
	int pozY = position.GetY();
	int sizeX = world->GetSizeX();
	int sizeY = world->GetSizeY();
	int directions_possible = 0;
	Organism* tmpOrganizm;

	if (pozX == 0) block_direction(Direction::LEWO);
	else {
		tmpOrganizm = world->get_grid()[pozY][pozX - 1];
		if (tmpOrganizm != nullptr && tmpOrganizm->get_str() > this->str) {
			block_direction(Direction::LEWO);
		}
		else directions_possible++;
	}

	if (pozX == sizeX - 1) block_direction(Direction::PRAWO);
	else {
		tmpOrganizm = world->get_grid()[pozY][pozX + 1];
		if (tmpOrganizm != nullptr && tmpOrganizm->get_str() > this->str) {
			block_direction(Direction::PRAWO);
		}
		else directions_possible++;
	}

	if (pozY == 0) block_direction(Direction::GORA);
	else {
		tmpOrganizm = world->get_grid()[pozY - 1][pozX];
		if (tmpOrganizm != nullptr && tmpOrganizm->get_str() > this->str) {
			block_direction(Direction::GORA);
		}
		else directions_possible++;
	}

	if (pozY == sizeY - 1) block_direction(Direction::DOL);
	else {
		tmpOrganizm = world->get_grid()[pozY + 1][pozX];
		if (tmpOrganizm != nullptr && tmpOrganizm->get_str() > this->str) {
			block_direction(Direction::DOL);
		}
		else directions_possible++;
	}

	if (directions_possible == 0) return Point(pozX, pozY);
	while (true) {
		int tmpLosowanie = rand() % 100;
		//RUCH W LEWO
		if (tmpLosowanie < 25 && !is_direction_blocked(Direction::LEWO))
			return Point(pozX - 1, pozY);
		//RUCH W PRAWO
		else if (tmpLosowanie >= 25 && tmpLosowanie < 50 && !is_direction_blocked(Direction::PRAWO))
			return Point(pozX + 1, pozY);
		//RUCH W GORE
		else if (tmpLosowanie >= 50 && tmpLosowanie < 75 && !is_direction_blocked(Direction::GORA))
			return Point(pozX, pozY - 1);
		//RUCH W DOL
		else if (tmpLosowanie >= 75 && !is_direction_blocked(Direction::DOL))
			return Point(pozX, pozY + 1);
	}
}

Fox::~Fox()
{
}