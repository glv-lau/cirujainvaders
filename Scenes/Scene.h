¬¬

#ifdef "Scene.h"
#define "Scene.h"
#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;
class game;

class scene{
    public:
    scene();
    virtual void HandleEvent(const sf::event& event)=0;
    virtual void update(Game &game)=0;
    virtual void Draw(sf::RenderWindow &Window) =0;
    virtual ~Scene() {};
    private:
};

#endif
