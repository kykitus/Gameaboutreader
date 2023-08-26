#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <conio.h>
#include <fstream>
#include "pl.h"  


std::string typetranslator(int category, int typeofequipment) {
	std::string returnval;

	switch (typeofequipment) {
	case 1:
		switch (category) {
		case sword_weapon:
			returnval = "sword";
			break;
		case mace_weapon:
			returnval = "mace";
			break;
		case spear_weapon:
			returnval = "spear";
			break;
		}
		break;
	case 2:
		switch (category) {
		case side_attack:
			returnval = "side attack";
			break;
		case above_attack:
			returnval = "above attack";
			break;
		case stab_attack:
			returnval = "stab attack";
			break;
		}
		break;
	case 3:
		switch (category) {
		case light_armor:
			returnval = "light";
			break;
		case medium_armor:
			returnval = "medium";
			break;
		case heavy_armor:
			returnval = "heavy";
			break;
		}
		break;
	case 4:
		switch (category) {
		case heal_potion:
			returnval = "healing";
			break;
		case energy_potion:
			returnval = "energy";
			break;
		case brick:
			returnval = "resistance";
			break;
		}
		break;
	}
	return returnval;

}


////////////////////////////////////////


std::string item::getname() {
	return name;
}
void item::setname(std::string newname) {
	name = newname;
}
int item::getprice() {
	return price;
}
void item::setprice(int newprice) {
	price = newprice;
}
int item::getlvlreq() {
	return lvlreq;
}
void item::setlvlreq(int newlvlreq) {
	lvlreq = newlvlreq;
}
bool item::getisbought() {
	return isbought;
}
void item::setisbought(bool newisbought) {
	isbought = newisbought;
}


/////////////////////////////////////////////


int weapon::getvalueattack() {
	return valueattack;
}
void weapon::setvalueattack(int newattack) {
	valueattack = newattack;
}
int weapon::getdirectionattack(int attacktype) {
	switch (attacktype) {
	case side_attack:
		return sideattack;
		break;
	case above_attack:
		return aboveattack;
		break;
	case stab_attack:
		return stabattack;
		break;
	}
}
int weapon::getdirectiontiring(int attacktype) {
	switch (attacktype) {
	case side_attack:
		return sideattacktiring;
		break;
	case above_attack:
		return aboveattacktiring;
		break;
	case stab_attack:
		return stabattacktiring;
		break;
	}
}
void weapon::setdirectionattack(int newattack, int weapontype) {
	switch (weapontype) {
	case sword_weapon:
		sideattack = newattack;
		sideattacktiring = 1;
		aboveattack = 1.10 * newattack;
		aboveattacktiring = 1.5;
		stabattack = 1.15 * newattack;
		stabattacktiring = 1.5;
		break;
	case mace_weapon:
		sideattack = newattack;
		sideattacktiring = 1.5;
		aboveattack = 1.20 * newattack;
		aboveattacktiring = 1.66;
		stabattack = 0.60 * newattack;
		stabattacktiring = 1.33;
		break;
	case spear_weapon:
		sideattack = 0.65 * newattack;
		sideattacktiring = 1.66;
		aboveattack = 0.65 * newattack;
		aboveattacktiring = 2;
		stabattack = 1.20 * newattack;
		stabattacktiring = 1.33;
		break;
	}
}
float weapon::getrange() {
	return range;
}
void weapon::setrange(float newrange) {
	range = newrange;
}
unsigned int weapon::getclassweapon() {
	return classweapon;
}
void weapon::setclassweapon(unsigned int newclassweapon) {
	classweapon = newclassweapon;
}


/////////////////////////////////////////////


float armor::gethardness() {
	return hardness;
}
void armor::sethardness(float newhardness) {
	hardness = newhardness;
}

bool armor::getisforhead() {
	return isforhead;
}
void armor::setisforhead(int newisforhead) {
	isforhead = newisforhead;
}
int armor::getclassarmor() {
	return classarmor;
}
void armor::setclassarmor(int newclassarmor) {
	classarmor = newclassarmor;
}


/////////////////////////////////////////////


std::string luckyitem::getabilitydes() {
	return abilitydescription;
}
void luckyitem::setabilitydes(std::string newabilitydes) {
	abilitydescription = newabilitydes;
}
bool luckyitem::gethavepassiveability() {
	return havepassiveability;
}
void luckyitem::sethavepassiveability(bool newhavepassive) {
	havepassiveability = newhavepassive;
}
std::string luckyitem::getcategory() {
	return category;
}
void luckyitem::setcategory(std::string newcategory) {
	category = newcategory;
}


/////////////////////////////////////////////


int consumable::gethealpower() {
	return healpower;
}
void consumable::sethealpower(int newhealpower) {
	healpower = newhealpower;
}
float consumable::getresistancepower() {
	return resistancepower;
}
void consumable::setresistancepower(float newresistancepower) {
	resistancepower = newresistancepower;
}
int consumable::gettirednessfixpower() {
	return tirednessfixpower;
}
void consumable::settirednessfixpower(int newtirednessfixpower) {
	tirednessfixpower = newtirednessfixpower;
}
int consumable::getattack() {
	return attack;
}
void consumable::setattack(int newattack) {
	attack = newattack;
}
int consumable::gettypeofconsumable() {
	return typeofconsumable;
}
void consumable::settypeofconsumable(int newtypeofconsumable) {
	typeofconsumable = newtypeofconsumable;
}
float consumable::consumable_showpower() {
	switch (typeofconsumable) {
	case heal_potion:
		return round(healpower);
		break;
	case energy_potion:
		return round(tirednessfixpower);
		break;
	case brick:
		return resistancepower;
		break;
	default:
		std::cerr << "\nconsumable power not detected";
		break;
	}
}


////////////////////////////////////////////

int livingentity::getbackpack_size() {
	return backpack.size();
}
int livingentity::getidofcons(int categoryorid, int thing) { //2 returns id in specific vector, 1 returns id of category (mace/spear/sword)
	switch (categoryorid) {
	case 0:
		return backpack[thing];
		break;
	case 1:
		return floor(backpack[thing] / 10) - 1;
		break;
	case 2:
		return (backpack[thing] - floor(backpack[thing] / 10) * 10) - 1;
		break;
	}
}
void livingentity::getbackpack_whole() {
	int category;
	int tier;
	std::cout << "{---BACKPACK---}\n";
	for (int thing = 0; thing < backpack.size(); thing++) {
		category = floor(backpack[thing] / 10); // taking multiplicity of ten
		tier = backpack[thing] - category * 10;
		std::cout << "-[" << thing + 1 << "]- " << consumable_list[category - 1][tier - 1]->getname() << "\n";
	}
	std::cout << "--------------";
}
bool livingentity::addtobackpack(int thing, bool quiet) {
	if (backpack.size() >= 8) {
		if (!quiet) {
			std::cout << "you can't take more items with you";
		}
		return true;
	}
	else {
		backpack.push_back(thing);
	}
}
void livingentity::removefrombackpack(int thing, bool quiet) { // "quiet" is used during fight
	int place = thing;
	if (place >= 0 && place < backpack.size()) {
		backpack.erase(backpack.begin() + place);
		if (!quiet) {
			std::cout << "item removed from backpack";
		}
	}
	else {
		std::cout << "sadly, you can't remove free space or space, that doesn't exists";
	}
}
void livingentity::usebackpack_single(int choose, int round) {
	int category;
	int tier;
	category = getidofcons(1, choose); // taking multiplicity of ten
	tier = getidofcons(2, choose);

	switch (consumable_list[category][tier]->gettypeofconsumable()) {
	case heal_potion:
		addhp(consumable_list[category][tier]->consumable_showpower());
		if (hp > basehp) { sethp(basehp); }
		break;
	case energy_potion:
		addtiredness(consumable_list[category][tier]->consumable_showpower());
		if (tiredness > basetiredness) { settiredness(basetiredness); }
		break;
	case brick:
		float power = consumable_list[category][tier]->consumable_showpower();
		int expiretime = tier + 3 + round;
		addeffect(new single_statupdate(expiretime, power, this));
		break;
	}

	removefrombackpack(choose, true);
}
bool livingentity::checkbackpack_for(int typeofcons) {
	int category;
	for (int count = 0; count < backpack.size(); count++) {
		category = (floor(backpack[count] / 10));
		if (typeofcons - 1 == category) {
			break;
			return true;
		}
	}
	return false;
}
int livingentity::findinbackpack(int typeofcons) {
	int category;
	for (int count = 0; count < backpack.size(); count++) {
		category = (floor(backpack[count] / 10));
		if (typeofcons - 1 == category) {
			break;
			return count;
		}
	}
	return 0;
}
void livingentity::addeffect(effect* neweffect) {
	effectstatus.push_back(neweffect);
	neweffect->effectfunc(this);
}
int livingentity::getalleffects_size() {
	return effectstatus.size();
}
void livingentity::getalleffects(int round) {
	std::cout << "Effects:\n";
	for(effect* member : effectstatus) {
		std::cout << member->name << " ["<<member->expiretime - round<<"]\n";
	}
	std::cout << "------------";
}
void livingentity::effectstatus_tick(int currentround) {
	std::string enter;
	bool happened = false;
	int member = 0;
	while (effectstatus.size() > member) {
		if (effectstatus[member]->repeat == true) { 
			effectstatus[member]->effectfunc(this);
			happened = true;
		}
		if (effectstatus[member]->expiretime <= currentround) {
			delete effectstatus[member];
			effectstatus.erase(effectstatus.begin() + member);
			happened = true;
		}
		member++;
	}
	if (happened) { enter = _getch(); }
}
void livingentity::addtoqueue(int newmove) {
	movequeue.push_back(newmove);
}
void livingentity::removefromqueue() {
	movequeue.erase(movequeue.begin());
}
int livingentity::getqueuevar(int id, int categoryorid) {
	switch (categoryorid) {
	case 0:
		return movequeue[id];
		break;
	case 1:
		return floor(movequeue[id] / 10);
		break;
	case 2:
		return movequeue[id] - floor(movequeue[id] / 10) * 10;
		break;
	}
}
bool livingentity::havequeue() {
	if (movequeue.size() != 0) { return true; }
	else { return false; }
}



std::string livingentity::getstatus() {
	return status;
}
void livingentity::setstatus(std::string newstatus) {
	status = newstatus;
}
std::string livingentity::gethealthstatus() {
	return healthstatus;
}
void livingentity::sethealthstatus(std::string newhealthstatus) {
	healthstatus = newhealthstatus;
}
void livingentity::checkhpstatus() {
	if (hp >= 0.75 * basehp) {
		healthstatus = "high";
	}
	else if (hp > 0.25 * basehp) {
		healthstatus = "medium";
	}
	else if (hp <= 0.25 * basehp) {
		healthstatus = "low";
	}
}
std::string livingentity::gettirednessstatus() {
	return tirednessstatus;
}
void livingentity::checktirednessstatus() {
	if (tiredness >= 0.75 * basetiredness) {
		tirednessstatus = "high";
	}
	else if (tiredness > 0.25 * basetiredness) {
		tirednessstatus = "medium";
	}
	else if (tiredness <= 0.25 * basetiredness) {
		tirednessstatus = "low";
	}
}

std::string livingentity::gethaveattacked() {
	return haveattacked;
}
void livingentity::sethaveattacked(std::string newhaveattacked) {
	haveattacked = newhaveattacked;
}
std::string livingentity::gettookdamage() {
	return tookdamage;
}
void livingentity::settookdamage(std::string newtookdamage) {
	tookdamage = newtookdamage;
}
int livingentity::getmuchdamage() {
	return muchdamage;
}
void livingentity::addmuchdamage(int newdamage) {
	muchdamage += newdamage;
}
std::string livingentity::gethaveused() {
	return haveused;
}
void livingentity::sethaveused(std::string newhaveused) {
	haveused = newhaveused;
}
int livingentity::getnumberofused() {
	return numberofused;
}
void livingentity::addnumberofused(int newused){
	numberofused += newused;
}
std::string livingentity::gethavemoved() {
	return havemoved;
}
void livingentity::sethavemoved(std::string newhavemoved) {
	havemoved = newhavemoved;
}
auto livingentity::deductbystatus(std::string gstatus) { // if havemoved, then returns specific havemoved status
	if (gstatus == "haveattacked") { return gethaveattacked(); }
	if (gstatus == "tookdamage") { return gettookdamage(); }
	if (gstatus == "haveused") { return gethaveattacked(); }
	if (gstatus == "havemoved") { return gethaveattacked(); }

}
void livingentity::clearstatus() {
	status = "";
	healthstatus = "";
	tirednessstatus = "";

	haveattacked = "";
	tookdamage = "";
	muchdamage = 0;
	haveused = "";
	numberofused = 0;
	havemoved = "";
}
int livingentity::getlastmove() {
	return lastmove;
}
void livingentity::setlastmove(int newmove) {
	lastmove = newmove;
}


std::string livingentity::getname() {
	return name;
}
void livingentity::setname(std::string newname) {
	name = newname;
}
int livingentity::getlvl() {
	return lvl;
}
void livingentity::setlvl(int newlvl) {
	lvl = newlvl;
}
int livingentity::getatk() {
	return atk;
}
void livingentity::addatk(int natk) {
	atk += natk;
}
void livingentity::setatk(int newbaseatk) {
	atk = newbaseatk;
}
int livingentity::gethp() {
	return hp;
}
void livingentity::sethp(int newhp) {
	hp = newhp;
}
void livingentity::addhp(int newhp) {
	hp += newhp;
}
int livingentity::getbasehp() {
	return basehp;
}
void livingentity::setbasehp(int newbasehp) {
	basehp = newbasehp;
}
int livingentity::gettiredness() {
	return tiredness;
}
void livingentity::settiredness(int newtiredness) {
	tiredness = newtiredness;
}
void livingentity::addtiredness(int tirednesss) {
	tiredness = tiredness + tirednesss;
}
int livingentity::getbasetiredness() {
	return basetiredness;
}
void livingentity::setbasetiredness(int newbasetiredness) {
	basetiredness = newbasetiredness;
}
int livingentity::getendurance() {
	return endurance;
}
void livingentity::setendurance(int newendurance) {
	endurance = newendurance;
}
void livingentity::addendurance(int newendurance) {
	endurance += newendurance;
}
float livingentity::getdistance() {
	return distance;
}
void livingentity::setdistance(float newbasedistance) {
	distance = newbasedistance;
}
void livingentity::adddistance(float newdistance) {
	distance += newdistance;
}
float livingentity::getrange() {
	return range;
}
void livingentity::setrange(int newbaserange) {
	range = newbaserange;
}
void livingentity::addrange(int newrange) {
	range += newrange;
}
float livingentity::getresistance() {
	return resistance;
}
void livingentity::setresistance(float newresistance) {
	resistance = newresistance;
}
void livingentity::addresistance(float newresistance) {
	resistance += newresistance;
}
float livingentity::getmobility() {
	return mobility;
}
void livingentity::setmobility(float newmobility) {
	mobility = newmobility;
}
void livingentity::addmobility(float newmobility) {
	mobility += newmobility;
}
std::string livingentity::getidofwep() {
	return idofwep;
}
int livingentity::getidofwep(int categoryorid) { //2 returns id in specific vector, 1 returns id of category (mace/spear/sword)
	std::string id = idofwep;
	switch (categoryorid) {
	case 1:
		return id[0] - 48;
		break;
	case 2:
		id.erase(id.begin());
		return std::stoi(id);
		break;
	}
}
void livingentity::setidofwep(std::string newidofwep) {
	idofwep = newidofwep;
}
std::string livingentity::getidofarmor() {
	return idofarmor;
}
int livingentity::getidofarmor(int categoryorid) {  //2 returns id in specific vector, 1 returns id of category (breastplate/helm)
	std::string id = idofarmor;
	switch (categoryorid) {
	case 1:
		return id[0] - 48;
		break;
	case 2:
		id.erase(id.begin());
		return std::stoi(id);
		break;
	}
}
void livingentity::setidofarmor(std::string newidofarmor) {
	idofarmor = newidofarmor;
}
std::string livingentity::getidofhelm() {
	return idofhelm;
}
int livingentity::getidofhelm(int categoryorid) {
	std::string id = idofhelm;
	switch (categoryorid) {
	case 1:
		return id[0] - 48;
		break;
	case 2:
		id.erase(id.begin());
		return std::stoi(id);
		break;
	}
}
void livingentity::setidofhelm(std::string newidofhelm) {
	idofhelm = newidofhelm;
}
void livingentity::addarmor(int armorhp) {
	hp = hp + armorhp;
}
int livingentity::getidofitem() {
	return std::stoi(idofitem);
}
void livingentity::setidofitem(std::string newidofitem) {
	idofitem = newidofitem;
}

//moves for fight.cpp
bool livingentity::movement_check(std::string enter, bool quiet) {
	if (tiredness < 2) {
		if (!quiet) {
			std::cout << "\ntoo tired to walk\n";
			enter = _getch();
		}
		return false;
	}
	else if (tiredness < 3 && enter.size() > 1) { //
		if (enter[0] == enter[1]) {
			if (!quiet) {
				std::cout << "\ntoo tired to run\n";
				enter = _getch();
			}
			return false;
		}
	}
	return true;
}
void livingentity::movement_process(int choose) {
	bool wrong = false;
	int classofarmor = 0.70 * armor_list[getidofarmor(1)][getidofarmor(2)]->getclassarmor();
	float movementmobility = 1.25 * (1 - (classofarmor * 0.15));
	float reduction = 1 * mobility;

	switch (choose) {
	case 8:
		if (tiredness < floor(-1.5 * classofarmor)) { reduction = 0.75; } // lower than required tiredness will cost shorter distance
		distance += movementmobility * -1 * reduction;
		havemoved = "front";
		tiredness += floor(-1.5 * classofarmor) * endurance;
		break;
	case 88:
		if (tiredness < floor(-3.5 * classofarmor)) { reduction = 0.75; }
		distance += movementmobility * -1.5 * reduction;
		havemoved = "runfront";
		tiredness += floor(-2.5 * classofarmor) * endurance;
		break;
	case 2:
		if (tiredness < floor(-1.5 * classofarmor)) { reduction = 0.75; }
		distance += movementmobility * reduction;
		havemoved = "back";
		tiredness += floor(-1.5 * classofarmor) * endurance;
		break;
	case 22:
		if (tiredness < floor(-3.5 * classofarmor)) { reduction = 0.75; }
		distance += movementmobility * 1.5 * reduction;
		havemoved = "runback";
		tiredness += floor(-2.5 * classofarmor) * endurance;
		break;
	case 4:
		if (tiredness < floor(-1.34 * classofarmor)) { reduction = 0.75; }
		distance += (sqrt(pow(movementmobility, 2) + 3)) / 2 * reduction;
		havemoved = "left";
		tiredness += floor(-1.34 * classofarmor) * endurance;
		break;
	case 44:
		if (tiredness < floor(-2.67 * classofarmor)) { reduction = 0.75; }
		distance += (sqrt(pow(mobility * 1.5, 2) + 3)) / 2 * reduction;
		havemoved = "runleft";
		tiredness += floor(-2.67 * classofarmor) * endurance;
		break;
	case 6:
		if (tiredness < floor(-1.34 * classofarmor)) { reduction = 0.75; }
		distance += (sqrt(pow(movementmobility, 2) + 3)) / 2 * reduction;
		havemoved = "right";
		tiredness += floor(-1.34 * classofarmor) * endurance;
		break;
	case 66:
		if (tiredness < floor(-2.67 * classofarmor)) { reduction = 0.75; }
		distance += (sqrt(pow(movementmobility * 1.5, 2) + 3)) / 2 * reduction;
		havemoved = "runright";
		tiredness += floor(-2.67 * classofarmor) * endurance;
		break;
	default:
		std::cout << "you picked wrong number fool";
		wrong = true;
		break;
	}
	if (distance < 0.25) {
		distance = 0.25;
	}
	if (tiredness < 0) {

		tiredness = 0;
	}
	if (!wrong) {
		status = "havemoved";
	}
	checktirednessstatus();
}
void livingentity::rest_process() {
	tiredness += 6;
	if (tiredness > basetiredness) { tiredness = basetiredness; }
}


/////////////////////////////////////////////////////


int player::getlvlpts() {
	return lvlpts;
}
void player::setlvlpts(int newlvlpts) {
	lvlpts = newlvlpts;
}
void player::addlvlpts(int addlvlpts) {
	lvlpts += addlvlpts;
}
int player::getggol() {
	return ggol;
}
void player::setggol(int newggol) {
	ggol = newggol;
}
void player::addggol(int addggol) {
	ggol += addggol;
}
void player::cleanup() {
	hp = basehp;
	tiredness = basetiredness;
	distance = 4;
	gameplayer.clearstatus();
}
bool player::checklvl(bool savetype) { //single lvl up
	if (lvlpts >= 200 * (lvl * 0.55) && savetype == false) {
		lvl++;
		atk += 2;
		basehp += 7;
		hp += 7;
		lvlpts = 0;
		if (lvl % 5 == 0) {
			basetiredness += 3;
			tiredness += 3;
		}
		return true;
	}
	if (savetype == true) { // multiple lvl ups
		basetiredness = 20 + (lvl / 5) * 3;
		tiredness = 20 + (lvl / 5) * 3;
		atk = 6 + 2 * (lvl - 1);
		basehp = 40 + 7 * (lvl - 1);
		hp = 40 + 7 * (lvl - 1);
		return true;
	}
	return false;
}
void player::playerload(std::string lname, int llvl, int llvlpts, int gggol, std::string lidwep, std::string lidarm, std::string lidhelm, std::string liditem) {
	name = lname;
	lvl = llvl;
	lvlpts = llvlpts;
	checklvl(true);
	ggol = gggol;
	idofwep = lidwep;
	idofarmor = lidarm;
	idofhelm = lidhelm;
	idofitem = liditem;
}


///////////////////////////////////////


int enemy::getlvlptsvalue() {
	return lvlptsvalue;
}
void enemy::setlvlpts(int newlvlptsvalue) {
	lvlptsvalue = newlvlptsvalue;
}
int enemy::getggolvalue() {
	return ggolvalue;
}
void enemy::setggolvalue(int newggolvalue) {
	ggolvalue = newggolvalue;
}


///////////////////////////////////////

//EFFECTS:

// hardness:
void single_statupdate::effectfunc(livingentity* user) {
	std::cout << "User got additional resistance";
	user->addresistance(power);
}
void single_statupdate::effectcancel(livingentity* user) {
	user->addresistance(-1 * power);
	std::cout << "User lost additional resistance";
}