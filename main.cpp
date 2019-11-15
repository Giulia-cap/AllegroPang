#include "includes.h"
#include "Game.h"

using namespace std;

bool esc=false; 
float resizeX=1;
float resizeY=1;

int main(int argc, char **argv)
{
	Game game (640,480);
   	game.init();
   
   return 0;
}