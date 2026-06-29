#include <iostream>
#include "Game.h"
#include <SFML/Window/Event.hpp>

using namespace sf;

Game::Game (Scene * e): m_win (VideoMode(800,600), "Ciruja Invaders"){
    m_win.setFramerateLimit(60);
    m_esc= e;
}

void Game::play (){
    while(m-win.isopen()){
        Event e;
        while(m_win.pollEvent(e)){
            if(e.type==Event::Closed){
                m_win.close();
            }
            m_esc->update(*this);
            m_esc->draw(*this);
            m_win.display();
            if(m_prox){
                delete m_esc;
                m_esc = m_prox;
                m_prox= nullptr;
            }
        }

    }
}

Game::~Game(){
    delete m_esc;
}

void Game::changescene (scene * new_scene){
    m_prox= new_scene;
}