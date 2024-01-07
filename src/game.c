#include "game.h"
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;

    int width;
    int height;

    bool running;
};

Game *game_create(const char *title, int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return NULL;

    Game *game = malloc(sizeof(Game));

    if (!game)
        return NULL;

    game->window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );

    if (!game->window)
        return game;

    game->renderer = SDL_CreateRenderer(game->window, -1, 0);

    if (!game->renderer)
        return game;

    game->width = width;
    game->height = height;
    game->running = true;

    return game;
}

void game_run(Game *game)
{
    if (!game)
        return;

    SDL_Event event;

    while (game->running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) game->running = false;
        }
    }
}

void game_destroy(Game *game)
{
    if (game && game->renderer)
        SDL_DestroyRenderer(game->renderer);

    if (game && game->window)
        SDL_DestroyWindow(game->window);

    SDL_Quit();
    free(game);
}
