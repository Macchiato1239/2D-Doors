#include "linker.h"
#include <iostream>
#include <tuple>
#include <variant>
std::vector<Rect> entity={};
Result Collision(Rect player) {
    for (int i=0; i<entity.size(); i++){
        if (player.collide_rect(entity[i])) {
            return std::make_tuple(entity[i].rect.x, entity[i].rect.y,
             entity[i].rect.w, entity[i].rect.h);
        }
    }
    return false;
}