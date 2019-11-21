#include <list>
#include "GameState.h"
#include <ctime>
#include <sstream>

bool key[3] = { false, false ,false };  //Qui è dove memorizzeremo lo stato delle chiavi a cui siamo interessati.
bool doexit;
int ran;

Ball *b,*b2,*b3,*b4,*b5,*b6;
Obstacle *o1,*o2,*o3;
Weapons *bullet;
Bonus * newBonus;

//VARIABILI CHE SERVONO PER ATTIVARE I BONUS PRESI 
bool orologio,arpione,machineGun,arpionex2;

ALLEGRO_BITMAP * sfondi[5];

//-------------------------------------BLOCCO FUNZIONI 1----------------------------------------
GameState::GameState(ALLEGRO_DISPLAY * & d,ALLEGRO_EVENT_QUEUE * &e,ALLEGRO_TIMER * &t,int w,int h):State(d,e,t,w,h){}


GameState::~GameState()
{
  delete b,b2,b3,b4,b5;
  delete player;
  delete bullet;
  delete newBonus;
}
//--------------------------------------------------------------------------------------------------------


//++++++++++++++++++++++++++++++++++BLOCCO FUNZIONI 2++++++++++++++++++++++++++++++++++++++++++++++++++++++
void GameState::init()
{
  orologio=false;
  arpione=false;
  machineGun=false;
  arpionex2=false;
  finish=false;
  redraw = true;
  doexit = false;
  firerate=10.0f; // quanto velocemente si puo sparare
  bulletDelay=10.0f; 
  hitRate=10.0f; //timer reverse, dopo essere stati colpiti 1 volta devono passare 10tick per poter essere ricolpiti
  hitDelay=10.0f; 
  timeRate=60.0f; //ogni 60tick scende 1 secondo
  timeDelay=0.0f;
  bonusRate=500.0f; //durata bonus orologio
  bonusDelay=0.0f;
  

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
     sfondi[3]=al_load_bitmap("./resources/gameOver.png");
     sfondi[4]=al_load_bitmap("./resources/youWin.png");
 }
  // else
  // {
      reset();
  // }

    al_set_target_bitmap(al_get_backbuffer(display));

    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();
}

void GameState::generateBalls()
{
  if(level==1)
  {
     b=new Ball(BALL,32,320,120,2,3);
     object.push_back(b);
     return;
  }
   else 
  {

     b=new Ball(BALL,32,320,120,2,3),b2=new Ball(BALL,32,420,160,-2,4),b3=new Ball(BALL,32,120,220,2,-4);
     object.push_back(b);
     object.push_back(b2);
     object.push_back(b3);
     if(level==3)
     {
        b6=new Ball(BALL,32,320,350,2,-3);
        object.push_back(b6);
        o1=new Obstacle(OBSTACLE,450,220);
       //obstacle.push_back(o1);
        o2=new Obstacle(OBSTACLE,750,300);
       //obstacle.push_back(o2);
     }
     return;
  } 
  
}

void GameState::tick()
{
   while(!doexit)
   {

      //cout<<"OROLOGIO: "<<orologio<<"ARPIONE: "<<arpione<<"MACHINEGUN: "<<machineGun<<endl;
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
       if(checkLevelOver())
     { 
        if(level<3)
          level=level+1;
        else 
          state=2;     
        doexit=true;
        break;
     }  


      if(ev.type == ALLEGRO_EVENT_TIMER) 
      {
         /*-------------------MOVIMENTO PLAYER---------------------*/
         if(key[KEY_LEFT] )  
            player->move(0);

         if(key[KEY_RIGHT])
             player->move(1);

         if(key[SPACE_BAR])
         {
            if (bulletDelay >= firerate)
            {
              if(!machineGun && getBulletsNumber() ==0)
              {
                increaseBulletsNumber();
                bullet=new Weapons(WEAPONS,player->getBouncer_x(),player->getBouncer_y());
                object.push_back(bullet);
                al_set_target_bitmap(al_get_backbuffer(display));
                bulletDelay=0;
                //cout<<"sparo arpione"<<endl;
              }
              else if(machineGun)
              {
                bullet=new MachineGun(WEAPONS,player->getBouncer_x(),player->getBouncer_y()+32);
                object.push_back(bullet);
                al_set_target_bitmap(al_get_backbuffer(display));
                bulletDelay=0;
                //cout<<"sparo machineGun"<<endl;
              } 
              else if(arpionex2 && getBulletsNumber()<=1)
              {
                increaseBulletsNumber();
                bullet=new Weapons(WEAPONS,player->getBouncer_x(),player->getBouncer_y()+32);
                object.push_back(bullet);
                al_set_target_bitmap(al_get_backbuffer(display));
                bulletDelay=0;
              }
            }

            bulletDelay++;
         }

         /*-------------------------MOVIMENTO Object-------------------------*/
         for(list<DynamicObject*>::iterator it=object.begin();it!=object.end();)
         {
            if((*it)->getType()==WEAPONS && !arpione && (*it)->dead)
            {
              decreaseBulletsNumber();
              object.erase(it); break;
            }
            else if((*it)->getType()!=BALL)  //se abbiamo il potere dell'orologio le palle devono restare ferme
              (*it)->move(SCREEN_W);
            else if(orologio==false)
              (*it)->move(SCREEN_W);
         /*------------------------------------------------------------*/
            
           /*------------------COLLISIONI OBJECT-----------------------*/
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
              (*it4)->move(0);
              //SE IL PLAYER PRENDE IL BONUS
               if((*it4)->collision(player->getBouncer_x(),player->getBouncer_y(),player->BOUNCER_SIZE))
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
         break;}
    setKey(ev);
    TtlManager(); 
    render();
    hitDelay++;

      /*--------------------------------------------------------------*/
    
     //CONTROLLI TIMER GENERICI
   if(timeDelay>=timeRate){ //GETSTISCE IL TEMPO IN GAME
   		decreaseTime();
       // cout<<getMyTime()<<endl;
        timeDelay=0;
   }else{
        timeDelay++;
   }
  if(bonusDelay>=bonusRate)//GESTISCE IL TIMER DEL BONUS OROLOGIO PER FAR SBLOCCARE LE PALLE
  {
  	orologio=false;
  	bonusDelay=0;
  }else{
  	bonusDelay++;
  }
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
         /*for(list<Obstacle*>::iterator it3=obstacle.begin();it3!=obstacle.end();it3++)
            (*it3)->render();*/
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
    al_draw_text(pangFont, al_map_rgb(30, 80, 255), lw*i, 600,ALLEGRO_ALIGN_LEFT, "* ");

  string t=convert(gameTime);
  al_draw_text(pangFontBig, al_map_rgb(30, 80, 255), 560, 600,ALLEGRO_ALIGN_LEFT, t.c_str());

  string s=convert(score);
  al_draw_text(pangFont, al_map_rgb(30, 80, 255), 1100, 550,ALLEGRO_ALIGN_LEFT,"Score: ");
  al_draw_text(pangFont, al_map_rgb(30, 80, 255), 1100, 600,ALLEGRO_ALIGN_LEFT,s.c_str());
  
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
              doexit=true;
              esc=true;
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

  if(level==3)
  {
    if((o1)->collision((*it)->getBouncer_x(),(*it)->getBouncer_y(),(*it)->BOUNCER_SIZE)){
    if(o1->collisionX)
      (*it)->bouncer_dx=-((*it)->bouncer_dx);
    else 
      (*it)->bouncer_dy=-((*it)->bouncer_dy);
    o1->collisionX=false;
    o1->collisionY=false;}

    else if((o2)->collision((*it)->getBouncer_x(),(*it)->getBouncer_y(),(*it)->BOUNCER_SIZE)){
     if(o2->collisionX)
      (*it)->bouncer_dx=-((*it)->bouncer_dx);
    else 
      (*it)->bouncer_dy=-((*it)->bouncer_dy);
    o2->collisionX=false;
    o2->collisionY=false;}
  }

    if((*it)->collision(player->getBouncer_x(),player->getBouncer_y(),player->BOUNCER_SIZE)){
      if (hitDelay >= hitRate){
      player->RemoveOneLife();
      player->respawn();
      hitDelay=0;
      if (gameOver())return; 
       it++;
         }
    }
    else if(checkCollision(it)) //VEDE SE LA PALLA COLLIDE CON IL COLPO
    {
       if((*it)->BOUNCER_SIZE/2>=6) //CREA LE PALLE PICCOLE 
       {
          b4=new Ball(BALL,(*it)->BOUNCER_SIZE/2,(*it)->getBouncer_x(),(*it)->getBouncer_y(),(*it)->bouncer_dx,(*it)->bouncer_dy);
          b5=new Ball(BALL,(*it)->BOUNCER_SIZE/2,(*it)->getBouncer_x(),(*it)->getBouncer_y(),-(*it)->bouncer_dx,(*it)->bouncer_dy);
                                   // cout<<"POSIZIONE PALLA X:"<<(*it)->getBouncer_x()<<" Y:"<<(*it)->getBouncer_y()<<endl;

          it=object.erase(it); //DISTRUGGO LA PALLA SE HA TOCCATO UN COLPO

          object.push_back(b4);   
          object.push_back(b5);
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
              if((*it)->collision(o->getBouncer_x(),o->getBouncer_y(),o->BOUNCER_SIZE))
              {
                 decreaseBulletsNumber();
                 it2=object.erase(it2);
                  //DISTRUGGO IL COLPO SE HA TOCCATO UNA PALLA
                 return true;
              }
              if(!machineGun &&((*it)->getBouncer_x()<o->getBouncer_x()+5 && (*it)->getBouncer_x()>o->getBouncer_x()-5  && (*it)->getBouncer_y()>o->getBouncer_y()))
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

void GameState::createBonus(int posX, int posY)
{
   //FACCIAMO CHE SE ESCE 5(I TIPI DI BONUS SONO 5) IL BONUS NON DEVE USCIRE
      //ALTRIMENTI GENERIAMO UN BONUS E GLI PASSIAMO IL ran CHE SARÀ IL TIPO DI BONUS
      ran=rand()%9;
     if( ran<=6 && bonus.size()<=4)
      {
        newBonus=new Bonus(BONUS,ran,posX,posY);
        bonus.push_back(newBonus);

       // cout<<"HO CREATO UN BONUS "<<endl;
      }
}

void GameState::findPower(int t)
{
  if(t==OROLOGIO){
    orologio=true;
  }
  else if(t==ARPIONE){ 
    arpione=true;
    machineGun=false;
    resetBulletsNumber();
  }
  else if(t==MACHINEGUN){ 
    machineGun=true;
    arpione=false;
  }
  else if(t==ARPIONEX2)
  {
  	resetBulletsNumber();
    machineGun=false;
    arpione=false;
    arpionex2=true;
  }
  else if(t==CLESSIDRA)
  {
    gameTime+=15;
  }
  else if(t==GIRANDOLA)
  {
    player->setLife(player->getLife()+1);
  }
   else if(t==PROTEZIONE)
  {
    player->setProtezione(true);
  }

}

void GameState::TtlManager()
{
  for(list<DynamicObject*>::iterator it2=object.begin();it2!=object.end();)
      {
  
         if((*it2)->getType()==WEAPONS && (*it2)->getTtl()==0 ){  //((*it2)->getType()==BULLET&&(*it2)->getBouncer_x() > SCREEN_W || (*it2)->getType()==BULLET&&(*it2)->getBouncer_y() > SCREEN_H ) 
           decreaseBulletsNumber();
           it2=object.erase(it2); 
          }else 
          {
            (*it2)->decreaseTtl();
            it2++;
          }
      }
}



//++++++++++++++++++++++++++++BLOCCO FUNZIONI 4++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool GameState::gameOver(/*ALLEGRO_EVENT ev*/)
{

  if(player->getLife()==0 || gameTime==0)
    {
      //cout<<"YOUR SCORE: "<<score<<endl;
      bool gameOver=true;
      al_clear_to_color(al_map_rgb(0,0,0));

      while(gameOver)
      {
        al_draw_scaled_bitmap(sfondi[3], 0, 0, al_get_bitmap_width(sfondi[3]), al_get_bitmap_height(sfondi[3]), 0, 0, SCREEN_W/resizeX, SCREEN_H/resizeY, 0);
        al_draw_text(pangFont, al_map_rgb(30, 80, 255), 50, 500,ALLEGRO_ALIGN_LEFT, "PRESS ENTER TO" );
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
                doexit=true;
                gameOver=false;
                state=1;
                break;
              case ALLEGRO_KEY_M:
                doexit=true;
                gameOver=false;
                state=0;
                break;
              case ALLEGRO_KEY_ESCAPE:
                esc=true;
                doexit=true;
                gameOver=false;
                break;
            }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        { esc=true; 
         break;
       }

    }
   return true;
  }
  return false;
}

bool GameState::checkLevelOver()
{
   int numbBalls=0;

   if(object.size()!=0)
   {
     for(list<DynamicObject*>::iterator it2=object.begin();it2!=object.end();it2++)
        if((*it2)->getType()==BALL) 
          numbBalls++;
       if(numbBalls==0)
       {
          al_clear_to_color(al_map_rgb(0,0,0));
          al_draw_scaled_bitmap(sfondi[4], 0, 0, al_get_bitmap_width(sfondi[4]), al_get_bitmap_height(sfondi[4]), 0, 0, SCREEN_W, SCREEN_H, 0);
          al_flip_display();
          al_rest(4.0);
          increaseScore(gameTime);
          increaseScore((player->getLife())*100); // PIU VITE SONO RIMASTE PIU IL PUNTEGGIO SALE
          return true;
     } 

   }
   return false;
}

void GameState::reset()
{
  key[0]=false;
  key[1]=false;
  key[2]=false;
 

  player->reset();

  object.clear();
  bonus.clear();
  obstacle.clear();
  generateBalls();

  resetTime();
  resetBulletsNumber();
}




