
#include "Game.h"
#include "Scenes/SceneMenu.h"

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    Game game(new SceneMenu());
    game.play();
    return 0;
}

