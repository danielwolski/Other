#include "Organism.h"
//#include "Kolory.h"
//HANDLE static color = GetStdHandle(STD_OUTPUT_HANDLE);
#define LICZBA_ROZNYCH_GATUNKOW 10

void Organism::Rysowanie()
{
	//SetConsoleTextAttribute(color, kolor);
	cout << symbol;
	//SetConsoleTextAttribute(color, WHITE);
}

bool Organism::special_action_while_attack(Organism* atakujacy, Organism* ofiara)
{
	return false;
}

int Organism::get_str()
{
	return str;
}

void Organism::SetSila(int str)
{
	this->str = str;
}

int Organism::GetInitiative()
{
	return inicjatywa;
}

void Organism::SetInicjatywa(int inicjatywa)
{
	this->inicjatywa = inicjatywa;
}

bool Organism::GetCzyUmarl()
{
	return czyUmarl;
}

void Organism::SetCzyUmarl(bool czyUmarl)
{
	this->czyUmarl = czyUmarl;
}

Organism::OrganismType Organism::get_organism_type()
{
	return organism_type;
}

void Organism::SetTypOrganizmu(OrganismType organism_type)
{
	this->organism_type = organism_type;
}

Point Organism::get_position()
{
	return Point(position.GetX(), position.GetY());
}

void Organism::SetPozycja(int x, int y)
{
	position.SetX(x);
	position.SetY(y);
}

int Organism::GetBirthTurn()
{
	return age;
}

void Organism::SetTuraUrodzenia(int turaUrodzenia)
{
	this->age = turaUrodzenia;
}

World* Organism::getWorld()
{
	return world;
}

void Organism::setWorld(World* world)
{
	this->world = world;
}

Organism::~Organism()
{
	delete[] direction;
}

string Organism::organism_to_string()
{
	return (organism_type_to_string() + " x[" + to_string(position.GetX()) + "] y["
		+ to_string(position.GetY()) + "] str[" + to_string(str) + "]");
}

Organism::Organism(OrganismType organism_type, World* world, Point position, int turaUrodzenia, int str, int inicjatywa)
{
	this->organism_type = organism_type;
	this->world = world;
	this->position = position;
	this->age = turaUrodzenia;
	this->str = str;
	this->inicjatywa = inicjatywa;
	czyUmarl = false;
}

void Organism::make_move(Point przyszlaPozycja)
{
	int x = przyszlaPozycja.GetX();
	int y = przyszlaPozycja.GetY();
	world->get_grid()[position.GetY()][position.GetX()] = nullptr;
	world->get_grid()[y][x] = this;
	position.SetX(x);
	position.SetY(y);
}

Point Organism::draw_any_position(Point position)
{
	unlock_all_directions();
	int pozX = position.GetX();
	int pozY = position.GetY();
	int sizeX = world->GetSizeX();
	int sizeY = world->GetSizeY();
	int ileKierunkowMozliwych = 0;

	if (pozX == 0) block_direction(Direction::LEWO);
	else ileKierunkowMozliwych++;
	if (pozX == sizeX - 1) block_direction(Direction::PRAWO);
	else ileKierunkowMozliwych++;
	if (pozY == 0) block_direction(Direction::GORA);
	else ileKierunkowMozliwych++;
	if (pozY == sizeY - 1) block_direction(Direction::DOL);
	else ileKierunkowMozliwych++;

	if (ileKierunkowMozliwych == 0) return Point(pozX, pozY);
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

Point Organism::draw_free_position(Point position)
{
	unlock_all_directions();
	int pozX = position.GetX();
	int pozY = position.GetY();
	int sizeX = world->GetSizeX();
	int sizeY = world->GetSizeY();
	int ileKierunkowMozliwych = 0;

	if (pozX == 0) block_direction(Direction::LEWO);
	else {
		if (world->check_if_free(Point(pozX - 1, pozY)) == false) ileKierunkowMozliwych++;
		else block_direction(Direction::LEWO);
	}

	if (pozX == sizeX - 1) block_direction(Direction::PRAWO);
	else {
		if (world->check_if_free(Point(pozX + 1, pozY)) == false) ileKierunkowMozliwych++;
		else block_direction(Direction::PRAWO);
	}

	if (pozY == 0) block_direction(Direction::GORA);
	else {
		if (world->check_if_free(Point(pozX, pozY - 1)) == false) ileKierunkowMozliwych++;
		else block_direction(Direction::GORA);
	}

	if (pozY == sizeY - 1) block_direction(Direction::DOL);
	else {
		if (world->check_if_free(Point(pozX, pozY + 1)) == false) ileKierunkowMozliwych++;
		else block_direction(Direction::DOL);
	}

	if (ileKierunkowMozliwych == 0) return Point(pozX, pozY);
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

int Organism::GetKolor()
{
	return kolor;
}

void Organism::SetKolor(int kolor)
{
	this->kolor = kolor;
}

char Organism::GetSymbol()
{
	return symbol;
}

void Organism::SetSymbol(char symbol)
{
	this->symbol = symbol;
}

void Organism::block_direction(Direction direction)
{
	this->direction[(int)direction] = false;
}

void Organism::OdblokujKierunek(Direction direction)
{
	this->direction[(int)direction] = true;
}

void Organism::unlock_all_directions()
{
	OdblokujKierunek(Direction::LEWO);
	OdblokujKierunek(Direction::PRAWO);
	OdblokujKierunek(Direction::GORA);
	OdblokujKierunek(Direction::DOL);
}

void Organism::ZablokujWszystkieKierunki()
{
	block_direction(Direction::LEWO);
	block_direction(Direction::PRAWO);
	block_direction(Direction::GORA);
	block_direction(Direction::DOL);
}

bool Organism::is_direction_blocked(Direction direction)
{
	return !(this->direction[(int)direction]);
}

bool Organism::get_was_breeding()
{
	return was_breeding;
}

void Organism::set_was_breeding(bool was_breeding)
{
	this->was_breeding = was_breeding;
}
