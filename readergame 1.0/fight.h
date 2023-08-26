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

int randomnumber(int limit) {
	std::random_device numgenerator;
	std::uniform_int_distribution<size_t> gen(0, limit);
	return gen(numgenerator);
}

size_t enemyname_generator() { // int makes exception error
	std::random_device numgenerator;
	std::uniform_int_distribution<size_t> enemyname_gen(1, Enemynames_list.size() - 1);
	int enemyname = enemyname_gen(numgenerator);
	return enemyname;
}

int enemylvl_generator() {
	std::random_device generator;
	std::uniform_int_distribution<int> genlvl(1, gameplayer.getlvl() + (1 + gameplayer.getlvl() * 0.30));
	int lvl = genlvl(generator);
	return lvl;
}

int equipment_seed(int limit) { //seed for each equipment for enemy
	std::random_device numgenerator;
	std::uniform_int_distribution<int> equp_seed(0, limit);
	int chosennumber = equp_seed(numgenerator);

	return chosennumber;
}



std::string weapon_randomizer(int lvl) { //weapon seed limit maker
	int category = equipment_seed(2);
	int limit = 0;
	int count = 0;
	while (count < weapon_list[category].size()) {
		if (weapon_list[category][count]->getlvlreq() > lvl) {
			limit = count - 1;
			break;
		}
		count++;
	}

	return std::to_string(category) + std::to_string(equipment_seed(limit));
}

std::string armor_randomizer(int lvl, int helm) { //breastplate/helm seed limit maker
	int limit = 0;

	while (limit < armor_list[helm].size()) {
		if (armor_list[helm][limit]->getlvlreq() > lvl) {
			limit--;
			break;
		}
		limit++;
	}

	return std::to_string(helm) + std::to_string(equipment_seed(limit));
}

std::string item_randomizer(int lvl) { //item seed limit maker
	int limit = 0;
	int count = 0;
	while (count < item_list.size()) {
		if (item_list[count]->getlvlreq() > lvl) {
			limit = count - 1;
			break;
		}
		count++;
	}

	return std::to_string(equipment_seed(limit));
}

enemy* enemy_creator() {
	std::random_device generator;
	std::uniform_int_distribution<int> seed(1, 15); //stats seeds
	std::uniform_int_distribution<int> seed2(1, 10);
	int statseed1 = seed(generator);
	int statseed2 = seed2(generator);
	int seedlvl = enemylvl_generator();
	std::string name = Enemynames_list[enemyname_generator()];
	int atk = ((seedlvl - 1) * 2) * 6 + (0.3 * statseed2);
	int hp = 33 + seedlvl * 7 + (0.6 * statseed1);
	int ptval = (seedlvl * 0.75) * 36 + (statseed2 + statseed1);
	int ggolval = seedlvl * 6 + (statseed2 + statseed1);
	std::string idwep = weapon_randomizer(seedlvl);
	std::string idarm = armor_randomizer(seedlvl, 0);
	std::string idhem = armor_randomizer(seedlvl, 1);


	std::string iditem = "0";
	if (gameplayer.getlvl() > 2) {
		std::string iditem = item_randomizer(seedlvl);
	}
	return new enemy(name, seedlvl, atk, hp, ptval, ggolval, idwep, idarm, idhem, iditem); //new enemy pointer
}

void enemybackpack_creator(enemy * opponent) {
	int numberofcons = 0;
	int limit1 = 1;
	int limit2 = 3;
	std::random_device generator;
	std::uniform_int_distribution<int> seed(limit1, limit2);
	int seedofbackpack = seed(generator);
	if (gameplayer.getlvl() > 1) {
		numberofcons = seedofbackpack * (gameplayer.getlvl() / 2) * 0.25;
	}
	limit1 = 0;
	limit2 = 2;
	int tierseed;
	int typeseed;
	int cons;
	for (int count = 0; count < numberofcons; count++) {
		typeseed = seed(generator);
		tierseed = seed(generator);
		if (gameplayer.getlvl() < 10 && tierseed == 3) { tierseed--; }
		if (gameplayer.getlvl() < 5 && tierseed != 1 ) { tierseed--; }
		cons = tierseed + (typeseed * 10);
		opponent->addtobackpack(cons, true);
	}
}

//-------------------------------------fight functions---------------------------------------------------------------

void bar_writer(enemy* opponent, int round) {
	int hpcount = 0;
	std::cout << "===================			" << opponent->getname() << "				===================";
	std::cout << "\n\nHP: ";
	while (hpcount < opponent->gethp()) {
		std::cout << "/";
		hpcount++;
		if (hpcount % 100 == 0) {
			std::cout << "\n";
		}
	} // makes slashes look like hp bar
	hpcount = 0;
	std::cout << "\n\n\n\n";
	std::cout << "YOU\nHP: ";
	while (hpcount < gameplayer.gethp()) {
		std::cout << "/";
		hpcount++;
		if (hpcount % 100 == 0) {
			std::cout << "\n";
		}
	}
	hpcount = 0;
	std::cout << "\nSTAMINA: ";
	while (hpcount < gameplayer.gettiredness()) {
		std::cout << "/";
		hpcount++;
		if (hpcount % 100 == 0) {
			std::cout << "\n";
		}
	}
	std::cout << "\n";
	if (gameplayer.getalleffects_size() > 0) {
		gameplayer.getalleffects(round);
	}
}

void refresh(livingentity* guy, livingentity* foe) {
	foe->checktirednessstatus();
	foe->checkhpstatus();
	guy->checktirednessstatus();
	guy->checkhpstatus();
}
bool conditionchecker(livingentity* user, livingentity* victim, std::string goal) { //looks up required conditions of special item and activates them when fullfilled
	if (item_list[user->getidofitem()]->getcategory() == goal) {
		if (item_list[user->getidofitem()]->condition(user, victim) == true) {
			item_list[user->getidofitem()]->magicpower(user, victim);
			return true;
		}
	}
	return false;
}

bool attackprocess(livingentity* user, livingentity* victim, int attacktype) {
	weapon* userwep = weapon_list[user->getidofwep(1)][user->getidofwep(2)];
	armor* victimarmor = armor_list[victim->getidofarmor(1)][victim->getidofarmor(2)];
	armor* victimhelm = armor_list[victim->getidofhelm(1)][victim->getidofhelm(2)];

	std::string enter;
	int atk = user->getatk();
	if (victimarmor != 0) { atk = user->getatk() * 0.5; }
	int damage = atk + userwep->getdirectionattack(attacktype);
	int reduction = (victimarmor->gethardness() + victimhelm->gethardness());
	float bonus = 1;
	if (user->getdistance() > user->getrange() + userwep->getrange()) {
		user->setstatus("missed");
		user->sethaveattacked("missed");
		user->addtiredness(-1 * ((userwep->getdirectiontiring(attacktype) * 1.5) * armor_list[user->getidofarmor(1)][user->getidofarmor(2)]->getclassarmor())-1);
		return false;
	}
	else {
		if (userwep->getclassweapon() == mace_weapon && victimarmor->getclassarmor() == heavy_armor) { bonus += 0.10; }
		else if (userwep->getclassweapon() == spear_weapon && victimarmor->getclassarmor() == light_armor) { bonus += 0.15; }
		else if (userwep->getclassweapon() == spear_weapon && victimarmor->getclassarmor() == heavy_armor) { bonus -= 0.20; }
		int attack = bonus * (damage - 3 * sqrt(reduction));
		if (attack <= 0) { attack = 1; }
		victim->addhp(-1 * attack);
		victim->setstatus("tookdamage");
		victim->checkhpstatus();
		victim->settookdamage(std::to_string(attack));
		user->setstatus("haveattacked");
		user->sethaveattacked(typetranslator(attacktype, 2));
		int tiring = userwep->getdirectiontiring(attacktype) * armor_list[user->getidofarmor(1)][user->getidofarmor(2)]->getclassarmor();
		if (tiring > user->gettiredness()) { tiring = user->gettiredness(); }
		user->addtiredness(tiring * -1);
		return true;
	}
	if (user->gettiredness() < 0) { user->settiredness(0); }
}

void queuechecker(livingentity* user, livingentity* victim, int round) {
	std::string enter;
	std::cout << "Thinking of move is damped by confusing desire\n";
	enter = _getch();
	int specificmove = user->getqueuevar(0, 2);
	int var;
	switch (user->getqueuevar(0, 1)) {
	case 1:
		conditionchecker(user, victim, "beforeattacking");
		attackprocess(user, victim, specificmove);
		user->setlastmove(10 + specificmove);
		std::cout << "enough to attack for no reason\n";
		enter = _getch();
		break;
	case 2:
		conditionchecker(user, victim, "beforeusing");
		if (user->getalleffects_size() != 0) {
			var = user->findinbackpack(specificmove);
			if(var != 0) {
				user->usebackpack_single(var, round);
				user->setlastmove(20 + specificmove);
				std::cout << "enough to waste equipment for no reason\n";
				enter = _getch();
			}
		}
		else {
			std::cout << "\enough choose to rest";
			user->rest_process();
			user->setlastmove(40 + specificmove);
		}
		break;     
	case 3:
		conditionchecker(user, victim, "beforemoving");
		if (user->movement_check(std::to_string(specificmove), false)) {
			user->movement_process(specificmove);
			victim->setdistance(user->getdistance());
			user->setlastmove(30 + specificmove);
			std::cout << "enough to move for no reason\n";
			enter = _getch();
		}
		break;
	case 4:
		conditionchecker(user, victim, "beforeresting");
		user->rest_process();
		gameplayer.setlastmove(40 + specificmove);
		std::cout << "enough to rest for no reason\n";
		enter = _getch();
		break;
	default:
		std::cerr << "\nerror type of move";
		break;
	}	
	user->removefromqueue();
}

void enemy_ai(enemy * opponent, equipmentinfo * eqinfo, int round) {
	std::string enter;
	int number = 2;
	int movement = 0;
	int preferedmove = 0;
	int use = 0;
	int prefereduse = 0;
	int rest = 0;
	int attack = 0;
	int prefsideatk1 = 0;
	int prefaboveatk2 = 0;
	int prefstabatk3 = 0;
	int preferedattack = 0;
	std::random_device generator;
	std::uniform_int_distribution<int> genlvl(1, 100);
	std::uniform_int_distribution<int> prefer(1, number);
	int gennumber;
	float distancecheck = opponent->getdistance() - (opponent->getrange() + weapon_list[eqinfo->e_weapon_category][eqinfo->e_weapon_index]->getrange());
	if (distancecheck > 0){
		if (distancecheck >= 0.5 && opponent->gethealthstatus() != "low") {
			movement = 45 + distancecheck / 0.40;
			preferedmove = runforward;
		}
		else {
			movement = 35;
			preferedmove = forward;
		}
	}
	else {
		if (opponent->gethealthstatus() != "low") {
			movement = 25;
			number = 3;
			gennumber = prefer(generator);
			switch (gennumber) {
			case 1:
				preferedmove = left;
				break;
			case 2:
				preferedmove = right;
				break;
			case 3:
				preferedmove = back;
				break;
			}
		}
		else {
			movement = 45;
			number = 3;
			gennumber = prefer(generator);
			switch (gennumber) {
			case 1:
				preferedmove = runleft;
				break;
			case 2:
				preferedmove = runright;
				break;
			case 3:
				preferedmove = runback;
				break;
			}

		}
	}
	if (false) {
		use = 15;
		prefereduse = brick;

		if (opponent->gettirednessstatus() == "low" && opponent->checkbackpack_for( energy_potion)) {
			prefereduse = energy_potion;
		}
		if (opponent->gethealthstatus() == "low" && opponent->checkbackpack_for(heal_potion)) {
			prefereduse = heal_potion;
		}
	}
	if (opponent->gettirednessstatus() != "high" && distancecheck >= 0) {
		rest = 33;
	}
	else { rest = 25; }

	number = 30;
	attack = 100 - movement + use + rest;
	gennumber = prefer(generator);
	switch (weapon_list[eqinfo->e_weapon_category][eqinfo->e_weapon_index]->getclassweapon()) {
	case sword_weapon:
		prefsideatk1 = 11;
		prefaboveatk2 = 12;
		prefstabatk3 = 7;
		break;
	case mace_weapon:
		prefsideatk1 = 13;
		prefaboveatk2 = 14;
		prefstabatk3 = 3;
		break;
	case spear_weapon:
		prefsideatk1 = 3;
		prefaboveatk2 = 5;
		prefstabatk3 = 22;
		break;
	}
	if (prefsideatk1 >= gennumber) { preferedattack = side_attack;}
	else if (prefsideatk1 + prefaboveatk2 >= gennumber) { preferedattack = above_attack; }
	else if (prefsideatk1 + prefaboveatk2 + prefstabatk3 >= gennumber) { preferedattack = stab_attack; }

	int generatedmove = genlvl(generator);
	if (movement >= generatedmove) {
		std::cout << "Enemy decided to move\n";
		enter = _getch();
		conditionchecker(opponent, gameplayer_ptr, "beforemoving");
		if (opponent->movement_check(std::to_string(preferedmove), false)) {
			opponent->movement_process(preferedmove);
			gameplayer.setdistance(opponent->getdistance());
		}
	}
	else if (movement + use >= generatedmove) {
		std::cout << "Enemy decided to use his backpack goods\n";
		enter = _getch();
		conditionchecker(opponent, gameplayer_ptr, "beforeusing");
		opponent->usebackpack_single(opponent->findinbackpack(prefereduse), round);
	}
	else if (movement + use + rest >= generatedmove) {
		std::cout << "Enemy decided to use this while to quickly regain his stamina\n";
		enter = _getch();
		conditionchecker(opponent, gameplayer_ptr, "beforeresting");
		opponent->rest_process();
	}
	else if (movement + use + rest + attack >= generatedmove) {
		std::cout << "Enemy decided to attack\n";
		enter = _getch();
		conditionchecker(opponent, gameplayer_ptr, "beforeattacking");
		if (opponent->gettiredness() > 3) {
			if (attackprocess(opponent, gameplayer_ptr, preferedattack)) {
				std::cout << "You took damage";
				enter = _getch();
			}
			else {
				std::cout << "His attack missed";
				enter = _getch();
			}
		}
		else
		{
			std::cout << "But he is too tired to attack\n";
			enter = _getch();
		}
	}
}


