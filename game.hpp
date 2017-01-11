
const int window_x_size = 795;
const int window_y_size = 585;

const int amount_of_levels = 3;

class game
{
	public:
        //constructor and destructor
        game() {
            levels = new game_map();
            window = new sf::RenderWindow(sf::VideoMode(window_x_size, window_y_size), "IO Silver");
            sprite_clock = new sf::Clock();
            move_clock = new sf::Clock();

        };
        ~game() {
            delete levels;
            delete window;
            delete sprite_clock;
            delete move_clock;
        };

		//draw routines
		void draw_sprite( sf::Sprite, float x, float y );
        void draw_map(void);

        void level_up();
        void level_down();
        void handle_key_event( int key);

        //do all motion lookups
        void motion_lookups( void );

        void move_motion_lookup(void);
        void sprite_motion_lookup(void);

        bool player_chip_collision(void);

		//the game_map
		game_map *levels;

		//SFML specific stuff
        sf::RenderWindow *window;
        sf::Clock *sprite_clock;
        sf::Clock *move_clock;

	private:
        int last_key_pressed;

};

