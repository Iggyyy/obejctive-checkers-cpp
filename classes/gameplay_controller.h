#pragma once
#include <vector>
#include "abstract_piece.h"
#include "pieces.h"




class GameplayController
{
    private:
        //Game board containing references to pieces
        std::vector< std::vector<AbstractPiece*> > m_board;
        int m_eliminated_white_pieces = 0, m_eliminated_black_pieces = 0;
        void set_reference_at_board(AbstractPiece* new_reference, int row, int col)
        {
            m_board[row][col] = new_reference;
        }
        AbstractPiece* get_reference_to_piece_at_board(int row, int col)
        {
            return m_board[row][col];
        }
        int get_board_size()
        {
            return m_board.size();
        }

    protected:
        //clear all references from board
        void gc_clear_board();
        //Destroy piece and populate eliminated counter
        void gc_eliminate_piece(std::pair<int, int> tile);
        //Load basic setup
        void gc_load_start_setup();
    public:
        //clear all variables and references
        void gc_reset_game();
        //make move. return whether move was succesfull
        bool gc_make_move(std::pair<int, int> from_tile, std::pair<int, int> to_tile);
        //get whole board
        std::vector< std::vector<AbstractPiece*> > gc_get_board();
        //try to get piece at coords
        AbstractPiece* gc_try_to_get_piece_at_coords(sf::Vector2f coords); 

        GameplayController();
};