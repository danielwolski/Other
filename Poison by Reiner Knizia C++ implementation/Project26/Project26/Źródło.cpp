///////////////////////////////////////
//////////NAJMNIEJSZA KARTA/////////////
////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define Max_numb_of_cards 1000
#define Max_numb_of_players 100
#define Max_numb_of_piles 100

struct card {
    char color[20];
    int value;
};
card players_deck[Max_numb_of_players][Max_numb_of_players];
card cauldron_deck[Max_numb_of_players][Max_numb_of_players];

int player_cards_verse[Max_numb_of_players];
int pile_cards_verse[Max_numb_of_piles];

int colors_counter[7];
//i=0 green
//1 blue
//2 red
//3 violet
//4 yellow
//5 white
//6 black

int number_of_colors_values[7];
int colors_values[7][Max_numb_of_players];

int checkVALUE[Max_numb_of_players];
int checkCOLOR[7];

int resistance[7];
int total_points[Max_numb_of_players];
int colors_of_player[Max_numb_of_players][7];
int points[Max_numb_of_players];

void input_data(int* n, int* r, int* k, int* g, int* gv, int* e, int* o)
{
    int n_, r_, k_, g_, gv_, e_, o_;
    cout << "----------------------------------------------------------------------------------" << endl;

    cout << "Liczba graczy: ";
    cin >> n_;
    *n = n_;
    cout << endl;

    cout << "Liczba rund: ";
    cin >> r_;
    *r = r_;
    cout << endl;

    cout << "Liczba kociolkow odpowiadajaca liczbie kolorow kart z wylaczeniem zielonego: ";
    cin >> k_;
    *k = k_;
    cout << endl;

    cout << "Liczba zielonych kart w talii: ";
    cin >> g_;
    *g = g_;
    cout << endl;

    cout << "Wartosc zielonych kart: ";
    cin >> gv_;
    *gv = gv_;
    cout << endl;

    cout << "Wytrzymalosc kociolka: ";
    cin >> e_;
    *e = e_;
    cout << endl;

    cout << "Liczba kart dla kazdego innego koloru niz zielony: ";
    cin >> o_;
    *o = o_;
    cout << endl;
}

const char* color(int j)
{
    if (j == 0)
        return "green";
    else if (j == 1)
        return "blue";
    else if (j == 2)
        return "red";
    else if (j == 3)
        return "violet";
    else if (j == 4)
        return "yellow";
    else if (j == 5)
        return "white";
    else if (j == 6)
        return "black";
    else
        return 0;
}

card* create_cards(int n, int k, int g, int gv, int o)
{
    cout << "Wartosc kolejnych kart: ";
    int* V;//array of values for each color (excl. green)
    V = new int[o];
    for (int z = 0; z < o; z++)
        cin >> V[z];

    cout << "----------------------------------------------------------------------------------" << endl;

    card* deck;   //declaring array of values for each color     
    deck = new card[k * o + g];

    int i = 0;//which card is in the queue
    for (i; i < g; i++)//green cards
    {
        strcpy(deck[i].color, "green");
        deck[i].value = gv;
    }
    for (int j = 1; j <= k; j++)//remaining colors
        for (int a = 0; a < o; a++)//values of cards in each color (excl. green)
        {
            strcpy(deck[i].color, color(j));
            deck[i].value = V[a];
            i++;
        }

    delete[]V;
    return deck;
}

void shuffle(card* deck, int k, int o, int g)
{
    card temp_card;

    for (int i = 0; i < k * o + g; i++)
    {
        int a = rand() % (k * o + g);

        temp_card.value = deck[i].value;
        strcpy(temp_card.color, deck[i].color);

        deck[i].value = deck[a].value;
        strcpy(deck[i].color, deck[a].color);

        deck[a].value = temp_card.value;
        strcpy(deck[a].color, temp_card.color);
    }

}

int correct_number_of_cards_for_each_player[Max_numb_of_players];
void first_deal_and_make_a_file(card* deck, int n, int k, int g, int o)
{
    for (int i = 0; i < Max_numb_of_players; i++)
        correct_number_of_cards_for_each_player[i] = 0;

    int sum = k * o + g;
    int i = 0;
    while (sum > 0)
    {
        if (i >= n)
        {
            i = i - n;
            correct_number_of_cards_for_each_player[i]++;
        }
        else
            correct_number_of_cards_for_each_player[i]++;
        i++;
        sum--;
    }

    FILE* state;
    state = fopen("state.txt", "w");
    cout << "active player = 1" << endl;
    cout << endl;
    fprintf(state, "active player = 1\n");
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        int l = 0;
        fprintf(state, "%d player hand cards: ", i + 1);
        cout << i + 1 << " player hand cards: ";

        while (l < correct_number_of_cards_for_each_player[i])
        {
            fprintf(state, "%d %s ", deck[j].value, deck[j].color);
            cout << deck[j].value << " " << deck[j].color << " ";
            j++;
            l++;
        }

        fprintf(state, "\n");
        cout << endl;

        fprintf(state, "%d player deck cards: ", i + 1);
        cout << i + 1 << " player deck cards: " << endl;
        fprintf(state, "\n");
    }
    cout << endl;

    for (int i = 0; i < k; i++)
    {
        fprintf(state, "%d pile cards: \n", i + 1);
        cout << i + 1 << " pile cards: " << endl;
    }

    cout << "----------------------------------------------------------------------------------" << endl;
    fclose(state);
}



int main()
{
    /////////POCZ?TEK ROZGRWKI/////////
    int n, r, k, g, gv, e, o;

    input_data(&n, &r, &k, &g, &gv, &e, &o);//wprowadzanie danych

    card* deck = create_cards(n, k, g, gv, o);//tworzenie niepotasowanej talii



    ////////P?TLA JAD?CA r RUND////////
    for (int round = 1; round <= r; round++)
    {
        cout << "----------------------------------------------------------------------------------" << endl;
        cout << "//////////////////////////////////////////////////////////////////////////////////" << endl;
        cout << "//////////////////////////////////// RUNDA " << round << " /////////////////////////////////////" << endl;
        cout << "//////////////////////////////////////////////////////////////////////////////////" << endl;
        cout << "----------------------------------------------------------------------------------" << endl;

        shuffle(deck, k, o, g);//tasowanie

        int active_player = 1;

        first_deal_and_make_a_file(deck, n, k, g, o);//tworzenie pliku z zerowym stanem gry

        ///////ZEROWANIE TABLIC PRZED RUND?//////////
        for (int i = 0; i < 7; i++)
        {
            colors_counter[i] = 0;
            resistance[i] = 0;
            number_of_colors_values[i] = 0;
            for (int j = 0; j < Max_numb_of_players; j++)
                colors_values[i][j] = 0;
        }

        for (int i = 0; i < Max_numb_of_players; i++)
        {
            player_cards_verse[i] = 0;
            pile_cards_verse[i] = 0;
            checkVALUE[i] = 0;
            for (int j = 0; j < 7; j++)
                colors_of_player[i][j] = 0;
        }


        FILE* state;
        state = fopen("state.txt", "r");
        if (state == NULL)
        {
            cout << "error with state.txt";
            return 1;
        }


        ////////P?TLA JAD?CA A? DO KO?CA RUNDY//////
        while (true)
        {

            /////////ODCZYT STANU GRY Z PLIKU/////////
            //pierwszy wers
            char verse[9999];
            fgets(verse, sizeof(verse), state);
            //nastepne 2*n wersów - wczytywanie danych kart do struktur graczy/liczenie kart
            for (int i = 0; i < 2 * n; i++)
            {
                char verse[9999];
                fgets(verse, sizeof(verse), state);
                char* token = strtok(verse, " \n");//tokenem jest numer gracza

                int j = 0;
                while (token != NULL)
                {
                    if (j <= 3)
                    {
                        token = strtok(NULL, " \n");
                        j++;
                    }
                    else
                    {
                        int a;
                        a = atoi(token);
                        players_deck[i][j].value = a;
                        token = strtok(NULL, " \n");

                        strcpy(players_deck[i][j].color, token);
                        //zliczanie kolorow dla graczy
                        for (int v = 0; v < 7; v++)
                        {
                            if (strcmp(players_deck[i][j].color, color(v)) == 0)
                                colors_counter[v]++;
                        }

                        token = strtok(NULL, " \n");
                        j++;
                        player_cards_verse[i]++;//licznik kart odpowiadajacy liczbie kart w ka?dym wersie wej?cia dla graczy
                    }
                }
            }
            //nastepne k wersów - wczytywanie danych kart do struktur kocio?ka/liczenie kart
            for (int i = 0; i < k; i++)
            {
                char verse[9999];
                fgets(verse, sizeof(verse), state);
                char* token = strtok(verse, " \n");//tokenem jest numer gracza

                int j = 0;
                while (token != NULL)
                {
                    if (j <= 2)
                    {
                        token = strtok(NULL, " \n");
                        j++;
                    }
                    else
                    {
                        int a;
                        a = atoi(token);
                        cauldron_deck[i][j].value = a;
                        token = strtok(NULL, " \n");

                        strcpy(cauldron_deck[i][j].color, token);

                        for (int v = 0; v < 7; v++)
                        {
                            if (strcmp(cauldron_deck[i][j].color, color(v)) == 0)
                                colors_counter[v]++;
                        }

                        token = strtok(NULL, " \n");
                        j++;
                        pile_cards_verse[i]++;//licznik kart dla ka?dego wersu odpowiadajacego kocio?kom
                    }
                }
            }



            //////////NAJMNIEJSZA KARTA////////////
            //szukanie najmniejszej wartosci kart w r?ku gracza

            int correct_pile = -1;

            struct pile_data {
                int can_you_drop_card_to_this_pile;
                int total_value;
            };

            struct card_data {
                int is_it_min_value_card;
                int allowed_piles[Max_numb_of_piles];
                int allowed_piles_values[Max_numb_of_piles];
                int pile_position;
                int minimum_pile_value;
            };

            pile_data data_for_pile[Max_numb_of_piles];
            card_data data_for_card[Max_numb_of_cards];

            for (int i = 0; i < k; i++)
            {
                data_for_pile[i].can_you_drop_card_to_this_pile = -1;
                data_for_pile[i].total_value = 0;
            }

            for (int i = 0; i < Max_numb_of_cards; i++)
            {
                data_for_card[i].is_it_min_value_card = -1;
                data_for_card[i].pile_position = -1;
                data_for_card[i].minimum_pile_value = -1;
                for (int j = 0; j < k; j++)
                {
                    data_for_card[i].allowed_piles[j] = -1;
                    data_for_card[i].allowed_piles_values[j] = 0;
                }
            }

            card moved_card;
            int min_card_value = 999999999;
            for (int j = 4; j < player_cards_verse[active_player * 2 - 2] + 4; j++)
                if (players_deck[active_player * 2 - 2][j].value < min_card_value)
                    min_card_value = players_deck[active_player * 2 - 2][j].value;
            //ile jest takich kart
            int min_value_cards_counter = 0;
            for (int j = 4; j < player_cards_verse[active_player * 2 - 2] + 4; j++)
                if (players_deck[active_player * 2 - 2][j].value == min_card_value)
                    min_value_cards_counter++;


            if (min_value_cards_counter == 1)
            {
                //szukam i tworz? kopi? tej karty
                int moved_card_position;
                for (int j = 4; j < player_cards_verse[active_player * 2 - 2] + 4; j++)
                    if (players_deck[active_player * 2 - 2][j].value == min_card_value)
                    {
                        moved_card.value = players_deck[active_player * 2 - 2][j].value;
                        strcpy(moved_card.color, players_deck[active_player * 2 - 2][j].color);
                        moved_card_position = j;
                        break;
                    }

                //przesuwanie kart w wersie aktywnego gracza "o jeden w lewo" - oryginal wyj?tej karty jest nadpisywany
                for (int j = moved_card_position + 1; j < player_cards_verse[active_player * 2 - 2] + 4; j++)
                {
                    players_deck[active_player * 2 - 2][j - 1].value = players_deck[active_player * 2 - 2][j].value;
                    strcpy(players_deck[active_player * 2 - 2][j - 1].color, players_deck[active_player * 2 - 2][j].color);
                }
                player_cards_verse[active_player * 2 - 2]--;
                //\\//\\//\\//\\//\\//\\
                //szukanie potencjalnych kociolkow

                for (int i = 0; i < k; i++)
                    if (strcmp(moved_card.color, "green") == 0)//1 mozliwosc - karta jest zielona
                        data_for_pile[i].can_you_drop_card_to_this_pile = 1;
                for (int i = 0; i < k; i++)
                    if (data_for_pile[i].can_you_drop_card_to_this_pile == -1)//2 mozliwosc - jest juz odpowiedni kociolek
                        for (int j = 3; j < pile_cards_verse[i] + 3; j++)
                            if (strcmp(moved_card.color, cauldron_deck[i][j].color) == 0)
                            {
                                data_for_pile[i].can_you_drop_card_to_this_pile = 1;
                                correct_pile = i;
                            }
                for (int i = 0; i < k; i++)
                    if (data_for_pile[i].can_you_drop_card_to_this_pile == -1 && correct_pile == -1)//3 mozliwosc - karta laduje do pustego kociolka albo tego z tylko zielonymi
                    {
                        if (pile_cards_verse[i] == 0)
                            data_for_pile[i].can_you_drop_card_to_this_pile = 1;
                        else
                        {
                            int check_all_green = 1;
                            for (int j = 3; j < pile_cards_verse[i] + 3; j++)
                                if (strcmp(cauldron_deck[i][j].color, "green") != 0)
                                    check_all_green = 0;
                            if (check_all_green == 1)
                                data_for_pile[i].can_you_drop_card_to_this_pile = 1;
                        }
                    }

                //szukanie kociolka z najmniejsza wartoscia do ktorego mozna wrzuci? wyj?t? kart?
                int min_pile_value = 99999999;
                for (int i = 0; i < k; i++)
                    if (data_for_pile[i].can_you_drop_card_to_this_pile == 1)
                    {
                        for (int j = 3; j < pile_cards_verse[i] + 3; j++)
                            data_for_pile[i].total_value = data_for_pile[i].total_value + cauldron_deck[i][j].value;
                        if (min_pile_value > data_for_pile[i].total_value)
                            min_pile_value = data_for_pile[i].total_value;
                    }
                //szukam kociolka z ta najmniejsza wartoscia
                correct_pile = -1;
                for (int i = 0; i < k; i++)
                    if (data_for_pile[i].total_value == min_pile_value && data_for_pile[i].can_you_drop_card_to_this_pile == 1)
                    {
                        correct_pile = i;
                        break;
                    }
                //karta laduje w kociolku
                cauldron_deck[correct_pile][pile_cards_verse[correct_pile] + 3].value = moved_card.value;
                strcpy(cauldron_deck[correct_pile][pile_cards_verse[correct_pile] + 3].color, moved_card.color);
                pile_cards_verse[correct_pile]++;//zwiekszamy liczbe kart w danym kociolku o 1
            }
            else
            {   //wyznacza ktore karty maja najmniejsza wartosc
                for (int j = 4; j < player_cards_verse[active_player * 2 - 2] + 4; j++)
                    if (players_deck[active_player * 2 - 2][j].value == min_card_value)
                        data_for_card[j].is_it_min_value_card = 1;

                //dla kazdej karty wyznacza do ktorego kociolka mo?e trafi?
                int stop = 0;
                for (int j = 4; j < player_cards_verse[active_player * 2 - 2] + 4; j++)
                {
                    stop = 0;
                    if (data_for_card[j].is_it_min_value_card == 1)
                    {
                        for (int i = 0; i < k; i++)
                        {
                            if (strcmp(players_deck[active_player * 2 - 2][j].color, "green") == 0)//1 mozliwosc - karta jest zielona
                                data_for_card[j].allowed_piles[i] = 1;
                            if (data_for_card[j].allowed_piles[i] == -1)//2 mozliwosc - jest juz odpowiedni kociolek
                                for (int j_ = 3; j_ < pile_cards_verse[i] + 3; j_++)
                                {
                                    if (strcmp(players_deck[active_player * 2 - 2][j].color, cauldron_deck[i][j_].color) == 0)
                                    {
                                        data_for_card[j].allowed_piles[i] = 1;
                                        stop = 1;
                                    }
                                }
                        }
                        for (int i = 0; i < k; i++)
                        {
                            if (stop == 1)
                                break;
                            if (data_for_card[j].allowed_piles[i] == -1)//3 mozliwosc - karta laduje do pustego kociolka albo tego z tylko zielonymi
                            {
                                if (pile_cards_verse[i] == 0)
                                    data_for_card[j].allowed_piles[i] = 1;
                                else
                                {
                                    int check_all_green = 1;
                                    for (int j = 3; j < pile_cards_verse[i] + 3; j++)
                                        if (strcmp(cauldron_deck[i][j].color, "green") != 0)
                                            check_all_green = 0;
                                    if (check_all_green == 1)
                                        data_for_card[j].allowed_piles[i] = 1;
                                }
                            }
                        }
                    }
                }

                //dla ka?dej karty aktywnego gracza ktora ma najmniejsza wartosc, dla ka?dego kociolka do ktorego moze byc ona wrzucona liczy sum? warto?ci w tym kociolku
                for (int j = 4; j < player_cards_verse[active_player * 2 - 2] + 4; j++)
                    if (data_for_card[j].is_it_min_value_card == 1)
                        for (int i = 0; i < k; i++)
                            if (data_for_card[j].allowed_piles[i] == 1)
                                for (int x = 3; x < pile_cards_verse[i] + 3; x++)
                                    data_for_card[j].allowed_piles_values[i] = data_for_card[j].allowed_piles_values[i] + cauldron_deck[i][x].value;

                int min_pile_value;
                for (int j = 4; j < player_cards_verse[active_player * 2 - 2] + 4; j++)
                {
                    min_pile_value = 9999999;
                    for (int i = 0; i < k; i++)//szuka najmniejszej wartosci
                        if (data_for_card[j].is_it_min_value_card == 1 && data_for_card[j].allowed_piles[i] == 1)
                            if (data_for_card[j].allowed_piles_values[i] < min_pile_value)
                            {
                                min_pile_value = data_for_card[j].allowed_piles_values[i];
                                data_for_card[j].pile_position = i;
                                data_for_card[j].minimum_pile_value = min_pile_value;
                            }
                }

                int card_position = -1;
                int optimal_pile_value = 9999999;
                for (int j = 4; j < player_cards_verse[active_player * 2 - 2] + 4; j++)//szukam która karta bedzie najlepsza
                    if (data_for_card[j].is_it_min_value_card == 1 && data_for_card[j].minimum_pile_value < optimal_pile_value)
                    {
                        optimal_pile_value = data_for_card[j].minimum_pile_value;
                        card_position = j;
                    }

                //kopiowanie tej karty
                moved_card.value = players_deck[active_player * 2 - 2][card_position].value;
                strcpy(moved_card.color, players_deck[active_player * 2 - 2][card_position].color);

                //przesuwanie kart w wersie aktywnego gracza "o jeden w lewo" - oryginal wyj?tej karty jest nadpisywany
                for (int j = card_position + 1; j < player_cards_verse[active_player * 2 - 2] + 4; j++)
                {
                    players_deck[active_player * 2 - 2][j - 1].value = players_deck[active_player * 2 - 2][j].value;
                    strcpy(players_deck[active_player * 2 - 2][j - 1].color, players_deck[active_player * 2 - 2][j].color);
                }
                player_cards_verse[active_player * 2 - 2]--;

                correct_pile = data_for_card[card_position].pile_position;

                //karta laduje w kociolku
                cauldron_deck[correct_pile][pile_cards_verse[correct_pile] + 3].value = moved_card.value;
                strcpy(cauldron_deck[correct_pile][pile_cards_verse[correct_pile] + 3].color, moved_card.color);
                pile_cards_verse[data_for_card[card_position].pile_position]++;//zwiekszamy liczbe kart w danym kociolku o 1
            }

            /////////SPRAWDZANIE POPRAWNO?CI/////////
            //ilo?ci kart ka?dego koloru
            int check_colors_number = 1;
            for (int i = 2; i < 7; i++)
                if (colors_counter[i - 1] != colors_counter[i] && colors_counter[i - 1] != 0 && colors_counter[i] != 0)
                    check_colors_number = 0;
            if (check_colors_number != 1)
            {
                cout << "At least two colors with a different number of cards were found: " << endl;
                for (int i = 1; i < 7; i++)
                {
                    if (colors_counter[i] != 0)
                        cout << color(i) << " cards are " << colors_counter[i] << endl;
                }
                return 0;
            }

            //sprawdzanie poprawnosci ilosci kart w reku gracza
            int checkPLAYERScards = 1;
            int default_difference = 1;
            for (int i = 0; i < 2 * n; i = i + 2)
                for (int j = 0; j < 2 * n; j = j + 2)
                    if (abs(player_cards_verse[i] - player_cards_verse[j]) > default_difference)
                    {
                        checkPLAYERScards = 0;
                        cout << "The number of players cards on hand is wrong" << endl;
                        return 0;
                    }

            //sprawdzanie poprawnosci kolorów dla kocio?ka
            for (int i = 0; i < 7; i++)
                checkCOLOR[i] = 0;
            for (int i = 0; i < k; i++)
                checkCOLOR[i] = 2;//wypelnianie istniejacych kociolkow wartoscia 2
            for (int i = 0; i < k; i++)
                for (int j = 4; j < pile_cards_verse[i] + 3; j++)
                {
                    if ((strcmp(cauldron_deck[i][j].color, cauldron_deck[i][j - 1].color) != 0) && (strcmp(cauldron_deck[i][j].color, "green") != 0) && (strcmp(cauldron_deck[i][j - 1].color, "green") != 0))
                    {
                        checkCOLOR[i] = 1;//0 znaczy ze kociolek nie istnieje, 1 ?e jest b??d a 2 ?e jest prawid?owy
                        cout << strcmp(cauldron_deck[i][j].color, cauldron_deck[i][j - 1].color) << endl;
                        cout << checkCOLOR[i];
                        cout << cauldron_deck[i][j].color << " " << cauldron_deck[i][j - 1].color << endl;
                        cout << "Two different colors were found on the " << i + 1 << " pile" << endl;
                        return 0;
                    }
                }
            //sprawdzanie poprawnosci wartosci dla kocio?ka(czy nie powinna nastapic wczesniej eksplozja)
            for (int i = 0; i < k; i++)
                checkVALUE[i] = 2;//wypelnianie istniejacych kociolkow wartoscia 2
            //sprawdzanie poprawnosci
            for (int i = 0; i < k; i++)
            {
                int suma = 0;
                for (int j = 3; j < pile_cards_verse[i] + 3; j++)
                {
                    suma = suma + cauldron_deck[i][j].value;
                    if (suma > e)
                        checkVALUE[i] = 1;//0 znaczy ze kociolek nie istnieje, 1 ?e jest b??d a 2 ?e jest prawid?owy
                }
            }

            //Sprawdzania i ew. wybuch kocio?ka
            checkVALUE[correct_pile] = 2;//2=poprawny stan
            int suma = 0;
            for (int j = 3; j < pile_cards_verse[correct_pile] + 3; j++)
            {
                suma = suma + cauldron_deck[correct_pile][j].value;
                if (suma > e)
                    checkVALUE[correct_pile] = 1;//1=b??d
            }

            //wybuch
            if (checkVALUE[correct_pile] == 1)
            {
                cout << "Cauldron " << correct_pile + 1 << " exploded!" << endl;
                cout << "Cards are going to player " << active_player << endl;
                for (int j = 3; j < pile_cards_verse[correct_pile] + 3; j++)
                {
                    players_deck[active_player * 2 - 1][player_cards_verse[active_player * 2 - 1] + j + 1].value = cauldron_deck[correct_pile][j].value;
                    strcpy(players_deck[active_player * 2 - 1][player_cards_verse[active_player * 2 - 1] + j + 1].color, cauldron_deck[correct_pile][j].color);
                }
                player_cards_verse[active_player * 2 - 1] = player_cards_verse[active_player * 2 - 1] + pile_cards_verse[correct_pile];//zwiekszanie liczby kart na stosie
                pile_cards_verse[correct_pile] = 0;
            }

            fclose(state);
            /////////WYPISANIE NA EKRANIE I ZAPISANIE W PLIKU/////////
            state = fopen("state.txt", "w");

            cout << "----------------------------------------------------------------------------------" << endl;

            if (active_player + 1 > n)
                active_player = active_player + 1 - n;
            else
                active_player++;
            cout << "active player = " << active_player << endl;
            fprintf(state, "active player =  %d\n", active_player);
            cout << endl;

            //dla graczy
            int vers = 0;
            for (int p = 1; p <= n; p++)
            {
                cout << p << " player hand cards: ";
                fprintf(state, "%d player hand cards: ", p);
                for (int j = 4; j < player_cards_verse[vers] + 4; j++)
                {
                    cout << players_deck[vers][j].value << " " << players_deck[vers][j].color << " ";
                    fprintf(state, "%d %s", players_deck[vers][j].value, players_deck[vers][j].color);
                }
                cout << endl;
                fprintf(state, "\n");
                vers++;

                cout << p << " player deck cards: ";
                fprintf(state, "%d player deck cards: ", p);
                for (int j = 4; j < player_cards_verse[vers] + 4; j++)
                {
                    cout << players_deck[vers][j].value << " " << players_deck[vers][j].color << " ";
                    fprintf(state, "%d %s", players_deck[vers][j].value, players_deck[vers][j].color);
                }
                cout << endl;
                fprintf(state, "\n");
                vers++;
            }
            cout << endl;
            //dla kociolka
            for (int i = 1; i <= k; i++)
            {
                cout << i << " pile cards: ";
                fprintf(state, "%d pile cards: ", i);
                for (int j = 3; j < pile_cards_verse[i - 1] + 3; j++)
                {
                    cout << cauldron_deck[i - 1][j].value << " " << cauldron_deck[i - 1][j].color << " ";
                    fprintf(state, "%d %s", cauldron_deck[i - 1][j].value, cauldron_deck[i - 1][j].color);
                }
                cout << endl;
                fprintf(state, "\n");
            }

            cout << "----------------------------------------------------------------------------------" << endl;

            fclose(state);

            //czy nastapil koniec rundy
            int check_ifEnd = 0;
            for (int i = 0; i < 2 * n; i = i + 2)
                if (player_cards_verse[i] != 0)
                    check_ifEnd = 1;
            if (check_ifEnd == 0)
                break;
        }

        /////////OBS?UGA KO?CA RUNDY/////////
        for (int i = 1; i < 2 * n; i = i + 2)//dla kazdego gracza tylko stos lezacy przed nim
            for (int j = 4; j < player_cards_verse[i] + 4; j++)//jedzie od pierwszej karty do ostatniej
            {
                for (int v = 1; v < 7; v++)//sprawdzanie jaki kolor (wy?. zielony)
                {
                    if (strcmp(players_deck[i][j].color, color(v)) == 0)
                        colors_of_player[i][v]++;
                }
            }

        //wyznaczanie ktory gracz ma nawjwiecej danego koloru (od 1 do 6 - bez zielonego)
        for (int v = 1; v < 7; v++)
        {
            int secondmax = 0;
            int firstmax = 0;
            for (int i = 1; i < 2 * n; i = i + 2)
                if (colors_of_player[i][v] >= firstmax)
                {
                    secondmax = firstmax;
                    firstmax = colors_of_player[i][v];
                }

            if (firstmax > secondmax)
                for (int i = 1; i < 2 * n; i = i + 2)
                    if (colors_of_player[i][v] == firstmax)
                        resistance[v] = i;
        }


        for (int i = 0; i < Max_numb_of_players; i++)
            points[i] = 0;

        for (int i = 1; i < 2 * n; i = i + 2)
        {
            for (int j = 4; j < player_cards_verse[i] + 4; j++)
            {
                if (strcmp(players_deck[i][j].color, "green") == 0)
                {
                    points[i] = points[i] + 2;
                    total_points[i] = total_points[i] + 2;
                }
            }
            for (int v = 1; v < 7; v++)
                if (resistance[v] != i)//jesli nie ma odpornosci na dany kolor
                {
                    points[i] = points[i] + colors_of_player[i][v];
                    total_points[i] = total_points[i] + colors_of_player[i][v];
                }
        }

        for (int v = 1; v < 7; v++)
            if (resistance[v] != 0)
                cout << "Na kolor " << color(v) << " odporny jest gracz " << (resistance[v] + 1) / 2 << endl;

        for (int i = 1; i < 2 * n; i = i + 2)
            cout << "Wynik gracza " << (i + 1) / 2 << " = " << points[i] << endl;
        fclose(state);
    }

    int min = 999999;
    cout << endl;
    cout << "**************WYNIKI***************" << endl;
    for (int i = 1; i < 2 * n; i = i + 2)
    {
        cout << "Ostateczny wynik gracza " << (i + 1) / 2 << " = " << total_points[i] << endl;
        if (total_points[i] < min)
            min = total_points[i];
    }

    cout << endl;
    cout << "**************ZWYCIEZCA/Y***************" << endl;
    for (int i = 1; i < 2 * n; i = i + 2)
        if (total_points[i] == min)
            cout << "Gracz " << (i + 1) / 2 << " = " << total_points[i] << endl;

    return 0;
}