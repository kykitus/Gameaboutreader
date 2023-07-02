#pragma once

std::vector<std::string> Enemynames_list;

void InitEnemynames() //makes list of possible names like rest init functions objects
{
	std::ifstream inFile;
	try {
		inFile.open("enames.txt");
	}
	catch (std::exception& e) {
		std::cerr << "Exception opening/reading enames.txt\n";
		std::exit(0);
	}

	std::string enemyname;
	int start = 0; // first line
	while (!inFile.eof()) {
		std::getline(inFile, enemyname, '\n');

		if (start != 1) {
			start++;
			continue;
		}

		if (inFile.eof()) {
			break;
		}

		Enemynames_list.push_back(enemyname);

	}

}

size_t enemyname_generator() { // int makes exception error
	std::random_device numgenerator;
	std::uniform_int_distribution<size_t> enemyname_gen(1, Enemynames_list.size() - 1);
	int enemyname = enemyname_gen(numgenerator);
	return enemyname;
}

int equipment_seed(int limit) { //seed for each equipment for enemy
	std::random_device numgenerator;
	std::uniform_int_distribution<int> equp_seed(0, limit);
	int chosennumber = equp_seed(numgenerator);

	return chosennumber;
}



int weapon_randomizer() { //weapon seed limit maker
	int limit = 0;
	int count = 0;
	while (count < weapon_list.size()) {
		if (weapon_list[count]->getlvlreq() > gameplayer.getlvl()) {
			limit = count - 1;
			break;
		}
		count++;
	}

	return equipment_seed(limit);
}

int armor_randomizer(bool helm) { //breastplate/helm seed limit maker
	int limit = 0;
	std::vector<armor*> armorr;
	
	if (helm == true) { armorr = helm_list; }
	else if (helm == false) { armorr = armor_list; }

	while (limit < armorr.size()) {
		if (armorr[limit]->getlvlreq() > gameplayer.getlvl()) {
			limit--;
			break;
		}
		limit++;
	}

	return equipment_seed(limit);
}

int item_randomizer() { //item seed limit maker
	int limit = 0;
	int count = 0;
	while (count < item_list.size()) {
		if (item_list[count]->getlvlreq() > gameplayer.getlvl()) {
			limit = count - 1;
			break;
		}
		count++;
	}

	return equipment_seed(limit);
}

enemy* enemy_creator() {
	std::random_device generator;
	std::uniform_int_distribution<int> seed(1, 15); //stats seeds
	std::uniform_int_distribution<int> seed2(1, 10);
	std::uniform_int_distribution<int> seed3(1, 5);
	int statseed1 = seed(generator);
	int statseed2 = seed2(generator);
	int statseed3 = seed3(generator);
	std::string name = Enemynames_list[enemyname_generator()];
	int atk = gameplayer.getlvl() * 2 + (0.5 * statseed2);
	int hp = gameplayer.getlvl() * 15 + (0.3 * statseed1);
	int ptval = gameplayer.getlvl() * 20 + (statseed2 + statseed1);
	int ggolval = gameplayer.getlvl() * statseed3 * (1 + (gameplayer.getlvl() * 0.5));
	int idwep = weapon_randomizer();
	int idarm = armor_randomizer(false);
	int idhem = armor_randomizer(true);

	int iditem = 0;
	if (gameplayer.getlvl() > 2) {
		int iditem = item_randomizer();
	}
	return new enemy(name, atk, hp, ptval, ggolval, idwep, idarm, idhem, iditem); //new enemy pointer
}

void attackprocess(enemy * opponent, int choose, int attacktype) {

	int damage = gameplayer.getatk() + weapon_list[gameplayer.getidofwep()]->getdirectionattack(attacktype);
	double bonus = 1 + (-0.13 * opponent->getidofarmor());
	std::string enter;
	if (gameplayer.getdistance() > gameplayer.getrange() + weapon_list[gameplayer.getidofwep()]->getrange()) {
		std::cout << "your attack missed";
		enter = _getch();

	}
	else {
		switch (weapon_list[gameplayer.getidofwep()]->getclassweapon() & armor_list[opponent->getidofarmor()]->getclassarmor()) {
		case mace_weapon & heavy_armor:
			bonus += 0.33;
			break;
		case spear_weapon & light_armor:
			bonus += 0.43;
			break;
		case spear_weapon & heavy_armor:
			bonus += -0.06;
			break;
		}
		opponent->addhp(-1 * (damage * bonus));
		std::cout << "enemy took damage";
		enter = _getch();
	}
}

void enemyattack_process() {
	std::string clicker;

}

void movement_process(int choose) {
	float mobility = 1.25 * (1 - (armor_list[gameplayer.getidofarmor()]->getclassarmor() * 0.15));
	switch (choose) {
	case 8:
		gameplayer.adddistance(mobility * -1);
		gameplayer.sethavemoved("front");
		break;
	case 88:
		gameplayer.adddistance(mobility * -1.5);
		gameplayer.sethavemoved("front");
		break;
	case 2:
		gameplayer.adddistance(mobility);
		gameplayer.sethavemoved("back");
		break;
	case 22:
		gameplayer.adddistance(mobility * 1.5);
		gameplayer.sethavemoved("back");
		break;
	case 4:
		gameplayer.adddistance((sqrt(pow(mobility, 2)+ pow(gameplayer.getdistance(), 2)))/2);
		gameplayer.sethavemoved("left");
		break;
	case 44:
		gameplayer.adddistance((sqrt(pow(mobility * 1.5, 2) + pow(gameplayer.getdistance(), 2)))/2);
		gameplayer.sethavemoved("left");
		break;
	case 6:
		gameplayer.adddistance((sqrt(pow(mobility, 2) + pow(gameplayer.getdistance(), 2)))/2);
		gameplayer.sethavemoved("right");
		break;
	case 66:
		gameplayer.adddistance((sqrt(pow(mobility * 1.5, 2) + pow(gameplayer.getdistance(), 2)))/2);
		gameplayer.sethavemoved("right");
		break;
	default:
		std::cout << "you wrote wrong number bro";
		break;
	}
	if (gameplayer.getdistance() < 0.25) {
		gameplayer.setdistance(0.25);
	}
}


