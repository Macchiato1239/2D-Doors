#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "linker.h"

//each frame, loops through the list, 
void Room::put(Rect object) {
    Room::objects.push_back(object);
};

void Room::render(SDL_Renderer* renderer){
    for (int i=0; i<objects.size(); i++){
        objects[i].draw(renderer);
    }
};

void Room::room_entity(){
    for (int i=0; i<objects.size(); i++){
        entity.push_back(objects[i]);
    }
};
//Room --> objects in that room are pushed into entities{} and then drawn
//Each objects are predefined first, then push_back --> copy into Room
//std::vector<int> room_collection()
//room's objects are pushed back at the start
//Have a function that render the current room's objects, variable, so as to always render the current room only

