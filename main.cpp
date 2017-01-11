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

#include "game.hpp"

int main()
{

    game *iosilver;
    iosilver = new game();

    iosilver->window->setActive();
    while (iosilver->window->isOpen())
    {
        sf::Event event;
        while (iosilver->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                iosilver->window->close();
            if (event.type == sf::Event::KeyPressed)
                iosilver->handle_key_event( event.key.code );
        }

        iosilver->window->clear();

        //lets watch the clock that is running on the background
        // calls player->draw_player
        iosilver->motion_lookups();

        /* later issue, main gameplay here*/
        iosilver->levels->draw_map(iosilver->window);

        iosilver->window->display();
    }

    return 0;
}
