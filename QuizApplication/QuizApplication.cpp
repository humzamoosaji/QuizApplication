#include "QuestionBank.h"
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "UserInterface.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "GlobalVariables.h"
#include "TicTacToe.h"

int main()
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(videoMode, "Quiz Application", sf::Style::Fullscreen);

    MainMenu menu(window.getSize().x, window.getSize().y);

    QuestionBank<MultipleChoiceQuestion> mcqbank;

    QuestionBank<TrueFalseQuestion> tfbank;

    UserInterface<MultipleChoiceQuestion> ui;

    UserInterface<TrueFalseQuestion> ui2;

    sf::Time timer;

    MainMenu::QuizTopic selectedTopic = MainMenu::None;

    bool isMultipleChoice = false;

    bool gameOver = false;;

    window.clear();
    menu.draw(window);
    window.display();
    while (window.isOpen()) {
        for (int level = numLevels; level > 0; level--)
        {
            //ui.displayLevelDifficulty(window, level);
            timer = sf::seconds((5 * level));
            if (selectedTopic == MainMenu::None)
            {
                selectedTopic = menu.getSelectedTopic(window);
            }
            if (selectedTopic != MainMenu::TicTacToe && selectedTopic != MainMenu::None) {
                string fileName = menu.getFileName(selectedTopic, isMultipleChoice);
                if (!fileName.empty() && selectedTopic != MainMenu::None)
                {
                    vector<TrueFalseQuestion> tfquestions = tfbank.getQuestions(NUM_QUESTIONS / 2, fileName);
                    isMultipleChoice = true;
                    fileName = menu.getFileName(selectedTopic, isMultipleChoice);
                    vector<MultipleChoiceQuestion> mcquestions = mcqbank.getQuestions(NUM_QUESTIONS / 2, fileName);

                    int numMCQused = 0;
                    int numTFused = 0;
                    int questionType;

                    for (int i = 0; i < NUM_QUESTIONS; i++)
                    {
                        srand(time(0));
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
                }
                currentLevel++;
                isMultipleChoice = false;
                gameOver = currentLevel == 4 ? true : false;
            }
            else if (selectedTopic == MainMenu::TicTacToe)
            {
                TicTacToe tictactoe;
                tictactoe.playGame();
                gameOver = true;
            }
            if (gameOver) {
                if (ui.displayEndGameScreen(window, score) == "main menu") {
                    score = 0;
                    questionNumber = 1;
                    level = numLevels;
                    currentLevel = 1;
                    window.clear();
                    menu.draw(window);
                    window.display();
                    selectedTopic = MainMenu::None;
                    gameOver = false;
                }
            }
        }
    }
    return 0;
}