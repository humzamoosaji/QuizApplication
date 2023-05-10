#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 4

class MainMenu
{
public:
	MainMenu(float width, float height);
	~MainMenu();

	void draw(sf::RenderWindow& window);

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Sprite sprite;
	sf::Texture texture;

};