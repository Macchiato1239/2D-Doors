#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "linker.h"


typedef struct Rect {
    SDL_Rect rect;
    Uint8 r, g, b, a;

    // Draw method
    void draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }
    std::vector<int> space_taken(){
        int x = rect.x;
        int y = rect.y;
        int x1 = x+rect.w;
        int y1= y+rect.h;
        return {x,y,x1,y1};
    }


    //Collision check
    bool collide_rect(Rect other_rect) {        
        // left = rect.right > other.left
        bool collide_left = (rect.x + rect.w > other_rect.rect.x)  ;

        // right = rect.left < other.right
        bool collide_right = rect.x < (other_rect.rect.x + other_rect.rect.w);

        // up = rect.up < other.bottom -> rect.y>other.y+h
        bool collide_up = rect.y < (other_rect.rect.y+other_rect.rect.h) ;

        // down = rect.down > other.up ->rect.y+h > other.yas
        bool collide_down = (rect.y+rect.h) > other_rect.rect.y;

        bool colliding = (
            (collide_left == 1) && 
            (collide_right == 1) && 
            (collide_up == 1) && 
            (collide_down == 1)
        );


        //Collision Testing
        // std::cout << collide_left << collide_right << collide_down << collide_up << '\n';   
        return colliding;
    }
    bool collide_check(std::vector<Rect> a){
        for(int i=0; i<a.size(); i++){
            if (collide_rect(a[i])){
                return true;
            };
        };
        return false;
    } 
} Rect;
std::vector<Rect> entity={};




Rect rect1 = { {20, 20, 60, 60}, (Uint8)255, (Uint8)0, (Uint8)0, (Uint8)255 };

// Putting created hard material into a list for collision check, (on creation?)
//->
Rect wall1= {{200,200, 60,100}, (Uint8)0, (Uint8)255, (Uint8)0, (Uint8)255};
Rect wall2= {{400,250, 60,100}, (Uint8)0, (Uint8)255, (Uint8)0, (Uint8)255};



//SPEED
int speed_x = 30;
int speed_y = 30;

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





// MAIN MAIN MAIN MAIN MAIN




int main(int argc, char* argv[]) { //Places for execution 

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    bool running = true;
    entity.push_back(wall1);
    entity.push_back(wall2);
    SDL_Event event;

    while (running) {
  


        current_time=SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_q) {
                    running = false;
                };

                //Call collision check on movement results before confirmation
                //collide_check(vector)
                //If true, move the block right next to the walls
                //rect1.rect.y-overlap amount
                

                // moving up
                if (event.key.keysym.sym == SDLK_w) {
                    rect1.rect.y=std::max(top, rect1.rect.y-speed_y);
                // moving left
                };
                if (event.key.keysym.sym == SDLK_a) {
                    rect1.rect.x=std::max(left, rect1.rect.x-speed_x);
                // moving down
                };
                if (event.key.keysym.sym == SDLK_s) { 
                    rect1.rect.y=std::min(bottom-rect1.rect.h, rect1.rect.y+speed_y);
                };
                //moving right
                if (event.key.keysym.sym == SDLK_d) { 
                    rect1.rect.x=std::min(right-rect1.rect.w, rect1.rect.x+speed_x);
                };
            }
        }
        
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


//functions can be defined here or in other files