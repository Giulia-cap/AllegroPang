#include <stdio.h>
#include <allegro5/allegro.h>
#include "Player.h"
#include "Ball.h"
#include "Bullet.h"
#include "Object.h"
#include <iostream>
#include <vector>
#include "Game.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

using namespace std;

float FPS = 60;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_DISPLAY *display = NULL;
bool key[3] = { false, false ,false };  //Qui è dove memorizzeremo lo stato delle chiavi a cui siamo interessati.
bool redraw = true;
bool doexit = false;

Ball *b,*b2,*b3,*b4,*b5;
Bullet *bullet;

ALLEGRO_BITMAP * sfondo=NULL; //--> poi facciamo una lista di sfondi per ogni livello

Game::Game(int w, int h)
{
	int SCREEN_W=w;
	int SCREEN_H=h;
}

Game::~Game()
{
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
   al_destroy_display(display);
   delete b,b2,b3;
	delete player;
   delete bullet;
}

void Game::tick()
{
 
   ALLEGRO_EVENT ev;
   al_wait_for_event(event_queue, &ev);

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
               bullet=new Bullet(1,BULLET,player->getBouncer_x(),player->getBouncer_y());
               object.push_back(bullet);
               al_set_target_bitmap(al_get_backbuffer(display));
               bulletDelay=0;
            }

            bulletDelay++;
         }

         /*--------------------------MOVIMENTO-------------------------*/
         int i=0;
         for(vector<DynamicObject*>::iterator it=object.begin();it!=object.end();)
         {
            (*it)->move(SCREEN_W,SCREEN_H);
         /*------------------------------------------------------------*/

            /*------------------COLLISIONI-----------------------*/
            if((*it)->getType()==BALL)
            {
                  if((*it)->collision(player->getBouncer_x(),player->getBouncer_y(),player->BOUNCER_SIZE))
                  {
                     gameOver();
                     it++; i++;
                  }
                  else if(checkCollision(it))
                  {
                     if((*it)->BOUNCER_SIZE/2>=6)
                     {
                        b4=new Ball(1,BALL,(*it)->BOUNCER_SIZE/2,(*it)->getBouncer_x(),(*it)->getBouncer_y(),2,3);
                        b5=new Ball(1,BALL,(*it)->BOUNCER_SIZE/2,(*it)->getBouncer_x(),(*it)->getBouncer_y(),-2,3);
                        it=object.erase(it); //DISTRUGGO LA PALLA SE HA TOCCATO UN COLPO

                        object.push_back(b4);   
                        object.push_back(b5);
                     }
                     else
                      it=object.erase(it); //DISTRUGGO LA PALLA SE HA TOCCATO UN COLPO

                      al_set_target_bitmap(al_get_backbuffer(display));
                  }
                  else {it++; i++;}
            }
            else {it++; i++;} 
            /*----------------------------------------------------*/
            //cout<<"FOR 1:"<<i<<" "<<object.size()<<endl;
         }

         redraw = true;
      }
    

      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
         break;
      
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) //tasto premuto (lo stato del tasto nell'array si setta a true)
      {  
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

      else if(ev.type == ALLEGRO_EVENT_KEY_UP) //tasto rilasciato (si setta a false)
      {  
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
 int j=0;
      /*-------------------DRAW.......................................*/
      for(vector<DynamicObject*>::iterator it2=object.begin();it2!=object.end();)
      {
  
         if((*it2)->getType()==BULLET && (*it2)->getTtl()==0 )  {//((*it2)->getType()==BULLET&&(*it2)->getBouncer_x() > SCREEN_W || (*it2)->getType()==BULLET&&(*it2)->getBouncer_y() > SCREEN_H ) 
           it2=object.erase(it2); j++;}
          else 
          {
          	(*it2)->decreaseTtl();
            it2++; j++;
          }
    	 //cout<<"FOR2:"<<j<<" "<<object.size()<<endl;
     }
    // cout<<"SIZE: "<<object.size()<<endl;
     render();
      /*--------------------------------------------------------------*/
   if(object.size()!=0&&checkLevelOver()){ 
     // cout<<"LEVEL OVER";
      doexit=true;
   }
   }
  
}

void Game::render()
{
      if(redraw && al_is_event_queue_empty(event_queue)) 
      {
         redraw = false;

         al_clear_to_color(al_map_rgb(0,0,0));

         player->render();
      
         for(int i=0;i<object.size();i++){ //cout<<"FOR 3:"<<i<<" "<<object.size()<<endl;
            object[i]->render();
         }

         al_flip_display();

      }
}

void Game::generateBalls()
{

   b=new Ball(1,BALL,32,320,120,2,3),b2=new Ball(1,BALL,32,420,160,-2,4),b3=new Ball(1,BALL,32,120,220,2,-4);
   object.push_back(b);
   object.push_back(b2);
   object.push_back(b3);
   return;	
}

bool Game::checkCollision(vector<DynamicObject*>::iterator it )
{
  int i=0;
	for(vector<DynamicObject*>::iterator it2=object.begin();it2!=object.end();it2++)
  {
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
     i++;
    // cout<<"FOR 4:"<<i<<" "<<object.size()<<endl;
  }
   return false;
}

void Game::init()
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
//
   if(!al_init_image_addon()) {
       fprintf(stderr, "failed to create image!\n");
      return ;
   }
//

   //
   /*ALLEGRO_MONITOR_INFO disp_data;
   al_get_monitor_info(al_get_num_video_adapters()-1, & disp_data);
   
   SCREEN_W= (disp_data.x2 - disp_data.x1)-62;
   SCREEN_H= (disp_data.y2 - disp_data.y1)-60;
   //
   display = al_create_display(SCREEN_W, SCREEN_H);
   al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);*/
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

   //al_set_target_bitmap(player->image); -------->li ho commentati per inserire le immagini. Perchè se la carico da file l'immagine queste due istruzioni non ci vanno
   //al_clear_to_color(al_map_rgb(255, 0, 255));


   /*for(int i=0;i<object.size();i++)
   { 
      al_set_target_bitmap(object[i]->image);
      al_clear_to_color(al_map_rgb(255, 0, 255));
   }*/

   //
   sfondo=al_load_bitmap("./resources/sfondo1.bmp"); 
   //

   al_set_target_bitmap(al_get_backbuffer(display));

   event_queue = al_create_event_queue();

   if(!event_queue) 
   {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return;
   }

   //
 // al_init_image_addon();
  //

   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));

   al_register_event_source(event_queue, al_get_keyboard_event_source());

   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);	
}

void Game::gameOver()
{
	cout<<"YOU LOOOOOOOOOOSE!"<<endl;
   return;
}

bool Game::checkLevelOver()
{
   int numbBalls=0;
   if(object.size()!=0){
   for(vector<DynamicObject*>::iterator it2=object.begin();it2!=object.end();it2++)
      if((*it2)->getType()==BALL) numbBalls++;
   if(numbBalls==0) return true;
   }
   return false;
}
