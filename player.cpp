
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "player.hpp"

const char* playerfile = "./sprites/player.png";

void game_player :: init( void )
{

    current_player_sprite.setPosition(sf::Vector2f(60,65));

    sprite_step = 1;

    set_player_file_name( sf::String(playerfile) );
    sprite_texture = new sf::Texture;
    player_sprites.reserve(25);
    init_sprites_vector();
    player_direction = up;
    start_moving();
    stop_pushing();
}


void game_player :: init_sprites_vector( void )
{
    int i;
    int j;

    if( !sprite_texture->loadFromFile( player_file_name) )
        throw std::runtime_error( "Could not load player sprite file " );

    // initialize the chip sprite vector
    sf::Sprite sprite;


    for(i=0;i < 5 ;i++) {
        for(j=0;j < 5 ;j++) {
            sprite.setTexture(*sprite_texture );
            sprite.setTextureRect(sf::IntRect(60 * j, 65 *i, 60, 65));

            player_sprites.push_back(sprite);

        }
    }
}

void game_player :: set_player_file_name( sf::String arg)
{
    player_file_name = arg;
}


sf::Sprite game_player :: get_current_player_sprite( void )
{
    return current_player_sprite;
}

sf::Sprite game_player :: get_player_sprite( int num )
{
    return player_sprites.at(num);
}



void game_player :: draw_player ( sf::RenderWindow *win )
{
    sf::Sprite sprite;

    sprite = get_current_player_sprite();

    win->draw(sprite);

}

void game_player :: set_player_direction( direction d )
{
    player_direction = d;
}
direction game_player :: get_player_direction( void )
{
    return player_direction;
}

void game_player :: set_current_player_sprite (sf::Sprite sprite )
{
    current_player_sprite = sprite;
    return;
}

/*
    THIS ROUTINES SHOULD DO TYPECHECK
*/

void game_player :: set_sprite_step( int step )
{
    sprite_step = step;
}

int  game_player :: get_sprite_step( void )
{
    return sprite_step;
}


void game_player :: start_moving( void )
{
    moving = true;
}
void game_player :: stop_moving( void )
{
    moving = false;
}
void game_player :: start_pushing( void )
{
    pushing = true;
}
void game_player :: stop_pushing( void )
{
    pushing = false;
}

bool game_player :: is_pushing( void )
{
    return pushing;
}
bool game_player :: is_moving( void )
{
    return moving;
}

