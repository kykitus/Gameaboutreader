#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

#include "pl.h"


#include "shop.h"





void shop() {
	void menu();
	while (true) {
		std::cout << "\n	_____________________________";
		std::cout << "\n	+            Shop           +";
		std::cout << "\n	_____________________________\n\n";
		std::cout << "[1] - weapon\n";
		std::cout << "[2] - armor\n";
		std::cout << "[3] - items\n";
		std::cout << "[4] - exit\n";




		std::string d;
		std::string enter;
		std::cin >> d;
		try {
			switch (std::stoi(d)) {
			case 1:
				system("CLS");
				wapon();
				break;
			case 2:
				system("CLS");
				amor();
				break;
			case 3:
				system("CLS");
				sitem();
				break;
			case 4:
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
		if (d == "4") {
			break;
		}
	}
}