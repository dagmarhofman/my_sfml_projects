
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
        void set_player_file_name( sf::String arg);
        void set_player_cell_position( int x, int y);

        sf::Sprite get_current_player_sprite( void );
        sf::Vector2f get_current_player_sprite_location();
        void set_current_player_sprite_location( sf::Vector2f loc );


        void init_sprites_vector(void);
        void sprite_motion_lookup( sf::RenderWindow *win );
        void move_motion_lookup( sf::RenderWindow *win );

        void draw_player(sf::RenderWindow *win );
        void set_player_direction( direction d );
        void set_last_key_pressed( int key );
    private:

        //cell position
        int x_pos;
        int y_pos;

        direction player_direction;


        //er zijn 3 sprites in de sprite sheet als het poppetje loopt.
        //sprite_step, bepaalt welke van deze drie getekend moet worden.
        int sprite_step;

        sf::String player_file_name;
        std::vector<sf::Sprite> player_sprites;
        //welke sprite moet ik op dit moment tekenen (wordt bepaald in timer routine)
        // deze worden via get_ wrapper functie gebruikt door map in draw_map.
        sf::Sprite current_player_sprite;
        sf::Vector2f current_player_sprite_location;
        //---

        sf::Texture *sprite_texture;
        sf::Clock *sprite_clock;
        sf::Clock *move_clock;
        sf::Time elapsed_time;

        int last_key_pressed;
};
