#ifndef PLAYERE
#define PLAYERE
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


enum weapontype {
	sword_weapon = 1,
	mace_weapon = 2,
	spear_weapon = 3
};
enum attacktype {
	side_attack = 1,
	above_attack = 2,
	stab_attack = 3
};
enum armortype {
	light_armor = 1,
	medium_armor = 2,
	heavy_armor = 3
};
enum usabletype {
	heal_potion = 1,
	energy_potion = 2,
	brick = 3
}; // different names can be used for same value depending on context



class item { // main equipable class
protected:
	std::string name;
	int price;
	int lvlreq;
	bool isbought;
public:
	std::string getname() {
		return name;
	}
	void setname(std::string newname) {
		name = newname;
	}
	int getprice() {
		return price;
	}
	void setprice(int newprice) {
		price = newprice;
	}
	int getlvlreq() {
		return lvlreq;
	}
	void setlvlreq(int newlvlreq) {
		lvlreq = newlvlreq;
	}
	bool getisbought() {
		return isbought;
	}
	void setisbought(bool newisbought) {
		isbought = newisbought;
	}
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
};




class weapon : public item {
private:
	int valueattack; //first one for shop
	int sideattack;
	int aboveattack;
	int stabattack;
	float range;

	int classweapon;

public:
	int getvalueattack() {
		return valueattack;
	}
	void setvalueattack(int newattack) {
		valueattack = newattack;
	}
	int getdirectionattack(int attacktype) {
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
	void setdirectionattack(int newattack, int weapontype) {
		switch(weapontype){
		case sword_weapon:
			sideattack = newattack;
			aboveattack = newattack;
			stabattack = 1.10 * newattack;
			break;
		case mace_weapon:
			sideattack = newattack;
			aboveattack = 1.20 * newattack;
			stabattack = 0.60 * newattack;
			break;
		case spear_weapon:
			sideattack = 0.75 * newattack;
			aboveattack = 0.75 * newattack;
			stabattack = 1.20 * newattack;
			break;
		}
	}
	float getrange() {
		return range;
	}
	void setrange(float newrange) {
		range = newrange;
	}
	unsigned int getclassweapon() {
		return classweapon;
	}
	void setclassweapon(unsigned int newclassweapon) {
		classweapon = newclassweapon;
	}




	weapon() = default;
	weapon(std::string wname, int wattack, float wrange, int wprice, int wlvlreq, unsigned int wclassweapon) {
		name = wname;
		setvalueattack(wattack);
		setdirectionattack(wattack, wclassweapon);
		range = wrange;
		price = wprice;
		lvlreq = wlvlreq;
		classweapon = wclassweapon;
		setisbought(0);
	}
};


class armor : public item {
private:
	int isforhead;
	float hardness;
	int classarmor;


public:

	
	float gethardness() {
		return hardness;
	}
	void sethardness(float newhardness) {
		hardness = newhardness;
	}

	bool getisforhead() {
		return isforhead;
	}
	void setisforhead(int newisforhead) {
		isforhead = newisforhead;
	}
	int getclassarmor() {
		return classarmor;
	}
	void setclassarmor(int newclassarmor) {
		classarmor = newclassarmor;
	}


	armor() = default;
	armor(std::string aname, float ahardness, int aprice, int alvlreq, unsigned int aisforhead, unsigned int aclassarmor) {
		name = aname;
		hardness = ahardness;
		price = aprice;
		lvlreq = alvlreq;
		isforhead = aisforhead;
		classarmor = aclassarmor;
		setisbought(0);
	}
};


class luckyitem : public item { //items have separate functions wich are their effects
private:
	std::string abilitydescription;
	std::string category;
public:
	auto ability();

	std::string getabilitydes() {
		return abilitydescription;
	}
	void setabilitydes(std::string newabilitydes) {
		abilitydescription = newabilitydes;
	}
	std::string getcategory() {
		return category;
	}
	void setcategory(std::string newcategory) {
		category = newcategory;
	}

	luckyitem() = default;
	luckyitem(std::string iname, int iprice, int ilvlreq, std::string icategory, std::string iabilitydes) {
		name = iname;
		price = iprice;
		lvlreq = ilvlreq;
		category = icategory;
		abilitydescription = iabilitydes;
		setisbought(0);
	}
};

class consumable : public item {
private:
	int healpower;
	float resistancepower;
	int tirednessfixpower;
	int attack;
	int tier;
	int typeofconsumable; //hp potion, energy potion, brick
public:
	int gethealpower() {
		return healpower;
	}
	void sethealpower(int newhealpower) {
		healpower = newhealpower;
	}
	float getresistancepower() {
		return resistancepower;
	}
	void setresistancepower(float newresistancepower) {
		resistancepower = newresistancepower;
	}
	int gettirednessfixpower() {
		return tirednessfixpower;
	}
	void settirednessfixpower(int newtirednessfixpower) {
		tirednessfixpower = newtirednessfixpower;
	}
	int getattack() {
		return attack;
	}
	void setattack(int newattack) {
		attack = newattack;
	}
	int gettypeofconsumable() {
		return typeofconsumable;
	}
	void settypeofconsumable(int newtypeofconsumable) {
		typeofconsumable = newtypeofconsumable;
	}
	float consumable_use() {
		switch (gettypeofconsumable()) {
		case heal_potion:
			return round(healpower);
			break;
		case energy_potion:
			return round(tirednessfixpower);
			break;
		case brick:
			return resistancepower;
			break;
		}
	}
	consumable(std::string cname, float cpower, int cprice, int clvlreq, int ctypeofconsumable,  int ctier) {
		name = cname;
		switch (ctypeofconsumable) {
		case heal_potion:
			healpower = cpower;
			break;
		case energy_potion:
			tirednessfixpower = cpower;
			break;
		case brick:
			resistancepower = cpower;
			break;
		}
		price = cprice;
		lvlreq = clvlreq;
		typeofconsumable = ctypeofconsumable;
		tier = ctier;
	}
};

extern std::vector<weapon*> weapon_list;
extern std::vector<armor*> armor_list;
extern std::vector<armor*> helm_list;
extern std::vector<luckyitem*> item_list;

extern std::vector<consumable*> heal_usable;
extern std::vector<consumable*> energy_usable;
extern std::vector<consumable*> resistance_usable;
extern std::vector<std::vector <consumable*>> consumable_list;




// main entity class

class livingentity {
protected:
	std::vector<int> backpack;
	std::string name;
	std::string haveattacked;
	std::string haveused;
	std::string havemoved;

	int atk;
	int hp;
	int tiredness; //less value = more tired
	float range;
	int idofwep; // id equal to index of vector of pointers to class objects
	int idofarmor;
	int idofhelm;
	int idofitem;
public:

	int getbackpack_single(int choose) {
		return backpack[choose];
	}
	void getbackpack_whole() {
		int category;
		int tier;
		std::cout << "{BACKPACK}";
		for(int thing = 0; thing < backpack.size(); thing++) {
			category = floor(backpack[thing] / 10); // taking multiplicity of ten
			tier = (backpack[thing] - category * 10);
			std::cout << "\n  -" << consumable_list[category - 1][tier - 1]->getname();
		}
		std::cout << "----------";
	}
	bool addtobackpack(int thing) {
		if (backpack.size() >= 8) {
			std::cout << "you can't take more items with you";
			return true;
		}
		else {
			backpack.push_back(thing);
		}
	}




	std::string getname() {
		return name;
	}
	void setname(std::string newname) {
		name = newname;
	}
	std::string gethaveattacked() {
		return haveattacked;
	}
	void sethaveattacked(std::string newhaveattacked) {
		haveattacked = newhaveattacked;
	}
	std::string gethaveused() {
		return haveused;
	}
	void sethaveused(std::string newhaveused) {
		haveused = newhaveused;
	}
	std::string gethavemoved() {
		return havemoved;
	}
	void sethavemoved(std::string newhavemoved) {
		havemoved = newhavemoved;
	}


	int getatk() {
		return atk;
	}
	void setatk(int newbaseatk) {
		atk = newbaseatk;
	}
	int gethp() {
		return hp;
	}
	void sethp(int newbasehp) {
		hp = newbasehp;
	}
	void addhp(int newhp) {
		hp = hp + newhp;
	}
	int gettiredness() {
		return tiredness;
	}
	void settiredness(int newbasetiredness) {
		tiredness = newbasetiredness;
	}
	void addtiredness(int tirednesss) {
		tiredness = tiredness + tirednesss;
	}
	float getrange() {
		return range;
	}
	void setrange(int newbaserange) {
		range = newbaserange;
	}
	void addrange(int rangee) {
		range = range + rangee;
	}
	int getidofwep() {
		return idofwep;
	}
	void setidofwep(int newidofwep) {
		idofwep = newidofwep;
	}
	void addatkwep(int atkwep) {
		atk = atk + atkwep;
	}
	void decatkwep(int atkwep) {
		atk = atk - atkwep;
	}
	int getidofarmor() {
		return idofarmor;
	}
	void setidofarmor(int newidofarmor) {
		idofarmor = newidofarmor;
	}
	int getidofhelm() {
		return idofhelm;
	}
	void setidofhelm(int newidofhelm) {
		idofhelm = newidofhelm;
	}
	void addarmor(int armorhp) {
		hp = hp + armorhp;
	}
	int getidofitem() {
		return idofitem;
	}
	void setidofitem(int newidofitem) {
		idofitem = newidofitem;
	}
};
class player : public livingentity {
private:
	int lvl;
	int lvlpts;
	float distance;
	unsigned int ggol;


public:
	int getlvl() {
		return lvl;
	}
	void setlvl(int newlvl) {
		lvl = newlvl;
	}
	int getlvlpts() {
		return lvlpts;
	}
	void setlvlpts(int newlvlpts) {
		lvlpts = newlvlpts;
	}
	void addlvlpts(int addlvlpts) {
		lvlpts += addlvlpts;
	}
	float getdistance() {
		return distance;
	}
	void setdistance(float newbasedistance) {
		distance = newbasedistance;
	}
	void adddistance(float newdistance) {
		distance = distance + newdistance;
	}
	int getggol() {
		return ggol;
	}
	void setggol(int newggol) {
		ggol = newggol;
	}
	void addggol(int addggol) {
		ggol += addggol;
	}
	void checklvl(int currentlvl, bool savetype) { //single lvl up
		if (lvlpts >= 200 * currentlvl * (1 * (currentlvl * 0.1)) && savetype == false) {
			lvl++;
			atk += 2;
			hp += 4;
			lvlpts = 0;
			if (lvl % 5 == 0) {
				tiredness++;
			}
		}
		if (savetype == true) { // multiple lvl ups
			tiredness = 20 + (lvl / 5) * 2;
			atk = 1 * lvl;
			hp = 20 + 5 * lvl;
		}
	}
	void playerload(std::string lname, int llvl, int llvlpts, int gggol, int lidwep, int lidarm, int lidhelm, int liditem) {
		name = lname;
		lvl = llvl;
		lvlpts = llvlpts;
		checklvl(llvl, true);
		ggol = gggol;
		idofwep = lidwep;
		idofarmor = lidarm;
		idofhelm = lidhelm;
		idofitem = liditem;
	}
	player() {
		name = "bezimienny";
		haveattacked = "";
		haveused = "";
		havemoved = "";
		lvl = 1;
		lvlpts = 0;
		atk = 3;
		hp = 20;
		tiredness = 20;
		distance = 4.00;
		range = 0.65;
		ggol = 20;
		idofwep = 0;
		idofarmor = 0;
		idofhelm = 0;
		idofitem = 0;
	}


};

class enemy : public livingentity {
private:
	int lvlptsvalue;
	int ggolvalue;
public:
	int getlvlptsvalue() {
		return lvlptsvalue;
	}
	void setlvlpts(int newlvlptsvalue) {
		lvlptsvalue = newlvlptsvalue;
	}
	int getggolvalue() {
		return ggolvalue;
	}
	void setggolvalue(int newggolvalue) {
		ggolvalue = newggolvalue;
	}

	enemy() {
		name = "randomhoboguy";
	}
	enemy(std::string ename, int eatk, int ehp, int eptval, int eggolval, int eidwep, int eidarm, int eidhelm, int eiditem) {
		name = ename;
		haveattacked = "";
		haveused = "";
		havemoved = "";
		atk = eatk;
		hp = ehp;
		lvlptsvalue = eptval;
		ggolvalue = eggolval;
		idofwep = eidwep;
		idofarmor = eidarm;
		idofhelm = eidhelm;
		idofitem = eiditem;
		tiredness = 20;
		range = 0.65;

	}
};

extern player gameplayer; // make player be everywhere

#endif