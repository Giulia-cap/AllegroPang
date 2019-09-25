using namespace std;
#include "GameManager.h"

GameManager::GameManager(){display = NULL;}
GameManager::~GameManager(){}


void GameManager::init()
{

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return;
   }

   display = al_create_display(640, 480);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return;
   }

   al_clear_to_color(al_map_rgb(0,0,0));
   
   al_flip_display();

   al_rest(10.0);

   al_destroy_display(display);
}