#ifndef INCLUDES_H
#define INCLUDES_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include <stdio.h>
#include<iostream>
using namespace std;

#define gameAreaW 1360
#define gameAreaH 500
#define FPS 60

extern bool esc;
extern int state;
extern float resizeX;
extern float resizeY;

extern void setState(int);


#endif

