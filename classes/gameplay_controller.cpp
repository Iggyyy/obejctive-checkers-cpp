#include "gameplay_controller.h"
#include "abstract_piece.h"
#include "graphics_renderer.h"
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
    

    std::cout<<"BOARD"<<std::endl;
    
    
    for (int i = 0; i<m_board.size(); i++)
    {
        std::cout<<i<<": ";
        for (int j = 0; j<m_board[0].size(); j++)
        {
            std::cout<<m_board[i][j]->pi_get_piece_color()<<" ";
        }
        std::cout<<std::endl;
    }   
    std::cout<<"BOARD END"<<std::endl;


    AbstractPiece* piece_moving = get_reference_to_piece_at_board(from_tile.first, from_tile.second);
    int move_direction = piece_moving->pi_get_move_direction();
    
    bool is_attacking = false;
    if(abs(to_tile.second - from_tile.second) == 2 && abs(to_tile.first - from_tile.first) == 2)
    {
        is_attacking = true;
        //Check if can attack further
    }
    


    //Check if move is legal; if not return that it is illegal 
    std::cerr<<(to_tile.second > from_tile.second)<<move_direction<<std::endl;
    std::cerr<<(to_tile.second < from_tile.second)<<move_direction<<std::endl;
    //std::cerr<<!((to_tile.second > from_tile.second) && move_direction == 1)<<!((to_tile.second < from_tile.second) && move_direction == -1)<<std::endl;
    // 1. bad direction
    if( (to_tile.second > from_tile.second) && move_direction != 1 )
    {
        std::cerr<<"Bad direction"<<std::endl;
        return false;
    }
    if((to_tile.second < from_tile.second) && move_direction != -1 )
    {
        std::cerr<<"Bad direction"<<std::endl;
        return false;
    }
    // 2. taken
    if(is_tile_taken(to_tile))
    {
        std::cerr<<"Tile is taken"<<std::endl;
        return false;
    }
    // 3. isn't attacking and normal move is too long
    if(!is_attacking && ( abs(to_tile.second - from_tile.second) > 1 || abs(to_tile.first - from_tile.first) > 1) )
    {
        std::cerr<<"Too long move"<<std::endl;
        return false;
    }
    // 4. out of board
    if( to_tile.second >= 10 || to_tile.first >= 10 )
    {
        std::cerr<<"Moved out of the board"<<std::endl;
        return false;
    }
    // 5. placed at bad color
    if(to_tile.second % 2 == 0 && to_tile.first % 2 ==0
        || to_tile.second % 2 == 1 && to_tile.first%2 == 1)
    {
        std::cerr<<"Wrong tile color"<<std::endl;
        return false;
    }

    //If legal then do the move
    set_reference_at_board(new PieceDummy(), from_tile.second, from_tile.first);
    set_reference_at_board(piece_moving, to_tile.second, to_tile.first);

    //If there was an attack, remove enemy piece
    if(is_attacking)
    {
        int row = (from_tile.second + to_tile.second ) /2;
        int col = (from_tile.first + to_tile.first) /2;

        std::cerr<<"Attacking at row"<<row<<" col"<<col<<std::endl;
        m_ref_to_dead_piece = get_reference_to_piece_at_board(col, row);
        set_reference_at_board(new PieceDummy(), row, col);
    }
    
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

            //std::cerr<<"Mouse at: "<< coords.x<<","<<coords.y<<std::endl;
            //std::cerr<<"sprite at: "<< sp->getGlobalBounds().top<<std::endl;
            if (overlaps)
                return p;
        }
    return nullptr;
}

AbstractPiece* GameplayController::gc_get_dead_piece_pointer()
{
   AbstractPiece* to_return = m_ref_to_dead_piece;
    //m_ref_to_dead_piece = nullptr;
    //AbstractPiece* to_return = new PieceDummy();
    return to_return;
}

void GameplayController::gc_reset_dead_piece_pointer()
{
   m_ref_to_dead_piece = nullptr;
}