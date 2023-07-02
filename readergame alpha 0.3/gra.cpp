#include <iostream>
#include <conio.h>

#include "pl.h"

#include "gra.h"


player gameplayer;
std::vector<weapon*> weapon_list;
std::vector<armor*> armor_list;
std::vector<armor*> helm_list;
std::vector<luckyitem*> item_list; // theese are only variables that makes you be able to access item objects

std::vector<consumable*> heal_usable;
std::vector<consumable*> energy_usable;
std::vector<consumable*> resistance_usable; // vectors for main consumable list
std::vector<std::vector <consumable*>> consumable_list;

int main() { //pre initialisations for game
	InitWeapons();
	InitArmor();
	InitLitem();
	InitConsumables();
	playercret();

	menu();

	return 0;
}