#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "map.hpp"
#include "game.hpp"

void game :: draw_sprite( sf::Sprite sprite, float x, float y )
{

    sprite.setPosition(sf::Vector2f(x, y)); // absolute position

    this->window->draw(sprite);

    return;
}

void game :: draw_map( void )
{
    sf::Sprite sprite;

    int i,j;
    int sprite_num;

    for(i=0;i<13;i++) {
        for(j=0;j<9;j++) {
            sprite_num = levels->get_sprite_ref(i,j);
            if( sprite_num != -1 ) {
                sprite = levels->get_sprite_by_num(sprite_num);
                draw_sprite( sprite, i * 60, j * 65);
            }
        }
    }

    return;
}

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
}

