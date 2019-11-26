#include "Player.h"
#include "Ball.h"
#include "Weapons.h"
#include "Object.h"
#include <list>
#include "State.h"
#include "Bonus.h"
#include "obstacle.h"

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
		//list<Obstacle*> obstacle;
		list<Bonus*> bonus;
		int bulletDelay;
		int firerate;
		int hitDelay;
		int hitRate;	
		int timeDelay;
 		int timeRate;	
 		int bonusDelay;
 		int bonusRate;
		int level=1;
		int score=0;
		int gameTime =120;
		int bulletsNumber=0;
		ALLEGRO_FONT * pangFont;
		ALLEGRO_FONT *pangFontBig;

	public:
		GameState(ALLEGRO_DISPLAY * &,ALLEGRO_EVENT_QUEUE * &,ALLEGRO_TIMER * &, int,int);
		~GameState();

		//INIZIALIZZA IL LIVELLO
		void init(); 
		//CHIAMATA IN INIT E RESET, CREA LE PALLE AD INIZIO LIVELLO
		void generateBalls(); 
		//CONTROLLORE DEL LIVELLO, FA IL REFRESH DEL GIOCO	
		void tick(); 
		//CHIAMATO NEL TICK RENDERIZZA IL GIOCO A SCHERMO
		void render();
		//CHIAMATA NEL RENDER SERVE A VISUALIZZARE LE BARRE SOTTO E A LATO DELLA FINESTRA DI GIOCO
		void drawBar();
		// CONVERTE GLI INTERI IN MODO DA POTER ESSERE STAMPATI A VIDEO TRAMITE FUNZIONE  al_draw_text DI ALLEGRO
		string convert(int);
		//GESTISCE LA TASTIERA  
		void setKey(ALLEGRO_EVENT ); 

		//GESTISCE LE COLLISIONI DELLE PALLE
		void BallCollision(list<DynamicObject*>::iterator &);
		//CHIAMATA IN OBJECTCOLLISION VERIFICA SE C'È STATA EFFETTIVAMENTE UNA COLLISIONE
		bool checkCollision(list<DynamicObject*>::iterator );
		//CHIAMATA IN objectCollision DECIDE SE CREARE UN BONUS QUANDO UNA PALLA VIENE COLPITA
		void createBonus(int, int);
		//CHIAMATA NEL TICK VERIFICA SE E QUALE POTERE HA IL GIOCATORE IN QUEL MOMENTO
		void findPower(int);
		//CHIAMATA NEL TICK GESTISCE I TIMER DEL GIOCO 
		void timerManager();
		

		//CONTROLLA SE IL PLAYER HA PERSO IL LIVELLO
		bool gameOver(); 
		//APRE IL MENU DI OPZIONI (QUANDO IL GIOCATORE HA PERSO O QUANDO METTE IN PAUSA O QUANDO FINISCE IL GIOCO)
		void OptionMenu(ALLEGRO_BITMAP *);
		//CONTROLLA SE IL GIOCATORE HA VINTO IL LIVELLO
		bool checkLevelOver();
		//RESETTA IL LIVELLO
		void reset(); 

		bool finish;

		//int getLevel(){return level;}
		void setLevel(int l){level=l;}
		int getBulletsNumber(){return bulletsNumber;}
		void increaseBulletsNumber(){bulletsNumber+=1; cout<<"incremento"<<endl;}
		void decreaseBulletsNumber(){bulletsNumber-=1;}
		void resetBulletsNumber(){bulletsNumber=0;}
		void decreaseTime(){gameTime-=1;}
		void resetScore(){score=0;}
		void increaseScore(int s){score+=(s*10);}
		int getScore(){return score;}
};
#endif