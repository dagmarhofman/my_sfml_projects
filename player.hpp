
enum direction { up, down, left, right };

class game_player
{
    public:

        game_player( ) {
            init();
        };
        ~game_player() {
            delete sprite_texture;
        };

        void init(void);

        //set wrappers
        void set_player_file_name( sf::String arg);
        void set_player_direction( direction d );
        void set_sprite_step( int step );
        void set_current_player_sprite( sf::Sprite sprite );

        void start_moving();
        void start_pushing();
        void stop_moving();
        void stop_pushing();
        bool is_moving();
        bool is_pushing();


        //get wrappers
        int get_sprite_step( void );
        direction get_player_direction( void );
        sf::Sprite get_current_player_sprite( void );
        sf::Sprite get_player_sprite( int num );


        void init_sprites_vector(void);

        void draw_player(sf::RenderWindow *win );
        sf::Vector2i player_cell_position( void );


    private:

        bool moving;
        bool pushing;

        //this all shouldn't be public. wrap later
        int sprite_step;
        /*
        int x_pos;
        int y_pos;
        */
        direction player_direction;

        sf::String player_file_name;
        std::vector<sf::Sprite> player_sprites;
        //welke sprite moet ik op dit moment tekenen (wordt bepaald in timer routine)
        // deze worden via get_ wrapper functie gebruikt door map in draw_map.
        sf::Sprite current_player_sprite;
        sf::Vector2f current_player_sprite_location;
        //---

        sf::Texture *sprite_texture;


};
