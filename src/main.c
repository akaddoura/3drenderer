#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

#include "display.h"
#include "vector.h"

/**************************************
 * Declare an array of vectors/points *
 **************************************/
#define N_POINTS (9 * 9 * 9)
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];

vec3_t camera_position = { .x = 0.0f, .y = 0.0f, .z = -5.0f };
vec3_t cube_rotation = { .x = 0, .y = 0, .z = 0 };

float fov_factor = 640;

bool is_running = false;
int previous_frame_time = 0;

void setup() {
    // allocate the required memory in bytes to hold the color buffer
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

    // creating an SDL texture that is used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

    int point_count = 0;

    // start loading an array of vectors from -1 to 1 for a 9x9x9 cube
    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                const vec3_t new_point = { .x = x, .y = y, .z = z };
                cube_points[point_count++] = new_point;
            }
        }
    }
}   

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            is_running = false;
        }
        break;
    }
}

/*
 * projects a 3d vector to 2d
 */
vec2_t project(vec3_t point) {
    const vec2_t projected_point = {
        .x = (fov_factor * point.x) / point.z, // perspective divide
        .y = (fov_factor * point.y) / point.z
    };
    return projected_point;
}

void update() {

    // wait some time until we reach the target frame time in milliseconds
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    // delay execution if we are running too fast
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    previous_frame_time = SDL_GetTicks();

    cube_rotation.x += 0.01f;
    cube_rotation.y += 0.01f;
    cube_rotation.z += 0.01f;

    for (int i = 0; i < N_POINTS; ++i) {
        const vec3_t point = cube_points[i];

        vec3_t transformed_point = vec3_rotate_x(point, cube_rotation.x);
        transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y);
        transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);

        // translate the point away from the camera
        //camera_position.z += 0.00001f;
        transformed_point.z -= camera_position.z;

        //if (camera_position.z > 5.0f) {
        //    camera_position.z = -5.0f;
        //}

        // project the current point and save it
        const vec2_t projected_point = project(transformed_point);
        projected_points[i] = projected_point;
    }
}

void render() {
    draw_grid(10, 0x32323232, true);
    
    // loop through all projects points and render them
    for (int i = 0; i < N_POINTS; ++i) {
        const vec2_t projected_point = projected_points[i];
        draw_rect(
            projected_point.x + (window_width / 2),
            projected_point.y + (window_height / 2),
            4,
            4,
            0xFFFFFF00
        );
    }
    
    render_color_buffer();
    clear_color_buffer(0xFF000000);
    SDL_RenderPresent(renderer);
}

int main(int argc, char* arg[]) {
    is_running = initialize_window();

    setup();
    
    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
