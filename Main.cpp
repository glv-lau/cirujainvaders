#include "Game.h"
#include "Match.h"
int Main (int argc, char *argc[]){
    Game g (new Match);
    g.play();
    return 0;
}