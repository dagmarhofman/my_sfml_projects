class game
{
	public:
        //constructor and destructor
        game() {
            levels = new game_map();
            window = new sf::RenderWindow(sf::VideoMode(800, 565), "IO Silver");
        };
        ~game() {
            delete levels;
            delete window;
        };

		//draw routines
		void draw_sprite( sf::Sprite, float x, float y );
        void draw_map(void);

		//the game_map
		game_map *levels;

		//SFML specific stuff
        sf::RenderWindow *window;

	private:

};

