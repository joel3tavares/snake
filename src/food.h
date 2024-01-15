#ifndef FOOD_H
#define FOOD_H

#include <SDL2/SDL.h>

typedef struct Food Food;

Food *food_create(int w, int h, int screen_w, int screen_h);
void food_destroy(Food *food);
void food_render(Food *food, SDL_Renderer *renderer);
void food_update(Food *food);
void food_eat(Food *food);
SDL_Rect food_get_position(Food *food);

#endif
