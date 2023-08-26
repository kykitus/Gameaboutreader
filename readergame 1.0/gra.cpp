#include <iostream>
#include <conio.h>
#include <random>

#include "pl.h"
#include "litemabilities.h"

#include "gra.h"


player gameplayer;
player* gameplayer_ptr = &gameplayer;
std::vector<weapon*> sword_list;
std::vector<weapon*> mace_list;
std::vector<weapon*> spear_list;
std::vector<std::vector<weapon*>> weapon_list;

std::vector<armor*> helm_list;
std::vector<armor*> breastplate_list;
std::vector<std::vector<armor*>> armor_list;

std::vector<luckyitem*> item_list;

std::vector<consumable*> heal_usable;
std::vector<consumable*> energy_usable;
std::vector<consumable*> resistance_usable; // vectors for main consumable list
std::vector<std::vector<consumable*>> consumable_list;

int main() { //pre initialisations for game
	InitWeapons();
	InitArmor();
	InitLitem();
	luckyitem_powerinitializer();
	InitConsumables();
	playercret();
	menu();

	return 0;
}