#include "linker.h"
#include <iostream>
//9,8m/s^2
//The player is constantly falling but the ground is stopping that, thanks to collision check
//It should not hinder movement, as well as jumping
//But i can not use -fall speed every frame
//Make it so that when falling, moving left or right becomes harder
//When jump, trigger a process of moving up, not just 1 frame but multiple
//Cant jump if on ground
//Keep a state: Jump, idle, walking, falling, moving up&down a ladder
float gravity=500; 

void object_falling(){
    if (state==State::jumping
    || state==State::hiding) {
        return;
    }
    rect1.rect.y+=gravity*dt;
    Result result = Collision(rect1);
    if (!std::holds_alternative<bool>(result)){
        state=State::walking;
        auto [x, y, w, h] =
        std::get<std::tuple<int, int, int, int>>(result);

        rect1.rect.y=y-rect1.rect.h;
        
    }
    else
    {
        state=State::falling;
    }
}



