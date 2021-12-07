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



