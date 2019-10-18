#include "Game.h"

ALLEGRO_DISPLAY *display = NULL;

Game::Game(int w, int h)
{
  int SCREEN_W=w;
  int SCREEN_H=h;
}


Game::~Game()
{
  al_destroy_display(display);
  delete gamestate;
}

void Game::init()
{

   if(!al_init()) {
         fprintf(stderr, "failed to initialize allegro!\n");
         return;
      }

    //
   ALLEGRO_MONITOR_INFO disp_data;
   al_get_monitor_info(al_get_num_video_adapters()-1, & disp_data);
   
   SCREEN_W= (disp_data.x2 - disp_data.x1)-62;
   SCREEN_H= (disp_data.y2 - disp_data.y1)-60;
   //
   display = al_create_display(SCREEN_W, SCREEN_H);
   al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
   //display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) 
   {
      fprintf(stderr, "failed to create display!\n");
      return;
   }

   al_clear_to_color(al_map_rgb(0,0,0));
   
   al_flip_display();

   //al_set_target_bitmap(al_get_backbuffer(display));
 
  gamestate = new GameState(display,SCREEN_W,SCREEN_H);
  gamestate->init();

   tick();
}


void Game::tick()
{
  gamestate->tick();
}
