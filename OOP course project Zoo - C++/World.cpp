#pragma once
#include "World.h"
#include "Commentator.h"
#include "OrganismMaker.h"
#include "Keys.h"
#include <algorithm>
#include <tuple>
#include <iostream>
#include <fstream>
#include <conio.h>

#define NUMBER_OF_SPECIES 10
#define NUMBER_OF_ANIMALS_AT_THEBEG 2 //number of animals of each kind at the beginning of the game

World::World(int sizeX, int sizeY) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	turn_number = 0;
	is_player_alive = true;
	organisms.reserve(sizeX * sizeY / 2);

	world_grid = new Organism * *[sizeY];
	for (int i = 0; i < sizeY; i++) {
		world_grid[i] = new Organism * [sizeX];
	}
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			world_grid[i][j] = nullptr;
		}
	}
}

World::World()
{
	this->sizeX = 0;
	this->sizeY = 0;
	turn_number = 0;
	is_player_alive = true;
	organisms.reserve(0);
}

World::World(World&& other)
{
	this->sizeX = other.sizeX;
	this->sizeY = other.sizeY;
	this->turn_number = other.turn_number;
	this->world_grid = other.world_grid;
	this->is_player_alive = other.is_player_alive;
	this->is_game_finished = other.is_game_finished;
	this->organisms = other.organisms;
	this->human = other.human;

	for (size_t i = 0; i < organisms.size(); i++) {
		organisms[i]->setWorld(this);
	}

	other.sizeX = 0;
	other.sizeY = 0;
	other.turn_number = 0;
	other.world_grid = nullptr;
	other.is_player_alive = false;
	other.is_game_finished = false;
	other.human = nullptr;
}

void World::sortOrganisms()
{
	sort(organisms.begin(), organisms.end(),
		[](Organism* org1, Organism* org2) {
			int ini1 = org1->GetInitiative();
			int ini2 = org2->GetInitiative();
			int turn_of_birth1 = org1->GetBirthTurn();
			int turn_of_birth2 = org2->GetBirthTurn();
			return tie(ini2, turn_of_birth1) < tie(ini1, turn_of_birth2);
		});
}

World::~World() {
	for (int i = 0; i < sizeY; i++) {
		delete[] world_grid[i];
	}
	delete world_grid;
}

void World::generate_world() {
	Point position = DrawFreeField();
	Organism* tmpOrganizm = organisms_maker::create_new_organism(Organism::OrganismType::HUMAN, this, position);
	add_organism(tmpOrganizm);
	human = (Human*)tmpOrganizm;
	for (int i = 0; i < NUMBER_OF_ANIMALS_AT_THEBEG; i++)
	{
		Point position = DrawFreeField();
		if (!(position == Point(-1, -1))) {
			add_organism(organisms_maker::create_new_organism(Organism::OrganismType::WOLF, this, position));
		}
		else return;
		position = DrawFreeField();
		if (!(position == Point(-1, -1))) {
			add_organism(organisms_maker::create_new_organism(Organism::OrganismType::SHEEP, this, position));
		}
		else return;
		position = DrawFreeField();
		if (!(position == Point(-1, -1))) {
			add_organism(organisms_maker::create_new_organism(Organism::OrganismType::FOX, this, position));
		}
		else return;
		position = DrawFreeField();
		if (!(position == Point(-1, -1))) {
			add_organism(organisms_maker::create_new_organism(Organism::OrganismType::TURTLE, this, position));
		}
		else return;
		position = DrawFreeField();
		if (!(position == Point(-1, -1))) {
			add_organism(organisms_maker::create_new_organism(Organism::OrganismType::ANTYLOPA, this, position));
		}
		else return;
		position = DrawFreeField();
		if (!(position == Point(-1, -1))) {
			add_organism(organisms_maker::create_new_organism(Organism::OrganismType::GRASS, this, position));
		}
		else return;
		position = DrawFreeField();
		if (!(position == Point(-1, -1))) {
			add_organism(organisms_maker::create_new_organism(Organism::OrganismType::SOW_THISTLE, this, position));
		}
		else return;
		position = DrawFreeField();
		if (!(position == Point(-1, -1))) {
			add_organism(organisms_maker::create_new_organism(Organism::OrganismType::GUARANA, this, position));
		}
		else return;
		position = DrawFreeField();
		if (!(position == Point(-1, -1))) {
			add_organism(organisms_maker::create_new_organism(Organism::OrganismType::BELLADONNA, this, position));
		}
		else return;
		position = DrawFreeField();
		if (!(position == Point(-1, -1))) {
			add_organism(organisms_maker::create_new_organism(Organism::OrganismType::SOSNOWSKYS_HOGWEED, this, position));
		}
		else return;
	}
}

void World::makeTurn()
{
	Commentator::clear_comment();
	ObslugaInputu();
	if (is_game_finished) return;
	turn_number++;
	drawWorld();
	sortOrganisms();
	for (size_t i = 0; i < organisms.size(); i++) {
		if (organisms[i]->GetCzyUmarl() == true) { continue; }
		else if (organisms[i]->GetBirthTurn() != turn_number) {
			organisms[i]->action();
			drawWorld();
		}
	}

	for (size_t i = 0; i < organisms.size(); i++) {
		if (organisms[i]->GetCzyUmarl() == true) {
			delete organisms[i];
			organisms.erase(organisms.begin() + i);
		}
	}
	for (size_t i = 0; i < organisms.size(); i++) {
		organisms[i]->set_was_breeding(false);
	}
}

void World::drawWorld() {
	system("cls");
	cout << "												Daniel Wolski 184872\n";
	cout << "Use arrow keys to move\n";
	cout << "Space - special skill\n";
	cout << "Esc - finish \nEnter - next turn\n\n";

	//GRANICA GORNA
	for (int j = 0; j < (2 * sizeX) + 3; j++)
		cout << "#";
	cout << endl;
		
	for (int i = 0; i < sizeY; i++) 
	{
		//GRANICA LEWA
		for (int j = 0; j < 1; j++)
			cout << "#";

		//PLANSZA
		for (int j = 0; j < sizeX; j++) {
			cout << " ";
			if (world_grid[i][j] == nullptr) cout << " ";
			else world_grid[i][j]->Rysowanie();
		}
		cout << " ";
		//GRANICA PRAWA
		for (int j = 0; j < 1; j++)
			cout << "#";
		cout << endl;
	}

	//GRANICA DOLNA	
	for (int j = 0; j < (2 * sizeX) + 3; j++)
		cout << "#";
	cout << endl;
	cout << "Turn " << turn_number << endl;
		
	cout << endl;
	Commentator::comment();
}

int World::GetSizeX() {
	return sizeX;
}

int World::GetSizeY() {
	return sizeY;
}

const int World::GetNumerTury() {
	return turn_number;
}

bool World::check_if_free(Point pole)
{
	if (world_grid[pole.GetY()][pole.GetX()] == nullptr) return false;
	else return true;
}

Organism* World::whats_on_pos(Point pole)
{
	return world_grid[pole.GetY()][pole.GetX()];
}

Organism*** World::get_grid()
{
	return world_grid;
}

vector<Organism*> World::getOrganisms()
{
	return organisms;
}

bool World::get_is_human_aliv()
{
	return is_player_alive;
}

void World::set_is_human_alive(bool is_player_alive)
{
	this->is_player_alive = is_player_alive;
}

bool World::is_game_over()
{
	return is_game_finished;
}

void World::set_is_game_finished(bool is_game_finished)
{
	this->is_game_finished = is_game_finished;
}

void World::add_organism(Organism* organizm)
{
	organisms.push_back(organizm);
	world_grid[organizm->get_position().GetY()][organizm->get_position().GetX()] = organizm;
}

void World::delete_organism(Organism* organizm)
{
	get_grid()[organizm->get_position().GetY()][organizm->get_position().GetX()] = nullptr;
	organizm->SetCzyUmarl(true);
	if (organizm->get_organism_type() == Organism::OrganismType::HUMAN) {
		is_player_alive = false;
		human = nullptr;
	}
}

void World::ObslugaInputu()
{
	while (true) {
		//cout << endl << "Nacisnij klawisze...\n";
		int input;
		input = _getch();
		if (input == IF_ARROWS) {
			if (is_player_alive) {
				input = _getch();
				if (input == UP) {
					human->set_direction(Organism::Direction::GORA);
					break;
				}
				else if (input == DOWN) {
					human->set_direction(Organism::Direction::DOL);
					break;
				}
				else if (input == LEFT) {
					human->set_direction(Organism::Direction::LEWO);
					break;
				}
				else if (input == RIGHT) {
					human->set_direction(Organism::Direction::PRAWO);
					break;
				}
			}
			else {
				cout << "Human umarl, nie mozesz im wiecej sterowac" << endl;
				_getch();
				continue;
			}
		}
		if (is_player_alive && input == SPACE /*|| input == ABILITY2*/) {
			Human::Skill* tmpUmiejetnosc = human->get_skill();
			if (tmpUmiejetnosc->get_can_be_activated()) {
				tmpUmiejetnosc->activate();
				human->drink();
				break;
			}
			else if (tmpUmiejetnosc->get_is_active()) {
				cout << "Skill juz zostala aktywowana (Pozostaly czas trwania wynosi "
					<< tmpUmiejetnosc->get_duration() << " tur)" << endl;
				continue;
			}
			else {
				cout << "Skill mozna wlaczyc tylko po " << tmpUmiejetnosc->get_cooldown() << " turach" << endl;
				continue;
			}
		}
		else if ((!is_player_alive) && input == SPACE /*|| input == ABILITY2*/) {
			cout << "Human umarl, nie mozesz im wiecej sterowac" << endl;
			continue;
		}
		if (input ==  ESC/* || input == EXIT2*/) {
			is_game_finished = true; //WYJSCIE Z GRY
			break;
		}
		if (input == ENTER) { break; }// Przejscie do nastepnej tury(w przypadku gdy czlowiek umiera)
		else {
			cout << "Nieoznaczony symbol, sprobuj ponownie" << endl;
			continue;
		}
	}
}

Organism* World::GetHuman()
{
	return human;
}

Point World::DrawFreeField()
{
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			if (world_grid[i][j] == nullptr) {
				while (true) {
					int x = rand() % sizeX;
					int y = rand() % sizeY;
					if (world_grid[y][x] == nullptr) 
						return Point(x, y);
				}
			}
		}
	}
	return Point(-1, -1);
}
