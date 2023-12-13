#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

SDL_Window* window;

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    window = SDL_CreateWindow(
        NULL, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOW_BORDERLESS
    );
    return true;
}

int main(int argc, char* arg[]) {
    if (!initialize_window()) {
        return -1;
    }
    return 0;
}