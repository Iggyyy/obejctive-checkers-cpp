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

bool GameplayController::check_move_legal(std::pair<int, int> from_tile, std::pair<int, int> to_tile, bool is_attacking, int move_direction)
{
    //Check if move is legal; if not return that it is illegal 
    // 1. bad direction
    if( (to_tile.second > from_tile.second) && move_direction != 1 && !is_attacking)
    {
        std::cerr<<"Bad direction"<<std::endl;
        return false;
    }
    if((to_tile.second < from_tile.second) && move_direction != -1 && !is_attacking)
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

    return true;
}

void GameplayController::print_board()
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
}

bool GameplayController::move_queen(std::pair<int, int> from_tile, std::pair<int, int> to_tile)
{
    AbstractPiece* piece_moving = get_reference_to_piece_at_board(from_tile.first, from_tile.second);
    //Check if legal
    //Not taken
    if (is_tile_taken(to_tile))
        return false;
    //On diagonal
    if(abs(to_tile.first - from_tile.first) != abs(to_tile.second - from_tile.second)
            && from_tile != to_tile)
        return false;

    //Check if jumping only over one
    int x_dir = from_tile.first - to_tile.first > 0 ? 1 : -1;
    int y_dir = from_tile.second - to_tile.second> 0 ? 1 : -1;
    std::pair<int, int> current_tile = to_tile;
    current_tile.first += x_dir;
    current_tile.second += y_dir;

    int found_pieces =0;
    AbstractPiece* piece_to_kill;
    std::pair<int, int> attack_tile;
    std::cerr<<"Queen at: "<<from_tile.first<<" "<<from_tile.second<<std::endl;
    std::cerr<<"Queen goes to: "<<to_tile.first<<" "<<to_tile.second<<std::endl;
    while(current_tile.first != from_tile.first && current_tile.second != from_tile.second)
    {
        std::cerr<<"Check tiles: "<<current_tile.first<<" "<<current_tile.second<<std::endl;
        AbstractPiece* p = get_reference_to_piece_at_board(current_tile.first, current_tile.second);
        if(p->pi_get_piece_color() != PieceColor::dummy)
        {
            found_pieces++;
            piece_to_kill = p;
            attack_tile = current_tile;
        }

        if(p->pi_get_piece_color() == piece_moving->pi_get_piece_color())
            return false;

        current_tile.first += x_dir;
        current_tile.second += y_dir;
    }

    if (found_pieces > 1)
        return false;
    
    //MOVE
    set_reference_at_board(new PieceDummy(), from_tile.second, from_tile.first);
    set_reference_at_board(piece_moving, to_tile.second, to_tile.first);

    //ATTACK
    if (found_pieces == 1)
    { 
        std::cerr<<"Attacking at row"<<attack_tile.second<<" col"<< attack_tile.first<<std::endl;
        m_ref_to_dead_piece = piece_to_kill;
        set_reference_at_board(new PieceDummy(), attack_tile.second, attack_tile.first);
    }

    return true;
}

bool GameplayController::gc_make_move(std::pair<int, int> from_tile, std::pair<int, int> to_tile)
{
    print_board();

    AbstractPiece* piece_moving = get_reference_to_piece_at_board(from_tile.first, from_tile.second);
    int move_direction = piece_moving->pi_get_move_direction();

    if (piece_moving->is_queen())
    {
        std::cerr<<"Try to move queen"<<std::endl;
        bool moved = move_queen(from_tile, to_tile);
        return moved;
    }

    bool is_attacking = false;
    int attack_row, attack_col; 
    if(abs(to_tile.second - from_tile.second) == 2 && abs(to_tile.first - from_tile.first) == 2)
    {
        attack_row = (from_tile.second + to_tile.second ) /2;
        attack_col = (from_tile.first + to_tile.first) /2;

        if(get_reference_to_piece_at_board(attack_col, attack_row)->pi_get_piece_color() 
            == piece_moving->pi_get_piece_color())
        {
            std::cerr<<"Cannot attack your piece"<<std::endl;
            return false;
        }

        is_attacking = true;
        //Check if can attack further
    }
    
    //Check if move is legal
    bool legal = check_move_legal(from_tile, to_tile, is_attacking, move_direction);
    if (legal == false)
        return false;
    
    //If legal then do the move
    set_reference_at_board(new PieceDummy(), from_tile.second, from_tile.first);
    set_reference_at_board(piece_moving, to_tile.second, to_tile.first);

    //If there was an attack, remove enemy piece
    if(is_attacking)
    {
        std::cerr<<"Attacking at row"<<attack_row<<" col"<<attack_col<<std::endl;
        m_ref_to_dead_piece = get_reference_to_piece_at_board(attack_col, attack_row);
        set_reference_at_board(new PieceDummy(), attack_row, attack_col);
    }
    
    return true;
}

void GameplayController::check_make_queen(AbstractPiece* moving_piece, std::pair<int, int> to_tile)
{
    //is on the edge
    if ((to_tile.second == 0 && moving_piece->pi_get_piece_color() == PieceColor::white )
        || (to_tile.second == 9 && moving_piece->pi_get_piece_color() == PieceColor::black))
    {
        moving_piece->change_to_queen();
    }   
}

bool GameplayController::gc_make_mandatory_attack_move(std::pair<int, int> from_tile, std::pair<int, int> to_tile, std::pair<int, int> attack_tile)
{
    std::cerr<<"sss"<<attack_tile.second<<" "<<from_tile.first<<" "<<to_tile.first<<std::endl;
    //Check if player choosed to attack mandatory target
    if (!(attack_tile.first == to_tile.first && attack_tile.second == to_tile.second))
    {
        std::cerr<<"Player has to attack highlighted tile!!!"<<attack_tile.second<<" "<<attack_tile.first<<std::endl;
        return false;
    }

    AbstractPiece* piece_moving = get_reference_to_piece_at_board(from_tile.first, from_tile.second);
    int attack_row = (from_tile.second + to_tile.second ) /2;
    int attack_col = (from_tile.first + to_tile.first) /2;

    //If legal then do the move
    set_reference_at_board(new PieceDummy(), from_tile.second, from_tile.first);
    set_reference_at_board(piece_moving, to_tile.second, to_tile.first);

    std::cerr<<"Attacking at row"<<attack_row<<" col"<<attack_col<<std::endl;
    m_ref_to_dead_piece = get_reference_to_piece_at_board(attack_col, attack_row);
    set_reference_at_board(new PieceDummy(), attack_row, attack_col);

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

            if (overlaps)
                return p;
        }
    return nullptr;
}

AbstractPiece* GameplayController::gc_get_dead_piece_pointer()
{
   AbstractPiece* to_return = m_ref_to_dead_piece;
    return to_return;
}

void GameplayController::gc_reset_dead_piece_pointer()
{
   m_ref_to_dead_piece = nullptr;
}

std::pair<int, int> GameplayController::gc_check_if_has_to_attack(int player_turn_flag)
{
    for (int i =0; i<10; i++)
        for(int j = 0; j<10; j++)
        {
            //If piece belongs to current player
            if(get_reference_to_piece_at_board(i, j)->pi_get_move_direction() == player_turn_flag)
            {
                std::vector<std::pair<int, int>> pairs = {
                    std::make_pair(2,2), 
                    std::make_pair(-2,2), 
                    std::make_pair(2,-2), 
                    std::make_pair(-2,-2)
                };

                //Check if there is any option to attack in the area around piece
                for(auto pair : pairs)
                {
                    if ( i+ pair.first < 10 && i + pair.first >= 0 && j+ pair.second < 10 && j + pair.second >= 0)
                        if(get_reference_to_piece_at_board(i + pair.first, j+pair.second)->pi_get_piece_color() == PieceColor::dummy)
                            if(get_reference_to_piece_at_board(i + (pair.first / 2), j+ (pair.second/2) )->pi_get_move_direction() == player_turn_flag*-1)
                            {
                                std::cerr<<"Tile "<<i + (pair.first / 2)<<" "<<j+ (pair.second/2)<<" can be attacked"<<std::endl;
                                return std::make_pair(i + pair.first, j+ pair.second);
                            }
                }

            }
        }
    
    return std::make_pair(-1, -1);
}

int GameplayController::gc_is_game_done()
{
    int left_pieces[3] = {0, 0, 0};
    for (int i =0; i<10; i++)
        for(int j = 0; j<10; j++)
            left_pieces[get_reference_to_piece_at_board(i, j)->pi_get_piece_color()]++;
    
    if(left_pieces[1] == 0)
        return 2;
        
    if(left_pieces[2] == 0)
        return 1;
    
    return 0;
}
