#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "linker.h"


//SPEED
float speed_x = 300; //speed per second
float speed_y = 300; //speed per second
float dt;
//how much y increases per loop

float jump_height=600;
float jump_time=100; //0.5 seconds or 500 ms
float jump_cd=500; //2s
Uint32 last_jump=SDL_GetTicks();
//BOUNDS

float window_height = 500;
float window_width = 700;

float left=0;
float top=0;
float bottom=window_height;
float right=window_width;