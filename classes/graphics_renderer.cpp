#include "graphics_renderer.h"
#include "abstract_piece.h"
#include <iostream>


void GraphicsRenderer::gr_render_whole_scene(sf::RenderWindow* window)
{

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

   
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }

    window->clear();
    

    //Render all sprites on consecutive layers
    for(auto record : m_sprite_map)
    {
        for(auto spr : record.second)
        {
            window->draw(*spr);
        }
    }


    window->display();

}

//Priority 0-board, 1-on board
void GraphicsRenderer::gr_add_sprite_to_rendering(sf::Sprite* sprite, int priority)
{
    m_sprite_map[priority].push_back(sprite);
}

bool GraphicsRenderer::gr_remove_sprite_from_rendering(sf::Sprite* sprite)
{
    std::cerr<<"Endte"<<std::endl;
    for(int i =0 ; i < m_sprite_map[1].size(); i++)
    {
        if(m_sprite_map[1][i] == sprite)
            {
                m_sprite_map[1].erase(m_sprite_map[1].begin() + i);
                std::cerr<<"Erased sprite from rendering"<<std::endl;
                return true;
            }
    }
    return false;
}



