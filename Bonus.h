#include <stdio.h>
#include <allegro5/allegro.h>
#include "DynamicObject.h"
using namespace std;

#ifndef Bonus_H
#define Bunus_H

//ARPIONEX2=CONSENTE DI LANCIARE DUE ARPIONI PER VOLTA
//ARPIONE=CONSENTE ALL'ARPIONE DI RIMANERE ATTACCATO AL SOFFITTO INVECE DI SPARIRE 
//OROLOGIO=BLOCCA LE PALLE PER QUALCHE SECONDO (DOVREBBE RENDERTI ANCHE INVULNERABILE)
//CLESSIDRA=CI DA UN BONUS DI TEMPO PER COMPLETARE IL LIVELLO
enum BonusType:int {OROLOGIO=0, ARPIONE=1, MACHINEGUN=2, ARPIONEX2=3,CLESSIDRA=4, GIRANDOLA=5/* PROTEZIONE, DINAMITE, */};

class Bonus:public DynamicObject
{
	public:
		BonusType bonusType;

		Bonus(Type, int, int, int);
		~Bonus();  //CONTROLLARE SE DISTRUGGE LA BITMAP VISTO CHE È VIRTUAL
		void render();
		void move(int);
};
#endif
