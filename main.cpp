#include <stdio.h>
#include <allegro5/allegro.h>
#include "Game.h"
#include <iostream>
using namespace std;

int livello=1;

int main(int argc, char **argv)
{
	Game game (640,480);
   	game.init();
   	game.tick();
   
   return 0;
}