#include "linker.h"
#include <iostream>

void Rect::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
}

std::vector<int> Rect::space_taken() {
    int x = rect.x;
    int y = rect.y;
    int x1 = x + rect.w;
    int y1 = y + rect.h;

    return {x, y, x1, y1};
}

bool Rect::collide_rect(const Rect& other_rect) {

    bool collide_left =
        rect.x + rect.w > other_rect.rect.x;

    bool collide_right =
        rect.x < other_rect.rect.x + other_rect.rect.w;

    bool collide_up =
        rect.y < other_rect.rect.y + other_rect.rect.h;

    bool collide_down =
        rect.y + rect.h > other_rect.rect.y;

    return (
        collide_left &&
        collide_right &&
        collide_up &&
        collide_down
    );
}

bool Rect::collide_check(const std::vector<Rect>& a) {

    for (int i = 0; i < a.size(); i++) {

        if (collide_rect(a[i])) {
            return true;
        }
    }

    return false;
}