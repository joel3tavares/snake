#include "game.h"
#include "snake.h"
#include "food.h"
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;

    int width;
    int height;
    int fps;
    int fpsTime;
    int lastTick;
    bool running;

    Snake *snake;
    Food *food;
    Direction direction;
};

static void process_input(Game *game);
static void update_game(Game *game);
static void render(Game *game);

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

    game->lastTick = 0;
    game->fps = 20;
    game->fpsTime = 1000. / game->fps;
    game->width = width;
    game->height = height;
    game->direction = LEFT;
    game->snake = snake_create(2, width / 2, height / 2, 20, 20);
    game->food = food_create(20, 20, width, height);
    game->running = game->snake != NULL && game->food != NULL;

    return game;
}

void game_run(Game *game)
{
    if (!game)
        return;

    while (game->running) {
        process_input(game);
        update_game(game);
        render(game);
    }
}

void game_destroy(Game *game)
{
    if (game) {
        if (game->renderer)
            SDL_DestroyRenderer(game->renderer);

        if (game->window)
            SDL_DestroyWindow(game->window);

        if (game->snake)
            snake_destroy(game->snake);

        if (game->food)
            food_destroy(game->food);
    }

    SDL_Quit();
    free(game);
}

static void process_input(Game *game)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game->running = false;
            break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        game->direction = UP;
                    break;
                    case SDLK_DOWN:
                        game->direction = DOWN;
                    break;
                    case SDLK_LEFT:
                        game->direction = LEFT;
                    break;
                    case SDLK_RIGHT:
                        game->direction = RIGHT;
                    break;
                }
            break;
        }
    }
}

static void update_game(Game *game)
{
    // FPS
    int wait = game->fpsTime - (SDL_GetTicks64() - game->lastTick);

    if (wait > 0 && wait <= game->fpsTime)
        SDL_Delay(wait);

    game->lastTick = SDL_GetTicks64();
    // FPS

    snake_update(game->snake, game->direction, game->food);
    food_update(game->food);
}

static void render(Game *game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    snake_render(game->snake, game->renderer);
    food_render(game->food, game->renderer);

    SDL_RenderPresent(game->renderer);
}
