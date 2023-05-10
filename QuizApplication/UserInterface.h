#pragma once
#include "QuestionBank.h"
#include "SFML/Graphics.hpp"
class UserInterface
{
public:
	void displayQuestion(sf::RenderWindow&, MultipleChoiceQuestion);
	void displayAnswerOptions(sf::RenderWindow&, MultipleChoiceQuestion);
	string getUserAnswer(sf::RenderWindow&, sf::Time, MultipleChoiceQuestion, UserInterface);
	void displayFeedback(sf::RenderWindow&, string, MultipleChoiceQuestion);
};

