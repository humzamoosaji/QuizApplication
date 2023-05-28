#include "QuestionBank.h"
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "UserInterface.h"
#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include "GlobalVariables.h"
#include "TicTacToe.h"

int main()
{
    srand(time(0));

    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(videoMode, "Quiz Application", sf::Style::Fullscreen);

    MainMenu menu(window.getSize().x, window.getSize().y);

    UserInterface<MultipleChoiceQuestion> ui;

    UserInterface<TrueFalseQuestion> ui2;

    sf::Time timer;

    MainMenu::QuizTopic selectedTopic = MainMenu::None;

    bool isMultipleChoice = false;

    bool gameOver = false;;

    window.clear();
    menu.draw(window);
    window.display();
    int levels = numLevels;
    while (window.isOpen()) {
        if (selectedTopic == MainMenu::None)
        {
           selectedTopic = menu.getSelectedTopic(window);
        }
        if (selectedTopic != MainMenu::TicTacToe && selectedTopic != MainMenu::None) 
        {
            QuestionBank<MultipleChoiceQuestion> mcqbank;

            QuestionBank<TrueFalseQuestion> tfbank;
            for (int level = 3; level > 0; --level)
            {
                string fileName = menu.getFileName(selectedTopic, isMultipleChoice);
                vector<TrueFalseQuestion> tfquestions = tfbank.getQuestions(NUM_QUESTIONS / 2, fileName);
                isMultipleChoice = true;
                fileName = menu.getFileName(selectedTopic, isMultipleChoice);
                vector<MultipleChoiceQuestion> mcquestions = mcqbank.getQuestions(NUM_QUESTIONS / 2, fileName);
                int numMCQused = 0;
                int numTFused = 0;
                int questionType;
                timer = sf::seconds((5 * level));
                for (int i = 0; i < NUM_QUESTIONS; i++)
                {
                    questionType = rand() % 2;
                    if (questionType == 0 && numMCQused < NUM_QUESTIONS / 2)
                    {
                        MultipleChoiceQuestion* currentQuestion = &mcquestions[numMCQused];
                        sf::Event event;
                        while (window.pollEvent(event))
                        {
                            if (event.type == sf::Event::Closed)
                            {
                                window.close();
                            }
                        }
                        window.clear();
                        ui.displayGameInfo(window, currentQuestion, score, currentLevel, questionNumber, NUM_QUESTIONS, selectedTopic);
                        ui.displayQuestion(window, currentQuestion, selectedTopic);
                        ui.displayAnswerOptions(window, currentQuestion);
                        string userResponse = ui.handleUserInteraction(window, timer, currentQuestion, ui, selectedTopic);
                        window.display();
                        window.clear();
                        if (ui.displayFeedback(window, userResponse, currentQuestion) == true)
                            score++;
                        sf::sleep(sf::milliseconds(1000));
                        numMCQused++;
                    }
                    else if (questionType == 1 && numTFused < NUM_QUESTIONS / 2)
                    {
                        TrueFalseQuestion* currentQuestion = &tfquestions[numTFused];
                        sf::Event event;
                        while (window.pollEvent(event))
                        {
                            if (event.type == sf::Event::Closed)
                            {
                                window.close();
                            }
                        }
                        window.clear();
                        ui2.displayQuestion(window, currentQuestion, selectedTopic);
                        ui2.displayAnswerOptions(window, currentQuestion);
                        string userResponse = ui2.handleUserInteraction(window, timer, currentQuestion, ui2, selectedTopic);
                        window.display();
                        window.clear();
                        if (ui2.displayFeedback(window, userResponse, currentQuestion) == true)
                            score++;
                        sf::sleep(sf::milliseconds(1000));
                        numTFused++;
                    }
                    else {
                        i--;
                        questionNumber--;
                    }
                    questionNumber++;
                }
                currentLevel++;
                isMultipleChoice = false;
                gameOver = currentLevel == 4 ? true : false;
            }
        }
        else if (selectedTopic == MainMenu::TicTacToe)
        {
            TicTacToe tictactoe;
            tictactoe.playGame();
            gameOver = true;
        }
        if (gameOver) 
        {
            string response = ui.displayEndGameScreen(window, score);
            if (response == "main menu") {
                score = 0;
                questionNumber = 1;
                currentLevel = 1;
                window.clear();
                menu.draw(window);
                window.display();
                selectedTopic = MainMenu::None;
                gameOver = false;
            }
            else if(response == "exit")
            {
                window.close();
            }
        }
    }
    return 0;
}