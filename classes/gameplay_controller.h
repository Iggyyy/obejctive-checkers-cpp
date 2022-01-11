#pragma once
#include <vector>
#include <iostream>
#include "abstract_piece.h"
#include "pieces.h"




class GameplayController
{
    private:
        //Game board containing references to pieces
        std::vector< std::vector<AbstractPiece*> > m_board;
        int m_eliminated_white_pieces = 0, m_eliminated_black_pieces = 0;
        AbstractPiece* m_ref_to_dead_piece = nullptr;

        
        void set_reference_at_board(AbstractPiece* new_reference, int row, int col)
        {
            std::cerr<<"setting ref to "<<new_reference->pi_get_piece_color()<<" at: (row, col) "<<row<<" "<<col<<std::endl;
            m_board[row][col] = new_reference;
        }
        AbstractPiece* get_reference_to_piece_at_board(int row, int col)
        {
            //std::cerr<<"Getting ref at row"<<col<<" col"<<row<<""<<std::endl;
           
            return m_board[col][row];
        }
        int get_board_size()
        {
            return m_board.size();
        }
        bool is_tile_taken(std::pair<int, int> tile)
        { 
            
            if (m_board[tile.second][tile.first]->pi_get_piece_color() == PieceColor::dummy)
                return false;
            std::cerr<<"Tile "<<tile.second<<" "<<tile.first<<" is taken"<<std::endl;
            return true;
        }


    protected:
        //clear all references from board
        void gc_clear_board();
        //Destroy piece and populate eliminated counter
        void gc_eliminate_piece(std::pair<int, int> tile);
        //Load basic setup
        void gc_load_start_setup();
        //Check move
        bool check_move_legal(std::pair<int, int> from_tile, std::pair<int, int> to_tile, bool is_attacking, int move_direction);
        //Print Board
        void print_board();
    public:
        //clear all variables and references
        void gc_reset_game();
        //make move. return whether move was succesfull
        bool gc_make_move(std::pair<int, int> from_tile, std::pair<int, int> to_tile);
        //get whole board
        std::vector< std::vector<AbstractPiece*> > gc_get_board();
        //try to get piece at coords
        AbstractPiece* gc_try_to_get_piece_at_coords(sf::Vector2f coords); 
        AbstractPiece* gc_get_dead_piece_pointer();
        void gc_reset_dead_piece_pointer();
        std::pair<int, int> gc_check_if_has_to_attack(int player_turn_flag);
        bool gc_make_mandatory_attack_move(std::pair<int, int> from_tile, std::pair<int, int> to_tile, std::pair<int, int> attack_tile);
        //Return 0 if not, 1 if white won, 2 if black won
        int gc_is_game_done();
        //Check if create queen, if yes then do it
        void check_make_queen(AbstractPiece* moving_piece, std::pair<int, int> to_tile);
        bool move_queen(std::pair<int, int> from_tile, std::pair<int, int> to_tile);
        GameplayController();
};