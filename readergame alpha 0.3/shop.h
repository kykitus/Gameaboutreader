#ifndef SH
#define SH


int weapondisplay(unsigned int weapon_type) { // function for all three types of weapon
	int count = 1;

	while (count < weapon_list.size()) {
		if (gameplayer.getlvl() < weapon_list[count]->getlvlreq() || weapon_list[count]->getclassweapon() != weapon_type) {
			count++;
			continue;
		}
		std::cout << "-[" << count << "]- " << weapon_list[count]->getname() << "\t| attack - " << weapon_list[count]->getvalueattack() << "\t | length - " << weapon_list[count]->getrange() << "m\t||| price: ";
		if (weapon_list[count]->getisbought() == 0) { std::cout << weapon_list[count]->getprice() << "\n"; }
		else {
			if (count == gameplayer.getidofwep()) { std::cout << "equipped\n"; }
			else {
				std::cout << "equip\n";
			}
		}
		count++;
	}
	return count;
}

int armordisplay(std::vector<armor*> armor_type) { //makes also a variable have number equal to number of items in list
	int numberofitems = 1;
	while (numberofitems < armor_type.size()) {
		if (gameplayer.getlvl() < armor_type[numberofitems]->getlvlreq()) {
			numberofitems++;
			continue;
		}
		std::cout << "-[" << numberofitems << "]- " << armor_type[numberofitems]->getname() << "\t| hardness - " << armor_type[numberofitems]->gethardness() << "\t| type - ";
		armor_type[numberofitems]->typetranslator(armor_type[numberofitems]->getclassarmor(), 3);
		std::cout << "\t||| price: ";
		if (armor_type[numberofitems]->getisbought() == 0) { std::cout << armor_type[numberofitems]->getprice() << "\n"; }
		else {
			if (numberofitems == gameplayer.getidofhelm() || numberofitems == gameplayer.getidofarmor()) { std::cout << "equipped\n"; }
			else {
				std::cout << "equip\n";
			}
		}

		numberofitems++;
	}
	return numberofitems;

}

void consumabledisplay(int choose) {
	int chosen = choose;
	int count = 0;
	std::string powername = consumable_list[chosen][count]->typetranslator(consumable_list[chosen][count]->gettypeofconsumable(), 4);
	if (chosen < consumable_list.size()) {
		while (count < consumable_list[chosen].size()) {
			if (gameplayer.getlvl() < consumable_list[chosen][count]->getlvlreq()) {
				count++;
				continue;
			}
			std::cout << "-[" << count + 1 << "]- " << consumable_list[chosen][count]->getname() << "\t|" << powername << " power - " << consumable_list[chosen][count]->consumable_use();
			std::cout << "\t||| price: ";
			std::cout << consumable_list[chosen][count]->getprice() << "\n";
			count++;
		}
		std::cout << "-[y]- to choose category again";
	}

}

void exceptionhandler(std::string enter, int shoptype) { //acts as non variable player response handler and as unq (unequip) function
	if (enter == "y" || enter == "Y") {
		system("CLS");
	}
	try {
		if (toupper(enter[0]) == 85 && toupper(enter[1]) == 78 && toupper(enter[2]) == 81) {
			switch (shoptype) {
			case 1:
				gameplayer.setidofwep(0);
				std::cout << "weapon unequipped";
				enter = _getch();
				system("CLS");
				break;

			case 2:
				if (enter == "unq1" || enter == "UNQ1") {
					gameplayer.setidofarmor(0);
					std::cout << "breastplate unequipped";
					enter = _getch();
					break;
				}
				else if (enter == "unq2" || enter == "UNQ2") {
					gameplayer.setidofhelm(0);
					std::cout << "headpiece unequipped";
					enter = _getch();
				}
				break;

			case 3:
				gameplayer.setidofitem(0);
				std::cout << "item unequipped";
				enter = _getch();
				break;

			default:
				std::cout << "how";
				enter = _getch();
				break;
			}
		}
		else if(enter != "y" && enter != "Y") {
			std::cout << "youstupid";
			enter = _getch();
		}
    }
	catch(std::exception& l) {
		std::cout << "youstupid";
		enter = _getch();
	}
	system("CLS");
}

void weapon_shop() {
	std::string choose;
	std::string enter;
	int available_weapons = 0; // number of equipable weapons

	std::cout << "\n\n		SHOP OF WEAPONS\n\n";
	std::cout << "\n//////////////////////////\n SWORD \n//////////////////////////\n";
	available_weapons += weapondisplay(1);
	std::cout << "\n//////////////////////////\n MACE \n//////////////////////////\n";
	available_weapons += weapondisplay(2);
	std::cout << "\n//////////////////////////\n SPEAR \n//////////////////////////\n";
	available_weapons += weapondisplay(3);
	std::cout << "\n- ggols:" << gameplayer.getggol() << "\n	write number of option to buy it ('unq' will unequip your weapon)\n\n	exit[y]";

	while (true) { // whole interaction process
		std::cin >> choose;
		try {
			int chose = std::stoi(choose);
			if (chose < 0 || chose - 1 >= available_weapons || weapon_list[chose - 1]->getlvlreq() > gameplayer.getlvl()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			if (weapon_list[chose]->getprice() > gameplayer.getggol()) {
				std::cout << "you have not enough money";
				continue;
			}
			std::cout << "are you sure?\nYES[y]\tNO[n]\n";
			std::cin >> enter;
			if (enter == "y" || enter == "Y") {
				if (gameplayer.getidofwep() == chose) {
					std::cout << "you already have it";
					enter = _getch();
					continue;
				}
				gameplayer.addggol(weapon_list[chose]->getprice() * -1);
				gameplayer.setidofwep(chose);
				weapon_list[chose]->setisbought(1);
				weapon_list[chose]->setprice(0); // you need to save to keep item after closing game
				std::cout << "thanks\n";
				enter = _getch();
				system("CLS");
				break;
			}
			else if (enter == "n" || enter == "N") {
				std::cout << "ok";
				enter = _getch();
				system("CLS");
				break;
			}
		}
		catch(std::exception& d) {
			exceptionhandler(choose, 1);
			break;
		}
	}
}

void armor_shop() {
	std::string choose;
	std::string choose2;
	std::string enter;
	std::vector<armor*> armorr;
	int numberofarmors = 0;
	int numberofhelms = 0;
	int count = 0;

	std::cout << "\n\n		SHOP OF ARMORS\n\n";
	std::cout << "\n//////////////////////////\n  BREASTPLATE [1] \n//////////////////////////\n";
	numberofarmors = armordisplay(armor_list);
	std::cout << "\n//////////////////////////\n  HEADPIECE [2] \n//////////////////////////\n";
	numberofhelms = armordisplay(helm_list);
	std::cout << "\n- ggols:" << gameplayer.getggol() << "\n	write number of type of armor and press space, then number of option to buy it ('unq1' will unequip your breastplate and 'unq2' unequip headpiece)\n\n	exit[y]";
	
	
	// whole interaction process for both breastplate and helm, so it needs double number of checkers
	while (true) {
		std::cin >> choose2;
		try {
			int categoryofarmor  = std::stoi(choose2);
			std::cin >> choose;
			int choosenid = std::stoi(choose);

			if (categoryofarmor == 1) {
				count = numberofarmors;
				armorr = armor_list;
			}
			else if (categoryofarmor == 2) {
				count = numberofhelms;
				armorr = helm_list;
			}
			else {
				std::cout << "so you want something more than armor and helm? Do mod or buy dlc if I will do one. :)\n";
				enter = _getch();
				continue;
			}
			if (choosenid <= 0 || choosenid > count || armorr[choosenid]->getlvlreq() > gameplayer.getlvl()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			if (armorr[choosenid]->getprice() > gameplayer.getggol()) {
				std::cout << "you have not enough money";
				continue;
			}
			std::cout << "are you sure?\nYES[y]\tNO[n]\n";
			std::cin >> enter;
			if (enter == "y" || enter == "Y") {
				if (gameplayer.getidofarmor() == choosenid && categoryofarmor == 1) {
					std::cout << "you already have it";
					enter = _getch();
					continue;
				}
				if (gameplayer.getidofhelm() == choosenid && categoryofarmor == 2) {
					std::cout << "you already have it";
					enter = _getch();
					continue;
				}
				gameplayer.addggol(armorr[choosenid]->getprice() * -1);
				if (count == numberofarmors) {
					gameplayer.setidofarmor(choosenid);
				}
				else if (count == numberofhelms) {
					gameplayer.setidofhelm(choosenid);
				}
				armorr[choosenid]->setisbought(1);
				armorr[choosenid]->setprice(0); // you need to save to keep item after closing game
				std::cout << "thanks\n";
				enter = _getch();
				system("CLS");
				break;
			}
			else if (enter == "n" || enter == "N") {
				std::cout << "ok";
				enter = _getch();
				system("CLS");
				break;
			}
		}
		
		catch (std::exception& l) {
			exceptionhandler(choose2, 2);
			break;
		}
	}
}


void litem_shop() {
	std::string choose;
	std::string enter;
	int count = 1;
	std::cout << "\n\n		SHOP OF ITEMS\n\n";
	std::cout << "\n//////////////////////////\n LUCKY ITEMS \n//////////////////////////\n";
	while (count < item_list.size()) {
		if (gameplayer.getlvl() < item_list[count]->getlvlreq()) {
			count++;
			continue;
		}
		std::cout << "-[" << count << "]- " << item_list[count]->getname() << "\t||| price: ";
		if (item_list[count]->getisbought() == 0) { std::cout << item_list[count]->getprice() << "\n"; }
		else {
			if (count == gameplayer.getidofitem()) { std::cout << "equipped\n"; }
			else {
				std::cout << "equip\n";
			}
		}
		count++;
	}


	std::cout << "\n- ggols:" << gameplayer.getggol() << "\n	write number of option to buy it ('unq' will unequip your  lucky item)\n\n	exit[y]";

	// whole interaction process
	while (true) {
		std::cin >> choose;
		try {
			int choosenid = std::stoi(choose);
			if (choosenid < 0 || choosenid - 1 >= count || item_list[choosenid - 1]->getlvlreq() > gameplayer.getlvl()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			if (item_list[choosenid]->getprice() > gameplayer.getggol()) {
				std::cout << "you have not enough money";
				continue;
			}
			std::cout << "description:" << item_list[choosenid]->getabilitydes();
			std::cout << "\nare you sure?\nYES[y]\tNO[n]\n";
			std::cin >> enter;
			if (enter == "y" || enter == "Y") {
				if (gameplayer.getidofitem() == choosenid) {
					std::cout << "you already have it";
					enter = _getch();
					system("CLS");
					break;
				}
				gameplayer.addggol(item_list[choosenid]->getprice() * -1);
				gameplayer.setidofitem(choosenid);
				item_list[choosenid]->setisbought(1);
				item_list[choosenid]->setprice(0); // you need to save to keep item after closing game
				std::cout << "thanks\n";
				enter = _getch();
				system("CLS");
				break;
			}
			else if (enter == "n" || enter == "N") {
				std::cout << "ok";
				enter = _getch();
				system("CLS");
				break;
			}
		}
		catch (std::exception& d) {
			exceptionhandler(choose, 3);
			break;
		}
	}
}

void consumable_shop() {
	std::string choose;
	std::string choose2;
	std::string enter;
	std::cout << "\n//////////////////////////\n FUNNY EATABLES AND NON-EATABLES \n//////////////////////////";
	std::cout << "\n-[1]- potions of healing";
	std::cout << "\n-[2]- potions of energy";
	std::cout << "\n-[3]- things of resistance\n\n";
	std::cout << "\n- ggols:" << gameplayer.getggol() << "\nexit[y]\n";
	while (true) {
		std::cin >> choose2;
		try {
			int choosen2id = std::stoi(choose2) - 1;
			if (choosen2id < 0 || choosen2id  >= consumable_list.size()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			else {
				consumabledisplay(choosen2id);
			}
			std::cin >> choose;
			if (choose == "y" || choose == "Y") { // going back from chosen category
				continue;
			}
			int choosenid = std::stoi(choose) - 1; // choosenid is for backend while choose for backpack (technically frontend)
			if (consumable_list[choosen2id][choosenid]->getlvlreq() > gameplayer.getlvl()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			if (consumable_list[choosen2id][choosenid]->getprice() > gameplayer.getggol()) {
				std::cout << "you have not enough money";
				continue;
			}
			std::cout << "\nare you sure?\nYES[y]\tNO[n]\n";
			std::cin >> enter;
			if (enter == "y" || enter == "Y") {
				if (gameplayer.addtobackpack(std::stoi(choose2) * 10 + std::stoi(choose)) == true) { // example: 32 means 3 as type of potion and 2 as tier
					enter = _getch();
					system("CLS");
					break;
				}
				gameplayer.addggol(consumable_list[choosen2id][choosenid]->getprice() * -1);
				std::cout << "thanks\n";
				enter = _getch();
				system("CLS");
				break;
			}
			else if (enter == "n" || enter == "N") {
				std::cout << "ok";
				enter = _getch();
				system("CLS");
				break;
			}
		}
		catch (std::exception& d) {
			exceptionhandler(choose, 4);
			break;
		}
	}

}
#endif
