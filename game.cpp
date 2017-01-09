#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "map.hpp"
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

    levels->player->set_last_key_pressed(key);
}

