#pragma once
#include "SFML/Graphics.hpp"
#include "QuestionBank.h"
#include "MainMenu.h"
#
using namespace std;
template <class QuestionType>
class UserInterface
{
public:
	void displayQuestion(sf::RenderWindow&, QuestionType*, MainMenu::QuizTopic);
	void displayAnswerOptions(sf::RenderWindow&, QuestionType*);
	string handleUserInteraction(sf::RenderWindow&, sf::Time, QuestionType*, UserInterface<QuestionType>&, MainMenu::QuizTopic);
	bool displayFeedback(sf::RenderWindow&, string, QuestionType*);
	void displayGameInfo(sf::RenderWindow&, const QuestionType*, int, int, int, int, const MainMenu::QuizTopic&);
	void displayNavigationButtons(sf::RenderWindow&);
	string displayEndGameScreen(sf::RenderWindow&, int);
};

