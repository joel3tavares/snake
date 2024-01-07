#ifndef GAME_H
#define GAME_H

typedef struct Game Game;

Game *game_create(const char *title, int width, int height);
void game_run(Game *game);
void game_destroy(Game *game);

#endif
