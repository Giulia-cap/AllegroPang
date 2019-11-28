#include <list>
#include "GameState.h"
#include "Scoreboard.h"
#include "Parrot.h"
#include <ctime>
#include <sstream>

bool key[3] = { false, false ,false };  //Qui è dove memorizzeremo lo stato delle chiavi a cui siamo interessati.
bool doexit,paused;
int ran;

Object *o1,*o2;
Scoreboard scoreboard;
//VARIABILI CHE SERVONO PER ATTIVARE I BONUS PRESI 
bool orologio,arpione,machineGun,arpionex2;

//-------------------------------------BLOCCO FUNZIONI 1----------------------------------------
GameState::GameState(ALLEGRO_DISPLAY * & d,ALLEGRO_EVENT_QUEUE * &e,ALLEGRO_TIMER * &t,int w,int h):State(d,e,t,w,h){}


GameState::~GameState()
{
  delete player;
  delete o1,o2;
  for(int i=0;i<7;i++)
    al_destroy_bitmap(sfondi[i]);
  al_destroy_bitmap(Vite);
  al_destroy_font(pangFont);
  al_destroy_font(pangFontBig);
}
//--------------------------------------------------------------------------------------------------------


//++++++++++++++++++++++++++++++++++BLOCCO FUNZIONI 2++++++++++++++++++++++++++++++++++++++++++++++++++++++
void GameState::init()
{
  if(level==1)
  {
     if(!al_init_image_addon()) {
         fprintf(stderr, "failed to create image!\n");
        return ;
     }
     al_init_font_addon(); al_init_ttf_addon();
     
    pangFont=al_load_ttf_font("pangFont.ttf",30,0 ); //il secondo paramentro è la size, il terzo il flag
    pangFontBig=al_load_ttf_font("pangFont.ttf",50,0 );
    if(!pangFont)
      cout<<"NO FONT";
   
     player=new Player(PLAYER);
     generateBalls();

     sfondi[0]=al_load_bitmap("./resources/sfondo1.png");
     sfondi[1]=al_load_bitmap("./resources/sfondo2.png");
     sfondi[2]=al_load_bitmap("./resources/sfondo3.png");
     sfondi[3]=al_load_bitmap("./resources/GameOver.jpg");
     sfondi[4]=al_load_bitmap("./resources/LevelCompleted.jpg");
     sfondi[5]=al_load_bitmap("./resources/GameCompleted.jpg");
     sfondi[6]=al_load_bitmap("./resources/paused.jpg");
     Vite=al_load_bitmap("./resources/bonus/protezione.png");
 }
  
      reset();

    al_set_target_bitmap(al_get_backbuffer(display));

    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();
}

void GameState::generateBalls()
{
  if(level==1)
  {
     object.push_back(new Ball(BALL,48,320,120,2,3));
     return;
  }
   else 
  {
    object.push_back(new Ball(BALL,48,100,100,2,3));
    object.push_back(new Ball(BALL,48,1000,120,2,-4));
    if(level==3)
     {
        object.push_back(new Ball(BALL,48,150,150,-2,4));
        o1=new Object(OBSTACLE);
        o1->setBouncer_x(450);
        o1->setBouncer_y(350);
        o2=new Object(OBSTACLE);
        o2->setBouncer_x(850);
        o2->setBouncer_y(320);
     }
     return;
  } 
  
}

void GameState::tick()
{
  while(!doexit)
  {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
      setKey(ev);
      if (gameOver())return; 
      if(checkLevelOver())
      { 
        if(level<3)
          level=level+1;
        else 
          state=2;     
        doexit=true;
        return;
      }  

      if(ev.type == ALLEGRO_EVENT_TIMER) 
      {
         /*-------------------MOVIMENTO PLAYER---------------------*/
         if(key[KEY_LEFT] )  
        { player->direction=0;
            player->move();
         }

         else if(key[KEY_RIGHT]){player->direction=1;
             player->move();
            }

         if(key[SPACE_BAR]&&!animalMalus)
         {
            if (bulletDelay >= firerate && !player->getLifeRemoved())
            {
              //cout<<getBulletsNumber()<<endl;
              if(!machineGun && getBulletsNumber()==0)
              {
                //bulletsNumber=0;
                 increaseBulletsNumber();
                object.push_back(new Weapons(WEAPONS,player->getBouncer_x(),player->getBouncer_y(),"hook"));
                al_set_target_bitmap(al_get_backbuffer(display));
                bulletDelay=0;
              }
              else if(machineGun)
              {
               //bulletsNumber=0;
                object.push_back(new Weapons(WEAPONS,player->getBouncer_x(),player->getBouncer_y()+32,"machineGun"));
                al_set_target_bitmap(al_get_backbuffer(display));
                bulletDelay=0;
                 increaseBulletsNumber();
              } 
              else if(arpionex2 && getBulletsNumber()<=1)
              {
                //bulletsNumber=0;
                 increaseBulletsNumber();
                object.push_back(new Weapons(WEAPONS,player->getBouncer_x(),player->getBouncer_y()+32,"hook"));
                al_set_target_bitmap(al_get_backbuffer(display));
                bulletDelay=0;
              }
            }

            bulletDelay++;
         }

         
         for(list<DynamicObject*>::iterator it=object.begin();it!=object.end();)
         {
           /*-----------------------------Animals manager--------------------------------------------*/
            if((*it)->getType()==ANIMAL)
            {
              if((*it)->getBouncer_x()>=0 && (*it)->getBouncer_x()<=gameAreaW) animalMalus=true; 
              else if((*it)->getBouncer_x()>=gameAreaW) {
                animalMalus=false;
                animalCount=0;
                it=object.erase(it); break;
                cout<<(*it)->getBouncer_x()<<" "<<gameAreaW<<endl;
              }
            }
            
          /*-----------------------------ttl manager--------------------------------------------*/
            if((*it)->getType()==WEAPONS && (*it)->getTtl()==0 )
            {  //((*it)->getType()==BULLET&&(*it)->getBouncer_x() > SCREEN_W || (*it)->getType()==BULLET&&(*it)->getBouncer_y() > SCREEN_H ) 
//FANNO LA STESSA COSA, SI PUÒ UNIRE    
              decreaseBulletsNumber();
              it=object.erase(it); break;
            }
            else 
            {
                (*it)->decreaseTtl();
                //it++;
            }
          /*-------------------------MOVIMENTO Object e gestione ttl-------------------------*/
            if((*it)->getType()==WEAPONS && !arpione && (*it)->dead)
            {
//CON QUESTA
                decreaseBulletsNumber();
                it=object.erase(it); break;
            }
            else if((*it)->getType()!=BALL)  //se abbiamo il potere dell'orologio le palle devono restare ferme
              (*it)->move();
            else if(orologio==false)
              (*it)->move();
         /*------------------------------------------------------------*/
            
           /*------------------COLLISIONI OBJECT-----------------------*/
            if(level==3) //collisone con gli obstacle
            {
              if(!(*it)->collisionWithObstacle(o1->getBouncer_x(), o1->getBouncer_y(), o1->BOUNCER_SIZEX, o1->BOUNCER_SIZE ))
                (*it)->collisionWithObstacle(o2->getBouncer_x(), o2->getBouncer_y(), o2->BOUNCER_SIZEX, o2->BOUNCER_SIZE );
            }
            if((*it)->getType()==BALL)
            { 
              BallCollision(it);
            }
            else it++; 
            /*----------------------------------------------------*/
         }

          //----------------COLLISIONI E MOVIMENTO BONUS---------------------
           for(list<Bonus*>::iterator it4=bonus.begin();it4!=bonus.end();)
            {
              (*it4)->move();
              //SE IL PLAYER PRENDE IL BONUS
               if((*it4)->collision(player->getBouncer_x(),player->getBouncer_y(),player->BOUNCER_SIZEX,player->BOUNCER_SIZE))
              {
                findPower((*it4)->bonusType);
                it4=bonus.erase(it4);
              }
              else it4++;
            }
        //-------------------------------------------------------------


         redraw = true;
      }
    

      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { esc=true; 
         return;}
    
    timerManager(); 
    render();
    hitDelay++;

      /*--------------------------------------------------------------*/

  }

   finish=true; 
}

void GameState::render()
{
      if(redraw && al_is_event_queue_empty(event_queue)) 
      {
         redraw = false;

         al_clear_to_color(al_map_rgb(0,0,0));

         al_draw_scaled_bitmap(sfondi[level-1], 0, 0, al_get_bitmap_width(sfondi[level-1]), al_get_bitmap_height(sfondi[level-1]), 0, 0, gameAreaW, gameAreaH+20, 1);

         player->render();
      
         for(list<DynamicObject*>::iterator it=object.begin();it!=object.end();it++){ //cout<<"FOR 3:"<<i<<" "<<object.size()<<endl;
              (*it)->render();
         }

        for(list<Bonus*>::iterator it2=bonus.begin();it2!=bonus.end();it2++){ //cout<<"FOR 3:"<<i<<" "<<object.size()<<endl;
            (*it2)->render(); 
         }

        if(level==3)
        {
          o1->render();
          o2->render();
        }

      drawBar();

      al_flip_display();

      }
}

void GameState:: drawBar()
{
  al_draw_text(pangFontBig, al_map_rgb(30, 80, 255), 500, 550,ALLEGRO_ALIGN_LEFT, "Time: "); //w h
  int lw=50;
  al_draw_text(pangFont, al_map_rgb(30, 80, 255), lw, 550,ALLEGRO_ALIGN_LEFT, "Life: ");
  for (int i=1;i<=player->getLife();i++)
    al_draw_bitmap(Vite,  lw*i, 600, 0);

  string t=convert(gameTime);
  al_draw_text(pangFontBig, al_map_rgb(30, 80, 255), 560, 600,ALLEGRO_ALIGN_LEFT, t.c_str());

  string s=convert(score);
  al_draw_text(pangFont, al_map_rgb(30, 80, 255), 1100, 550,ALLEGRO_ALIGN_LEFT,"Score: ");
  al_draw_text(pangFont, al_map_rgb(30, 80, 255), 1100, 600,ALLEGRO_ALIGN_LEFT,s.c_str());

  if(arpionex2)
    al_draw_text(pangFont, al_map_rgb(30, 80, 255), 50, 650,ALLEGRO_ALIGN_LEFT,"DOUBLE HARPOON");
  if(machineGun)
    al_draw_text(pangFont, al_map_rgb(30, 80, 255), 50, 650,ALLEGRO_ALIGN_LEFT,"MACHINEGUN");
  if(arpione)
    al_draw_text(pangFont, al_map_rgb(30, 80, 255), 50, 650,ALLEGRO_ALIGN_LEFT,"HOOKED HARPOON");
}

string GameState::convert(int i)
{
  string s;
  stringstream ss;
  ss<<i;
  s=ss.str();
  return s;
}

void GameState::setKey(ALLEGRO_EVENT ev)
{
  if(ev.type == ALLEGRO_EVENT_KEY_DOWN) //tasto premuto (lo stato del tasto nell'array si setta a true)
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

            case ALLEGRO_KEY_ESCAPE:
            paused=true;
            key[0]=false;
            key[1]=false;
            key[2]=false;
            OptionMenu(sfondi[6]);
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
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//----------------------------BLOCCO FUNZIONI 3--------------------------------------------------------
void GameState::BallCollision(list<DynamicObject*>::iterator &it)
{
  int posX=(*it)->getBouncer_x();
  int posY=(*it)->getBouncer_y();

    if((*it)->collision(player->getBouncer_x(),player->getBouncer_y(),player->BOUNCER_SIZEX,player->BOUNCER_SIZE))
    {
      if (hitDelay >= hitRate)
      {
      	if(orologio) orologio = false;
        player->RemoveOneLife();
        hitDelay=0;
         it++;
      }
    }
    else if(checkCollision(it)) //VEDE SE LA PALLA COLLIDE CON IL COLPO
    {
         if((*it)->BOUNCER_SIZE/2>=16) //CREA LE PALLE PICCOLE 
       {
          object.push_back(new Ball(BALL,(*it)->BOUNCER_SIZE-16,(*it)->getBouncer_x(),(*it)->getBouncer_y(),(*it)->bouncer_dx,(*it)->bouncer_dy));   
          object.push_back(new Ball(BALL,(*it)->BOUNCER_SIZE-16,(*it)->getBouncer_x(),(*it)->getBouncer_y(),-(*it)->bouncer_dx,(*it)->bouncer_dy));

          it=object.erase(it); //DISTRUGGO LA PALLA SE HA TOCCATO UN COLPO
       }
       else{
        it=object.erase(it); //DISTRUGGO LA PALLA SE HA TOCCATO UN COLPO
      score+=50; //aumento lo score se distruggo una pallina
      }
      //---------------CREO I BONUS RANDOMICAMENTE-------------//
      srand(time(NULL));
      createBonus(posX,posY);
      //-------------------------------------------------------//
        al_set_target_bitmap(al_get_backbuffer(display));
      return;
    }
    else it++;
  return;
}

bool GameState::checkCollision(list<DynamicObject*>::iterator it )
{
  for(list<DynamicObject*>::iterator it2=object.begin();it2!=object.end();)
  {
     {      
       if((*it2)->getType()==WEAPONS) 
       {
          Object *o=(*it2);
          if((*it)->collision(o->getBouncer_x(),o->getBouncer_y(),o->BOUNCER_SIZEX,o->BOUNCER_SIZE))
          {
             decreaseBulletsNumber();
             it2=object.erase(it2);
              //DISTRUGGO IL COLPO SE HA TOCCATO UNA PALLA
             return true;
          }
          if(!machineGun &&((*it)->getBouncer_x()< o->getBouncer_x()+((*it)->BOUNCER_SIZE/2)+3 && (*it)->getBouncer_x()+((*it)->BOUNCER_SIZE/2)+3>o->getBouncer_x()  && (*it)->getBouncer_y()>o->getBouncer_y()))
          {
            decreaseBulletsNumber();
             it2=object.erase(it2); //DISTRUGGO IL COLPO SE HA TOCCATO UNA PALLA
             return true;
          }
       }
     }
     it2++;
  }
   return false;
}
int bonusDropRate=60;
int bonusDropDelay=0;
void GameState::createBonus(int posX, int posY)
{
  ran=rand()%15; //10
  if( ran<=6 && bonus.size()<=3 && bonusDelay>bonusDropRate)
  {
    bonus.push_back(new Bonus(BONUS,ran,posX,posY));
    bonusDelay=0;
  }
  bonusDelay++;
}

void GameState::findPower(int t)
{
  switch(t)
  {
    case OROLOGIO:
      orologio=true;
      break;
    case ARPIONE:
      arpione=true;
      machineGun=false;
      arpionex2=false;
      break;
    case ARPIONEX2:
      machineGun=false;
      arpione=false;
      arpionex2=true;
      break;
    case MACHINEGUN:
      machineGun=true;
      arpione=false;
      arpionex2=false;
      break;
    case CLESSIDRA:
      gameTime+=15;
      break;
    case GIRANDOLA:
      player->setLife(player->getLife()+1);
      break;
    case PROTEZIONE:
      player->setProtezione(true);
      break;

  }
}

void GameState::timerManager()
{
    if(timeDelay>=timeRate)//GETSTISCE IL TEMPO IN GAME
    { 
      decreaseTime();
      timeDelay=0;

    }else timeDelay++;
  
    if(bonusDelay>=bonusRate)//GESTISCE IL TIMER DEL BONUS OROLOGIO PER FAR SBLOCCARE LE PALLE
    {
      orologio=false;
      bonusDelay=0;
    }
    else
    {
      bonusDelay++;
    }
     if(level==2)ran=rand()%630;
     if(level==3)ran=rand()%930;
     if( ran==3 && animalCount==0 && level !=1)
      {
        object.push_back(new Parrot(ANIMAL,-64));
        animalCount++;
      
      }
}



//++++++++++++++++++++++++++++BLOCCO FUNZIONI 4++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool GameState::gameOver()
{
  if(player->getLife()==0 || gameTime==0)
  {
    OptionMenu(sfondi[3]);
    return true;
  }
  return false;
}

void GameState::OptionMenu(ALLEGRO_BITMAP * sfondoMenuOption)
{
  bool condition=true;
  al_clear_to_color(al_map_rgb(0,0,0));
  while(condition)
    {
      al_draw_scaled_bitmap(sfondoMenuOption, 0, 0, al_get_bitmap_width(sfondoMenuOption), al_get_bitmap_height(sfondoMenuOption), 0, 0, SCREEN_W/resizeX, SCREEN_H/resizeY, 0);
      al_draw_text(pangFont, al_map_rgb(30, 80, 255), 50, 500,ALLEGRO_ALIGN_LEFT, "PRESS ENTER TO" );
      if(paused)
        al_draw_text(pangFont, al_map_rgb(30, 80, 255), 50, 550,ALLEGRO_ALIGN_LEFT, "CONTINUE");
      else
      al_draw_text(pangFont, al_map_rgb(30, 80, 255), 50, 550,ALLEGRO_ALIGN_LEFT, "TRY AGAIN");
      al_draw_text(pangFont, al_map_rgb(30, 80, 255), 450, 500,ALLEGRO_ALIGN_LEFT, "PRESS ESC TO EXIT ");
      al_draw_text(pangFont, al_map_rgb(30, 80, 255), 1000, 500,ALLEGRO_ALIGN_LEFT, "PRESS M TO");
      al_draw_text(pangFont, al_map_rgb(30, 80, 255), 1000, 550,ALLEGRO_ALIGN_LEFT,"RETURN TO MENU");

      al_flip_display();

      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
      if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        switch (ev.keyboard.keycode)
          {
            case ALLEGRO_KEY_ENTER:
              if(!paused){
                state=1;
                 doexit=true;
              }
              else paused=false;
              condition=false;
              break;
            case ALLEGRO_KEY_M:
              doexit=true;
              condition=false;
              state=0;
              break;
            case ALLEGRO_KEY_ESCAPE:
              esc=true;
              doexit=true;
              condition=false;
              break;
          }
    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
      { esc=true; 
       break;
     }

  }
}

bool GameState::checkLevelOver()
{
   int numbBalls=0;

   
   for(list<DynamicObject*>::iterator it2=object.begin();it2!=object.end();it2++)
      if((*it2)->getType()==BALL) 
        numbBalls++;
      //cout<<numbBalls<<endl;
     if(numbBalls==0 && level<3)
     {
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(sfondi[4], 0, 0, al_get_bitmap_width(sfondi[4]), al_get_bitmap_height(sfondi[4]), 0, 0, SCREEN_W, SCREEN_H, 0);
        al_draw_text(pangFont, al_map_rgb(30, 80, 255), 350, 500,ALLEGRO_ALIGN_LEFT, "Get ready for the next level" );
        al_flip_display();
        al_rest(3.0);
        increaseScore(gameTime);
        increaseScore((player->getLife())*100); // PIU VITE SONO RIMASTE PIU IL PUNTEGGIO SALE
        return true;
      }
      else if(numbBalls==0 && level==3)
      {
        scoreboard.addScore(score);
        OptionMenu(sfondi[5]);
      }
   return false;
}

void GameState::reset()
{
  key[0]=false;
  key[1]=false;
  key[2]=false;


  orologio=false;  
  arpione=false;
  machineGun=false;
  arpionex2=false;
  finish=false;
  redraw = true;
  doexit = false;
  firerate=10.0f; // quanto velocemente si puo sparare
  bulletDelay=10.0f; 
  hitRate=100.0f; //timer reverse, dopo essere stati colpiti 1 volta devono passare 10tick per poter essere ricolpiti
  hitDelay=10.0f; 
  timeRate=60.0f; //ogni 60tick scende 1 secondo
  timeDelay=0.0f;
  bonusRate=250.0f; //durata bonus orologio
  bonusDelay=0.0f;
  bulletsNumber=0; 
  gameTime =120;
  animalMalus=false; //malus dell'uccello
  player->reset();
  player->respawn();

  object.clear();
  bonus.clear();
  generateBalls();

}




