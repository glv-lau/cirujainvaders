#include SceneMenu.h

Class SceneMenu : public scene{
    public:
    SceneMenu();
    virtual void HandleEvent(const sf::event& event) override;
    virtual void update(Game &game) override;
    virtual void Draw(sf::RenderWindow &Window) override;
    private:
    sf:: font m_fuente;
    sf:: text m_titulo;
    sf:: text m_opciones;
    sf:: text m_exit;
};
