#include "game.h"

int main(void)
{
    Game *game = game_create("Snake", 800, 600);

    game_run(game);
    game_destroy(game);

    return 0;
}
