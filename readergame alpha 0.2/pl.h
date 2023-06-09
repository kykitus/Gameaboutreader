#ifndef PLAYERE
#define PLAYERE
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


class livingentity {
protected:
	std::string name;
	int atk;
	int hp;
	int tiredness;
	float distance;
	float range;
	int idofwep;
	int idofarmor;
	int idofhelm;
	int idofitem;
public:
	std::string getname() {
		return name;
	}
	void setname(std::string newname) {
		name = newname;
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
	int gettiredness() {
		return tiredness;
	}
	void settiredness(int newbasetiredness) {
		tiredness = newbasetiredness;
	}
	void addtiredness(int tirednesss) {
		tiredness = tiredness + tirednesss;
	}
	float getdistance() {
		return distance;
	}
	void setdistance(int newbasedistance) {
		distance = newbasedistance;
	}
	void adddistance(int distancee) {
		distance = distance + distancee;
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
	void decarmor(int armorhp) {
		hp = hp - armorhp;
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
	int getggol() {
		return ggol;
	}
	void setggol(int newggol) {
		ggol = newggol;
	}
	void addggol(int addggol) {
		ggol += addggol;
	}
	void checklvl(int currentlvl, bool savetype) {
		if (lvlpts >= 200 * currentlvl * (currentlvl * 1.1)) {
			lvl++;
			atk += 2;
			hp += 4;
		}
		if (lvl % 5 == 0) {
			if (savetype == true) {
				tiredness = 20 + (lvl / 5);
			}
			tiredness++;
		}
		if (savetype == true) {
			atk += 2 * lvl -1;
			hp += 4 * lvl -1;
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
		lvl = 1;
		lvlpts = 0;
		atk = 3;
		hp = 20;
		tiredness = 20;
		distance = 4.00;
		range = 0.65;
		ggol = 30;
		idofwep = 0;
		idofarmor = 0;
		idofhelm = 0;
		idofitem = 0;
	}


};

class enemy : public livingentity {
private:
	int lvlptsvalue;
public:
	int getlvlptsvalue() {
		return lvlptsvalue;
	}
	void setlvlpts(int newlvlptsvalue) {
		lvlptsvalue = newlvlptsvalue;
	}

	enemy() {
		name = "randomhoboguy";
	}
	enemy(std::string ename, int eatk, int ehp, int eptval, int eidwep, int eidarm, int eidhelm, int eiditem) {
		name = ename;
		atk = eatk;
		hp = ehp;
		lvlptsvalue = eptval;
		idofwep = eidwep;
		idofarmor = eidarm;
		idofhelm = eidhelm;
		idofitem = eiditem;
		tiredness = 20;
		range = 0.65;

	}
};

extern player playere;


class item {
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
};

class weapon : public item {
private:
	int attack;
	float range;
	float crit;

	int classweapon;


public:


	int getattack() {
		return attack;
	}
	void setattack(int newattack) {
		attack = newattack;
	}
	float getrange() {
		return range;
	}
	void setrange(float newrange) {
		range = newrange;
	}
	float getcrit() {
		return crit;
	}
	void setcrit(float newcrit) {
		crit = newcrit;
	}
	unsigned int getclassweapon() {
		return classweapon;
	}
	void setclassweapon(unsigned int newclassweapon) {
		classweapon = newclassweapon;
	}




	weapon() = default;
	weapon(std::string name, int attack, float range, float crit, int price, int lvlreq, unsigned int classweapon) {
		setname(name);
		setattack(attack);
		setrange(range);
		setcrit(crit);
		setprice(price);
		setlvlreq(lvlreq);
		setclassweapon(classweapon);
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
	armor(std::string name, float hardness, int price, int lvlreq, unsigned int isforhead, unsigned int classarmor) {
		setname(name);
		sethardness(hardness);
		setisforhead(isforhead);
		setprice(price);
		setlvlreq(lvlreq);
		setclassarmor(classarmor);
		setisbought(0);
	}
};

class potion : public item {
private:
	int healpower;
	int resistancepower;
	int agilitypower;
	int tirednessfixpower;

public:

};

class funnyobject : public item {
private:
	std::string abilitydescription;
	std::string category; //movement, status, offense, defense
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

	funnyobject() = default;
	funnyobject(std::string name, int price, int lvlreq, std::string abilitydes) {
		setname(name);
		setprice(price);
		setlvlreq(lvlreq);
		setabilitydes(abilitydes);
		setisbought(0);
	}
};

extern std::vector<weapon*> wepon;
extern std::vector<armor*> armo;
extern std::vector<armor*> hem;
extern std::vector<funnyobject*> itme;


#endif