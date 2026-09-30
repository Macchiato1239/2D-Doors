#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "linker.h"
#include <variant>


Rect rect1 = { {20, 20, 60, 60}, (Uint8)255, (Uint8)0, (Uint8)0, (Uint8)255 };

// Putting created hard material into a list for collision check, (on creation?)
//->
Rect wall1= {{200,200, 60,100}, (Uint8)0, (Uint8)255, (Uint8)0, (Uint8)255};
Rect wall2= {{400,250, 60,100}, (Uint8)0, (Uint8)255, (Uint8)0, (Uint8)255};



//SPEED
int speed_x = 5; //speed per second
int speed_y = 5; //speed per second

//BOUNDS

int window_height = 500;
int window_width = 700;

int left=0;
int top=0;
int bottom=window_height;
int right=window_width;

int frame_counter = 0;
int* frame_counter_ptr=&frame_counter;

Uint32 last_time = SDL_GetTicks();
Uint32 current_time;


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

    bool running = true;
    entity.push_back(wall1); //Wall for collision check
    entity.push_back(wall2);
    SDL_Event event;

    while (running) {
  
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) { //Have to use state instead of keydown
                if (event.key.keysym.sym == SDLK_q) {
                    running = false;
                };
            }
            //Moving up
        }
        if (key_state[SDL_SCANCODE_W]) {
            rect1.rect.y=std::max(top, rect1.rect.y-speed_y);
            Result result=Collision(rect1);
            if (!std::holds_alternative<bool>(result)){
                auto [x, y, w, h] =
                    std::get<std::tuple<int, int, int, int>>(result);

                rect1.rect.y=y+h;
            }
        // moving left
        };
        if (key_state[SDL_SCANCODE_A]) {
            rect1.rect.x=std::max(left, rect1.rect.x-speed_x);
            Result result=Collision(rect1);
            if (!std::holds_alternative<bool>(result)){
                auto [x, y, w, h] =
                std::get<std::tuple<int, int, int, int>>(result);

                rect1.rect.x=x+w;
            }
        // moving down
        };
        if (key_state[SDL_SCANCODE_S]) { 
            rect1.rect.y=std::min(bottom-rect1.rect.h, rect1.rect.y+speed_y);
            Result result=Collision(rect1);
            if (!std::holds_alternative<bool>(result)){
                auto [x, y, w, h] =
                std::get<std::tuple<int, int, int, int>>(result);

                rect1.rect.y=y-rect1.rect.h;
            }
        };
        //moving right
        if (key_state[SDL_SCANCODE_D]) { 
            rect1.rect.x=std::min(right-rect1.rect.w, rect1.rect.x+speed_x);
            Result result=Collision(rect1);
            if (!std::holds_alternative<bool>(result)){
                auto [x, y, w, h] =
                std::get<std::tuple<int, int, int, int>>(result);

                rect1.rect.x=x-rect1.rect.h;
            }
        };
        
        // Per frame code
        //this is only checking collision with 1 wall, check for all entities

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        rect1.draw(renderer);
        wall1.draw(renderer);
        wall2.draw(renderer);
        rect1.collide_check(entity);

        // push out frame
        (*frame_counter_ptr)++;
        current_time = SDL_GetTicks();
        if ((current_time-last_time)>=1000){
            double second = (current_time-last_time)/1000;
            double fps=(*frame_counter_ptr)/second;
            std::string fps_string=std::to_string(fps);
            last_time=current_time;
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
