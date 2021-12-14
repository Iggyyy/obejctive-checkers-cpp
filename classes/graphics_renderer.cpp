#include "graphics_renderer.h"
#include "abstract_piece.h"
#include <iostream>


void GraphicsRenderer::gr_render_whole_scene(sf::RenderWindow* window)
{
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

    //Render all texts on consecutive layers
    for(auto record : m_text_map)
    {
        for(auto txt : record.second)
        {
            window->draw(*txt);
        }
    }


    window->display();

}

//Priority 0-board, 1-on board
void GraphicsRenderer::gr_add_sprite_to_rendering(sf::Sprite* sprite, int priority)
{
    m_sprite_map[priority].push_back(sprite);
    std::cerr<<"Added new sprite to rendering on layer: "<<priority<<std::endl;
}

void GraphicsRenderer::gr_add_text_to_rendering(sf::Text* text, int priority)
{
    
    std::cerr<<"Adress from renderer "<<text<<std::endl;
    
    m_text_map[priority].push_back(text);
    std::cerr<<"Added new text to rendering on layer: "<<priority<<std::endl;
}

bool GraphicsRenderer::gr_remove_sprite_from_rendering(sf::Sprite* sprite, int layer)
{
    std::cerr<<"Endte"<<std::endl;
    for(int i =0 ; i < m_sprite_map[layer].size(); i++)
    {
        if(m_sprite_map[layer][i] == sprite)
            {
                m_sprite_map[layer].erase(m_sprite_map[layer].begin() + i);
                std::cerr<<"Erased sprite from rendering"<<std::endl;
                return true;
            }
    }
    return false;
}



