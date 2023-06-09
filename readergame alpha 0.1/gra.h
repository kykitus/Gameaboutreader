 #pragma once


void playercret() {
	std::string enter;
	std::string name;
	std::cout << "\n	Enter name: ";
	std::cin >> name;

	if (name != "") {
		playere.setname(name);
	}

	system("CLS");
	std::cout << "\n STORY TIME: " << name << ", you stupid. You are the most useless thing in the earth.";
	std::cout << "\n              Even local hobo gave you 30 ggols after seeing your face. You got 30 ggols. Profit :)\n\nDo you accept your fate? - [y] ";
	std::cin >> enter;
	if (enter == "y" || enter == "Y") {
		system("CLS");
	}
	else {
		std::cout << "you stupid";
		std::cin >> enter;
		system("CLS");
	}

}

// stats option

void stats() {
	inline void menu();
	std::string enter;
	std::cout << "\n	NAME: " << playere.getname();
	std::cout << "\n	LVL: " << playere.getlvl();
	std::cout << "\n	Points to new LVL: " << playere.getlvlpts();
	std::cout << "\n	Ggolls: " << playere.getggol();
	std::cout << "\n\n	 HP:" << playere.gethp();
	std::cout << "\n	ATK:" << playere.getatk();
	std::cout << "\n	WEAPON:" << wepon[playere.getidofwep()]->getname();
	std::cout << "\n	BREASTPLATE:" << armo[playere.getidofarmor()]->getname();
	std::cout << "\n	HEADPIECE:" << hem[playere.getidofhelm()]->getname();
	std::cout << "\n\n [anything] back\n";
	std::cin >> enter;
	system("CLS");
	menu();
}

void InitWeapons()
{
	std::ifstream weaponn;
	std::string namee;
	std::string pricee;
	std::string attackk;
	std::string range;
	std::string critt;
	std::string lvlreqq;
	std::string classwep;
	int start = 0;
	try {
		weaponn.open("weapon.txt");
	}
	catch (std::exception& e) {
		std::cout << "no weapon.txt\n";
		std::exit(0);
	}

	while (!weaponn.eof()) {
		std::getline(weaponn, namee, '\t');
		std::getline(weaponn, attackk, '\t');
		std::getline(weaponn, range, '\t');
		std::getline(weaponn, critt, '\t');
		std::getline(weaponn, pricee, '\t');
		std::getline(weaponn, lvlreqq, '\t');
		std::getline(weaponn, classwep, '\n');

		if (start != 1) {
			start++;
			continue;
		}
		if (weaponn.eof()) {
			break;
		}

		wepon.push_back(new weapon(namee, std::stoi(attackk), std::stof(range), std::stof(critt), std::stoi(pricee), std::stoi(lvlreqq), std::stoi(classwep)));
		
	}
}

void InitArmor()
{
	std::ifstream armorr;
	std::string namee;
	std::string pricee;
	std::string hardnesss;
	std::string isforheadd;
	std::string lvlreqq;
	std::string classarmor;
	int start = 0;
	try {
		armorr.open("armor.txt");
	}
	catch (std::exception& e) {
		std::cout << "no armor.txt\n";
		std::exit(0);
	}
	while (!armorr.eof()) {
		std::getline(armorr, namee, '\t');
		std::getline(armorr, hardnesss, '\t');
		std::getline(armorr, pricee, '\t');
		std::getline(armorr, lvlreqq, '\t');
		std::getline(armorr, isforheadd, '\t');
		std::getline(armorr, classarmor, '\n');

		if (start != 1) {
			start++;
			continue;
		}
		if (armorr.eof()) {
			break;
		}

		if (std::stoi(isforheadd) == 0) {
			armo.push_back(new armor(namee, std::stof(hardnesss), std::stoi(pricee), std::stoi(lvlreqq), std::stoi(isforheadd), std::stoul(classarmor)));
		}else if(std::stoi(isforheadd) == 1){
			hem.push_back(new armor(namee, std::stof(hardnesss), std::stoi(pricee), std::stoi(lvlreqq), std::stoi(isforheadd), std::stoul(classarmor)));
		}

	}
}

void InitLitem()
{
	std::ifstream litem;
	std::string namee;
	std::string pricee;
	std::string lvlreqq;
	std::string abilitydess;
	int start = 0;
	try {
		litem.open("litem.txt");
	}
	catch (std::exception& e) {
		std::cout << "no litem.txt\n";
		std::exit(0);
	}
	
	while (!litem.eof()) {
		std::getline(litem, namee, '\t');
		std::getline(litem, pricee, '\t');
		std::getline(litem, lvlreqq, '\t');
		std::getline(litem, abilitydess, '\n');

		if (start != 1) {
			start++;
			continue;
		}
		if (litem.eof()) {
			break;
		}

		itme.push_back(new funnyobject(namee, std::stoi(pricee), std::stoi(lvlreqq), abilitydess));


	}
}

void menu() {
	void faight();
	void shop();
	void stats();
	while (true) {
	std::cout << "/////////////////////////////\n";
	std::cout << "           the rpg           \n";
	std::cout << "/////////////////////////////\n\n\n";
	std::cout << "[1] - fight\n";
	std::cout << "[2] - shop\n";
	std::cout << "[3] - stats\n";
	std::cout << "[4] - exit\n";


	std::cout << hem[3]->getname() << "\n";
	std::cout << hem[3]->getprice() << "\n";
	std::cout << hem[3]->getlvlreq() << "\n";
	std::cout << hem.size();
	
	std::string c;
	std::string enter;
	
		std::cin >> c;
		try {
			switch (std::stoi(c)) {
			case 1:
				system("CLS");
				faight();
				continue;
			case 2:
				system("CLS");
				shop();
				continue;
			case 3:
				system("CLS");
				stats();
				continue;
			case 4:
				exit(1);
				break;
			default:
				std::cout << "youstupid";
				enter = _getch();
				system("CLS");
				continue;
			}
		}
		catch (std::exception& l) {
			std::cout << "youstupid";
			enter = _getch();
			system("CLS");
		}
	}
}



