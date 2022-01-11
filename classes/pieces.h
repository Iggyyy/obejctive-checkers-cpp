#pragma once
#include <SFML/Graphics.hpp>
#include "abstract_piece.h"

class PieceWhite : public AbstractPiece
{
    private:
        //name of image in directory with extension
        std::string m_image_pathname = "white_piece.png";
    public:
        //load texture and setup sprite
        void pi_init_texture_and_sprite();
        //Constructor
        PieceWhite()
        {
            //define color
            pi_set_piece_color(PieceColor::white);
            //define move direction
            pi_set_move_direction(-1);
            //load visuals
            pi_init_texture_and_sprite();
        }
};

class PieceBlack : public AbstractPiece
{
    private:
        //name of image in directory with extension
        std::string m_image_pathname = "black_piece.png";
    public:
        //load texture and setup sprite
        void pi_init_texture_and_sprite();
        //Constructor
        PieceBlack()
        {
            //define color
            pi_set_piece_color(PieceColor::black);
            //define move direction
            pi_set_move_direction(1);
            //load visuals
            pi_init_texture_and_sprite();
        }
};

class PieceDummy : public AbstractPiece
{
    private:
        //name of image in directory with extension
        std::string m_image_pathname = "";
    public:
        //load texture and setup sprite
        void pi_init_texture_and_sprite()
        {
            //do nothing
        }
        //Constructor
        PieceDummy()
        {
            //define color
            pi_set_piece_color(PieceColor::dummy);
        }
};
