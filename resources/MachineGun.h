#include "Weapons.h"
#ifndef MACHINEGUN_H
#define MACHINEGUN_H
class MachineGun:public Weapons  // colpi della mitragliatrice 
{
	public:
	MachineGun(Type,float,float);
	~MachineGun();
  	virtual void render(); 

};
#endif