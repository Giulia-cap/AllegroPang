#include "MenuState.h"
#include "includes.h"
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_audio.h>

bool dexit;
ALLEGRO_VIDEO *video;
 ALLEGRO_MIXER *mixer;
 ALLEGRO_BITMAP *frame;

ALLEGRO_BITMAP *schermata;

MenuState::MenuState(ALLEGRO_DISPLAY * & d,ALLEGRO_EVENT_QUEUE * &e,ALLEGRO_TIMER * &t,int w,int h):State(d,e,t,w,h){}

MenuState::~MenuState(){

}

void MenuState::init()
{
	dexit=false;


if(!al_init_image_addon()) {
         fprintf(stderr, "failed to create image!\n");
        return ;
     }
	schermata=al_load_bitmap("./resources/press.png");
	if(!schermata)
		cout<<"no image";
   al_init_video_addon();

   video=al_open_video("./resources/introvideo.ogv");
   if(!video) cout<<"NO VIDEO";

    al_register_event_source(event_queue, al_get_video_event_source(video));
    al_clear_to_color(al_map_rgb(0,0,0));

     al_start_timer(timer); 
 
   al_flip_display();
}

void MenuState::tick()
{
	while(!dexit)
    {
      	ALLEGRO_EVENT ev;
      	al_wait_for_event(event_queue, &ev);
      	//  frame = al_get_video_frame(video);

      //	al_start_video(video, al_get_default_mixer());

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

void MenuState::render()
{
	//al_start_video(video,0);
	/* float scaled_w = al_get_video_scaled_width(video);
   float scaled_h = al_get_video_scaled_height(video);
   ALLEGRO_BITMAP *frame = al_get_video_frame(video);

   float x = (al_get_display_width(display) - SCREEN_W) / 2;
  float y = (al_get_display_height(display) - SCREEN_H) / 2;*/

   //al_draw_scaled_bitmap(frame, 0, 0,al_get_bitmap_width(frame),al_get_bitmap_height(frame), x, y, SCREEN_W, SCREEN_H, 0);
 // al_draw_bitmap(video,0,0);
	al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_scaled_bitmap(schermata, 0, 0, al_get_bitmap_width(schermata), al_get_bitmap_height(schermata), 0, 0, SCREEN_W, SCREEN_H, 0);
    al_flip_display();
}

