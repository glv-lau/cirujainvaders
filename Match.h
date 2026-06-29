#ifdef Match_h
#define Match_h
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "Scene.h"
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

Class Match:public Scene{
    public:
    Match();
    void Update(Game &g) override;
    void Draw(RenderWindow &w) override;
    void add_score(int points){m_score=m_score+points;}
    int get_score(){return m_score;}
    private:
    Player m_player;
    vector<Enemy> m_wave;
    vector<Bullet> m_Bullet;
    int m_score;
}
#endif