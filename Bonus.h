#include <stdio.h>
#include <allegro5/allegro.h>
#include "DynamicObject.h"
using namespace std;

#ifndef Bonus_H
#define Bunus_H

enum BonusType {OROLOGIO=0, CLESSIDRA, PROTEZIONE, DINAMITE, ARMA};

class Bonus:public DynamicObject
{
	public:
		BonusType bonusType;

		Bonus(int, Type, BonusType, int, int);
		~Bonus();  //CONTROLLARE SE DISTRUGGE LA BITMAP VISTO CHE È VIRTUAL
		void tick();
		void render();
		void die();
		void loadImage();
		void move(int, int);
};
#endif
