#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "linker.h"
#include <variant>

bool rush_active=false;
bool rush_attacked=false;
int rush_spawn_x=0;
int rush_spawn_y=200;
Rect rush = {{0, 290, 50, 50}, (Uint8)0, (Uint8)176, (Uint8)50, (Uint8)255 };
std::vector<Rect> threats={rush};//this would create a copy of rush

//behavior: move from left to right, hit, rendering, colliding
//dont move it yet, append it to threats, if its in threats, it can deal damage
//Every frame i can move rush, but what about checking if it has hit player? --> check if it's in deaggro


//press R to summon rush

//Loop through the vector, check for collision | if collide, minus health, for now change color to purple
//Actually if collided, move it out of the threats vector
//
//Move from left to right, if hit right, stop, shift position every frame ig