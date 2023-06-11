#pragma once

std::vector<std::string> enames;

void Enemynames()
{
	std::ifstream inFile;
	try {
		inFile.open("enames.txt");
	}
	catch (std::exception& e) {                      
		std::cerr << "Exception opening/reading enames.txt\n";
		std::exit(0);
	}


	std::string ename;
	int start = 0;
	while (!inFile.eof()) {
		std::getline(inFile, ename, '\n');

		if (start != 1) {
			start++;
			continue;
		}

		if (inFile.eof()) {
			break;
		}

		enames.push_back(ename);

	}

}

int eqnumgen(int limit) {
	std::random_device genegenerator;
	std::uniform_int_distribution<int> eqseed(0, limit);
	int chosenum = eqseed(genegenerator);

	return chosenum;
}

size_t enamegetter() {
	std::random_device generator;
	std::uniform_int_distribution<size_t> enameg(1, enames.size() - 1);
	int ename = enameg(generator);
	return ename;
}


int weprand() {
	int limit = 0;
	int d = 0;
	while (d < wepon.size()) {
		if (wepon[d]->getlvlreq() > playere.getlvl()) {
			limit = d - 1;
			break;
		}
		d++;
	}

	return eqnumgen(limit);
}

int armrand(bool helm) {
	int limit = 0;
	std::vector<armor*> armorr;
	
	if (helm == true) { armorr = hem; }
	else if (helm == false) { armorr = armo; }

	while (limit < armorr.size()) {
		if (armorr[limit]->getlvlreq() > playere.getlvl()) {
			limit--;
			break;
		}
		limit++;
	}

	return eqnumgen(limit);
}

int itemrand() {
	int limit = 0;
	int d = 0;
	while (d < itme.size()) {
		if (itme[d]->getlvlreq() > playere.getlvl()) {
			limit = d - 1;
			break;
		}
		d++;
	}

	return eqnumgen(limit);
}

enemy * enenemy() {
	std::random_device generator;
	std::uniform_int_distribution<int> seed(1, 15);
	std::uniform_int_distribution<int> seed2(1, 10);
	std::uniform_int_distribution<int> seed3(1, 5);
	int stseed1 = seed(generator);
	int stseed2 = seed2(generator);
	int stseed3 = seed3(generator);

	std::string name = enames[enamegetter()];
	int atk = playere.getlvl() * 2 + (0.5 * stseed2);
	int hp = playere.getlvl() * 15 + (0.3 * stseed1);
	int ptval = playere.getlvl() * 20 + (2 * (stseed2 + stseed1) / 2);
	int idwep = weprand();
	int idarm = armrand(false);
	int idhem = armrand(true);

	int iditem = 0;
	if (playere.getlvl() > 2) {
		int iditem = itemrand();
	}
	return new enemy(name, atk, hp, ptval, idwep, idarm, idhem, iditem);
}

void attackprocess(enemy * oponent, int choose, int attacktype) {
	double bonus;
	std::string clicker;
	if (playere.getdistance() > playere.getrange() + wepon[playere.getidofwep()]->getrange()) {
		std::cout << "your attack missed";
		clicker = _getch();
	}
	else {
	}
}

void eattackprocess() {
	std::string clicker;

}


