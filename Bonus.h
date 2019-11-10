#include <stdio.h>
#include <allegro5/allegro.h>
#include "DynamicObject.h"
using namespace std;

#ifndef Bonus_H
#define Bunus_H

//ARPIONEX2=CONSENTE DI LANCIARE DUE ARPIONI PER VOLTA
//ARPIONE=CONSENTE ALL'ARPIONE DI RIMANERE ATTACCATO AL SOFFITTO INVECE DI SPARIRE 
//OROLOGIO=BLOCCA LE PALLE PER QUALCHE SECONDO (DOVREBBE RENDERTI ANCHE INVULNERABILE)
enum BonusType:int {OROLOGIO=0, ARPIONE=1/*, ARPIONEX2,CLESSIDRA, PROTEZIONE, DINAMITE, ARMA*/};

class Bonus:public DynamicObject
{
	public:
		BonusType bonusType;

		Bonus(int, Type, int, int, int);
		~Bonus();  //CONTROLLARE SE DISTRUGGE LA BITMAP VISTO CHE È VIRTUAL
		void render();
		void die();
		void move(int);
};
#endif
