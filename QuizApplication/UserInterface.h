#pragma once
#include "QuestionBank.h"
#include "SFML/Graphics.hpp"
class UserInterface
{
public:
	void displayQuestion(sf::RenderWindow&, QuestionType);
	void displayAnswerOptions(sf::RenderWindow&, QuestionType);
	string getUserAnswer(sf::RenderWindow&, sf::Time, QuestionType, UserInterface);
	void displayFeedback(sf::RenderWindow&, string, QuestionType);
};

