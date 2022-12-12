#pragma once
#include <iostream>
#include <vector> 
#include "Organism.h"
#include "Point.h"

using namespace std;

class Organism;
class Human;

class World
{
public:
	World(int sizeX, int sizeY);
	World();
	World(World&& other);
	~World();
	void generate_world(/*double zapelnienieSwiatu*/);
	void makeTurn();
	void drawWorld();
	Point DrawFreeField();
	bool check_if_free(Point pole);
	Organism* whats_on_pos(Point pole);
	void add_organism(Organism* organism);
	void delete_organism(Organism* organism);

	int GetSizeX();
	int GetSizeY();
	const int GetNumerTury();
	Organism*** get_grid();
	vector<Organism*> getOrganisms();
	bool get_is_human_aliv();
	void set_is_human_alive(bool is_player_alive);
	bool is_game_over();
	void set_is_game_finished(bool is_game_finished);
	Organism* GetHuman();
protected:
	int sizeX, sizeY;
	int turn_number;
	Organism*** world_grid;
	bool is_player_alive;
	bool is_game_finished;
	vector<Organism*> organisms;
	Human* human;

	void sortOrganisms();
	void ObslugaInputu();
};