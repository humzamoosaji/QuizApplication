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

	string menuStrings[] = {
	"WELCOME! BEGIN BY CHOOSING A SPORT",
	"FOOTBALL",
	"CRICKET",
	"RUGBY"
	};
	int numItems = sizeof(menuStrings) / sizeof(menuStrings[0]);

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::White);
	menu[0].setString("WELCOME! BEGIN BY CHOOSING A SPORT");
	menu[0].setPosition(sf::Vector2f(width / 3, height / 2 - 150));

	for (int i = 1; i < numItems; i++) {
		menu[i].setFont(font);
		menu[i].setFillColor(sf::Color::White);
		menu[i].setString(menuStrings[i]);
		menu[i].setPosition(sf::Vector2f(width / 3, height / 2 + i * 50 - 100));
	}

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
