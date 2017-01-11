#include "player.hpp"

class game_map
{
    public:

        game_map() {
            player = new game_player();

            this->init();
        };
        ~game_map() {
            delete chip_sprite_texture;
        };

        void init( void );

        //map operations
        void read_map_file( void );
        bool check_map_file( void );

        //setting/getting member variables
        void set_map_file_name( sf::String );
        void set_chip_texture_file_name(sf::String );
        int get_current_level(void);

        // initializers
        int init_chip_sprites( void );
        void init_map( void );
        bool switch_level( int level_num);

        sf::Sprite get_sprite_by_num(int num);
        int get_sprite_ref (int x, int y );

        sf::Sprite get_xy_sprite( int x, int y );

        //draw routine.
        void draw_map( sf::RenderWindow *win );
        void calc_map_sprites( void );
        game_player *player;

        std::vector<sf::Sprite> mapped_chip_sprites;
    private:


        sf::String map_file_name;
        sf::String chip_texture_file_name;
        std::vector<sf::Sprite> chip_sprites;
        sf::Texture *chip_sprite_texture;

        //map specific variables
        sf::String map_file_buffer; //static?
        int current_level;
        int sprite_map_ref[13][9];

};
