#include "MainMenu.h"

using namespace std;

MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("BebasNeue-Regular.ttf"))
	{
		// handle error
	}

	if (!texture.loadFromFile("background.jpg"))
	{
		exit(1);
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

MainMenu::QuizTopic MainMenu::getSelectedTopic(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// Check if any menu item was clicked
				for (int i = 1; i < MAX_NUMBER_OF_ITEMS; i++)
				{
					if (menu[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						// Set the selected quiz topic based on the clicked menu item
						selectedTopic = static_cast<MainMenu::QuizTopic>(i);
						break;
					}
				}
			}
		}
	}
	return selectedTopic;
}

string MainMenu::getFileName(QuizTopic topic, bool isMCQ)
{
	string extension = isMCQ ? "MCQ.txt" : "TF.txt";
	switch (topic)
	{
	case MainMenu::Football:
		return "Football" + extension;
	case MainMenu::Cricket:
		return "Cricket" + extension;
	case MainMenu::Rugby:
		return "Rugby" + extension;
	default:
		return "";
	}
}
