// this will be the main class of the application
#include "QuestionBank.h"
#include <SFML/Graphics.hpp>
#include "MainMenu.h"

using namespace std;
class QuizApplication
{
private: 
	int score;
	int numQuestions;
	int currentQuestion;
	QuestionBank questions;
	string playerName;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Quiz Application");

    MainMenu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        menu.draw(window);
        window.display();
    }
}