#include <SFML/Graphics.hpp>
#include <iostream>
#include "classes/abstract_piece.h"
#include "classes/pieces.h"
#include "classes/graphics_renderer.h"
#include "classes/gameplay_controller.h"
#include "classes/game_ui_controller.h"

// FOR NOW COMPILATION IS MANUAL
// g++ -c main.cpp 
// g++ main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

//GameplayController
// implement game logic under make_move 

//Pieces
// implement black piece

// GameUiController
// implement moving
// implement tile calculations
// implement rounds 
// implement UI events
// implement buttons
// wire up with GraphicsRenderer

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    

    GraphicsRenderer graphicsRenderer;
    GameplayController gameplayController;
    GameUiController gameUiController(&graphicsRenderer, &gameplayController, &window);



    std::cout<<"BOARD"<<std::endl;
    auto b = gameplayController.gc_get_board();
    
    for (int i = 0; i<b.size(); i++)
    {
        std::cout<<i<<": ";
        for (int j = 0; j<b[0].size(); j++)
        {
            std::cout<<b[i][j]->pi_get_piece_color()<<" ";
            b[i][j]->set_sprite_position(i*64, j*64);
            if (b[i][j]->pi_get_piece_color() != PieceColor::dummy)
                graphicsRenderer.gr_add_sprite_to_rendering(b[i][j]->pi_get_sprite(), 1);
        }
        std::cout<<std::endl;
    }   
    std::cout<<"BOARD END"<<std::endl;


    // PieceWhite pcw;
    // pcw.pi_init_texture_and_sprite();
    // graphicsRenderer.gr_add_sprite_to_rendering(pcw.pi_get_sprite(), pcw.pi_get_render_priority());

    //b[9][0]->set_sprite_position(240, 120);
    //graphicsRenderer.gr_add_sprite_to_rendering(b[9][0]->pi_get_sprite(), 1);

    while (window.isOpen())
    {
        gameUiController.resolve_frame_events();
        graphicsRenderer.gr_render_whole_scene(&window); 

       // window.draw(*pcw.pi_get_sprite());
    }

   

    return 0;
}
