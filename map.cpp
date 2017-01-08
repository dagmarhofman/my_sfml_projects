/*
    on construction, this class should have all the sprites referenced.
    reference is read from the (const char *) levelfile.
    level 0 is the test level, made easy for testing.
    26 levels, of 13 * 9 squares.

*/

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "map.hpp"

//common filenames
const char* levelfile = "./level.dat";
const char* chipfile = "./sprites/chips.png";

// add more sprites in later version.
const int max_sprites = 6;


sf::Sprite game_map :: get_sprite_by_num (int num)
{
    return chip_sprites.at(num);
}

//init everything at construction of object
void game_map :: init()
{
    chip_sprites.reserve(6);
    set_map_file_name( sf::String(levelfile) );
    set_chip_texture_file_name( sf::String(chipfile) );
    //create SFML specific stuff
    chip_sprite_texture = new sf::Texture;

    //game initialize routines
    try {
        init_chip_sprites();
    } catch ( std::exception& e) {
        std::cout << "could not init sprites " << e.what() << "\n";
    }
}

void game_map :: set_map_file_name( sf::String arg )
{
    map_file_name = arg;
}

void game_map :: set_chip_texture_file_name( sf::String arg )
{
    chip_texture_file_name = arg;
}

//check if the map file is correct
bool game_map :: check_map_file ( void )
{
    return true;
}

void game_map :: read_map_file( void )
{

}

int game_map :: init_chip_sprites( void )
{

    int i;

    if( !chip_sprite_texture->loadFromFile( chip_texture_file_name) )
        throw std::runtime_error( "Could not load chip sprite file " );

    // initialize the chip sprite vector
    sf::Sprite sprite;


    for(i=0;i < max_sprites ;i++) {
        sprite.setTexture(*chip_sprite_texture);
        sprite.setTextureRect(sf::IntRect(60 * i, 0, 60, 70));

        chip_sprites.push_back(sprite);

    }

}
