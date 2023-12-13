#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

bool init_window(void);
int get_window_width(void);
int get_window_height(void);

void clear_color_buffer(uint32_t color);
void clear_z_buffer(void);
void render_color_buffer(void);

void draw_grid(void);

void destroy_window(void);
#endif