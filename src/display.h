#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;
extern int window_width;
extern int window_height;

bool initialize_window(void);

void draw_pixel(int x, int y, uint32_t color);
void draw_grid(int grid_size, uint32_t grid_color, bool dotted);
void draw_rect(int x, int y, int width, int height, uint32_t color);

void clear_color_buffer(uint32_t color);
void render_color_buffer(void);

void destroy_window(void);
#endif
