#include "DynamicObject.h"
#include <vector>
#ifndef Player_H
#define Player_H

class Player:public DynamicObject
{
	private:
		vector<ALLEGRO_BITMAP *> imagedx;  //vettori per le immagini destra e sinistra
		vector<ALLEGRO_BITMAP *> imagesx;
		ALLEGRO_BITMAP * dieImage;
		ALLEGRO_BITMAP * barriera;
		int movDx=0; //indice dell'immagine del vector da renderizzare
		int movSx=0;
		bool dx=false,sx=true; // booleana che indica se ci stiamo muovendo a dx o a sx
		int life;
		bool protezioneAttiva;
		bool lifeRemoved=false;
		int dieDelay=0;
		int dieRate=50.0f;
	public:
		Player(Type);
		~Player();
		void move(int);
		void render();
		void RemoveOneLife();
		void reset();
		int getLife();
		void setLife(int);
		void setProtezione(bool);
		void respawn(); //riposiziona il player al centro della mappa dopo la morte.
		bool getLifeRemoved(){return lifeRemoved;}
};
#endif