#include "snake.h"
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    SDL_Rect position;
    struct Node *next, *previous;
};

struct Snake {
    struct Node *head, *tail;
};

static bool empty(Snake *snake)
{
    return snake->head == NULL;
}

static bool push_front(Snake *snake, SDL_Rect position)
{
    struct Node *node = malloc(sizeof(struct Node));

    if (!node)
        return false;

    node->position = position;
    node->next = node->previous = NULL;

    if (empty(snake)) {
        snake->head = snake->tail = node;
    } else {
        node->next = snake->head;
        snake->head->previous = node;
        snake->head = node;
    }

    return true;
}

static bool push_back(Snake *snake, SDL_Rect position)
{
    if (empty(snake))
        return push_front(snake, position);

    struct Node *node = malloc(sizeof(struct Node));

    if (!node)
        return false;

    node->position = position;
    node->next = NULL;
    node->previous = snake->tail;
    snake->tail->next = node;
    snake->tail = node;

    return true;
}

Snake *snake_create(int length, int x, int y, int w, int h)
{
    Snake *snake = malloc(sizeof(Snake));

    if (!snake)
        return NULL;

    snake->head = snake->tail = NULL;
    
    for (int i = 0; i < length; i++) {
        SDL_Rect node = {x + (i * w), y, w, h};
        push_back(snake, node);
    }

    return snake;
}

void snake_destroy(Snake *snake)
{
    if (!snake)
        return;

    struct Node *node = snake->tail;

    while (node->previous != NULL) {
        struct Node *tmp = node;
        node = node->previous;
        free(tmp);
    }

    free(snake->head);
    free(snake);
}

void snake_render(Snake *snake, SDL_Renderer *renderer)
{
    struct Node *node = snake->head;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    while (node != NULL) {
        SDL_RenderFillRect(renderer, &node->position);
        node = node->next;
    }
}

void snake_move(Snake *snake, Direction direction)
{
    struct Node *node = snake->tail;

    while (node->previous != NULL) {
        node->position = node->previous->position;
        node = node->previous;
    }

    switch (direction) {
        case UP:
            snake->head->position.y -= snake->head->position.h;
        break;
        case DOWN:
            snake->head->position.y += snake->head->position.h;
        break;
        case LEFT:
            snake->head->position.x -= snake->head->position.w;
        break;
        case RIGHT:
            snake->head->position.x += snake->head->position.w;
        break;
    }
}
