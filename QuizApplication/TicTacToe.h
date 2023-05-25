#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
class TicTacToe {
private:
	sf::Image background_i;
	sf::Texture background_t;
	sf::Image board_i;
	sf::Texture board_t;
	sf::Image reset_i;
	sf::Texture reset_t;
	sf::Image cross_i;
	sf::Texture cross;
	sf::Image circle_i;
	sf::Texture circle;
	sf::Image blank_i;
	sf::Texture blank;
	sf::Font font;

	std::string msg;
	int cur;
	bool waitForReset;

	bool checkWin(int placement);
	bool checkDraw();

public:
	void playGame();
	sf::Sprite background;
	sf::Sprite board;
	sf::Sprite reset;
	sf::Sprite pieces[9];
	sf::Text text;

	char set[9];

	bool loadAssets();
	bool loadBoard(int startPlayer);

	void keyPress(sf::Vector2f pos);
};