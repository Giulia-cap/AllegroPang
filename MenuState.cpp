#include "MenuState.h"
#include "includes.h"
#include "Scoreboard.h"
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_audio.h>

bool dexit;

ALLEGRO_VIDEO *video;
ALLEGRO_MIXER *mixer;
ALLEGRO_BITMAP *frame;
ALLEGRO_EVENT ev;
ALLEGRO_BITMAP *schermata,*schermata2;
ALLEGRO_BITMAP *image;

int alternator=0;
bool enableScoreState=false,enableTutorial=false;
Scoreboard s;

MenuState::MenuState(ALLEGRO_DISPLAY * & d,ALLEGRO_EVENT_QUEUE * &e,ALLEGRO_TIMER * &t,int w,int h):State(d,e,t,w,h){}

MenuState::~MenuState()
{
  //al_destroy_video(video);
  cout<<"distruttore";
  al_destroy_bitmap(schermata);
  al_destroy_bitmap(schermata2);

}

void MenuState::init()
{
	dexit=false;

	
     al_init_font_addon(); al_init_ttf_addon();
     
    pangFont=al_load_ttf_font("pangFont.ttf",30,0 ); //il secondo paramentro è la size, il terzo il flag
    pangFontBig=al_load_ttf_font("pangFont.ttf",50,0 );
    if(!pangFont)
      cout<<"NO FONT";
if(!al_init_image_addon()) {
         fprintf(stderr, "failed to create image!\n");
        return ;
     }
  //ALLEGRO_SAMPLE *intro_music = al_load_sample("resources/intro_music.ogg");
  
  std::string count = "1";
  std::string name = "resources/intro/intro";
  std::string png = ".png";
  std::string all_name;
  std::string buffer;
  bool done = false;
  int c = 0, i = 0;

 // al_reserve_samples(1);
  //al_play_sample(intro_music, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

  while (!done)
  {
    
    al_wait_for_event(event_queue, &ev);
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
      if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
        done = true;
    }
    else if (ev.type == ALLEGRO_EVENT_TIMER)
    {
      all_name = name + count + png;
    //  cout<<all_name<<endl;
      image = al_load_bitmap(all_name.c_str());
     // al_draw_bitmap(image, 0, 0, 0);
      al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 0, 0, SCREEN_W/resizeX, SCREEN_H/resizeY, 0);

      al_flip_display();
      al_clear_to_color(al_map_rgb(0, 0, 0));
      al_destroy_bitmap(image);
      c++;
      count.clear();
      count = std::to_string(c);
      count = buffer + count;
      ++i;
    }
    if (i == 60)
      done = true;
  }
  //al_destroy_sample(intro_music);
schermata=al_load_bitmap("./resources/press.png");
schermata2=al_load_bitmap("./resources/press2.png");

  if(!schermata)
    cout<<"no image";

  al_init_video_addon();

  al_clear_to_color(al_map_rgb(0,0,0));

  //al_start_timer(timer); 
 
  al_flip_display();

  tick();
}

void MenuState::tick()
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
              state=1;
              break;
              case ALLEGRO_KEY_ESCAPE:
              esc=true;
              dexit=true;
              cout<<"esc";
              break;
              case ALLEGRO_KEY_S:
              if(enableScoreState)
              enableScoreState=false;
              else enableScoreState=true;
              break;
              case ALLEGRO_KEY_T:
              if(enableTutorial)
              enableTutorial=false;
              else enableTutorial=true;
              break;
            }
            
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { esc=true;
	    	break;
	      }

      if(!dexit)
	     render();
    }
}

void MenuState::render()
{
if(enableTutorial){

  std::string count = "1";
  std::string name = "resources/tutorial/tutorial";
  std::string png = ".jpg";
  std::string all_name;
  std::string buffer;
  bool done = false;
  int c = 0, i = 0;

 // al_reserve_samples(1);
  //al_play_sample(intro_music, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

  while (!done)
  {
    
    al_wait_for_event(event_queue, &ev);
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
      if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
        done = true;
      enableTutorial=false;
      break;
    }
    else if (ev.type == ALLEGRO_EVENT_TIMER)
    {
      all_name = name + count + png;
    //  cout<<all_name<<endl;
      image = al_load_bitmap(all_name.c_str());
     // al_draw_bitmap(image, 0, 0, 0);
      al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 0, 0, SCREEN_W/resizeX, SCREEN_H/resizeY, 0);

      al_flip_display();
      al_clear_to_color(al_map_rgb(0, 0, 0));
      al_destroy_bitmap(image);
      c++;
      count.clear();
      count = std::to_string(c);
      count = buffer + count;
      ++i;
    }
    if (i == 933){
      done = true;
      enableTutorial=false;

    }
          //al_rest(1.0/60);

  }

}
if(enableScoreState){
  vector<string> score=s.readFromFile();
  al_clear_to_color(al_map_rgb(0,0,0));
   for(unsigned i=0;i<10;i++){
  //cout<<i+1<<": "<<score[i]<<endl;

  al_draw_text(pangFont, al_map_rgb(255, 0, 0), (SCREEN_W/2)-SCREEN_W/10, SCREEN_H-40,ALLEGRO_ALIGN_LEFT,"Press S to return ");
  al_draw_text(pangFont, al_map_rgb(30, 80, 255), (SCREEN_W/2)-SCREEN_W/10, 0,ALLEGRO_ALIGN_LEFT,"Best Scores: ");
  if(i==0)
  al_draw_text(pangFont, al_map_rgb(255, 0, 0), (SCREEN_W/2)-SCREEN_W/10, 50+i*50,ALLEGRO_ALIGN_LEFT,score[i].c_str());
  else if(i==1)  
  al_draw_text(pangFont, al_map_rgb(255, 69, 0), (SCREEN_W/2)-SCREEN_W/10, 50+i*50,ALLEGRO_ALIGN_LEFT,score[i].c_str());
  else if(i==2)
  al_draw_text(pangFont, al_map_rgb(255, 255, 0), (SCREEN_W/2)-SCREEN_W/10, 50+i*50,ALLEGRO_ALIGN_LEFT,score[i].c_str());
  else 
  al_draw_text(pangFont, al_map_rgb(30, 80, 255), (SCREEN_W/2)-SCREEN_W/10, 50+i*50,ALLEGRO_ALIGN_LEFT,score[i].c_str());

   }
    al_flip_display();


}else{
	al_clear_to_color(al_map_rgb(0,0,0));
   if(alternator%60==0) al_draw_scaled_bitmap(schermata2, 0, 0, al_get_bitmap_width(schermata2), al_get_bitmap_height(schermata2), 0, 0, SCREEN_W/resizeX, SCREEN_H/resizeY, 0);
 else al_draw_scaled_bitmap(schermata, 0, 0, al_get_bitmap_width(schermata), al_get_bitmap_height(schermata), 0, 0, SCREEN_W/resizeX, SCREEN_H/resizeY, 0);
alternator++;
if(alternator>1000)alternator=0;
    al_flip_display();
}
}
