#ifndef SH
#define SH
int d = 1;
int y = 1;
void weapondisplay(unsigned int weapontype) {
	int g = 1;
	

	while (g < wepon.size()) {
		if (playere.getlvl() < wepon[g]->getlvlreq() || wepon[g]->getclassweapon() != weapontype) {
			g++;
			continue;
		}
		std::cout << "-[" << d << "]- " << wepon[g]->getname() << "\t| attack - " << wepon[g]->getattack() << "\t | length - " << wepon[g]->getrange() << "m\t||| price: ";
		if (wepon[g]->getisbought() == 0) { std::cout << wepon[g]->getprice() << "\n"; }
		else {
			if (g == playere.getidofwep()) { std::cout << "equipped\n"; }
			else {
				std::cout << "equip\n";
			}
		}
		g++;
		d++;
	}
}

int armordisplay(std::vector<armor*> aror, int u) {
	int g = 1;
	while (g < aror.size()) {
		if (playere.getlvl() < aror[g]->getlvlreq()) {
			g++;
			continue;
		}
		std::cout << "-[" << u << "]- " << aror[g]->getname() << "\t| hardness - " << aror[g]->gethardness() << "\t| type - ";
		switch (aror[g]->getclassarmor()) {
		case 1:
			std::cout << "light";
			break;
		case 2:
			std::cout << "medium";
			break;
		case 3:
			std::cout << "heavy";
			break;
		default:
			std::cout << "how do you see it";
			break;
		}
		std::cout << "\t||| price: ";
		if (aror[g]->getisbought() == 0) { std::cout << aror[g]->getprice() << "\n"; }
		else {
			if (g == playere.getidofhelm() || g == playere.getidofarmor()) { std::cout << "equipped\n"; }
			else {
				std::cout << "equip\n";
			}
		}
		g++;
		u++;
	}
	return u;

}

void excepthandler(std::string chose, int typeshop) {
	if (chose == "y" || chose == "Y") {
		system("CLS");
	}
	try {
		if (toupper(chose[0]) == 85 && toupper(chose[1]) == 78 && toupper(chose[2]) == 81) {
			switch (typeshop) {
			case 1:
				playere.setidofwep(0);
				std::cout << "weapon unequipped";
				chose = _getch();
				system("CLS");
				break;

			case 2:
				if (chose == "unq1" || chose == "UNQ1") {
					playere.setidofarmor(0);
					std::cout << "breastplate unequipped";
					chose = _getch();
					break;
				}
				else if (chose == "unq2" || chose == "UNQ2") {
					playere.setidofhelm(0);
					std::cout << "headpiece unequipped";
					chose = _getch();
				}
				break;

			case 3:
				playere.setidofitem(0);
				std::cout << "item unequipped";
				chose = _getch();
				break;

			default:
				std::cout << "how";
				chose = _getch();
				break;
			}
		}
		else if(chose != "y" && chose != "Y") {
			std::cout << "youstupid";
			chose = _getch();
		}
    }
	catch(std::exception& l) {
		std::cout << "youstupid";
		chose = _getch();
	}
	system("CLS");
}

void wapon() {
	void shop();
	std::string choose;
	std::string agreement;
	std::string enter;


	std::cout << "\n\n		SHOP OF WEAPONS\n\n";
	std::cout << "\n//////////////////////////\n SWORD \n//////////////////////////\n";
	weapondisplay(1);
	std::cout << "\n//////////////////////////\n MACE \n//////////////////////////\n";
	weapondisplay(2);
	std::cout << "\n//////////////////////////\n SPEAR \n//////////////////////////\n";
	weapondisplay(3);
	std::cout << "\n- ggols:" << playere.getggol() << "\n	write number of option to buy it ('unq' will unequip your weapon)\n\n	exit[y]";

	while (true) {
		std::cin >> choose;
		try {
			int chose = std::stoi(choose);
			if (chose < 0 || chose - 1 >= d || wepon[chose - 1]->getlvlreq() > playere.getlvl()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			if (wepon[chose]->getprice() > playere.getggol()) {
				std::cout << "you have not enough money";
				continue;
			}
			std::cout << "are you sure?\nYES[y]\tNO[anything]\n";
			std::cin >> agreement;
			if (agreement == "y" || agreement == "Y") {
				if (playere.getidofwep() == chose) {
					std::cout << "you already have it";
					enter = _getch();
					continue;
				}
				playere.addggol(wepon[chose]->getprice() * -1);
				playere.setidofwep(chose);
				wepon[chose]->setisbought(1);
				wepon[chose]->setprice(0);
				std::cout << "thanks\n";
				enter = _getch();
				system("CLS");
				break;
			}
			else if (agreement == "n" || agreement == "N") {
				std::cout << "ok";
				enter = _getch();
				system("CLS");
				break;
			}
		}
		catch(std::exception& d) {
			excepthandler(choose, 1);
			break;
		}
	}
	d = 1;
}

void amor() {
	void shop();
	std::string choose;
	std::string choose2;
	std::string agreement;
	std::string enter;
	std::vector<armor*> armorr;
	int count = 0;

	std::cout << "\n\n		SHOP OF ARMORS\n\n";
	std::cout << "\n//////////////////////////\n  BREASTPLATE [1] \n//////////////////////////\n";
	d = armordisplay(armo, d);
	std::cout << "\n//////////////////////////\n  HEADPIECE [2] \n//////////////////////////\n";
	y = armordisplay(hem, y);
	std::cout << "\n- ggols:" << playere.getggol() << "\n	write number of type of armor and then of option to buy it ('unq1' will unequip your breastplate and 'unq2' unequip headpiece)\n\n	exit[y]";
	
	
	
	while (true) {
		std::cin >> choose2;
		try {
			int catg  = std::stoi(choose2);
			std::cin >> choose;
			int chose = std::stoi(choose);

			if (catg == 1) {
				count = d;
				armorr = armo;
			}
			else if (catg == 2) {
				count = y;
				armorr = hem;
			}
			else {
				std::cout << "so you want something more than armor and helm? Do mod or buy dlc if I will do one. :)\n";
				enter = _getch();
				continue;
			}
			if (chose <= 0 || chose > count || armorr[chose]->getlvlreq() > playere.getlvl()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			if (armorr[chose]->getprice() > playere.getggol()) {
				std::cout << "you have not enough money";
				continue;
			}
			std::cout << "are you sure?\nYES[y]\tNO[anything]\n";
			std::cin >> agreement;
			if (agreement == "y" || agreement == "Y") {
				if (playere.getidofarmor() == chose && catg == 1) {
					std::cout << "you already have it";
					enter = _getch();
					continue;
				}
				if (playere.getidofhelm() == chose && catg == 2) {
					std::cout << "you already have it";
					enter = _getch();
					continue;
				}
				playere.addggol(armorr[chose]->getprice() * -1);
				if (count == d) {
					playere.setidofarmor(chose);
				}
				else if (count == y) {
					playere.setidofhelm(chose);
				}
				armorr[chose]->setisbought(1);
				armorr[chose]->setprice(0);
				std::cout << "thanks\n";
				enter = _getch();
				system("CLS");
				break;
			}
			else if (agreement == "n" || agreement == "N") {
				std::cout << "ok";
				enter = _getch();
				system("CLS");
				break;
			}
		}
		
		catch (std::exception& l) {
			excepthandler(choose2, 2);
			break;
		}
	}
	d = 1;
	y = 1;
}




void itemdisplay() {
	
}


void sitem() {
	void shop();
	std::string choose;
	std::string agreement;
	std::string enter;
	int g = 1;
	std::cout << "\n\n		SHOP OF ITEMS AND POTIONS\n\n";
	std::cout << "\n//////////////////////////\n FUNNY OBJECTS \n//////////////////////////\n";
	while (g < itme.size()) {
		if (playere.getlvl() < itme[g]->getlvlreq()) {
			g++;
			continue;
		}
		std::cout << "-[" << d << "]- " << itme[g]->getname() << "\t||| price: ";
		if (itme[g]->getisbought() == 0) { std::cout << itme[g]->getprice() << "\n"; }
		else {
			if (g == playere.getidofitem()) { std::cout << "equipped\n"; }
			else {
				std::cout << "equip\n";
			}
		}
		g++;
		d++;
	}


	std::cout << "\n- ggols:" << playere.getggol() << "\n	write number of option to buy it ('unq' will unequip your object)\n\n	exit[y]";


	while (true) {
		std::cin >> choose;
		try {
			int chose = std::stoi(choose);
			if (chose < 0 || chose - 1 >= d || itme[chose - 1]->getlvlreq() > playere.getlvl()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			if (itme[chose]->getprice() > playere.getggol()) {
				std::cout << "you have not enough money";
				continue;
			}
			std::cout << "description:" << itme[chose]->getabilitydes();
			std::cout << "\nare you sure?\nYES[y]\tNO[anything]\n";
			std::cin >> agreement;
			if (agreement == "y" || agreement == "Y") {
				if (playere.getidofitem() == chose) {
					std::cout << "you already have it";
					enter = _getch();
					system("CLS");
					break;
				}
				playere.addggol(itme[chose]->getprice() * -1);
				playere.setidofitem(chose);
				itme[chose]->setisbought(1);
				itme[chose]->setprice(0);
				std::cout << "thanks\n";
				enter = _getch();
				system("CLS");
				break;
			}
			else if (agreement == "n" || agreement == "N") {
				std::cout << "ok";
				enter = _getch();
				system("CLS");
				break;
			}
		}
		catch (std::exception& d) {
			excepthandler(choose, 3);
			break;
		}
	}
	d = 1;
}

#endif
