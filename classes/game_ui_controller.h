#pragma once
#include <vector>
#include "abstract_piece.h"
#include "pieces.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
        //Vector of buttons with string etiquette and sprite
        std::vector< std::pair<std::string,sf::Sprite* > > m_ui_buttons;
        std::vector< std::pair<std::string,sf::Text* > > m_ui_texts;
        sf::Font m_font;

        //AUDIO
        //Sound volume 0-100
        float m_sound_volume = 50.f;
        sf::Sound m_sound_btn;
        sf::Sound m_sound_piece;
        sf::SoundBuffer m_btn_soundbfr;
        sf::SoundBuffer m_piece_soundbfr;
    protected:
        void update_mouse_coordinates();
        sf::Text* create_text(std::string name, std::string content, int pos_x, int pos_y, int character_size);
        //Convert coords to row and col on board
        std::pair<int, int> coords_to_row_col(sf::Vector2f);
        void highlight_tile(std::pair<int, int> tile);
        void un_highlight_tile();
        void check_game_over();
        //Broadcast to all predefined UI elements that particular piece was killed
        void piece_killed_ui_broadcast(PieceColor pclr);
        //Counter update
        void update_kill_counter(std::string color_string);
        //BUTTONS
        void exit_game();
        void reset_game();
        void toggle_sound();
        void load_audio();
        void play_sound(std::string sound_name);
    public:
        void load_board_tiles_and_add_to_render();
        void load_all_ui_background_visuals();
        void load_pieces();
        void resolve_frame_events();
        GameUiController(GraphicsRenderer* renderer_ref, 
                            GameplayController *gameplay_controller_ref,
                            sf::RenderWindow* window)
        {
            m_gameplay_controller_ref = gameplay_controller_ref;
            m_renderer_ref = renderer_ref;
            m_window = window;
            m_is_piece_grabbed = false;
            load_pieces();
            load_all_ui_background_visuals();
            load_board_tiles_and_add_to_render();
            //load_audio(); 

        }

};

