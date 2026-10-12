#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "linker.h"



//W
// Actions: 
//1. push to entity (collision)
//2. push to door (room change)
//3. renderer(draw)

//each frame, loops through the list, 
Rect ground= {{0,400, 800,100}, (Uint8)0, (Uint8)0, (Uint8)0, (Uint8)255};
Rect wall1= {{300,350, 50,50}, (Uint8)0, (Uint8)0, (Uint8)0, (Uint8)255};
Rect wall2= {{370,300, 50,50}, (Uint8)0, (Uint8)0, (Uint8)0, (Uint8)255};



void Room::object_put(Rect object) {
    Room::objects.push_back(object);
};
void Room::interactive_put(Rect object) {
    Room::interactives.push_back(object);
};
// Render
void Room::render(SDL_Renderer* renderer){
    for (int i=0; i<objects.size(); i++){ //objects
        objects[i].draw(renderer);
    }
    for (int i=0; i<interactives.size(); i++){ //interactives
        interactives[i].draw(renderer);
    }
    if (has_next_door) {
        next_door.draw(renderer); //render the next door
    }

    if (has_prev_door) {
        prev_door.draw(renderer); // render the prev door
    }
};

void Room::room_entity(){ //Collision
    for (int i=0; i<objects.size(); i++){
        entity.push_back(objects[i]);
    }
};
//Room --> objects in that room are pushed into entities{} and then drawn
//Each objects are predefined first, then push_back --> copy into Room
//std::vector<int> room_collection()
//room's objects are pushed back at the start
//All rendering are done after all calculations
//Have a function that render the current room's objects, variable, so as to always render the current room only

//exiting and entering mechanism
//When entering door, player is tp'ed to the next door, in the middle of it, but they must not count as colliding
// Door should only work when player goes from being outside to overlapping with the door (colliding)
// It would not work when the player goes from overlapping with the door to overlapping with the door.