#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "linker.h"
#include <variant>

Rect rect1 = { {20, 20, 20, 20}, (Uint8)255, (Uint8)64, (Uint8)64, (Uint8)255 };
//Render only the selected cubes
//x, y, w, h
// Putting created hard material into a list for collision check, (on creation?)
//->

// i am not satisfied with the game loop arrangement, can it be ran multithreaded?
enum_colliding current_colliding=enum_colliding::none; //

Room current_room; // use a dictionary

int room_counter=1;

// void assigning_room_data() {

// }

// STATES
State state=State::walking;


int frame_counter = 0;
int* frame_counter_ptr=&frame_counter;

Uint64 last_time = SDL_GetPerformanceCounter();
Uint64 current_time;
Uint32 fps_last_time=SDL_GetTicks();
Uint32 fps_current_time;


const Uint8* key_state = SDL_GetKeyboardState(NULL);

// MAIN MAIN MAIN MAIN MAIN
//
//


int main(int argc, char* argv[]) { //Places for execution 



    SDL_Init(SDL_INIT_VIDEO);
    //Create a window
    SDL_Window* window = SDL_CreateWindow(
        "Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        0
    );


    // Drawer

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (TTF_Init() == -1) {
        SDL_Log("SDL_ttf could not initialize: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    };
    
    TTF_Font* font = TTF_OpenFont("Font.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    bool running = true;

    // ROOM TESTING
    map[1].object_put(wall1); // genuinely do not have to do this, im just duplicating
    map[1].object_put(ground);// why would map[1] but room1 wont, unless the one in map{} is a copy
                     

    map[2].object_put(wall2);
    map[2].object_put(ground);

    SDL_Event event;

    while (running) {
        std::cout<< current_colliding;
        room1.has_prev_door = false;
        room2.has_next_door = false;

        if (room_counter==1) {
            current_room=map[1];}
        else if (room_counter==2) {
            current_room=map[2];
        }; //i prolly dont have to do this every frame, i can implement a method to trigger room change
            entity.clear();
            current_room.room_entity();

  
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) { //Have to use state instead of keydown
                if (event.key.keysym.sym == SDLK_q) {
                    running = false;
                };
                if (event.key.keysym.sym == SDLK_SPACE) {
                    if ((SDL_GetTicks()-last_jump)>jump_cd 
                    && (state==State::walking)) {
                        state=State::jumping;
                        last_jump=SDL_GetTicks();
                    }
                };
                if (event.key.keysym.sym == SDLK_h) {
                    std::cout<<"Hiding";
                    if (state==State::hiding) {
                        state=State::walking;
                    }
                    else if (state==State::walking) {
                        state=State::hiding;
                    }
                };
            }
        }
        //DELTA TIME
        Uint64 current_time = SDL_GetPerformanceCounter();






        //MOVEMENT
        //Moving up

        dt =
            (float)(current_time - last_time)
            / SDL_GetPerformanceFrequency();

        last_time = current_time;
        if (key_state[SDL_SCANCODE_W] && state!=State::falling) {
            rect1.rect.y=std::max(top, rect1.rect.y-speed_y*dt);
            Result result=Collision(rect1);
            if (!std::holds_alternative<bool>(result)){
                auto [x, y, w, h] =
                    std::get<std::tuple<int, int, int, int>>(result);

                rect1.rect.y=y+h;
            }
        // moving left, state: walking, falling
        };
        if (key_state[SDL_SCANCODE_A]
        && (state==State::walking 
        || state==State::falling 
        || state==State::jumping)) {
            rect1.rect.x=std::max(left, rect1.rect.x-speed_x*dt);
            Result result=Collision(rect1);
            if (!std::holds_alternative<bool>(result)){
                auto [x, y, w, h] =
                std::get<std::tuple<int, int, int, int>>(result);

                rect1.rect.x=x+w;
            }
        // moving down
        };
        if (key_state[SDL_SCANCODE_S]) { 
            rect1.rect.y=std::min(bottom-rect1.rect.h, rect1.rect.y+speed_y*dt);
            Result result=Collision(rect1);
            if (!std::holds_alternative<bool>(result)){
                auto [x, y, w, h] =
                std::get<std::tuple<int, int, int, int>>(result);

                rect1.rect.y=y-rect1.rect.h;
            }
        };
        //moving right
        if (key_state[SDL_SCANCODE_D]
        && (state==State::walking 
        || state==State::falling 
        || state==State::jumping)) { 
            rect1.rect.x=std::min(right-rect1.rect.w, rect1.rect.x+speed_x*dt);
            Result result=Collision(rect1);
            if (!std::holds_alternative<bool>(result)){
                auto [x, y, w, h] =
                std::get<std::tuple<int, int, int, int>>(result);

                rect1.rect.x=x-rect1.rect.w;
            }
        };


        //Falling
        object_falling(); 

        
        // JUMPING
        if (state == State::jumping) { 
            //I should make this an attribute of rect object, so to give other rects the same thing
            rect1.rect.y-=jump_height*dt;
            Result result=Collision(rect1);
            if (!std::holds_alternative<bool>(result)){
                auto [x, y, w, h] =
                std::get<std::tuple<int, int, int, int>>(result);

                rect1.rect.y=y+h;
            }

        }
        Uint32 cur_jump=SDL_GetTicks();

        if (state == State::jumping && (cur_jump-last_jump>=jump_time)){
            state=State::walking;
        }


//ROOOM
//I do not need to do this, do not need to reassign room value every loop, send signals every time changes happen
        if (rect1.collide_rect(current_room.next_door)){
            if (current_colliding !=enum_colliding::door){
                current_colliding = enum_colliding::door;
                room_counter+=1;
                rect1.rect.x=0;
            };
        }
        else if (rect1.collide_rect(current_room.prev_door)){
            if (current_colliding != enum_colliding::door){
            current_colliding = enum_colliding::door;
            room_counter-=1;
            rect1.rect.x=right-rect1.rect.w;
            };
        }
        else {
            current_colliding=enum_colliding::none;
        };
        //Moving to the next room
        //If current_colliding=None, switch to current_colliding=door
        //If not colliding with a door, current_colliding=None

        // Per frame code
        //this is only checking collision with 1 wall, check for all entities
        //Gravity
        //Keep player falling, but not a great idea




        // Rendering rendering rendering rendering rendering
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white
        SDL_RenderClear(renderer);




        // ground.draw(renderer);
        current_room.render(renderer);
        rect1.draw(renderer);
        // wall1.draw(renderer);
        // wall2.draw(renderer);

        // push out frame
        (*frame_counter_ptr)++;
        fps_current_time = SDL_GetTicks();
        if ((fps_current_time-fps_last_time)>=1000){
            double second = (fps_current_time-fps_last_time)/1000;
            double fps=(*frame_counter_ptr)/second;
            std::string fps_string=std::to_string(fps);
            fps_last_time=fps_current_time;
            *frame_counter_ptr = 0;
            SDL_SetWindowTitle(window, fps_string.c_str());
        }        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
