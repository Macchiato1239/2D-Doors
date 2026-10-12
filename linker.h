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

struct Room {
    std::vector<Rect> objects;
    std::vector<Rect> interactives;

    Rect next_door;
    Rect prev_door;

    bool has_next_door = true;
    bool has_prev_door = true;

    void object_put(Rect object);
    void interactive_put(Rect object);
    void render(SDL_Renderer* renderer);
    void room_entity();
};


extern Rect rect1;
extern Rect ground;
extern Rect wall1;
extern Rect wall2;
extern Room room1;
extern Room room2;

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


//STATES

enum State {
    walking=0,
    climbing=1,
    falling=2,
    hiding=3,
    jumping=4,
};
//I have to set up a list, a state cant just switch to another without conditions.

enum enum_colliding {
    door,
    none,
};

extern enum_colliding current_colliding;

extern State state;
#endif
//I should check if collision happens when player is moved down (every loop), if it does then state=walking
//During walking state, player and jump
//Else state=falling, during falling, jump is disabled, and it is harder to move.