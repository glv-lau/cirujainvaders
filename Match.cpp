#include "match.h"
#include <cmath>
#include <iostream>
#include "Game.h"
#include "wave.h"

using namespace std;

bool out_screen (bullet &b){
    Vector2f p= d.getPosition();
    if (p.x<0 or p.x>800) return true;
    if (p.y<0 or p.y>600) return true;
    return false;
}

void Match::update (Game &g){
    m_player.update();
    if (m_player.shooting()){
        m_Bullet.push_back(m_player.create_bullet());
    }
    for (Bullet &b:m_Bullets){
        if (hit(b,m_player)){
            m_player.loseLife();
            m_bullets.erase(b); //se destruye la bala
        }
        for (Enemy &e:m_Wave){
            if (hit(b,*e) and b.GetType==true){
           //el enemigo pierde vida por bol 
            e.loseLife();
           m_bullets.erase(b); //se destruye la bala
        }
        }
    }
    auto it=remove_if(m_Bullets.begin(),m_Bullets.end(), out_screen());
}

void Match::draw (RenderWindow & w) {
	w.clear(Color(220,220,180,255));
	m_Player.Draw(w);
	for (Enemy &e : m_wave){
        e.Draw(w);
    }
    
	for(Disparo &d : m_disparos){
        d.Draw(w);
    }
}