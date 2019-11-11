#include <stdio.h>
#include <allegro5/allegro.h>
#include "Player.h"
#include "Ball.h"
#include "Weapons.h"
#include "MachineGun.h"
#include "Object.h"
#include <iostream>
#include <list>
#include "State.h"
#include "Bonus.h"
#include "includes.h"
#ifndef GameState_H
#define GameState_H

enum MYKEYS {
   KEY_LEFT, KEY_RIGHT , SPACE_BAR 
};

class GameState:public State
{
	private:
		Player *player;
		list<DynamicObject*> object;
		list<Bonus*> bonus;
		int bulletDelay;
		int firerate;
		int level=1;
		ALLEGRO_FONT * pangFont;
	public:
		GameState(ALLEGRO_DISPLAY * &,ALLEGRO_EVENT_QUEUE * &,ALLEGRO_TIMER * &, int,int);
		~GameState();

		void init(); //INIZIALIZZA IL LIVELLO
		void generateBalls(); //CHIAMATA IN INIT E RESET, CREA LE PALLE AD INIZIO LIVELLO
		void tick(); //CONTROLLORE DEL LIVELLO, FA IL REFRESH DEL GIOCO	
		//CHIAMATO NEL TICK RENDERIZZA IL GIOCO A SCHERMO
		void render();
		//CHIAMATA NEL RENDER SERVE A VISUALIZZARE LE BARRE SOTTO E A LATO DELLA FINESTRA DI GIOCO
		void drawBar();
		void setKey(ALLEGRO_EVENT ); //GESTISCE IL MOUSE 

		//GESTISCE LE COLLISIONI DELLE PALLE
		void BallCollision(list<DynamicObject*>::iterator &);
		//CHIAMATA IN OBJECTCOLLISION VERIFICA SE C'È STATA EFFETTIVAMENTE UNA COLLISIONE
		bool checkCollision(list<DynamicObject*>::iterator );
		//CHIAMATA IN objectCollision DECIDE SE CREARE UN BONUS QUANDO UNA PALLA VIENE COLPITA
		void createBonus(int, int);
		//CHIAMATA NEL TICK VERIFICA SE E QUALE POTERE HA IL GIOCATORE IN QUEL MOMENTO
		void findPower(int);
		//CHIAMATA NEL TICK GESTISCE I TTL DEGLI OGGETTI
		void TtlManager();

		void gameOver(); 
		bool checkLevelOver();
		void reset(); //RESETTA IL LIVELLO

		bool finish;

		int getLevel(){return level;}
		void setLevel(int l){level=l;}
};
#endif