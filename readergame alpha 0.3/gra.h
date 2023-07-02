
#pragma once


void playercret() {
	void loadprogress();
	std::string enter; // both for choosing and being "new filegame" value
	std::string name;
	std::string was_saved;
	std::ifstream progress_checker("savefile.txt", std::ios::in);

	try {
		if (progress_checker.is_open() == true) {
			std::getline(progress_checker, was_saved); // if file won't open, then filegame will act as first time opened
		}
		if (std::stoi(was_saved) == 1) {
			std::cout << "my sources you have been playing this game before. Would you like to load your progress already?[y]";
			std::cin >> enter;
			if (enter == "y" || enter == "Y") {
				loadprogress();
			}
			else {
				std::cout << "then again";
				enter = _getch(); 
				enter = "again"; //filegame start acting as new until next opening and seeing still existing file
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

	progress_checker.close();

	if (enter == "again") {
		std::cout << "\n	Enter name: ";
		std::cin >> name;

		if (name != "") {
			gameplayer.setname(name);
		}

		system("CLS");
		std::cout << "\n STORY TIME: " << name << ", you stupid. You are the most useless thing in the earth.";
		std::cout << "\n              Even local hobo gave you 20 ggols after seeing your face. You got 30 ggols. Profit :)\n\nDo you accept your fate? - [y] ";
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



void saveprogress() {
	std::ofstream bill;
	std::string game;
	int count = 0; //incrementing value for checking lists if there are bought items

	std::ofstream save_process("savefile.txt", std::ios::trunc);
	if (save_process.is_open()) {
		save_process << "1" << "\n";
		save_process << gameplayer.getname() << "\n";
		save_process << gameplayer.getlvl() << "\n";
		save_process << gameplayer.getlvlpts() << "\n";
		save_process << gameplayer.getggol() << "\n";
		save_process << gameplayer.getidofwep() << "\n";
		save_process << gameplayer.getidofarmor() << "\n";
		save_process << gameplayer.getidofhelm() << "\n";
		save_process << gameplayer.getidofitem();
		save_process.close();
		

		std::ofstream bill("bill.txt", std::ios::trunc);
		if (!bill.is_open()) {
			std::cerr << "open error\n";
		}

		while (count < weapon_list.size()) {
			if (weapon_list[count]->getisbought() == true) {
				bill << 1 << "\t" << count << "\n";
			}
			count++;
		}
		count = 0;
		while (count < armor_list.size()) {
			if (armor_list[count]->getisbought() == true) {
				bill << 2 << "\t" << count << "\n";
			}
			count++;
		}
		count = 0;
		while (count < helm_list.size()) {
			if (helm_list[count]->getisbought() == true) {
				bill << 3 << "\t" << count << "\n";
			}
			count++;
		}
		count = 0;
		while (count < item_list.size()) {
			if (item_list[count]->getisbought() == true) {
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
		std::cerr <<  "error while saving";
		std::exit(0);
	}
}
void loadprogress() {
	std::ifstream load_process("savefile.txt", std::ios::in);

	std::string filegame;
	std::string filename;
	std::string filelvl;
	std::string filelvlpts;
	std::string fileggols;
	std::string fileidweapon;
	std::string fileidarmor;
	std::string fileidhelm;
	std::string fileiditem;
	if (load_process.is_open() == true) {
		std::getline(load_process, filegame, '\n');
		std::getline(load_process, filename, '\n');
		std::getline(load_process, filelvl, '\n');
		std::getline(load_process, filelvlpts, '\n');
		std::getline(load_process, fileggols, '\n');
		std::getline(load_process, fileidweapon, '\n');
		std::getline(load_process, fileidarmor, '\n');
		std::getline(load_process, fileidhelm, '\n');
		std::getline(load_process, fileiditem, '\n');

		gameplayer.playerload(filename, std::stoi(filelvl), std::stoi(filelvlpts), std::stoi(fileggols), std::stoi(fileidweapon), std::stoi(fileidarmor), std::stoi(fileidhelm), std::stoi(fileiditem));
		load_process.close();

		std::ifstream bill("bill.txt", std::ios::in);
		std::string itemcategory;
		std::string itemid;
		if (!bill.is_open()) {
			std::cerr << "open error\n";
		}
		if (bill.eof()) {
			std::cout << "no paintings";
		}
		else {
			while (!bill.eof() && bill.is_open() == true) { // read saved items in bill.txt
				std::getline(bill, itemcategory, '\t');
				std::getline(bill, itemid, '\n');

				if (bill.eof()) {
					break;
				}

				int itemcat = std::stoi(itemcategory);
				int id = std::stoi(itemid);

				switch (itemcat) {
				case 1:
					weapon_list[id]->setisbought(1);
					weapon_list[id]->setprice(0);
					break;
				case 2:
					armor_list[id]->setisbought(1);
					armor_list[id]->setprice(0);
					break;
				case 3:
					helm_list[id]->setisbought(1);
					helm_list[id]->setprice(0);
					break;
				case 4:
					item_list[id]->setisbought(1);
					item_list[id]->setprice(0);
					break;
				default:
					break;
				}
			}
			bill.close();
			std::cout << "progress loaded succesfully";
			filegame = _getch();
		}
	}
	else {
		system("CLS");
		std::cout << "no savefile found";
		filegame = _getch();
	}
	
}
void save_load_option() {
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
			saveprogress();
			break;

		case 2:
			system("CLS");
			loadprogress();
			break;

		case 3:
			std::cout << "\nWait, would you like to support some wandering lone painter before leaving? [y]\n";
			std::cin >> enter;
			if (enter == "y" || enter == "Y") {
				gameplayer.addggol(-1);
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
	std::ifstream read_weapon;
	std::string readname;
	std::string readprice;
	std::string readattack;
	std::string readrange;
	std::string readlvlreq;
	std::string readclassofweapon;
	int start = 0; // first line
	try {
		read_weapon.open("weapon.txt");
	}
	catch (std::exception& e) {
		std::cerr << "no weapon.txt\n";
		std::exit(0);
	}

	while (!read_weapon.eof()) {
		std::getline(read_weapon, readname, '\t');
		std::getline(read_weapon, readattack, '\t');
		std::getline(read_weapon, readrange, '\t');
		std::getline(read_weapon, readprice, '\t');
		std::getline(read_weapon, readlvlreq, '\t');
		std::getline(read_weapon, readclassofweapon, '\n');

		if (start != 1) {
			start++;
			continue;
		}
		if (read_weapon.eof()) {
			break;
		}

		weapon_list.push_back(new weapon(readname, std::stoi(readattack), std::stof(readrange), std::stoi(readprice), std::stoi(readlvlreq), std::stoi(readclassofweapon)));
		
	}
}

void InitArmor()
{
	std::ifstream read_armor;
	std::string readname;
	std::string readprice;
	std::string readhardness;
	std::string readhelmchecker;
	std::string readlvlreq;
	std::string readclassofarmor;
	int start = 0; // first line
	try {
		read_armor.open("armor.txt");
	}
	catch (std::exception& e) {
		std::cerr << "no armor.txt\n";
		std::exit(0);
	}
	while (!read_armor.eof()) {
		std::getline(read_armor, readname, '\t');
		std::getline(read_armor, readhardness, '\t');
		std::getline(read_armor, readprice, '\t');
		std::getline(read_armor, readlvlreq, '\t');
		std::getline(read_armor, readhelmchecker, '\t');
		std::getline(read_armor, readclassofarmor, '\n');

		if (start != 1) {
			start++;
			continue;
		}
		if (read_armor.eof()) {
			break;
		}
		// breastplates and helms are in separate lists
		if (std::stoi(readhelmchecker) == 0) {
			armor_list.push_back(new armor(readname, std::stof(readhardness), std::stoi(readprice), std::stoi(readlvlreq), std::stoi(readhelmchecker), std::stoul(readclassofarmor)));
		
		}
		else if(std::stoi(readhelmchecker) == 1){
			helm_list.push_back(new armor(readname, std::stof(readhardness), std::stoi(readprice), std::stoi(readlvlreq), std::stoi(readhelmchecker), std::stoul(readclassofarmor)));
		
		}

	}
}

void InitLitem()
{
	std::ifstream read_item;
	std::string readname;
	std::string readprice;
	std::string readlvlreq;
	std::string readcategory;
	std::string readabilitydescription;
	int start = 0; // first line
	try {
		read_item.open("litem.txt");
	}
	catch (std::exception& e) {
		std::cerr << "no litem.txt\n";
		std::exit(0);
	}
	
	while (!read_item.eof()) {
		std::getline(read_item, readname, '\t');
		std::getline(read_item, readprice, '\t');
		std::getline(read_item, readlvlreq, '\t');
		std::getline(read_item, readcategory, '\t');
		std::getline(read_item, readabilitydescription, '\n');

		if (start != 1) {
			start++;
			continue;
		}
		if (read_item.eof()) {
			break;
		}

		item_list.push_back(new luckyitem(readname, std::stoi(readprice), std::stoi(readlvlreq), readcategory, readabilitydescription));

	}
}



void InitConsumables()
{
	consumable_list = {};
	consumable_list.push_back(heal_usable);
	consumable_list.push_back(energy_usable);
	consumable_list.push_back(resistance_usable);
	int current_vector = 0;
	std::ifstream read_consumable;
	std::string readname;
	std::string readpower;
	std::string readprice;
	std::string readlvlreq;
	std::string readtype;
	std::string readtier;
	int start = 0; // first line
	try {
		read_consumable.open("consumables.txt");
	}
	catch (std::exception& e) {
		std::cerr << "no consumables.txt\n";
		std::exit(0);
	}

	while (!read_consumable.eof()) {
		std::getline(read_consumable, readname, '\t');
		if (readname == "--") {
			read_consumable.ignore();
			current_vector++;
			continue;
		}
		std::getline(read_consumable, readpower, '\t');
		std::getline(read_consumable, readprice, '\t');
		std::getline(read_consumable, readlvlreq, '\t');
		std::getline(read_consumable, readtype, '\t');
		std::getline(read_consumable, readtier, '\n');

		if (start != 1) {
			start++;
			continue;
		}
		if (read_consumable.eof()) {
			break;
		}

		consumable_list[current_vector].push_back(new consumable(readname, std::stof(readpower), std::stoi(readprice), std::stoi(readlvlreq), std::stoi(readtype), std::stoi(readtier)));

	}
}


void menu() {
	void fight_option();
	void shop_option();
	void stats_option();
	while (true) {
	std::cout << "/////////////////////////////\n";
	std::cout << "          Gameabout:           \n";
	std::cout << "            Reader           \n";
	std::cout << "/////////////////////////////\n\n\n";
	std::cout << "[1] - fight\n";
	std::cout << "[2] - shop\n";
	std::cout << "[3] - stats\n";
	std::cout << "[4] - painter\n";
	std::cout << "[5] - exit\n";



	std::string enter;
	
		std::cin >> enter;
		try {
			switch (std::stoi(enter)) {
			case 1:
				system("CLS");
				fight_option();
				continue;
			case 2:
				system("CLS");
				shop_option();
				continue;
			case 3:
				system("CLS");
				stats_option();
				continue;
			case 4:
				system("CLS");
				save_load_option();
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


void stats_option() {
	inline void menu();
	std::string enter;
	gameplayer.checklvl(gameplayer.getlvl(), true);
	while (enter != "y" || enter != "Y") {
		std::cout << "\n	NAME: " << gameplayer.getname();
		std::cout << "\n	LVL: " << gameplayer.getlvl();
		std::cout << "\n	Points to new LVL: " << gameplayer.getlvlpts();
		std::cout << "\n	Ggolls: " << gameplayer.getggol();
		std::cout << "\n\n	 HP:" << gameplayer.gethp();
		std::cout << "\n	ATK:" << gameplayer.getatk();
		std::cout << "\n	STAMINA:" << gameplayer.gettiredness();
		std::cout << "\n	-[1]-WEAPON:" << weapon_list[gameplayer.getidofwep()]->getname();
		std::cout << "\n	-[2]-BREASTPLATE:" << armor_list[gameplayer.getidofarmor()]->getname();
		std::cout << "\n	-[3]-HEADPIECE:" << helm_list[gameplayer.getidofhelm()]->getname();
		std::cout << "\n	-[4]-LUCKY ITEM:" << item_list[gameplayer.getidofitem()]->getname();
		std::cout << "\n	-[5]-BACKPACK";
		std::cout << "\n\n [y] back\n\n";
		std::cin >> enter;
		if (enter == "y" || enter == "Y") {
			break;
		}
		try {
			switch (std::stoi(enter)) {
			case 1:         
				std::cout << "WEAPON: " << weapon_list[gameplayer.getidofwep()]->getname();
				std::cout << "\n-TYPE: " << weapon_list[gameplayer.getidofwep()]->typetranslator(armor_list[gameplayer.getidofarmor()]->getclassarmor(), 2);
				std::cout << "\n-SIDE ATTACK: " << weapon_list[gameplayer.getidofwep()]->getdirectionattack(side_attack);
				std::cout << "\n-ABOVE ATTACK: " << weapon_list[gameplayer.getidofwep()]->getdirectionattack(above_attack);
				std::cout << "\n-STAB ATTACK: " << weapon_list[gameplayer.getidofwep()]->getdirectionattack(stab_attack);
				std::cout << "\n-RANGE:" << weapon_list[gameplayer.getidofwep()]->getrange();
				std::cin >> enter;
				break;
			case 2:
				std::cout << "BREASTPLATE: " << armor_list[gameplayer.getidofarmor()]->getname();
				std::cout << "\n-HARDNESS: " << armor_list[gameplayer.getidofarmor()]->gethardness();
				std::cout << "\n-TYPE:" << armor_list[gameplayer.getidofarmor()]->typetranslator(armor_list[gameplayer.getidofarmor()]->getclassarmor(), 1);
				std::cin >> enter;
				break;
			case 3:
				std::cout << "HEADPIECE: " << helm_list[gameplayer.getidofhelm()]->getname();
				std::cout << "\n-HARDNESS: " << helm_list[gameplayer.getidofhelm()]->gethardness();
				std::cout << "\n-TYPE:" << helm_list[gameplayer.getidofhelm()]->typetranslator(helm_list[gameplayer.getidofhelm()]->getclassarmor(), 1);
				std::cin >> enter;
				break;
			case 4:
				std::cout << "LUCKY ITEM: " << item_list[gameplayer.getidofitem()]->getname();
				std::cout << "\n-CATEGORY: " << item_list[gameplayer.getidofitem()]->getcategory();
				std::cout << "\n-DESCRIPTION: " << item_list[gameplayer.getidofitem()]->getabilitydes();
				std::cin >> enter;
				break;
			case 5:
				std::cout << "BACKPACK:\n";
				gameplayer.getbackpack_whole();
				std::cin >> enter;
				break;
			default:
				std::cout << "youstupid";
				enter = _getch();
				break;
			}
		}
		catch (std::exception& l) {
			std::cout << "youstupid";
			enter = _getch();
		}
		system("CLS");
	}
	system("CLS");
	menu();
}

/*std::cout << weapon_list[13]->getsideattack() << "\n";
std::cout << weapon_list[13]->getaboveattack() << "\n";
std::cout << weapon_list[13]->getstabattack() << "\n";
std::cout << weapon_list.size();*/



/*/std::cout << consumable_list[0].size();
for (int i = 0; i < consumable_list[0].size(); i++) {
	std::cout << consumable_list[0][i]->getname() << "\n";
}
std::cout << consumable_list[1].size();
for (int i = 0; i < consumable_list[1].size(); i++) {
	std::cout << consumable_list[1][i]->getname() << "\n";
}
std::cout << consumable_list[2].size();
for (int i = 0; i < consumable_list[2].size(); i++) {
	std::cout << consumable_list[2][i]->getname() << "\n";
}*/
