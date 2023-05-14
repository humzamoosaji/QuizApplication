#include "QuestionBank.h"
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "UserInterface.h"
#include <iostream>
#include <vector>

void run()
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(videoMode, "Quiz Application", sf::Style::Fullscreen);

    MainMenu menu(window.getSize().x, window.getSize().y);

    QuestionBank<MultipleChoiceQuestion> mcqbank;

    QuestionBank<TrueFalseQuestion> tfbank;

    UserInterface<MultipleChoiceQuestion> ui;

    UserInterface<TrueFalseQuestion> ui2;

    sf::Time timer = sf::seconds(5.0f);

    MainMenu::QuizTopic selectedTopic = MainMenu::None;

    bool isMultipleChoice = true; // Flag to track the current question type

    while (window.isOpen())
    {
        window.clear();
        menu.draw(window);
        window.display();

        if (selectedTopic == MainMenu::None)
        {
            // Get the selected quiz topic from the MainMenu
            selectedTopic = menu.getSelectedTopic(window);
        }
        else
        {
            string fileName = menu.getFileName(selectedTopic, isMultipleChoice);

            if (!fileName.empty())
            {
                vector<MultipleChoiceQuestion> mcquestions = mcqbank.getQuestions(5, fileName);
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
                    ui.displayQuestion(window, mcquestions[i], selectedTopic);
                    ui.displayAnswerOptions(window, mcquestions[i]);
                    string userResponse = ui.getUserAnswer(window, timer, mcquestions[i], ui, selectedTopic);
                    window.display();
                    window.clear();
                    ui.displayFeedback(window, userResponse, mcquestions[i]);
                    window.display();
                    sf::sleep(sf::milliseconds(1000));
                }
                isMultipleChoice = false;
                fileName = menu.getFileName(selectedTopic, isMultipleChoice);
                vector<TrueFalseQuestion> tfquestions = tfbank.getQuestions(5, fileName);
                for (int i = 0; i < tfquestions.size(); i++)
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
                    ui2.displayQuestion(window, tfquestions[i], selectedTopic);
                    ui2.displayAnswerOptions(window, tfquestions[i]);
                    string userResponse = ui2.getUserAnswer(window, timer, tfquestions[i], ui2, selectedTopic);
                    window.display();
                    window.clear();
                    ui2.displayFeedback(window, userResponse, tfquestions[i]);
                    window.display();
                    sf::sleep(sf::milliseconds(1000));
                }
            }
            // Reset the selected topic and toggle the question type after completing the quiz
            selectedTopic = MainMenu::None;
            isMultipleChoice = !isMultipleChoice;
        }
    }
    return 0;
}