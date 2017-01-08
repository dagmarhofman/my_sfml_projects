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
    sprite = this->levels->get_sprite_by_num(4);
    draw_sprite( sprite, 50,50);

    return;
}

