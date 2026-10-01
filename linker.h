#ifndef LINKER_H
#define LINKER_H

#include <SDL2/SDL.h>
#include <vector>
//main.cpp
struct Rect { //Making cubes
    SDL_Rect rect;
    Uint8 r, g, b, a;

    void draw(SDL_Renderer* renderer);

    std::vector<int> space_taken();

    bool collide_rect(const Rect& other_rect);

    bool collide_check(const std::vector<Rect>& a);
};

extern Rect rect1;
extern Rect ground;

extern float speed_x;//speed per second
extern float speed_y;//speed per second

//how much y increases per loop

extern float jump_height;
extern float jump_time; //0.5 seconds or 500 ms
extern float jump_cd; //2s
extern Uint32 last_jump;
//BOUNDS

extern float window_height;
extern float window_width;

extern float left;
extern float top;
extern float bottom;
extern float right;



// CUBE.CPP
//COLLISION.CPP
extern std::vector<Rect> entity;
using Result = std::variant<bool, std::tuple<int, int, int, int>>;
extern Result Collision(Rect player);

//gravity.cpp
extern float dt;
extern float gravity;
extern void object_falling();


//state.cpp

enum State {
    walking=0,
    climbing=1,
    falling=2,
    jumping=3,
};
#endif