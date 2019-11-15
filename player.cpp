
#include "Player.h"

Player::Player(Type t):DynamicObject(t)
{
	BOUNCER_SIZE=32;
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

  bouncer_x=(gameAreaW / 2.0) - (BOUNCER_SIZE / 2.0);
  bouncer_y=(gameAreaH - BOUNCER_SIZE );

  protezioneAttiva=false;

	if(!image)
		cout<<"ERROR TO LOAD IMMAGE";
}

Player::~Player()
{
}
   int moveAnimDelay=1.0f;
   int moveAnimRate=3.5f;
void Player::move(int k)
{
   if(k==0 && bouncer_x >= (BOUNCER_SIZE-10 )+4.0 ) //MOVIMENTO A SINISTRA
   {
   	  if(movSx<imagesx.size()-1&& moveAnimDelay>=moveAnimRate) {
        movSx++;
   	  	moveAnimDelay=0;
      }
   	  else {
        moveAnimDelay++;

        movSx=0;
      }
   	  dx=false;
   	  sx=true;
   	  movDx=0;

      bouncer_x -= 4.0;
   }

   if(k==1 && bouncer_x <= gameAreaW - (BOUNCER_SIZE +20) - 4.0) //MOVIMENTO A DESTRA
   {
   	  if(movDx<imagedx.size()-1 && moveAnimDelay>=moveAnimRate){
   	  	movDx++;
        moveAnimDelay=0;
      }
   	  else{
      moveAnimDelay++;
       movDx=0;
      }
   	  dx=true;
   	  sx=false;
   	  movSx=0;
   	  
      bouncer_x += 4.0;
   }
    // cout<<"MOVEANIMDELAY "<<moveAnimDelay<<" MOVERATE "<<moveAnimRate<<endl;

}

void Player::render()
{
	if(sx)
  		al_draw_bitmap(imagesx[movSx], bouncer_x, bouncer_y, 0);
  	else if(dx){
  		al_draw_bitmap(imagedx[movDx],bouncer_x, bouncer_y, 0);
    }

    if(protezioneAttiva)
      al_draw_bitmap(barriera,bouncer_x, bouncer_y, 0);
}

void Player::RemoveOneLife()
{
  if(life>0 ){
    if(!protezioneAttiva)
      life--;
    if(protezioneAttiva)
      protezioneAttiva=false;
  }
}

void Player::reset()
{ 
  life=3;
  bouncer_x=(gameAreaW / 2.0) - (BOUNCER_SIZE / 2.0);
  bouncer_y=(gameAreaH - BOUNCER_SIZE );
  protezioneAttiva=false;
}

int Player::getLife(){return life;}
void Player::setLife(int l){life=l;}
void Player::setProtezione(bool p){protezioneAttiva=p;}