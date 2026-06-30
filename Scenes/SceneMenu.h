#ifndef SCENEMENU_H
#define SCENEMENU_H
#include "Scene.h"
using namespace sf;
class SceneMenu : public Scene{
    public:
    SceneMenu();
    virtual void HandleEvent(const sf::event& event) override;
    virtual void update(Game &game) override;
    virtual void Draw(sf::RenderWindow &Window) override;
    private:
    Font m_fuente;
    Text m_titulo;
    Text m_opciones;
    Text m_exit;
};
