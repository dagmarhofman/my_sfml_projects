#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "map.hpp"
#include "game.hpp"

// milliseconds for one player step
const float sprite_velocity = 100;
const float move_velocity = 2.5;

void game :: level_up(void)
{
    if( levels->get_current_level() < amount_of_levels )
        levels->switch_level(levels->get_current_level()+1);
    return;
}

void game :: level_down(void)
{
    if( levels->get_current_level() > 0 )
        levels->switch_level(levels->get_current_level()-1);
    return;
}

void game :: handle_key_event( int key )
{

    if( key == 67 )
        level_up();
    if( key == 68)
        level_down();

    last_key_pressed = key;
}

void game :: motion_lookups( void )
{

    move_motion_lookup();
    sprite_motion_lookup();
    levels->player->draw_player(window);

}

//klok word gecheckt in de main loop.
void game :: move_motion_lookup( void )
{

    int x_align;
    int y_align;

    sf::Vector2f p;

    p = levels->player->get_current_player_sprite_location();

    x_align = (int)p.x % 60;
    y_align = (int)p.y % 65;

    sf::Vector2u winpos;

    winpos = window->getSize();


    if( last_key_pressed == 71  && y_align == 0 )
        levels->player->set_player_direction( left );
    if( last_key_pressed == 72  && y_align == 0 )
        levels->player->set_player_direction( right );
    if( last_key_pressed == 73  && x_align == 0 )
        levels->player->set_player_direction( up );
    if( last_key_pressed == 74  && x_align == 0  )
        levels->player->set_player_direction( down );


    if( move_clock->getElapsedTime().asMilliseconds() > move_velocity ) {

            if( levels->player->player_direction == up && levels->player->y_pos > 0 )
                levels->player->y_pos--;
            if( levels->player->player_direction == down && levels->player->y_pos < winpos.y - 65 )
                levels->player->y_pos++;
            if( levels->player->player_direction == left && levels->player->x_pos > 0)
                levels->player->x_pos--;
            if( levels->player->player_direction == right && levels->player->x_pos < winpos.x -60)
                levels->player->x_pos++;

            move_clock->restart();
    }
}


//klok word gecheckt in de main loop.
void game :: sprite_motion_lookup( void )
{
        // tick functie van maken;
        if( sprite_clock->getElapsedTime().asMilliseconds() > sprite_velocity ) {
            //cycle de sprite
            if( levels->player->sprite_step >= 2)
                levels->player->sprite_step = 0;
            else
                levels->player->sprite_step++;

            sprite_clock->restart();
            return;
        }

}
