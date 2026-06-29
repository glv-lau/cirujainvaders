#pragma once
#include "Entity.h"

struct vectord{
    float x;
    float y;
    vectord operator+(const vectord& o) const {
        return {x + o.x, y + o.y};
    }
    vectord operator*(float s) const {
        return {x * s, y * s};
    }
}
class Bullet : public Entity
{
    public:
        Bullet(const sf::Texture& tex, const sf::Vector2f& pos, const sf::Vector2f& vel),

        virtual void update(float dt) override{
            switch (m_pattern)
            {
            case 1:
                m_angle=90;
                m_position=(m_position + m_velocity) * dt;
                break;
            case 2:
                m_position=(m_position + m_velocity + m_angle) * dt;
                m_angle+=10;
                break;
            case 3:
                m_position=(m_position + m_velocity) * dt;
                m_angle-=10;
                break;
            default:
                break;
            }
            
        }
        bool GetState(){return m_type;}
    private:
    int m_pattern;
    bool m_type;
    vectord m_velocity;
    vectord m_position;
    float m_speed;
    float m_angle; //grados


};