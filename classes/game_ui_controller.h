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
        //Whose turn is now, 1-black, -1white
        int m_whose_turn = 1;
        bool m_has_to_attack = false;
        std::pair<int, int> m_has_to_attack_tile;
        sf::Sprite* m_highlighted_tile;
    protected:
        void update_mouse_coordinates();
        //Convert coords to row and col on board
        std::pair<int, int> coords_to_row_col(sf::Vector2f);
        void highlight_tile(std::pair<int, int> tile);
        void un_highlight_tile();
        void check_game_over();
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

