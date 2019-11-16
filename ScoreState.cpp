#include "ScoreState.h"
#include "includes.h"
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_audio.h>

bool dexit;

 ALLEGRO_EVENT ev;
Scoreboard s();
ALLEGRO_BITMAP *schermata;
ScoreState::ScoreState(ALLEGRO_DISPLAY * & d,ALLEGRO_EVENT_QUEUE * &e,ALLEGRO_TIMER * &t,int w,int h):State(d,e,t,w,h){}

ScoreState::~ScoreState(){

}

void ScoreState::init()
{
	dexit=false;

	

if(!al_init_image_addon()) {
         fprintf(stderr, "failed to create image!\n");
        return ;
     }
    pangFont=al_load_ttf_font("pangFont.ttf",30,0 ); //il secondo paramentro è la size, il terzo il flag
    pangFontBig=al_load_ttf_font("pangFont.ttf",50,0 );
    if(!pangFont)
      cout<<"NO FONT";
    
schermata=al_load_bitmap("./resources/press.png");
  if(!schermata)
    cout<<"no image";
   al_init_video_addon();
    al_clear_to_color(al_map_rgb(0,0,0));

     al_start_timer(timer); 
 
   al_flip_display();

   tick();
}

void ScoreState::tick()
{
	while(!dexit)
    {
      	al_wait_for_event(event_queue, &ev);
      	if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
            switch (ev.keyboard.keycode)
            {
            	case ALLEGRO_KEY_ENTER:
          		dexit=true;
                break;
            }
            
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { esc=true;
	    	break;
	      }

	    render();
    }
}

void ScoreState:: render()
{
	vector<string> scores = s.readFromFile();
for(unsigned i=0;i<scores.size();i++)
  //al_draw_text(pangFont, al_map_rgb(30, 80, 255), 500, 550,ALLEGRO_ALIGN_LEFT,i+1);
  al_draw_text(pangFont, al_map_rgb(30, 80, 255), 500, 600,ALLEGRO_ALIGN_LEFT,scores[i].c_str());
  
}