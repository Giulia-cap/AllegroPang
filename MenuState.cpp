#include "MenuState.h"
#include "includes.h"
#include "Button.h"
#include <allegro5/allegro_video.h>

//ALLEGRO_EVENT_QUEUE *event_queue = NULL;
/*#define Blue al_map_rgb(0, 0, 255)
#define LightBlue al_map_rgb(30, 80, 255)
#define DarkBlue al_map_rgb(0, 0, 150)*/

//Button play_button(50, 20, Blue, 0, 20); //se non è schermo intero

bool dexit;
//int mouse_x,mouse_y;
/*bool left_mouse_button_down;
bool left_mouse_button_up;*/
ALLEGRO_VIDEO *video;
ALLEGRO_BITMAP *shermata;

MenuState::MenuState(ALLEGRO_DISPLAY * & d,ALLEGRO_EVENT_QUEUE * &e,ALLEGRO_TIMER * &t,int w,int h):State(d,e,t,w,h){}

MenuState::~MenuState(){

}

void MenuState::init()
{
	/*left_mouse_button_down = false;
	left_mouse_button_up = false;*/
	dexit=false;
// METTERE LA FUNZIONE CHE INIZIALIZZA LA TASTIERA DIRETTAMENTE IN GAME O IN STATE
/*	if(!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return;
     }*/

if(!al_init_image_addon()) {
         fprintf(stderr, "failed to create image!\n");
        return ;
     }
	shermata=al_load_bitmap("./resources/press.png");
	if(!shermata)
		cout<<"no image";
   al_init_video_addon();

   video=al_open_video("./resources/intro.mp3");
   if(!video) cout<<"NO VIDEO";

   //al_register_event_source(event_queue, al_get_mouse_event_source());

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

      	if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
            switch (ev.keyboard.keycode)
            {
            	case ALLEGRO_KEY_ENTER:
          		dexit=true;
                break;
            }
            
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
	    	break;
	      }

	    render();
    }
}

void MenuState::render()
{
	al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_scaled_bitmap(shermata, 0, 0, al_get_bitmap_width(shermata), al_get_bitmap_height(shermata), 0, 0, SCREEN_W, SCREEN_H, 0);
    al_flip_display();
}

/*void MenuState::tick()
{
    while(!dexit)
    {
      	ALLEGRO_EVENT ev;
      	al_wait_for_event(event_queue, &ev);

      	 if(ev.type == ALLEGRO_EVENT_TIMER) 
      	{		
      		redraw=true;
      	}

	    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
	    	break;
	      }

		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mouse_x = ev.mouse.x;
			mouse_y = ev.mouse.y;

			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			// left button 
			if (ev.mouse.button & 1)
			{
				left_mouse_button_down = true;
				redraw = true;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{ cout<<ev.mouse.x<<endl;
		cout<<ev.mouse.y<<endl; 
			// left button 
			if (ev.mouse.button & 1)
			{
				if((ev.mouse.x>350 || ev.mouse.x<100) || (ev.mouse.y<100 ||ev.mouse.y>250));
				else{
				left_mouse_button_down = false;
				left_mouse_button_up = true;
				redraw = true;
				press=true;
	    		dexit=true;}
	    	}
		}
		render();
	}

}*/


/*void MenuState::render()
{
	if(redraw && al_is_event_queue_empty(event_queue))
	{ 
		redraw = false;

         al_clear_to_color(al_map_rgb(0,0,0));

		if (play_button.MouseOverButton(mouse_x, mouse_y))
		{
			play_button.SetButtonColor(LightBlue);
			//button pressed 
			if (left_mouse_button_down)
			{
				play_button.pressed_button = true;
				play_button.SetButtonColor(DarkBlue);
			}
			// button released 
			else if (left_mouse_button_up)
			{
				play_button.pressed_button = false;
				play_button.StillPressingButton = false;
				play_button.SetButtonColor(Blue);

				//STARTING GAME NOW 
				press=true;
    			dexit=true;
					cout<<"tasto premuto!";
			}
		}
		play_button.DisplayButton();
		left_mouse_button_up = false;
		al_flip_display();
	
	}
}*/