#include "pieces.h"
#include <iostream>




void PieceWhite::pi_init_texture_and_sprite()
{
    sf::Texture* texture = new sf::Texture();
    if ( texture->loadFromFile("./source/" + m_image_pathname)  )
    {
        texture->setSmooth(true);
        pi_set_texture(texture);
        //std::cout<<"Texture loaded"<<std::endl;

        sf::Sprite* sprite = new sf::Sprite();
        sprite->setTexture(*texture);
        //sprite->setTextureRect(sf::IntRect(0,0,512,512));
        sprite->setScale(0.125, 0.125); //scale down by 8 times to 64px
        sprite->setPosition(0, 0);
        pi_set_sprite(sprite);

       // std::cout<<"Sprite set "<<sprite->getPosition().x<<std::endl;
    }
    else
    {
        std::cerr<<"Error while loading image as texture"<<std::endl;
    }

    
   // std::cout<<pi_get_texture()<<std::endl;
    //std::cout<<pi_get_sprite()<<std::endl;
}

void PieceBlack::pi_init_texture_and_sprite()
{
    sf::Texture* texture = new sf::Texture();
    if ( texture->loadFromFile("./source/" + m_image_pathname)  )
    {
        texture->setSmooth(true);
        pi_set_texture(texture);
        //std::cout<<"Texture loaded"<<std::endl;

        sf::Sprite* sprite = new sf::Sprite();
        sprite->setTexture(*texture);
        //sprite->setTextureRect(sf::IntRect(0,0,512,512));
        sprite->setScale(0.125, 0.125); //scale down by 8 times to 64px
        sprite->setPosition(0, 0);
        pi_set_sprite(sprite);

        //std::cout<<"Sprite set "<<sprite->getPosition().x<<std::endl;
    }
    else
    {
        std::cerr<<"Error while loading image as texture"<<std::endl;
    }

    
    //std::cout<<pi_get_texture()<<std::endl;
    //std::cout<<pi_get_sprite()<<std::endl;
}