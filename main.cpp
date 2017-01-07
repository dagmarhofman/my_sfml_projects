/*
    I/O Silver for Linux.

    As closest it could get to the real game.

    under construction.

*/


#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>


const char* levelfile = "./level.dat";
const char* chipfile = "./sprites/chips.png";

// add more sprites in later version.
const int max_sprites = 6;

class game
{
	public:
        //constructor
		game()
        {
            chip_sprites.reserve(6);
            set_map_file_name( sf::String(levelfile) );
            set_chip_texture_file_name( sf::String(chipfile) );

            //create SFML specific stuff
            chip_sprite_texture = new sf::Texture;
            window = new sf::RenderWindow(sf::VideoMode(800, 565), "IO Silver");

            std::cout << "Game object created\n";
        };

        ~game() {
            delete chip_sprite_texture;
            delete window;
        }
        //map operations
		void read_map_file( void );
		void draw_map( void );
        bool check_map_file( void );

        //setting member variables
		void set_map_file_name( sf::String );
		void set_chip_texture_file_name(sf::String );

		//draw routines
		void draw_sprite( sf::Sprite, float x, float y );

		// initializers
		int init_chip_sprites( void );
		void init_map( void );

		//SFML specific stuff
        sf::RenderWindow *window;
        sf::Texture *chip_sprite_texture;

	private:
		sf::String map_file_name;
		sf::String chip_texture_file_name;
		std::vector<sf::Sprite> chip_sprites;


};

void game :: draw_sprite( sf::Sprite sprite, float x, float y )
{

    sprite.setPosition(sf::Vector2f(x, y)); // absolute position

    window->draw(sprite);

    return;
}

void game :: set_map_file_name( sf::String arg )
{
    map_file_name = arg;
}

void game :: set_chip_texture_file_name( sf::String arg )
{
    chip_texture_file_name = arg;
}


//check if the map file is correct
bool game :: check_map_file ( void )
{
    return true;
}

void game :: read_map_file( void )
{

}

void game :: draw_map( void )
{
    sf::Sprite sprite;

}

int game :: init_chip_sprites( void )
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

int main()
{

    game iosilver;

    //game initialize routines
    try {
        iosilver.init_chip_sprites();
    } catch ( std::exception& e) {
        std::cout << "could not init sprites " << e.what() << "\n";
        return 1;
    }

    while (iosilver.window->isOpen())
    {
        sf::Event event;
        while (iosilver.window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                iosilver.window->close();
        }

        iosilver.window->clear();
        iosilver.draw_map();
        iosilver.window->display();
    }

    return 0;
}
