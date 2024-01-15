#include "food.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct Food {
    SDL_Rect position;
    int screen_w, screen_h;
    bool eaten;
};

Food *food_create(int w, int h, int screen_w, int screen_h)
{
    Food *food = malloc(sizeof(Food));

    if (!food)
        return NULL;

    srand(time(NULL));

    int x = rand() % screen_w;
    int y = rand() % screen_h;
    SDL_Rect position = {x, y, w, h};
    food->position = position;
    food->eaten = false;
    food->screen_w = screen_w;
    food->screen_h = screen_h;

    return food;
}

void food_destroy(Food *food)
{
    free(food);
}

void food_render(Food *food, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &food->position);
}

void food_update(Food *food)
{
    if (food->eaten) {
        food->position.x = rand() % food->screen_w;
        food->position.y = rand() % food->screen_h;
        food->eaten = false;
    }
}

void food_eat(Food *food)
{
    food->eaten = true;
}

SDL_Rect food_get_position(Food *food)
{
    return food->position;
}
