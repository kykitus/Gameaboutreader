#include <iostream>
#include <conio.h>
#include <random>
#include "pl.h"


#include "gra.h"

player playere;
std::vector<weapon*> wepon;
std::vector<armor*> armo;
std::vector<armor*> hem;
std::vector<funnyobject*> itme;

int main() {
	
	playercret();
	InitWeapons();
	InitArmor();
	InitLitem();
	while (true) {
		menu();
	}

	return 0;
}