#include <stdio.h>
#include <allegro5/allegro.h>
#include "Game.h"
#include <iostream>
using namespace std;
 
int main(int argc, char **argv)
{
   Game game (640,480);
   game.init();
   game.tick();
   /*-----DELETE-------*/
   //delete player;  //----------->CREA L'ERRORE ALLA FINE!
   //delete object[0];
 
   return 0;
}