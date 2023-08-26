#ifndef LITEM
#define LITEM

void luckyitem_powerinitializer() { // Yes, I took the easiest way
	item_list[0]->magicpower = [&](livingentity* user, livingentity* victim) {
		std::cout << "you don't have one";
	};
	item_list[0]->condition = [&](livingentity* user, livingentity* victim) {
		return false;
	};
	item_list[1]->magicpower = [&](livingentity* user, livingentity* victim) {
		std::string enter;
		std::random_device numgenerator;
		std::uniform_int_distribution<size_t> generator(1, 10);
		int chance = generator(numgenerator);
		if (chance == 10) {
			victim->addatk(-3 * victim->getlvl());
			std::cout << "\nAttacker got an splinter\n";
			enter = _getch();
		}
	};
	item_list[1]->condition = [&](livingentity* user, livingentity* victim) {
		if(user->getstatus() == "tookdamage")
		{
			return true;
		}
		else {
			return false;
		}
	};
	item_list[2]->magicpower = [&](livingentity* user, livingentity* victim) {
		std::string enter;
		user->addtiredness(floor(1.5 * (0.70 * armor_list[user->getidofarmor(1)][user->getidofarmor(2)]->getclassarmor()) * user->getendurance()));
		std::cout << "\nthanks to boots, that wasn't tiring\n";
		enter = _getch();
	};
	item_list[2]->condition = [&](livingentity* user, livingentity* victim) {
		if (user->getstatus() == "havemoved" && user->gethavemoved() == "forward")
		{
			return true;
		}
		else {
			return false;
		}
	};
	item_list[3]->magicpower = [&](livingentity* user, livingentity* victim) {
		std::string enter;
		victim->addhp(-1 * (3 * (1 + 0.33 * user->getlvl())));
		std::cout << "\nApproacher's sharp brick damaged his target\n";
		enter = _getch();
	};
	item_list[3]->condition = [&](livingentity* user, livingentity* victim) {
		if (user->getstatus() == "havemoved" && user->getdistance() <= 0.4)
		{
			return true;
		}
		else {
			return false;
		}
	};
	item_list[4]->magicpower = [&](livingentity* user, livingentity* victim) {
		user->movement_process(6);
	};
	item_list[4]->passivepower = [&](livingentity* user, livingentity* victim) {
		user->addmobility(0.25);
		user->addendurance(0.20);
	};
	item_list[4]->cancelpassive = [&](livingentity* user, livingentity* victim) {
		user->addmobility(-1 * 0.25);
		user->addendurance(-1 * 0.20);
	};
	item_list[4]->condition = [&](livingentity* user, livingentity* victim) {
		if (user->getstatus() == "haveattacked" && user->gethaveattacked() == "sideattack")
		{
			return true;
		}
		else {
			return false;
		}
	};
	item_list[5]->magicpower = [&](livingentity* user, livingentity* victim) {
		std::random_device numgenerator;
		std::uniform_int_distribution<size_t> generator(1, 100);
		int chance = generator(numgenerator);
		if (chance >= 15) {
			victim->addtoqueue(user->getlastmove());
		}
	};
	item_list[5]->condition = [&](livingentity* user, livingentity* victim) {
			return true;
	};
	item_list[6]->magicpower = [&](livingentity* user, livingentity* victim) {
		std::random_device numgenerator;
		std::uniform_int_distribution<size_t> generator(1, 4);
		int chance = generator(numgenerator) * 2;
		user->movement_process(chance);
	};
	item_list[6]->condition = [&](livingentity* user, livingentity* victim) {
		if (user->getnumberofused() > 2)
		{
			return true;
		}
		else {
			return false;
		}
	};
}

#endif
