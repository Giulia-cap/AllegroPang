
#include "Player.h"

Player::Player(Type t):DynamicObject(t)
{
  life=3;
	image=al_load_bitmap("./resources/player/rightA.png");
	imagedx.push_back(image);
	image=al_load_bitmap("./resources/player/rightB.png");
	imagedx.push_back(image); 
	image=al_load_bitmap("./resources/player/leftA.png");
	imagesx.push_back(image);
	image=al_load_bitmap("./resources/player/leftB.png");
	imagesx.push_back(image); 
	image=al_load_bitmap("./resources/player/player.png");
  barriera=al_load_bitmap("./resources/player/barriera.png");
  dieImage=al_load_bitmap("./resources/player/die.png");

  bouncer_x=(gameAreaW / 2.0) - (BOUNCER_SIZE / 2.0);
  bouncer_y=(gameAreaH - BOUNCER_SIZE );

  protezioneAttiva=false;

	if(!image)
		cout<<"ERROR TO LOAD IMMAGE";
}

Player::~Player()
{
	 al_destroy_bitmap(barriera);
	 al_destroy_bitmap(dieImage);
}
   int moveAnimDelay=1.0f;
   int moveAnimRate=3.5f;
void Player::move()
{
	if(!lifeRemoved)
	{
	   if(direction==0 && bouncer_x >= (BOUNCER_SIZE-10 )+4.0 ) //MOVIMENTO A SINISTRA
	   {
	   	  if(movSx<imagesx.size()-1&& moveAnimDelay>=moveAnimRate) {
	        movSx++;
	   	  	moveAnimDelay=0;
	      }
	   	  else {
	        moveAnimDelay++; movSx=0;
	      }
	   	  movDx=0;
	      bouncer_x -= 4.0;
	   }

	   else if(direction==1 && bouncer_x <= gameAreaW - (BOUNCER_SIZE +20) - 4.0) //MOVIMENTO A DESTRA
	   {
	   	  if(movDx<imagedx.size()-1 && moveAnimDelay>=moveAnimRate){
	   	  	movDx++;
	        moveAnimDelay=0;
	      }
	   	  else{
	      moveAnimDelay++; movDx=0;
	      }
	   	  movSx=0;
	      bouncer_x += 4.0;
	   }
	}
}

void Player::render()
{
	if(direction==0&&!lifeRemoved)
		al_draw_bitmap(imagesx[movSx], bouncer_x, bouncer_y, 0);
	else if(direction==1&&!lifeRemoved)
		al_draw_bitmap(imagedx[movDx],bouncer_x, bouncer_y, 0);

    if(protezioneAttiva && !lifeRemoved)
      al_draw_bitmap(barriera,bouncer_x, bouncer_y, 0);
    else if(lifeRemoved){  
      al_draw_bitmap(dieImage,bouncer_x,bouncer_y+dieDelay,0);
      dieDelay++;
    }
    if(dieDelay>dieRate){
    dieDelay=0;
    lifeRemoved=false;
    respawn();  
    }
}

void Player::RemoveOneLife()
{
  if(life>0 ){
    if(!protezioneAttiva){
      life--;
      lifeRemoved=true;
    }
    if(protezioneAttiva)
      protezioneAttiva=false;
  }

}

void Player::reset()  
{ 
  lifeRemoved=false;
  life=3;
  protezioneAttiva=false;
}

int Player::getLife(){return life;}
void Player::setLife(int l){life=l;}
void Player::setProtezione(bool p){protezioneAttiva=p;}

void Player::respawn(){                                     
   bouncer_x=(gameAreaW / 2.0) - (BOUNCER_SIZE / 2.0);
  bouncer_y=(gameAreaH - BOUNCER_SIZE ); 
}