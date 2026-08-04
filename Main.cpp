
#include "Game.h"
#include "Match.h"

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    Game game(new Match());
    game.play();
    return 0;
}

