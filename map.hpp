
class game_map
{
    public:

    game_map() {
        this->init();
    };
    ~game_map() {
        delete chip_sprite_texture;
    };

    void init( void );
    //map operations
    void read_map_file( void );
    bool check_map_file( void );

    //setting member variables
    void set_map_file_name( sf::String );
    void set_chip_texture_file_name(sf::String );

    // initializers
	int init_chip_sprites( void );
	void init_map( void );

    sf::Sprite get_sprite_by_num(int num);
    private:
        sf::String map_file_name;
        sf::String chip_texture_file_name;
        std::vector<sf::Sprite> chip_sprites;
        sf::Texture *chip_sprite_texture;

};
