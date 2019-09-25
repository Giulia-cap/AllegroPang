#include <stdio.h>
#include <allegro5/allegro.h>
#include "Player.h"
#include "Balls.h"
#include "Object.h"
#include <iostream>
#include <vector>
using namespace std;
 
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;

Player *player;
enum MYKEYS {
   KEY_LEFT, KEY_RIGHT
};

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
float bouncer_y = SCREEN_H- BOUNCER_SIZE;
bool key[2] = { false, false };  //Qui è dove memorizzeremo lo stato delle chiavi a cui siamo interessati.
bool redraw = true;
bool doexit = false;

vector<Balls*> object;


/*-------------FUNZIONI................*/
void init();
void generateBalls();

int main(int argc, char **argv)
{
   init();
  while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
      /*----------------------------------------MOVIMENTO PALLE----------------------*/
   /*    for(int i=0;i<object.size();i++)
      {
         object[0]->move(SCREEN_W,SCREEN_H);
      }*/

      /*-------------------MOVIMENTO PLAYER---------------------*/
 
      if(ev.type == ALLEGRO_EVENT_TIMER) 
      {
         if(key[KEY_LEFT] && bouncer_x >= 4.0) {
            bouncer_x -= 4.0;
         }

         if(key[KEY_RIGHT] && bouncer_x <= SCREEN_W - BOUNCER_SIZE - 4.0) {
            bouncer_x += 4.0;
         }

         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {  //tasto premuto (lo stato del tasto nell'array si setta a true)
         switch(ev.keyboard.keycode) 
      {
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = true;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {  //tasto rilasciato (si setta a false)
         switch(ev.keyboard.keycode) 
         {
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = false;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               break;

            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
         }
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) 
      {
         redraw = false;

         al_clear_to_color(al_map_rgb(0,0,0));

         player->move(bouncer_x,bouncer_y);
 
         al_flip_display();

      }

        //al_flip_display();

      /*-------------------------------------------------------------------------------------------------------------*/
  
   }

   
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

   /*-----DELETE-------*/
   //delete player;  //----------->CREA L'ERRORE ALLA FINE!
   //delete object[0];
 
   return 0;
}


void init()
{
    if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return;
   }
 
   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return;
   }
 
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return;
   }
 
   player=new Player(3,PLAYER);

   generateBalls();

   al_set_target_bitmap(player->image);

   al_clear_to_color(al_map_rgb(255, 0, 255));


 for(int i=0;i<object.size();i++)
 	{ cout<<"ciao";
     	al_set_target_bitmap(object[i]->image);
       al_clear_to_color(al_map_rgb(255, 0, 255));
   }

   al_set_target_bitmap(al_get_backbuffer(display));

   event_queue = al_create_event_queue();

   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));

   al_register_event_source(event_queue, al_get_keyboard_event_source());

   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);

}


void generateBalls()
{
   Balls *b=new Balls(1,BALL,32);
   object.push_back(b);
   return;
}