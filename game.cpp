#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "game.hpp"

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

    push_motion_lookup();
    sprite_motion_lookup();
    move_motion_lookup();
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

    //catch push events
    if( !levels->player->is_moving() ) {
        if( levels->player->get_player_direction() == right && last_key_pressed == right_key ) {
            levels->player->start_pushing();
            last_key_pressed = -1;
            return;
        }

        if( levels->player->get_player_direction() == left && last_key_pressed == left_key  ) {
            levels->player->start_pushing();
            last_key_pressed = -1;
            return;
        }

        if( levels->player->get_player_direction() == up  && last_key_pressed == up_key ) {
            levels->player->start_pushing();
            last_key_pressed = -1;
            return;
        }

        if( levels->player->get_player_direction() == down && last_key_pressed == down_key  ) {
            levels->player->start_pushing();
            last_key_pressed = -1;
            return;
        }
    }


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
                new_x = 12 * icon_size_x;

            if( new_x > 12 * icon_size_x )
                new_x = 0;

            if( new_y < 0 )
                new_y = 8 * icon_size_y;

            if( new_y > 8 * icon_size_y )
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

    //levels->player->start_pushing();

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

//gaat ervan uit dat collisie al gedetecteerd is.
// lange reeks aan propositielogica.
// berekend nog niet. of twee dezelfde chips colliden. (later issue)
bool game :: is_push_possible( void )
{
    /* hier bereken ik niet de collisie. maar of het blokje pushable is.*/

    int player_cell_x;
    int player_cell_y;

    /* deze moet via een wrapper!*/
    player_cell_x = (int) levels->player->get_current_player_sprite().getPosition().x/icon_size_x;
    player_cell_y = (int) levels->player->get_current_player_sprite().getPosition().y/icon_size_y;

    /* routines voor rondlopend scherm*/
    /* proposities mogen ook in andere volgorde. of zelfs in een regel*/
    if ( levels->player->get_current_player_sprite().getPosition().x == icon_size_x * 12 )
        if(levels->player->get_player_direction() == right )
            if( levels->get_sprite_ref( 0 , player_cell_y ) != -1 && levels->get_sprite_ref( 1, player_cell_y ) != -1 )
                return false;
            else
                return true;

    if ( levels->player->get_current_player_sprite().getPosition().y == icon_size_y * 8 )
        if(levels->player->get_player_direction() == down )
            if( levels->get_sprite_ref( player_cell_x , 0 ) != -1 && levels->get_sprite_ref( player_cell_x, 1 ) != -1 )
                return false;
            else
                return true;

    if ( levels->player->get_current_player_sprite().getPosition().x == 0 )
        if(levels->player->get_player_direction() == left )
            if( levels->get_sprite_ref( 12, player_cell_y ) != -1 && levels->get_sprite_ref( 11, player_cell_y ) != -1 )
                return false;
            else
                return true;

    if ( levels->player->get_current_player_sprite().getPosition().y == 0 )
        if(levels->player->get_player_direction() == up )
            if( levels->get_sprite_ref( player_cell_x, 8 ) != -1 && levels->get_sprite_ref( player_cell_x, 7 ) != -1 )
                return false;
            else
                return true;

    if (levels->player->get_current_player_sprite().getPosition().x == icon_size_x )
        if(levels->player->get_player_direction() == left )
            if( levels->get_sprite_ref( 0, player_cell_y ) != -1 && levels->get_sprite_ref( 12, player_cell_y ) != -1 )
                return false;
            else
                return true;

    if (levels->player->get_current_player_sprite().getPosition().y == icon_size_y )
        if(levels->player->get_player_direction() == up )
            if( levels->get_sprite_ref( player_cell_x, 0 ) != -1 && levels->get_sprite_ref( player_cell_x, 8 ) != -1 )
                return false;
            else
                return true;



    if (levels->player->get_current_player_sprite().getPosition().x == (11 * icon_size_x) )
        if(levels->player->get_player_direction() == right)
            if( levels->get_sprite_ref( 12, player_cell_y ) != -1 && levels->get_sprite_ref( 0, player_cell_y ) != -1 )
                return false;
            else
                return true;

    if (levels->player->get_current_player_sprite().getPosition().y == (7 * icon_size_y) )
        if(levels->player->get_player_direction() == down )
            if( levels->get_sprite_ref( player_cell_x, 8 ) != -1 && levels->get_sprite_ref( player_cell_x, 0 ) != -1 )
                return false;
            else
                return true;

    /* routines voor het midden van het spel*/
    if(levels->player->get_player_direction() == left )
        if( levels->get_sprite_ref(player_cell_x - 1, player_cell_y ) != -1 )
            if( levels->get_sprite_ref(player_cell_x - 2, player_cell_y ) != -1 )
                return false;

    if(levels->player->get_player_direction() == right )
        if( levels->get_sprite_ref(player_cell_x + 1, player_cell_y ) != -1 )
            if( levels->get_sprite_ref(player_cell_x + 2, player_cell_y ) != -1 )
                return false;

    if(levels->player->get_player_direction() == up )
        if( levels->get_sprite_ref(player_cell_x , player_cell_y - 1 ) != -1 )
            if( levels->get_sprite_ref(player_cell_x , player_cell_y - 2 ) != -1 )
                return false;

    if(levels->player->get_player_direction() == down )
        if( levels->get_sprite_ref(player_cell_x , player_cell_y + 1) != -1 )
            if( levels->get_sprite_ref(player_cell_x , player_cell_y  + 2) != -1 )
                return false;

    return true;
}

void game :: push_motion_lookup( void )
{
    int sprite_at;
    sf::Sprite sprite;


    if( levels->player->is_pushing() && is_push_possible() ) {
        //do_push

        std::cout << "SHOT!!!" << levels->player->get_current_player_sprite().getPosition().x << " "<< levels->player->get_current_player_sprite().getPosition().y << "\n";
        levels->player->stop_pushing();
        return;

    }

    if( levels->player->is_pushing() && !is_push_possible()) {
        std::cout << "BLOCKED!!!" << levels->player->get_current_player_sprite().getPosition().x << " "<< levels->player->get_current_player_sprite().getPosition().y << "\n";
        levels->player->stop_pushing();
        return;
    }


    if( levels->player->is_pushing()) {
        if( levels->player->get_player_direction() == up)
            sprite_at = 0;
        if( levels->player->get_player_direction() == down)
            sprite_at = 5;
        if( levels->player->get_player_direction() == left)
            sprite_at = 10;
        if( levels->player->get_player_direction() == right)
            sprite_at = 15;

        sprite_at += 4;

        sprite = levels->player->get_player_sprite(sprite_at);
        sprite.setPosition(levels->player->get_current_player_sprite().getPosition());
        levels->player->set_current_player_sprite(sprite);
        levels->player->draw_player(window);
    }

    if( push_clock->getElapsedTime().asMilliseconds() > push_velocity  ) {
        levels->player->stop_pushing();
        push_clock->restart();
    }


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

        /* scherm loopt rond */

        if( levels->player->get_player_direction() == left && player_pos.x == 0 )
            if(tmp_map_pos.x == 12 * icon_size_x &&  tmp_map_pos.y == player_pos.y ) {
                levels->player->stop_moving();
                last_key_pressed = -1;
                return true;
            }

        if( levels->player->get_player_direction() == right && player_pos.x == 12 * icon_size_x )
            if(tmp_map_pos.x == 0 &&  tmp_map_pos.y == player_pos.y ) {
                levels->player->stop_moving();
                last_key_pressed = -1;
                return true;
            }

        if( levels->player->get_player_direction() == up && player_pos.y == 0 )
            if(tmp_map_pos.x == player_pos.x  && tmp_map_pos.y == 8 * icon_size_y ) {
                levels->player->stop_moving();
                last_key_pressed = -1;
                return true;
            }

        if( levels->player->get_player_direction() == down && player_pos.y == 8 * icon_size_y )
            if(tmp_map_pos.x == player_pos.x &&  tmp_map_pos.y == 0 ) {
                levels->player->stop_moving();
                last_key_pressed = -1;
                return true;
            }

        /* --- */


        if( levels->player->get_player_direction() == left )
            if(tmp_map_pos.x == player_pos.x - icon_size_x && tmp_map_pos.y == player_pos.y ) {
                levels->player->stop_moving();
                last_key_pressed = -1;
                return true;
            }
        if( levels->player->get_player_direction() == right )
            if(tmp_map_pos.x == player_pos.x + icon_size_x && tmp_map_pos.y == player_pos.y ) {
                levels->player->stop_moving();
                last_key_pressed = -1;
                return true;
            }
        if( levels->player->get_player_direction() == up )
            if(tmp_map_pos.x == player_pos.x  && tmp_map_pos.y == player_pos.y - icon_size_y) {
                levels->player->stop_moving();
                last_key_pressed = -1;
                return true;
            }
        if( levels->player->get_player_direction() == down )
            if(tmp_map_pos.x == player_pos.x && tmp_map_pos.y == player_pos.y + icon_size_y) {
                levels->player->stop_moving();
                last_key_pressed = -1;
                return true;
            }
    }

    return false;
}
