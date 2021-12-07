#include "gameplay_controller.h"
#include "abstract_piece.h"
#include <iostream>



GameplayController::GameplayController()
{
    //Init memory for vector
    for (int i =0; i<10; i++)
        m_board.push_back(std::vector<AbstractPiece*>(10));
    
    gc_load_start_setup();
}

void GameplayController::gc_eliminate_piece(std::pair<int, int> tile)
{
    if(get_reference_to_piece_at_board(tile.first, tile.second)->pi_get_piece_color() == PieceColor::white)
        m_eliminated_white_pieces += 1;
    else 
        m_eliminated_black_pieces += 1;

    set_reference_at_board( new PieceDummy(), tile.first, tile.second);
}

void GameplayController::gc_clear_board()
{
    for(int i =0; i<get_board_size(); i++)
        for (int j=0; j<get_board_size(); j++)
            set_reference_at_board(new PieceDummy(), i, j);
}

void GameplayController::gc_load_start_setup()
{
    //set black figures
    for(int i =0; i<4; i++)
        for(int col =0; col < 10; col++)
        {
            if(i % 2 == 0 && col %2 == 1)
                set_reference_at_board(new PieceBlack(), i, col);
            else if(i % 2 == 1 && col %2 == 0)
                set_reference_at_board(new PieceBlack(), i, col);
            else
                set_reference_at_board(new PieceDummy(), i, col);
        }

    //set dummy figures
    for(int i =4; i<6; i++)
        for(int col =0; col < 10; col++)
            set_reference_at_board(new PieceDummy(), i, col);
    
    //set white figures
    for(int i =6; i<10; i++)
        for(int col =0; col < 10; col++)
        {
            if(i % 2 == 0 && col %2 == 1)
                set_reference_at_board(new PieceWhite(), i, col);
            else if(i % 2 == 1 && col %2 == 0)
                set_reference_at_board(new PieceWhite(), i, col);
            else
                set_reference_at_board(new PieceDummy(), i, col);
        }
    
}

void GameplayController::gc_reset_game()
{
    gc_clear_board();
    m_eliminated_black_pieces = 0;
    m_eliminated_white_pieces = 0;
    gc_load_start_setup();
}

std::vector< std::vector<AbstractPiece*> > GameplayController::gc_get_board()
{
    return m_board;
}

bool GameplayController::gc_make_move(std::pair<int, int> from_tile, std::pair<int, int> to_tile)
{
    AbstractPiece* piece_moving = get_reference_to_piece_at_board(from_tile.first, from_tile.second);

    //Check if move is legal
    int move_direction = piece_moving->pi_get_move_direction();
        //TODO

    //If legal then do the move
    set_reference_at_board(new PieceDummy(), from_tile.first, from_tile.second);
    set_reference_at_board(piece_moving, to_tile.first, to_tile.second);
    
    
    //TODO
    return true;
}


AbstractPiece* GameplayController::gc_try_to_get_piece_at_coords(sf::Vector2f coords)
{
    for (int i=0; i<10; i++)
        for(int j=0; j<10; j++)
        {
            auto p = get_reference_to_piece_at_board(i,j);
            if (p->pi_get_piece_color() == PieceColor::dummy)
                continue;
            
            auto sp = p->pi_get_sprite();
            bool overlaps = sp->getGlobalBounds().contains(coords);

            std::cerr<<"Mouse at: "<< coords.x<<","<<coords.y<<std::endl;
            std::cerr<<"sprite at: "<< sp->getGlobalBounds().top<<std::endl;
            if (overlaps)
                return p;
        }
    return nullptr;
}