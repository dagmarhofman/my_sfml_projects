/*
    on construction, this class should have all the sprites referenced.
    reference is read from the (const char *) levelfile.
    level 0 is the test level, made easy for testing.
    26 levels, of 13 * 9 squares.

*/

#include <sstream>
#include <iostream>
#include <vector>
#include <cstring>

#include <SFML/Graphics.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "map.hpp"

//common filenames
const char* levelfile = "/home/digi/my_iosilver/levels.dat";
const char* chipfile = "/home/digi/my_iosilver/sprites/chips.png";

// add more sprites in later version.
const int max_sprites = 6;
const int start_level = 1;



int game_map :: get_current_level ( void )
{
    return current_level;
}
int game_map :: get_sprite_ref (int x, int y )
{
    return sprite_map_ref[x][y];
}

sf::Sprite game_map :: get_sprite_by_num (int num)
{
    return chip_sprites.at(num);
}

//init everything at construction of object
void game_map :: init()
{
    current_level = 0;
    chip_sprites.reserve(6);
    mapped_chip_sprites.reserve(108);
    set_map_file_name( sf::String(levelfile) );
    set_chip_texture_file_name( sf::String(chipfile) );

    player = new game_player();

    read_map_file();

    switch_level( start_level );


    //create SFML specific stuff
    chip_sprite_texture = new sf::Texture;

    //game initialize routines
    try {
        init_chip_sprites();
    } catch ( std::exception& e) {
        std::cout << "could not init sprites " << e.what() << "\n";
    }

    calc_map_sprites();

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
    int64_t my_map_size;
    char *my_map_buffer;

    sf::FileInputStream *my_map;
    my_map = new sf::FileInputStream;
    my_map->open( map_file_name );
    my_map_size = my_map->getSize();
    my_map_buffer = new char[my_map_size];
    my_map->read((char *)my_map_buffer, my_map_size);

    //scan the whole buffer.
    map_file_buffer = my_map_buffer;

    delete my_map;

}

/* this thing depends on a good data file. insane things may happen when the buffer is incorrect initialized */
bool game_map :: switch_level( int level_num )
{
    int i,j;
    int found_level;
    bool flag = false;

    std::string parsebuf = map_file_buffer.toAnsiString();
    std::string line;
    std::istringstream strstream(parsebuf);
    std::stringstream line_stream;

    while(!strstream.eof()) {
        std::getline(strstream,line);
        line_stream.str(line);
        if( line.length() > 1 ) {
            if( line.at(0) =='L' )
                    std::sscanf( line.c_str(), "L%i\n", &found_level);
            if( found_level == level_num ) {
                for( i = 0; i < 9; i++) {
                    std::getline(strstream,line);
                    for(j=0;j<13;j++) {
                        if( line.at(j) != '.' )
                            sprite_map_ref[j][i] = line.at(j) - '0';
                        else
                            sprite_map_ref[j][i] = -1;
                    }
                }
                flag = true;
            }
        }
    }
    if( flag )
        current_level = level_num;

    return flag;
}

//aparte init_texture maken???
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

sf::Sprite game_map :: get_xy_sprite( int x, int y)
{
    sf::Sprite sprite;

    int i,j;
    int sprite_num;

    sprite_num = get_sprite_ref(x,y);
    if( sprite_num != -1 ) {
        sprite = get_sprite_by_num(sprite_num);
        sprite.setPosition(sf::Vector2f(x*60, x*65));
        return sprite;
    }

    return sprite;
}


void game_map :: calc_map_sprites( void )
{
    sf::Sprite sprite;

    int i,j;
    int sprite_num;

    for(i=0;i<13;i++) {
        for(j=0;j<9;j++) {
            sprite_num = get_sprite_ref(i,j);
            if( sprite_num != -1 ) {
                sprite = get_sprite_by_num(sprite_num);
                sprite.setPosition(sf::Vector2f(i*60, j*65));
                mapped_chip_sprites.push_back(sprite);
            }
        }
    }

    return;
}
void game_map :: draw_map( sf::RenderWindow *win )
{
    sf::Sprite sprite;

    int i,j;
    int sprite_num;

    for(i=0;i<13;i++) {
        for(j=0;j<9;j++) {
            sprite_num = get_sprite_ref(i,j);
            if( sprite_num != -1 ) {
                sprite = get_sprite_by_num(sprite_num);
                sprite.setPosition(sf::Vector2f(i*60, j*65));
                win->draw(sprite);
            }
        }
    }

    return;
}
