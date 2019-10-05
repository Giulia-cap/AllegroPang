#include <stdio.h>
#include <allegro5/allegro.h>
#include "Player.h"
#include "Balls.h"
#include "Bullet.h"
#include "Object.h"
#include <iostream>
#include <vector>
using namespace std;
 
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;

int bulletDelay=10.0f;
const int firerate=10.0f;

Player *player;
enum MYKEYS {
   KEY_LEFT, KEY_RIGHT , SPACE_BAR 
};

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

bool key[3] = { false, false ,false };  //Qui è dove memorizzeremo lo stato delle chiavi a cui siamo interessati.
bool redraw = true;
bool doexit = false;

vector<DynamicObject*> object;

/*-------------FUNZIONI................*/
void init();
void generateBalls();
void gameOver();
bool checkCollision(vector<DynamicObject*>::iterator  );

int main(int argc, char **argv)
{
   init();
  while(!doexit)
   {
      ALLEGRO_EVENT ev;
       al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) 
      {
         /*-------------------MOVIMENTO PLAYER---------------------*/
         if(key[KEY_LEFT] )  
            player->move(SCREEN_W,0);

         if(key[KEY_RIGHT])
             player->move(SCREEN_W,1);

         if(key[SPACE_BAR])
         {
            if (bulletDelay >= firerate)
            {
               Bullet *bullet=new Bullet(1,BULLET,player->getBouncer_x(),player->getBouncer_y());
               object.push_back(bullet);
               /*al_set_target_bitmap(bullet->image);---->vedi commento costruttore bullet
               al_clear_to_color(al_map_rgb(255, 0, 255));*/
               al_set_target_bitmap(al_get_backbuffer(display));
               bulletDelay=0;
            }
            bulletDelay++;
         }

         /*--------------------------MOVIMENTO-------------------------*/

         for(vector<DynamicObject*>::iterator it=object.begin();it!=object.end();)
         {
            (*it)->move(SCREEN_W,SCREEN_H);
         /*------------------------------------------------------------*/

            /*------------------COLLISIONI-----------------------*/
            if((*it)->getType()==BALL)
            {
                  if((*it)->collision(player->getBouncer_x(),player->getBouncer_y(),player->BOUNCER_SIZE)){
                     gameOver();
                   it++;
                  }
                  else if(checkCollision(it))
                    it=object.erase(it); //DISTRUGGO LA PALLA SE HA TOCCATO UN COLPO
                  else it++;
            }
            else it++;
            /*----------------------------------------------------*/

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

            case ALLEGRO_KEY_SPACE:
               key[SPACE_BAR]=true;
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

            case ALLEGRO_KEY_SPACE:
               key[SPACE_BAR]=false;
               break;

            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;

         }
      }

      /*-------------------DRAW.......................................*/
 
      if(redraw && al_is_event_queue_empty(event_queue)) 
      {
         redraw = false;

         al_clear_to_color(al_map_rgb(0,0,0));

         player->render();
      
         for(int i=0;i<object.size();i++)
            object[i]->render();

         al_flip_display();

      }
      /*--------------------------------------------------------------*/
  
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
   if(!display) 
   {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return;
   }
 
   player=new Player(3,PLAYER);
   player->setBouncer_x(SCREEN_W / 2.0 - player->BOUNCER_SIZE / 2.0);
   player->setBouncer_y(SCREEN_H - player->BOUNCER_SIZE );

   generateBalls();

   al_set_target_bitmap(player->image);
   al_clear_to_color(al_map_rgb(255, 0, 255));


 for(int i=0;i<object.size();i++)
   { 
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

      Balls *b=new Balls(1,BALL,32,320,120,2,3),*b2=new Balls(1,BALL,32,420,160,-2,4),*b3=new Balls(1,BALL,32,120,220,2,-4);

    object.push_back(b);
    object.push_back(b2);
    object.push_back(b3);
   return;
}

bool checkCollision( vector<DynamicObject*>::iterator  it)
{ 
  for(vector<DynamicObject*>::iterator it2=object.begin();it2!=object.end();it2++)
   {
      if((*it2)->getType()==BULLET) 
      {
         Object *o=(*it2);
         if((*it)->collision(o->getBouncer_x(),o->getBouncer_y(),o->BOUNCER_SIZE))
         {
            object.erase(it2); //DISTRUGGO IL COLPO SE HA TOCCATO UNA PALLA
            return true;
         }
      }
   }
   return false;
}

void gameOver()
{
   cout<<"YOU LOOOOOOOOOOSE!"<<endl;
   return;
}