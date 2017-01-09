
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "player.hpp"

const char* playerfile = "./sprites/player.png";
// milliseconds for one player step
const float player_velocity = 100;

void game_player :: init( void )
{
    x_pos = 1;
    y_pos = 1;

    sprite_step = 1;

    set_player_file_name( sf::String(playerfile) );
    sprite_texture = new sf::Texture;
    player_clock = new sf::Clock();
    player_sprites.reserve(25);
    init_sprites_vector();
    player_direction = up;


}

//klok word gecheckt in de main loop.
void game_player :: clock_lookup( sf::RenderWindow *win )
{
        // tick functie van maken;
        if( player_clock->getElapsedTime().asMilliseconds() > player_velocity ) {
            //cycle de sprite
            if( sprite_step >= 2)
                sprite_step = 0;
            else
                sprite_step++;

            player_clock->restart();
            return;
        }
        draw_player(win);

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

void game_player :: set_player_cell_position( int x, int y)
{
    x_pos = x;
    y_pos = y;
}

sf::Sprite game_player :: get_current_player_sprite( void )
{
    int sprite_at;

    if( player_direction == up)
        sprite_at = 0;
    if( player_direction == down)
        sprite_at = 5;
    if( player_direction == left)
        sprite_at = 10;
    if( player_direction == right)
        sprite_at = 15;

    sprite_at += sprite_step;

    return player_sprites.at(sprite_at);

}

sf::Vector2f game_player :: get_current_player_sprite_location( void )
{
    return sf::Vector2f( x_pos, y_pos);
}

void game_player :: draw_player ( sf::RenderWindow *win )
{
    sf::Sprite sprite;

    sprite = get_current_player_sprite();
    sprite.setPosition(get_current_player_sprite_location());
    win->draw(sprite);

}

void game_player :: set_player_direction( direction d )
{
    player_direction = d;
}
