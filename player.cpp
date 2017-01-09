
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
const float sprite_velocity = 100;
const float move_velocity = 2.5;

void game_player :: init( void )
{
    x_pos = 60;
    y_pos = 65;

    sprite_step = 1;

    set_player_file_name( sf::String(playerfile) );
    sprite_texture = new sf::Texture;
    sprite_clock = new sf::Clock();
    move_clock = new sf::Clock();
    player_sprites.reserve(25);
    init_sprites_vector();
    player_direction = up;


}

//klok word gecheckt in de main loop.
void game_player :: sprite_motion_lookup( sf::RenderWindow *win )
{
        // tick functie van maken;
        if( sprite_clock->getElapsedTime().asMilliseconds() > sprite_velocity ) {
            //cycle de sprite
            if( sprite_step >= 2)
                sprite_step = 0;
            else
                sprite_step++;

            sprite_clock->restart();
            return;
        }
        draw_player(win);


}
//klok word gecheckt in de main loop.
void game_player :: move_motion_lookup( sf::RenderWindow *win )
{

    int x_align;
    int y_align;

    sf::Vector2f p;

    p = get_current_player_sprite_location();

    x_align = (int)p.x % 60;
    y_align = (int)p.y % 65;

    sf::Vector2u winpos;

    winpos = win->getSize();


    if( last_key_pressed == 71  && y_align == 0 )
        set_player_direction( left );
    if( last_key_pressed == 72  && y_align == 0 )
        set_player_direction( right );
    if( last_key_pressed == 73  && x_align == 0 )
        set_player_direction( up );
    if( last_key_pressed == 74  && x_align == 0  )
        set_player_direction( down );


    if( move_clock->getElapsedTime().asMilliseconds() > move_velocity ) {
            if( player_direction == up && y_pos > 0 )
                y_pos--;
            if( player_direction == down && y_pos < winpos.y - 65 )
                y_pos++;
            if( player_direction == left && x_pos > 0)
                x_pos--;
            if( player_direction == right && x_pos < winpos.x -60)
                x_pos++;

            move_clock->restart();
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

void game_player :: set_current_player_sprite_location ( sf::Vector2f loc )
{
    current_player_sprite_location = sf::Vector2f(x_pos,y_pos);
}

void game_player :: draw_player ( sf::RenderWindow *win )
{
    sf::Sprite sprite;

    sprite = get_current_player_sprite();
    sprite.setPosition(sf::Vector2f(x_pos, y_pos));
    win->draw(sprite);

}

void game_player :: set_player_direction( direction d )
{
    player_direction = d;
}

void game_player :: set_last_key_pressed( int key )
{
    last_key_pressed = key;
}
