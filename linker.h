#ifndef LINKER_H
#define LINKER_H

#include <SDL2/SDL.h>
#include <vector>
// CUBE.CPP
struct Rect { //Making cubes
    SDL_Rect rect;
    Uint8 r, g, b, a;

    void draw(SDL_Renderer* renderer);

    std::vector<int> space_taken();

    bool collide_rect(const Rect& other_rect);

    bool collide_check(const std::vector<Rect>& a);
};

//COLLISION.CPP
extern std::vector<Rect> entity;
using Result = std::variant<bool, std::tuple<int, int, int, int>>;
extern Result Collision(Rect player);
#endif