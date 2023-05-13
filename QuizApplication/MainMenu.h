#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 4

using namespace std;

class MainMenu
{
public:
	enum QuizTopic { None, Football, Cricket, Rugby };
	QuizTopic selectedTopic;
	QuizTopic getSelectedTopic(sf::RenderWindow& window);
	MainMenu(float width, float height);
	~MainMenu();

	void draw(sf::RenderWindow& window);

private:
	string selectedSport;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Sprite sprite;
	sf::Texture texture;

};