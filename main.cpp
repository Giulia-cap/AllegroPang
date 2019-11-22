#include "includes.h"
#include "GameState.h"
#include "MenuState.h"
//#include "ScoreState.h"
#include "Scoreboard.h"

using namespace std;

bool esc=false; 
float resizeX=1;
float resizeY=1;


int SCREEN_W;
int SCREEN_H;
Scoreboard scores;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_TRANSFORM t;

enum _State{MENU=0, GAME,LEVEL1, LEVEL2, LEVEL3};
//_State state=MENU;
int state=0;

GameState *gamestate;
MenuState *menuState;

void init();
void tick();
void setState(int);

int main(int argc, char **argv)
{
   	init();


   return 0;
}

void init()
{

   if(!al_init()) {
         fprintf(stderr, "failed to initialize allegro!\n");
         return;
      }

    //
   ALLEGRO_MONITOR_INFO disp_data;
   al_get_monitor_info(al_get_num_video_adapters()-1, & disp_data);
   
   SCREEN_W= (disp_data.x2 - disp_data.x1);
   SCREEN_H= (disp_data.y2 - disp_data.y1);


  int w=1360 ;
  int h=768;
  resizeX = SCREEN_W / static_cast<float>(w);
  resizeY = SCREEN_H / static_cast<float>(h);
   
   display = al_create_display(SCREEN_W, SCREEN_H);
   al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
   //display = al_create_display(SCREEN_W, SCREEN_H);
   
   if(!display) 
   {
      fprintf(stderr, "failed to create display!\n");
      return;
   }

  al_identity_transform(&t);

  al_scale_transform(&t, resizeX, resizeY);

  al_use_transform(&t);

  event_queue = al_create_event_queue();

   if(!event_queue) 
   {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      return;
   }

   timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return;
     }

      if(!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return;
     }

     al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

   al_register_event_source(event_queue, al_get_display_event_source(display));

   al_clear_to_color(al_map_rgb(0,0,0));

   al_start_timer(timer);
   
   al_flip_display();
  
  gamestate = new GameState(display,event_queue,timer,SCREEN_W,SCREEN_H);
  menuState= new MenuState(display,event_queue,timer,SCREEN_W,SCREEN_H);

 // menuState->init();
  tick();

    al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_destroy_timer(timer);
 
  delete menuState;
  delete gamestate;
}

void tick()
{
   while(!esc)
   {
     gamestate->init();
      if(state==0)
      {
        gamestate->setLevel(1);
        menuState->init();
      }
      else 
      {
        gamestate->init();
        gamestate->tick();
      }
      
  }
 //scores.showScoreboard();
}

void setState(int s)
{
  state=(_State)s;
}