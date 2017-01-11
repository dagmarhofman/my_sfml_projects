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
const int left_key = 71;
const int right_key = 72;
const int up_key = 73;
const int down_key = 74;

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

    sf::Sprite c_sprite;

    int x_align;
    int y_align;

    float new_x;
    float new_y;

    sf::Vector2f p;
    sf::Vector2f new_sprite_location;

    c_sprite = levels->player->get_current_player_sprite();
    p = c_sprite.getPosition();

    x_align = (int)p.x % 60;
    y_align = (int)p.y % 65;

    new_x = p.x;
    new_y = p.y;


    if( last_key_pressed == left_key  && y_align == 0 ) {
        levels->player->set_player_direction( left );
        levels->player->start_moving();
    } else if( last_key_pressed == right_key  && y_align == 0 ) {
        levels->player->set_player_direction( right );
        levels->player->start_moving();
    } else if( last_key_pressed == up_key  && x_align == 0 ){
        levels->player->set_player_direction( up );
        levels->player->start_moving();
    } else if( last_key_pressed == down_key  && x_align == 0  ) {
        levels->player->set_player_direction( down );
        levels->player->start_moving();
    }


    //ring hier de move events
    if( move_clock->getElapsedTime().asMilliseconds() > move_velocity  ) {

        if( !player_chip_collision() ) {

            if( levels->player->get_player_direction() == right  )
                new_x++;

            if( levels->player->get_player_direction() == left  )
                new_x--;

            if( levels->player->get_player_direction() == up )
                new_y--;

            if( levels->player->get_player_direction() == down )
                new_y++;


            if( new_x < 0 )
                new_x = window_x_size;

            if( new_x > window_x_size )
                new_x = 0;

            if( new_y < 0 )
                new_y = window_y_size;

            if( new_y > window_y_size )
                new_y = 0;

            c_sprite.setPosition( sf::Vector2f( new_x, new_y));
            levels->player->set_current_player_sprite(c_sprite);
        }
        move_clock->restart();
    }
    levels->player->draw_player(window);

}


//klok word gecheckt in de main loop.
void game :: sprite_motion_lookup( void )
{
    int sprite_at;
    sf::Sprite sprite;

    int cycle_sprite = 0;

    // tick functie van maken;
    if( sprite_clock->getElapsedTime().asMilliseconds() > sprite_velocity ) {


        if( levels->player->get_player_direction() == up)
            sprite_at = 0;
        if( levels->player->get_player_direction() == down)
            sprite_at = 5;
        if( levels->player->get_player_direction() == left)
            sprite_at = 10;
        if( levels->player->get_player_direction() == right)
            sprite_at = 15;


        cycle_sprite = levels->player->get_sprite_step();

        cycle_sprite++;

        if(cycle_sprite > 2)
            cycle_sprite = 0;

        levels->player->set_sprite_step(cycle_sprite);


        if( !levels->player->is_moving() )
            sprite_at += 3;
        else if( levels->player->is_pushing() )
            sprite_at += 4;
        else
            sprite_at += levels->player->get_sprite_step();

        sprite = levels->player->get_player_sprite(sprite_at);

        sprite.setPosition(levels->player->get_current_player_sprite().getPosition());
        levels->player->set_current_player_sprite(sprite);

        sprite_clock->restart();


    }
    return;

}

bool game :: player_chip_collision( void )
{
    int i;
    sf::Vector2f player_pos;
    sf::Vector2f tmp_map_pos;

    sf::FloatRect player_rect;
    sf::FloatRect tmp_map_rect;

    int x,y;

    player_pos = levels->player->get_current_player_sprite().getPosition();

    for(i=0;i<levels->mapped_chip_sprites.size();i++) {
        tmp_map_pos = levels->mapped_chip_sprites.at(i).getPosition();
        if( levels->player->get_player_direction() == left )
            if(tmp_map_pos.x == player_pos.x - 60 && tmp_map_pos.y == player_pos.y ) {
                levels->player->stop_moving();
                last_key_pressed = -1;
                return true;
            }
        if( levels->player->get_player_direction() == right )
            if(tmp_map_pos.x == player_pos.x + 60 && tmp_map_pos.y == player_pos.y ) {
                levels->player->stop_moving();
                last_key_pressed = -1;
                return true;
            }
        if( levels->player->get_player_direction() == up )
            if(tmp_map_pos.x == player_pos.x  && tmp_map_pos.y == player_pos.y - 65) {
                levels->player->stop_moving();
                last_key_pressed = -1;
                return true;
            }
        if( levels->player->get_player_direction() == down )
            if(tmp_map_pos.x == player_pos.x && tmp_map_pos.y == player_pos.y + 65) {
                levels->player->stop_moving();
                last_key_pressed = -1;
                return true;
            }
    }

    return false;
}
