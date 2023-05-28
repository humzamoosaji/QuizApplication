#pragma once
#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS 5

using namespace std;

class MainMenu
{
public:
	enum QuizTopic { None, Football, Cricket, Rugby, TicTacToe };
	QuizTopic getSelectedTopic(sf::RenderWindow& window);
	string getFileName(const QuizTopic& topic, bool isMCQ);
	MainMenu(float width, float height);

	void draw(sf::RenderWindow& window);

private:
	string selectedSport;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Sprite sprite;
	sf::Texture texture;
};
