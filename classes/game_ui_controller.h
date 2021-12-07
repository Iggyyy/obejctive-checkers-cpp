#pragma once
#include <vector>
#include "abstract_piece.h"
#include "pieces.h"
#include <SFML/Graphics.hpp>
#include "graphics_renderer.h"
#include "gameplay_controller.h"

class GameUiController
{
    private:
        GraphicsRenderer* m_renderer_ref;
        GameplayController* m_gameplay_controller_ref;
        sf::Vector2i m_mouse_coords;
        sf::RenderWindow* m_window;
        std::pair<int, int> m_origin_tile;
        AbstractPiece* m_grabbed_piece;
        bool m_is_piece_grabbed = false;
    protected:
        void update_mouse_coordinates();
        //Convert coords to row and col on board
        std::pair<int, int> coords_to_row_col(sf::Vector2f);
    public:
        void load_board_tiles_and_add_to_render();
        void resolve_frame_events();
        GameUiController(GraphicsRenderer* renderer_ref, 
                            GameplayController *gameplay_controller_ref,
                            sf::RenderWindow* window)
        {
            m_gameplay_controller_ref = gameplay_controller_ref;
            m_renderer_ref = renderer_ref;
            m_window = window;
            m_is_piece_grabbed = false;
            load_board_tiles_and_add_to_render();

            
           
        }

};

