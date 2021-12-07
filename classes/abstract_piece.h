#pragma once
#include <SFML/Graphics.hpp>

enum PieceColor
{
    dummy,
    white,
    black
    
};

class AbstractPiece
{
    private:
        //1 is down -1 is up
        int m_move_direction; 
        //true - alive, false - dead
        bool m_alive = true;
        //piece texture
        sf::Texture* m_texture;
        //sprite texture
        sf::Sprite* m_sprite;
        //layer on which it should be rendered
        int m_render_priority;
        //piece color enum
        PieceColor m_piece_color;
    protected:
        void pi_set_piece_color(PieceColor color);
        void pi_set_move_direction(int direction);
    public:
        //return 1 if down and -1 if up
        int pi_get_move_direction();
        bool pi_get_alive_status();
        void pi_set_alive_status(bool new_status);
        //load and bound together sprite with its texture
        virtual void pi_init_texture_and_sprite() = 0;
        sf::Sprite* pi_get_sprite();
        sf::Texture* pi_get_texture();
        void pi_set_sprite(sf::Sprite*);
        void pi_set_texture(sf::Texture*);
        int pi_get_render_priority();
        void pi_set_render_priority(int priority);
        //get piece color
        PieceColor pi_get_piece_color();
        //Set sprite render position
        void set_sprite_position(int row, int col);
};

