#include "SosnowskysHogweed.h"
#include "Commentator.h"
#include "Symbols.h"
//#include "Kolory.h"

void SosnowskysHogweed::action()
{
	int pozX = position.GetX();
	int pozY = position.GetY();
	Organism* tmpOrganizm = nullptr;
	draw_any_position(position);// BLOKUJE GRANICE
	for (int i = 0; i < 4; i++) {
		if (i == 0 && !is_direction_blocked(Direction::DOL))
			tmpOrganizm = world->whats_on_pos(Point(pozX, pozY + 1));
		else if (i == 1 && !is_direction_blocked(Direction::GORA))
			tmpOrganizm = world->whats_on_pos(Point(pozX, pozY - 1));
		else if (i == 2 && !is_direction_blocked(Direction::LEWO))
			tmpOrganizm = world->whats_on_pos(Point(pozX - 1, pozY));
		else if (i == 3 && !is_direction_blocked(Direction::PRAWO))
			tmpOrganizm = world->whats_on_pos(Point(pozX + 1, pozY));

		if (tmpOrganizm != nullptr && tmpOrganizm->is_animal()
			/*&& tmpOrganizm->get_organism_type() != OrganismType::CYBER_OWCA*/) {
			world->delete_organism(tmpOrganizm);
			Commentator::add_comment(organism_to_string() + " zabija " + tmpOrganizm->organism_to_string());
		}
	}
	if (rand() % 100 < 5) Sawing();
}

SosnowskysHogweed::SosnowskysHogweed(World* world, Point position, int turaUrodzenia)
	:Plant(OrganismType::SOSNOWSKYS_HOGWEED, world, position, turaUrodzenia, STR_SOSNOWSKYS_HOGWEED, INITIATIVE_SOSNOWSKYS_HOGWEED)
{
	//this->kolor = GREEN;
	this->symbol = SOSNOWSKYS_HOGWEED;
}

string SosnowskysHogweed::organism_type_to_string()
{
	return "Barszcz Sosnowskiego";
}

bool SosnowskysHogweed::special_action_while_attack(Organism* atakujacy, Organism* ofiara)
{
	if (atakujacy->get_str() >= 10) {
		world->delete_organism(this);
		Commentator::add_comment(atakujacy->organism_to_string() + " ate " + this->organism_to_string());
	}
	if ((atakujacy->is_animal() /*&& atakujacy->get_organism_type() != OrganismType::CYBER_OWCA*/)
		|| atakujacy->get_str() < 10) {
		world->delete_organism(atakujacy);
		Commentator::add_comment(this->organism_to_string() + " kills " + atakujacy->organism_to_string());
	}
	return true;
}
