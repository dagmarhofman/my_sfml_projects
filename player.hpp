
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

        void draw_player(sf::RenderWindow *win );
        void set_player_direction( direction d );
        direction get_player_direction( void );

        sf::Vector2i player_cell_position( void );

        //this all shouldn't be public. wrap later
        int sprite_step;
        int x_pos;
        int y_pos;
        direction player_direction;

    private:



        sf::String player_file_name;
        std::vector<sf::Sprite> player_sprites;
        //welke sprite moet ik op dit moment tekenen (wordt bepaald in timer routine)
        // deze worden via get_ wrapper functie gebruikt door map in draw_map.
        sf::Sprite current_player_sprite;
        sf::Vector2f current_player_sprite_location;
        //---

        sf::Texture *sprite_texture;


};
