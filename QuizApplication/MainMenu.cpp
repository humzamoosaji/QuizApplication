#include "MainMenu.h"


MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("BebasNeue-Regular.ttf"))
	{
		// handle error
	}

	if (!texture.loadFromFile("background.jpg"))
	{
		exit;
	}

	sprite.setTexture(texture);
	sprite.setScale(width / texture.getSize().x, height / texture.getSize().y);

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Blue);
	menu[0].setString("WELCOME! BEGIN BY CHOOSING A SPORT");
	menu[0].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	if (!font.loadFromFile("BebasNeue-Regular.ttf"))
	{
		// handle error
	}

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("FOOTBALL");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_ITEMS + 1) * 2/1.25));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("CRICKET");
	menu[2].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_ITEMS + 1) * 3/1.5));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("RUGBY");
	menu[3].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_ITEMS + 1) * 4/1.6));

}


MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}
