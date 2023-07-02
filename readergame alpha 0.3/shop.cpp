#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

#include "pl.h"


#include "shop.h"





void shop_option() {
	void menu();
	while (true) {
		std::cout << "_____________________________";
		std::cout << "\n+            Shop           +";
		std::cout << "\n_____________________________\n\n\n\n";
		std::cout << "[1] - weapon\n";
		std::cout << "[2] - armor\n";
		std::cout << "[3] - items\n";
		std::cout << "[4] - miscellaneous\n";
		std::cout << "[5] - exit\n";



		std::string enter;
		std::cin >> enter;
		try {
			switch (std::stoi(enter)) {
			case 1:
				system("CLS");
				weapon_shop();
				break;
			case 2:
				system("CLS");
				armor_shop();
				break;
			case 3:
				system("CLS");
				litem_shop();
				break;
			case 4:
				system("CLS");
				consumable_shop();
				break;
			case 5:
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
		if (enter == "5") {
			break;
		}
	}
}