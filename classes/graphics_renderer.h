#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

//Render graphics on screen
class GraphicsRenderer
{
    private:
        std::map<int, std::vector<sf::Sprite*>> m_sprite_map;
        std::map<int, std::vector<sf::Text>> m_text_map;
    public:
        //Add sprite to rendering. Priority is layer, the higher the more on top
        void gr_add_sprite_to_rendering(sf::Sprite* sprite, int priority);
        bool gr_remove_sprite_from_rendering(sf::Sprite*, int layer);

        //Add text to rendering
        void gr_add_text_to_rendering(sf::Text text, int priority);

        //Render frane with current state of the window
        void gr_render_whole_scene(sf::RenderWindow* window);

        //Constructor with initializers
        GraphicsRenderer()
        {
            //init layers map
            for(int i =0; i<10; i++)
            {
                m_sprite_map.insert(std::make_pair(i, std::vector<sf::Sprite*>()));
            }
        }
};
