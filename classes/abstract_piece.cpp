#include "abstract_piece.h"
#include <iostream>

int AbstractPiece::pi_get_move_direction()
{
    return m_move_direction;
}

void AbstractPiece::pi_set_move_direction(int direction)
{
    if (direction == 1 || direction == -1)
        m_move_direction = direction;
    else
        std::cerr<<"Bad direction value."<<std::endl;
}

bool AbstractPiece::pi_get_alive_status()
{
    return m_alive;
}

void AbstractPiece::pi_set_alive_status(bool new_status)
{
    m_alive = new_status;
}

sf::Sprite* AbstractPiece::pi_get_sprite()
{
    return m_sprite;
}

sf::Texture* AbstractPiece::pi_get_texture()
{
    return m_texture;
}

void AbstractPiece::pi_set_texture(sf::Texture* new_texture)
{
    m_texture = new_texture;
}

void AbstractPiece::pi_set_sprite(sf::Sprite* new_sprite)
{
    m_sprite = new_sprite;
}

void AbstractPiece::set_sprite_position(int row, int col)
{
    if(m_piece_color != PieceColor::dummy)
        m_sprite->setPosition(sf::Vector2f(col,row));
}

int AbstractPiece::pi_get_render_priority()
{
    return m_render_priority;
}

void AbstractPiece::pi_set_render_priority(int priority)
{
    m_render_priority = priority;
}

void AbstractPiece::pi_set_piece_color(PieceColor color)
{
    m_piece_color = color;
}

PieceColor AbstractPiece::pi_get_piece_color()
{
    return m_piece_color;
}
