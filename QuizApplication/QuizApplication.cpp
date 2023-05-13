// this will be the main class of the application
#include "QuestionBank.h"
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "UserInterface.h"
#include <iostream>

int main()
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(videoMode, "Quiz Application", sf::Style::Fullscreen);

    MainMenu menu(window.getSize().x, window.getSize().y);

    QuestionBank<MultipleChoiceQuestion> mcqbank;

    QuestionBank<TrueFalseQuestion> tfbank;

    UserInterface ui;

    sf::Time timer = sf::seconds(5.0f);

    MainMenu::QuizTopic selectedTopic = MainMenu::None;

    while (window.isOpen())
    {
        window.clear();
        menu.draw(window);
        window.display();

        vector<MultipleChoiceQuestion> mcquestions;

        if (selectedTopic == MainMenu::None)
        {
            // Get the selected quiz topic from the MainMenu
            selectedTopic = menu.getSelectedTopic(window);
        }
        else
        {
            string fileName = menu.getFileName(selectedTopic);

            if (!fileName.empty())
            {
                mcquestions = mcqbank.getQuestions(10, fileName);
            }
            for (int i = 0; i < mcquestions.size(); i++)
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
                ui.displayQuestion(window, mcquestions[i]);
                ui.displayAnswerOptions(window, mcquestions[i]);
                string userResponse = ui.getUserAnswer(window, timer, mcquestions[i], ui);
                window.display();
                window.clear();
                ui.displayFeedback(window, userResponse, mcquestions[i]);
                window.display();
                sf::sleep(sf::milliseconds(1000));
            }

            // Reset the selected topic after completing the quiz
            selectedTopic = MainMenu::None;
        }
    }
}