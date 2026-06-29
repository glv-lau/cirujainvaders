#ifdef Game_h
#define Game_h
#include "Scene.h"
#include "Match.h"
#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;
class Game {
    public:
    Game (Scene *e ,score 0);
    void play();
    ~Game();
	void SetScene(Scene *next_scene);

    private:
    int score;
    RenderWindow m_win;
    Scene *m_scene, *m_prox =nullptr;
};
#endif