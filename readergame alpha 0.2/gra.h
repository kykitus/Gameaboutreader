 #pragma once


void playercret() {
	void loadein();
	std::string enter;
	std::string name;
	std::string game;
	std::ifstream loadin("savefile.txt", std::ios::in);

	try {
		if (loadin.is_open() == true) {
			std::getline(loadin, game);
		}
		if (std::stoi(game) == 1) {
			std::cout << "my sources you have been playing this game before. Would you like to load your progress already?[y]";
			std::cin >> enter;
			if (enter == "y" || enter == "Y") {
				loadein();
			}
			else {
				std::cout << "then again";
				enter = _getch();
				enter = "again";
			}
			system("CLS");
		}
		else {
			enter = "again";
		}
	}
	catch (std::exception& l) {
		enter = "again";
	}
	loadin.close();
	if (enter == "again") {
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
}



void savein() {
	std::fstream savinr("savefile.txt", std::ios::in);
	std::ofstream bill;
	std::string game;
	std::getline(savinr, game, '\n');
	int count = 0;
	savinr.close();

	std::ofstream savins("savefile.txt", std::ios::trunc);
	if (savins.is_open()) {
		savins << "1" << "\n";
		savins << playere.getname() << "\n";
		savins << playere.getlvl() << "\n";
		savins << playere.getlvlpts() << "\n";
		savins << playere.getggol() << "\n";
		savins << playere.getidofwep() << "\n";
		savins << playere.getidofarmor() << "\n";
		savins << playere.getidofhelm() << "\n";
		savins << playere.getidofitem();
		savins.close();
		

		std::ofstream bill("bill.txt", std::ios::trunc);
		if (!bill.is_open()) {
			std::cerr << "open error\n";
		}
		while (count < wepon.size()) {
			if (wepon[count]->getisbought() == true) {
				bill << 1 << "\t" << count << "\n";
			}
			count++;
		}
		count = 0;
		while (count < armo.size()) {
			if (armo[count]->getisbought() == true) {
				bill << 2 << "\t" << count << "\n";
			}
			count++;
		}
		count = 0;
		while (count < hem.size()) {
			if (hem[count]->getisbought() == true) {
				bill << 3 << "\t" << count << "\n";
			}
			count++;
		}
		count = 0;
		while (count < itme.size()) {
			if (itme[count]->getisbought() == true) {
				bill << 4 << "\t" << count << "\n";
			}
			count++;
		}
		count = 0;
		bill.close();
		std::cout << "progress saved succesfully";
		game = _getch();
		system("CLS");
	}
	else {
		std::cerr <<  "eror, not enough wood my lord";
		std::exit(0);
	}
}
void loadein() {
	std::ifstream loadin("savefile.txt", std::ios::in);

	std::string game;
	std::string namee;
	std::string lvll;
	std::string lvllpts;
	std::string ggol;
	std::string iw;
	std::string ia;
	std::string ih;
	std::string ii;
	if (loadin.is_open() == true) {
		std::getline(loadin, game, '\n');
		std::getline(loadin, namee, '\n');
		std::getline(loadin, lvll, '\n');
		std::getline(loadin, lvllpts, '\n');
		std::getline(loadin, ggol, '\n');
		std::getline(loadin, iw, '\n');
		std::getline(loadin, ia, '\n');
		std::getline(loadin, ih, '\n');
		std::getline(loadin, ii, '\n');

		playere.playerload(namee, std::stoi(lvll), std::stoi(lvllpts), std::stoi(ggol), std::stoi(iw), std::stoi(ia), std::stoi(ih), std::stoi(ii));
		loadin.close();

		std::ifstream bill("bill.txt", std::ios::in);
		std::string typee;
		std::string idd;
		if (!bill.is_open()) {
			std::cerr << "open error\n";
		}
		if (bill.eof()) {
			std::cout << "no paintings";
		}
		else {
			while (!bill.eof() && bill.is_open() == true) {
				std::getline(bill, typee, '\t');
				std::getline(bill, idd, '\n');

				if (bill.eof()) {
					break;
				}

				int typed = std::stoi(typee);
				int id = std::stoi(idd);

				switch (typed) {
				case 1:
					wepon[id]->setisbought(1);
					wepon[id]->setprice(0);
					break;
				case 2:
					armo[id]->setisbought(1);
					armo[id]->setprice(0);
					break;
				case 3:
					hem[id]->setisbought(1);
					hem[id]->setprice(0);
					break;
				case 4:
					itme[id]->setisbought(1);
					itme[id]->setprice(0);
					break;
				default:
					break;
				}
			}
			bill.close();
			std::cout << "progress loaded succesfully";
			game = _getch();
		}
	}
	else {
		std::cerr << "no opening";
		std::exit(0);
	}
	
}
void savenload() {
	std::ifstream loadin;
	std::string enter;
	
	std::cout << "/////////////////////////////\n";
	std::cout << "    house of lone painter    \n";
	std::cout << "/////////////////////////////\n\n\n\n";
	std::cout << "[1] - save progress\n";
	std::cout << "[2] - load progress\n";
	std::cout << "[3] - exit\n";

	std::cin >> enter;
	try {
		switch (std::stoi(enter)) {
		case 1:
			system("CLS");
			savein();
			break;
		case 2:
			system("CLS");
			loadein();
			break;
		case 3:
			std::cout << "\nWait, would you like to support some wandering lone painter before leaving?\n";
			std::cin >> enter;
			if (enter == "y" || enter == "Y") {
				playere.addggol(-1);
				std::cout << "thanks";
			}
			else {
				std::cout << "( 0 _ 0 )";
			}
			enter = _getch();
			system("CLS");
			break;
		default:
			std::cout << "youstupid";
			enter = _getch();
			system("CLS");
			break;
		}
	}
	catch (std::exception& l) {
		std::cout << "youstupid";
		enter = _getch();
		system("CLS");
	}
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
		std::cerr << "no weapon.txt\n";
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
		std::cerr << "no armor.txt\n";
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
	std::string categoryy;
	std::string abilitydess;
	int start = 0;
	try {
		litem.open("litem.txt");
	}
	catch (std::exception& e) {
		std::cerr << "no litem.txt\n";
		std::exit(0);
	}
	
	while (!litem.eof()) {
		std::getline(litem, namee, '\t');
		std::getline(litem, pricee, '\t');
		std::getline(litem, lvlreqq, '\t');
		std::getline(litem, categoryy, '\t');
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
	std::cout << "[4] - painter\n";
	std::cout << "[5] - exit\n";
	
	/*
	std::cout << hem[3]->getname() << "\n";
	std::cout << hem[3]->getprice() << "\n";
	std::cout << hem[3]->getlvlreq() << "\n";
	std::cout << hem.size();*/
	
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
				system("CLS");
				savenload();
				continue;
			case 5:
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
