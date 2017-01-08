
const int window_x_size = 795;
const int window_y_size = 585;

const int amount_of_levels = 4;

class game
{
	public:
        //constructor and destructor
        game() {
            levels = new game_map();
            window = new sf::RenderWindow(sf::VideoMode(window_x_size, window_y_size), "IO Silver");
        };
        ~game() {
            delete levels;
            delete window;
        };

		//draw routines
		void draw_sprite( sf::Sprite, float x, float y );
        void draw_map(void);

        void level_up();
        void level_down();
        void handle_key_event( int key);
		//the game_map
		game_map *levels;

		//SFML specific stuff
        sf::RenderWindow *window;

	private:

};

