#ifndef LINKER_H
#define LINKER_H

#include <SDL2/SDL.h>
#include <vector>

struct Rect {
    SDL_Rect rect;
    Uint8 r, g, b, a;

    void draw(SDL_Renderer* renderer);

    std::vector<int> space_taken();

    bool collide_rect(const Rect& other_rect);

    bool collide_check(const std::vector<Rect>& a);
};

#endif