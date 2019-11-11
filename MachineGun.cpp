#include "MachineGun.h"

MachineGun::MachineGun(Type t,float posx ,float posy):Weapons(t,posx, posy)
{
    image=al_load_bitmap("./resources/machineGun.png");
}
MachineGun::~MachineGun()
{
}

void MachineGun::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
}

