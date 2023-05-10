// this will be the main class of the application
#include "QuestionBank.h"
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "UserInterface.h"
#include <iostream>

using namespace std;
class QuizApplication
{
private: 
	int score;
	int numQuestions;
	int currentQuestion;
	vector<MultipleChoiceQuestion> questions;
	string playerName;
};

int main()
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(videoMode, "Quiz Application", sf::Style::Fullscreen);

    MainMenu menu(window.getSize().x, window.getSize().y);

    QuestionBank qb;
        
    vector<MultipleChoiceQuestion> questions = qb.getQuestions(10);

    UserInterface ui;

    sf::Time timer = sf::seconds(5.0f);


    while (window.isOpen())
    {
        window.clear();
        menu.draw(window);
        window.display();
        sf::sleep(sf::milliseconds(1000));
        for (int i = 0; i < questions.size(); i++)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            window.clear();
            ui.displayQuestion(window, questions[i]);
            ui.displayAnswerOptions(window, questions[i]);
            string userResponse = ui.getUserAnswer(window, timer, questions[i], ui);
            window.display();
            window.clear();
            ui.displayFeedback(window, userResponse, questions[i]);
            window.display();
            sf::sleep(sf::milliseconds(1000));
        }
    }
}