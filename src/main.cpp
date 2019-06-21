#include <string>
#include <iostream>
#include <pthread.h>
#include <chrono>
#include <SDL2/SDL.h>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <thread>

#include "game.h"
#include "key_event_manager.h"

#define M_PI       3.14159265358979323846
#define WIDTH 320 
#define HEIGHT 180
int width = WIDTH;
int height = HEIGHT;

std::mutex m;
std::condition_variable cv;

struct run_info{
    bool exited = false;
    bool allow_draw = true;
} run_state;
pthread_t raytracerThread;

int frame=0, timebase=0;
game g(WIDTH,HEIGHT);
 
void processNormalKeys(unsigned int key) {
    if(key > 0x7F) return;
    if (key == 27) {
        exit(0);
    }
    key_event_manager::get_instance()->set_key_press(char(key));
}


void processNormalKeysUp(unsigned int key) {
    if(key > 0x7F) return;
    key_event_manager::get_instance()->reset_key_press(char(key));
}

void *start_renderer(void *run_state){
    typedef std::chrono::high_resolution_clock Clock;
    int counter = 0;
    int msCounter = 0;
    int deltaTime = 0;
    run_info *state = ((run_info*) run_state);
    while(!state->exited){
        std::this_thread::sleep_for(std::chrono::milliseconds(33 - deltaTime/1000));
        auto t1 = Clock::now();

				std::lock_guard<std::mutex> lk(m);
				//UPDATE AND RENDER HERE
        g.tic();
				state->allow_draw = true;
        //Allow rendering
        auto t2 = Clock::now();
        
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        msCounter += deltaTime;
        counter++;
        if(counter == 30){
            counter++;
            std::cout << "fps: " << 1000000/((float) msCounter/(float)counter) << "fps"<< std::endl;
            counter = 0;
            msCounter = 0;
        }
    }
    pthread_exit(NULL);
}

void end_renderer(void){
    run_state.exited = true;
    printf("Trying to exit application now.\n");
    pthread_join(raytracerThread, NULL);
    printf("Renderer exited.\n");
}

int main(int argc, char **argv) {

    int threadC = pthread_create(&raytracerThread, NULL, start_renderer, (void*) &run_state);
    if(threadC){
        printf("Failed to create rendering thread, exiting.\n");
        exit(-1);
    } 
		//Initial window setup
    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &sdlWindow, &sdlRenderer);
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderPresent(sdlRenderer);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    SDL_RenderSetLogicalSize(sdlRenderer, WIDTH, HEIGHT);
		SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    SDL_RendererFlip flip = SDL_FLIP_VERTICAL;


		SDL_Event event;



		while(!run_state.exited){
			//std::lock_guard<std::mutex> lk(m);
			if(run_state.allow_draw && m.try_lock()){
				run_state.allow_draw = false;
				SDL_UpdateTexture(sdlTexture, NULL, g.get_framebuffer(), sizeof(char) * WIDTH);
				//SDL_RenderClear(sdlRenderer);
				SDL_RenderCopyEx(sdlRenderer, sdlTexture, NULL, NULL,0,NULL,flip);
				SDL_RenderPresent(sdlRenderer);
				m.unlock();
			}else{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			while(SDL_PollEvent(&event)){

				if (event.type == SDL_KEYUP){
          processNormalKeysUp(event.key.keysym.sym);
        }
				if (event.type == SDL_KEYDOWN){
					const char *c = SDL_GetKeyName(event.key.keysym.sym);
          std::string input(c);
          if(input == "Escape") {run_state.exited = true; end_renderer();}
          processNormalKeys(event.key.keysym.sym);
				}
			}
    }
    
    SDL_DestroyTexture(sdlTexture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
    return(0);
}
