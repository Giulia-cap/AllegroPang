#include "DynamicObject.h"
#include <vector>
#ifndef Player_H
#define Player_H

class Player:public DynamicObject
{
	private:
		vector<ALLEGRO_BITMAP *> imagedx;  //vettori per le immagini destra e sinistra
		vector<ALLEGRO_BITMAP *> imagesx;
		int movDx=0; //indice dell'immagine del vector da renderizzare
		int movSx=0;
		bool dx=false,sx=true; // booleana che indica se ci stiamo muovendo a dx o a sx
	public:
		Player(int,Type);
		~Player();
		void move(int);
		void render();
		void die();

		void reset();
};
#endif