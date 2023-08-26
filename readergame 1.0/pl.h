#ifndef PL
#define PL
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <conio.h>
#include <fstream>

class livingentity;
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
};
enum movementtype {
	forward = 8,
	runforward = 88,
	back = 2,
	runback = 22,
	left = 4,
	runleft = 44,
	right = 6,
	runright = 66
};

extern std::string typetranslator(int category, int typeofequipment);


class item { // main equipable class
protected:

	std::string name;
	int price;
	int lvlreq;
	bool isbought;

public:

	std::string getname();
	void setname(std::string newname);
	int getprice();
	void setprice(int newprice);
	int getlvlreq();
	void setlvlreq(int newlvlreq);
	bool getisbought();
	void setisbought(bool newisbought);

};




class weapon : public item {
private:

	int valueattack; //first one for shop
	int sideattack;
	int sideattacktiring;
	int aboveattack;
	int aboveattacktiring;
	int stabattack;
	int stabattacktiring;
	float range;

	int classweapon;

public:

	int getvalueattack();
	void setvalueattack(int newattack);
	int getdirectionattack(int attacktype);
	int getdirectiontiring(int attacktype);
	void setdirectionattack(int newattack, int weapontype);
	float getrange();
	void setrange(float newrange);
	unsigned int getclassweapon();
	void setclassweapon(unsigned int newclassweapon);

	weapon() = default;
	weapon(std::string wname, int wattack, float wrange, int wprice, int wlvlreq, unsigned int wclassweapon) {
		name = wname;
		setvalueattack(wattack);
		setdirectionattack(wattack, wclassweapon);
		range = wrange;
		price = wprice;
		lvlreq = wlvlreq;
		classweapon = wclassweapon;
		isbought = false;
	}
};


class armor : public item {
private:

	int isforhead;
	float hardness;
	int classarmor;

public:

	float gethardness();
	void sethardness(float newhardness);
	bool getisforhead();
	void setisforhead(int newisforhead);
	int getclassarmor();
	void setclassarmor(int newclassarmor);

	armor() = default;
	armor(std::string aname, float ahardness, int aprice, int alvlreq, unsigned int aisforhead, unsigned int aclassarmor) {
		name = aname;
		hardness = ahardness;
		price = aprice;
		lvlreq = alvlreq;
		isforhead = aisforhead;
		classarmor = aclassarmor;
		isbought = false;
	}
};

class luckyitem : public item { //items have separate functions wich are their effects
private:
	std::string abilitydescription;
	std::string category; // moments when used: default (after every move), attacking, moving, using, resting, before[previous example], beforedefault[start of round]. 
	bool havepassiveability;
public:

	std::function<void(livingentity*, livingentity*)> magicpower;
	std::function<void(livingentity*, livingentity*)> passivepower;
	std::function<void(livingentity*, livingentity*)> cancelpassive;
	std::function<bool(livingentity*, livingentity*)> condition;

	std::string getabilitydes();
	void setabilitydes(std::string newabilitydes);
	bool gethavepassiveability();
	void sethavepassiveability(bool newhavepassive);
	std::string getcategory();
	void setcategory(std::string newcategory);

	luckyitem() = default;
	luckyitem(std::string iname, int iprice, int ilvlreq, std::string icategory, bool havepassive, std::string iabilitydes) {
		name = iname;
		price = iprice;
		lvlreq = ilvlreq;
		category = icategory;
		havepassiveability = havepassive;
		abilitydescription = iabilitydes;

		isbought = false;
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
	
	int gethealpower();
	void sethealpower(int newhealpower);
	float getresistancepower();
	void setresistancepower(float newresistancepower);
	int gettirednessfixpower();
	void settirednessfixpower(int newtirednessfixpower);
	int getattack();
	void setattack(int newattack);
	int gettypeofconsumable();
	void settypeofconsumable(int newtypeofconsumable);
	float consumable_showpower();

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

extern std::vector<weapon*> sword_list;
extern std::vector<weapon*> mace_list;
extern std::vector<weapon*> spear_list;
extern std::vector<std::vector<weapon*>> weapon_list;

extern std::vector<armor*> helm_list;
extern std::vector<armor*> breastplate_list;
extern std::vector<std::vector<armor*>> armor_list;

extern std::vector<luckyitem*> item_list;

extern std::vector<consumable*> heal_usable;
extern std::vector<consumable*> energy_usable;
extern std::vector<consumable*> resistance_usable;
extern std::vector<std::vector <consumable*>> consumable_list;


struct effect {
	std::string name = "default";
	int expiretime = 5;
	bool repeat = false;
	float power;
	livingentity* guy;
	virtual void effectfunc(livingentity* user) { std::cout << "\ndefault effect activated " << expiretime; };
	virtual void effectcancel(livingentity* user) { std::cout << "\ndefault effect wore off"; };
	virtual ~effect() {
	};
}; // specific effects are below entity classes

struct single_statupdate : public effect { // for example: single hardness for amount of time
	void effectfunc(livingentity* user);
	void effectcancel(livingentity* user);

	single_statupdate(int nexpiretime, float npower, livingentity* user) {
		name = "hardness";
		expiretime = nexpiretime;
		repeat = false;
		power = npower;
		guy = user;

	}
	~single_statupdate(){
		effectcancel(guy);
	}
};

// main entity class

class livingentity {
protected:

	std::vector<int> backpack;
	std::vector<effect*> effectstatus;
	std::vector<int> movequeue;
	std::string status; // haveattacked, tookdamage, haveused, havemoved
	std::string healthstatus; // low - >=25% /medium - <75%/ high - <75%
	std::string tirednessstatus; // same thing ^

	std::string haveattacked; // "missed" also counts
	std::string tookdamage;
	int muchdamage;
	std::string haveused;
	int numberofused;
	std::string havemoved; // diference between status and specific strings are that the strings are for specific types of moves, attacks, etc..
	int lastmove;
	// status in this case is for checking just chosen move rather than specific types of them.

	// To fulfill more specific condition (example: tookdamage string - "aboveattack") it requires to also have "haveattacked" in status to prevent item doing things twice or more.
	std::string name;
	int lvl;
	int atk;
	int basehp;
	int hp;
	int basetiredness;
	int tiredness; //less value = more tired
	float endurance = 1; // fatigue tendency
	float distance;
	float range;
	float resistance; // <- used only for potions
	float mobility = 1;
	std::string idofwep; // id equal to index of vector of pointers to class objects
	std::string idofarmor;
	std::string idofhelm;
	std::string idofitem;

	/*int p_taken_damage, e_taken_damage;
	int p_numberofused_cons, e_numberofused_cons;*/
public:

	int getbackpack_size();
	int getidofcons(int categoryorid, int thing);
	void getbackpack_whole();
	bool addtobackpack(int thing, bool quiet);
	void removefrombackpack(int thing, bool quiet);
	void usebackpack_single(int choose, int round);
	bool checkbackpack_for(int typeofcons);
	int findinbackpack(int typeofcons);
	void addeffect(effect* neweffect);
	int getalleffects_size();
	void getalleffects(int round);
	void effectstatus_tick(int currentround);
	void addtoqueue(int newmove);
	void removefromqueue();
	int getqueuevar(int id, int categoryorid);
	bool havequeue();

	std::string getstatus();
	void setstatus(std::string newstatus);
	std::string gethealthstatus();
	void sethealthstatus(std::string newhealthstatus);
	void checkhpstatus();
	std::string gettirednessstatus();
	void checktirednessstatus();
	std::string gethaveattacked();
	void sethaveattacked(std::string newhaveattacked);
	std::string gettookdamage();
	void settookdamage(std::string newtookdamage);
	int getmuchdamage();
	void addmuchdamage(int newdamage);
	std::string gethaveused();
	void sethaveused(std::string newhaveused);
	int getnumberofused();
	void addnumberofused(int newused);
	std::string gethavemoved();
	void sethavemoved(std::string newhavemoved);
	auto deductbystatus(std::string gstatus);
	void clearstatus();
	int getlastmove();
	void setlastmove(int newmove);

	std::string getname();
	void setname(std::string newname);
	int getlvl();
	void setlvl(int newlvl);
	int getatk();
	void addatk(int natk);
	void setatk(int newbaseatk);
	int gethp();
	void sethp(int newhp);
	void addhp(int newhp);
	int getbasehp();
	void setbasehp(int newbasehp);
	int gettiredness();
	void settiredness(int newtiredness);
	void addtiredness(int tirednesss);
	int getendurance();
	void setendurance(int newendurance);
	void addendurance(int newendurance);
	int getbasetiredness();
	void setbasetiredness(int newbasetiredness);
	float getdistance();
	void setdistance(float newbasedistance);
	void adddistance(float newdistance);
	float getrange();
	void setrange(int newbaserange);
	void addrange(int newrange);
	float getresistance();
	void setresistance(float newresistance);
	void addresistance(float newresistance);
	float getmobility();
	void setmobility(float newmobility);
	void addmobility(float newmobility);

	std::string getidofwep();
	int getidofwep(int categoryorid);
	void setidofwep(std::string newidofwep);
	std::string getidofarmor();
	int getidofarmor(int categoryorid);
	void setidofarmor(std::string newidofarmor);
	std::string getidofhelm();
	int getidofhelm(int categoryorid);
	void setidofhelm(std::string newidofhelm);
	void addarmor(int armorhp);
	int getidofitem();
	void setidofitem(std::string newidofitem);
	bool movement_check(std::string enter, bool quiet);
	void movement_process(int choose);
	void rest_process();

};
class player : public livingentity {
private:

	int lvlpts;
	unsigned int ggol;

public:

	int getlvlpts();
	void setlvlpts(int newlvlpts);
	void addlvlpts(int addlvlpts);
	int getggol();
	void setggol(int newggol);
	void addggol(int addggol);
	void cleanup();
	bool checklvl(bool savetype);
	void playerload(std::string lname, int llvl, int llvlpts, int gggol, std::string lidwep, std::string lidarm, std::string lidhelm, std::string liditem);

	player() {
		name = "bezimienny";
		haveattacked = "";
		haveused = "";
		havemoved = "";
		lvl = 1;
		lvlpts = 0;
		atk = 10;
		hp = 40;
		basehp = 40;
		tiredness = 20;
		basetiredness = 20;
		distance = 4.00;
		range = 0.65;
		ggol = 20;
		idofwep = "00";
		idofarmor = "00";
		idofhelm = "00";
		idofitem = "0";
	}


};

class enemy : public livingentity {
private:

	int lvlptsvalue;
	int ggolvalue;

public:

	int getlvlptsvalue();
	void setlvlpts(int newlvlptsvalue);
	int getggolvalue();
	void setggolvalue(int newggolvalue);

	enemy() {
		name = "randomhoboguy";
		atk = 10;
	}
	enemy(std::string ename, int elvl, int eatk, int ehp, int eptval, int eggolval, std::string eidwep, std::string eidarm, std::string eidhelm, std::string eiditem) {
		name = ename;
		haveattacked = "";
		haveused = "";
		havemoved = "";
		lvl = elvl;
		atk = eatk;
		basehp = ehp;
		hp = ehp;
		lvlptsvalue = eptval;
		ggolvalue = eggolval;
		idofwep = eidwep;
		idofarmor = eidarm;
		idofhelm = eidhelm;
		idofitem = eiditem;
		basetiredness = 20 + (elvl / 5) * 3;
		tiredness = 20 + (elvl / 5) * 3;
		distance = 4.00;
		range = 0.65;

	}
};

extern player gameplayer; // make player be everywhere
extern player* gameplayer_ptr;

struct equipmentinfo { // created to contain data of both player and enemy equipment to make fight.h and cpp more readable
	int p_weapon_category, p_weapon_index, e_weapon_category, e_weapon_index; 
	int p_armor_category, p_armor_index, e_armor_category, e_armor_index;
	int p_helm_category, p_helm_index, e_helm_category, e_helm_index;
	int p_item_index, e_item_index;


	/*p stands for player while e for enemy   
	example of use : weapon_list[p_weapon_category][p_weapon_index] i think it is more readable
	*/

	equipmentinfo(enemy * opponent) {
		p_weapon_category = gameplayer.getidofwep(1), p_weapon_index = gameplayer.getidofwep(2), e_weapon_category = opponent->getidofwep(1), e_weapon_index = opponent->getidofwep(2);
		p_armor_category = gameplayer.getidofarmor(1), p_armor_index = gameplayer.getidofarmor(2), e_armor_category = opponent->getidofarmor(1), e_armor_index = opponent->getidofarmor(2);
		p_helm_category = gameplayer.getidofhelm(1), p_helm_index = gameplayer.getidofhelm(2), e_helm_category = opponent->getidofhelm(1), e_helm_index = opponent->getidofhelm(2);
		p_item_index = gameplayer.getidofitem(), e_item_index = opponent->getidofitem();
	}
};
#endif