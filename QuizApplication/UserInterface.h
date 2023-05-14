#pragma once
#include "SFML/Graphics.hpp"
#include "QuestionBank.h"
#include "MainMenu.h"
using namespace std;
template <class QuestionType>
class UserInterface
{
public:
	void displayQuestion(sf::RenderWindow&, QuestionType, MainMenu::QuizTopic);
	void displayAnswerOptions(sf::RenderWindow&, QuestionType);
	string getUserAnswer(sf::RenderWindow&, sf::Time, QuestionType, UserInterface<QuestionType>, MainMenu::QuizTopic);
	void displayFeedback(sf::RenderWindow&, string, QuestionType);
};

