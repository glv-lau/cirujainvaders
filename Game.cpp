#include <iostream>
#include "Game.h"
#include <SFML/Window/Event.hpp>

using namespace sf;

Game::Game (Scene * e): m_win (VideoMode(800,600), "Ciruja Invaders"){
    m_win.setFramerateLimit(60);
    Scene *m_scene;
}

void Game::play (){
    while(m_win.isOpen()){
        Event e;
        while(m_win.pollEvent(e)){
            if(e.type==Event::Closed){
                m_win.close();
            }
            m_scene->update(*this);
            m_scene->draw(*this);
            m_win.display();
            if(m_prox){
                delete m_scene;
                m_scene = m_prox;
                m_prox= nullptr;
            }
        }

    }
}

Game::~Game(){
    delete m_scene;
}

void Game::SetScene (Scene * new_scene){
    m_prox= new_scene;
}