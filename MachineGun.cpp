#include "MachineGun.h"

MachineGun::MachineGun(Type t,float posx ,float posy):Weapons(t,posx, posy)
{
	ttl=100;
	BOUNCER_SIZE=32;
	BOUNCER_SIZEX=32;
    image=al_load_bitmap("./resources/machineGun.png");
}
MachineGun::~MachineGun()
{
}

void MachineGun::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
	//al_draw_rectangle( bouncer_x,  bouncer_y, bouncer_x+BOUNCER_SIZEX, bouncer_y+BOUNCER_SIZE,
   //al_map_rgb(255, 0, 0), 1);
}

