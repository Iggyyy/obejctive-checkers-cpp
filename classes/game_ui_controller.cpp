#include "game_ui_controller.h"
#include    <iostream>


sf::Sprite* load_spirite_and_texture(std::string path)
{
    sf::Texture* texture = new sf::Texture();
    sf::Sprite* sprite = new sf::Sprite();

    if ( texture->loadFromFile("./source/" + path)  )
    {
        texture->setSmooth(true);

        sprite->setTexture(*texture);
        sprite->setScale(0.125, 0.125); //scale down by 8 times to 64px
        sprite->setPosition(0, 0);
    }
    else
    {
        std::cerr<<"Error while loading image as texture"<<std::endl;
    }

    return sprite;
}


void GameUiController::load_board_tiles_and_add_to_render()
{
    for(int i =0; i<10; i++)
    {
        for (int j =0 ; j<10; j++)
        {
            if (i %2 == 0 && j % 2== 0 || i %2 == 1 && j % 2== 1 )
            {
                sf::Sprite* sp = load_spirite_and_texture("tile_0.png");
                sp->setPosition(j*64, i*64);
                m_renderer_ref->gr_add_sprite_to_rendering(sp,0);
            }
            else
            {
                sf::Sprite* sp = load_spirite_and_texture("tile_1.png");
                sp->setPosition(j*64, i*64);
                m_renderer_ref->gr_add_sprite_to_rendering(sp,0);
            }
            
        }
    }
}


void GameUiController::update_mouse_coordinates()
{
    m_mouse_coords = sf::Mouse::getPosition( (*m_window) );
}

std::pair<int, int> GameUiController::coords_to_row_col(sf::Vector2f coords)
{
    int tile_width = 64;
    int tile_height = 64;
    int board_offset_horizontal = 0;
    int board_offset_vertical = 0;

    int row = ( coords.x - board_offset_horizontal ) / tile_width;
    int col = ( coords.y - board_offset_vertical ) / tile_height;

    std::cerr<<"Converting coords: "<<coords.x<<" "<<coords.y<<" to rowcol: "<<row<<" "<<col<<std::endl;
    
    if (row < 10 && col < 10)
        return std::make_pair(row, col);
    
    return std::make_pair(-1, -1);
}

void GameUiController::resolve_frame_events()
{
    sf::Event event;
    m_window->pollEvent(event);
    update_mouse_coordinates();
    
    //Update sprite coordinates if mouse is holding something
    if(m_is_piece_grabbed == true)
    {
        sf::Vector2i c = m_mouse_coords;
        c.x -= 32;
        c.y -= 32;
        m_grabbed_piece->pi_get_sprite()->setPosition(m_window->mapPixelToCoords(c));
    }

    if (event.type == sf::Event::Closed) m_window->close();
    if (event.type == sf::Event::MouseButtonPressed)
    {
        std::cerr<<"Mosue clicked at: "<<m_mouse_coords.x << ", "<<m_mouse_coords.y<<std::endl;
        //HANDLE BUTTONS

        //TRY TO GRAB
        if (m_is_piece_grabbed == false)
        {
            auto grabbed_piece = m_gameplay_controller_ref->gc_try_to_get_piece_at_coords(m_window->mapPixelToCoords(m_mouse_coords));
            if(grabbed_piece != nullptr)
            {
                if(grabbed_piece->pi_get_move_direction() == m_whose_turn)
                {
                    std::cerr<<"Piece just got grabbed"<<std::endl;
                    m_is_piece_grabbed = true;
                    m_grabbed_piece = grabbed_piece;
                    m_origin_tile = coords_to_row_col(m_window->mapPixelToCoords(m_mouse_coords));
                }
                else
                {
                    std::cerr<<"Tried to grab wrong player's piece"<<std::endl;
                }
            }
        }
        else
        {
            //TRY TO PLACE IT
            std::pair<int, int> rowcol = coords_to_row_col(m_window->mapPixelToCoords(m_mouse_coords));
            std::cerr<<"Trying to move from "<<m_origin_tile.first<<","<<m_origin_tile.second<<" to "
                                <<rowcol.first<<","<<rowcol.second<<std::endl;
            if(rowcol.first > 0) //check if legal move TODO 
            {
                bool successfull_move = m_gameplay_controller_ref->gc_make_move(m_origin_tile, rowcol);

                if(successfull_move)
                {
                    
                    std::cerr<<"Dropped piece at "<<rowcol.first<<","<<rowcol.second<<std::endl;
                    m_grabbed_piece->pi_get_sprite()->setPosition(rowcol.first*64, rowcol.second*64);

                    if( m_gameplay_controller_ref->gc_get_dead_piece_pointer() != nullptr)
                    {
                        std::cerr<<"YYY"<<std::endl;
                        m_renderer_ref->gr_remove_sprite_from_rendering(
                            m_gameplay_controller_ref->
                            gc_get_dead_piece_pointer()->
                            pi_get_sprite()
                            );       
                        m_gameplay_controller_ref->gc_reset_dead_piece_pointer(); 
                        
                    }
                    m_whose_turn*=-1;
                }
                else 
                {
                    std::cerr<<"ILLEGAL MOVE from "<<m_origin_tile.first<<","<<m_origin_tile.second<<" to "
                                <<rowcol.first<<","<<rowcol.second<<std::endl;
                    m_grabbed_piece->pi_get_sprite()->setPosition(m_origin_tile.first*64, m_origin_tile.second*64);
                }
                m_grabbed_piece = nullptr;
                m_is_piece_grabbed = false;
                m_origin_tile = std::make_pair(0,0);
                
            }

        }
    }
}