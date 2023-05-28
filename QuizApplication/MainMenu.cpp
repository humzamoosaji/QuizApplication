#include "MainMenu.h"
#include <iostream>
using namespace std;

MainMenu::MainMenu(float width, float height)
{
	font.loadFromFile("BebasNeue-Regular.ttf");

	texture.loadFromFile("background.jpg");

	sprite.setTexture(texture);
	sprite.setScale(width / texture.getSize().x, height / texture.getSize().y);

	string menuStrings[] = {
		"WELCOME! BEGIN BY CHOOSING A SPORT",
		"FOOTBALL",
		"CRICKET",
		"RUGBY",
		"TIC TAC TOE"
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
	MainMenu::QuizTopic selected = MainMenu::None;
	while (window.isOpen() && window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			for (int i = 1; i < MAX_NUMBER_OF_ITEMS; i++)
			{
				if (menu[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					selected = MainMenu::QuizTopic(i);
					break;
				}
			}
		}
	}
	return selected;
}

string MainMenu::getFileName(const QuizTopic& topic, bool isMCQ)
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
	case MainMenu::TicTacToe:
		return "TicTacToe";
	default:
		return "";
	}
}