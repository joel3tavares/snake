#ifndef SNAKE_H
#define SNAKE_H

#include "direction.h"
#include "food.h"
#include <SDL2/SDL.h>

typedef struct Snake Snake;

Snake *snake_create(int length, int x, int y, int w, int h);
void snake_destroy(Snake *snake);
void snake_render(Snake *snake, SDL_Renderer *renderer);
void snake_update(Snake *snake, Direction direction, Food *food);

#endif
