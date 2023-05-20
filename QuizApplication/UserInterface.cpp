#include "UserInterface.h"
#include <string>
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "GlobalVariables.h"
#include <iostream>

using namespace std;

template<class QuestionType>
void UserInterface<QuestionType>::displayQuestion(sf::RenderWindow& window, QuestionType q, MainMenu::QuizTopic selectedTopic)
{
    sf::Font font;
    font.loadFromFile("Trajan Bold.ttf");

    sf::Text questionText;
    questionText.setFont(font);
    questionText.setCharacterSize(32);
    questionText.setString(q.question);

    // Set the maximum width of the text to be the width of the window
    float maxWidth = window.getSize().x - 100; // assuming 100 pixels padding on either side
    questionText.setOutlineThickness(5);
    questionText.setOutlineColor(sf::Color::Black);
    questionText.setFillColor(sf::Color::White);

    // Scale the text if it is wider than the window
    if (questionText.getGlobalBounds().width >= maxWidth) {
        float scaleFactor = maxWidth / questionText.getGlobalBounds().width;
        questionText.setScale(scaleFactor, scaleFactor);
    }

    int width = window.getSize().x;
    int height = window.getSize().y;

    // Load background image based on the selected topic
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    if (selectedTopic == MainMenu::QuizTopic::Football) {
        backgroundTexture.loadFromFile("background_football.jpg");
    }
    else if (selectedTopic == MainMenu::QuizTopic::Cricket) {
        backgroundTexture.loadFromFile("background_cricket.jpg");
    }
    else if (selectedTopic == MainMenu::QuizTopic::Rugby) {
        backgroundTexture.loadFromFile("background_rugby.jpg");
    }

    // Set the background sprite properties
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getLocalBounds().width,
        window.getSize().y / backgroundSprite.getLocalBounds().height
    );

    // Draw the background sprite first
    window.draw(backgroundSprite);

    sf::FloatRect textBounds = questionText.getGlobalBounds();
    float textXPosition = (width - textBounds.width) / 2.f;
    questionText.setPosition(textXPosition, height / 2 - 175);

    window.draw(questionText);
}

template<class QuestionType>
void UserInterface<QuestionType>::displayAnswerOptions(sf::RenderWindow& window, QuestionType q)
{
    sf::Font font;
    font.loadFromFile("Trajan Bold.ttf");

    int width = window.getSize().x;
    int height = window.getSize().y;

    for (int i = 0; i < q.answers.size(); i++)
    {

        sf::Text answerText;
        answerText.setFont(font);
        answerText.setCharacterSize(28);
        answerText.setString(q.answers[i]);
        answerText.setOutlineColor(sf::Color::Black);
        answerText.setOutlineThickness(5);
        answerText.setPosition(sf::Vector2f(width / 3, height / 2 + i * 50 - 100));

        // Check if the mouse is hovering over an answer
        if (answerText.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
        {
            answerText.setFillColor(sf::Color::Green);
        }
        else
        {
            answerText.setFillColor(sf::Color::White);
        }
        window.draw(answerText);
    }
}




template<class QuestionType>
string UserInterface<QuestionType>::handleUserInteraction(sf::RenderWindow& window, sf::Time timerTime, QuestionType q, UserInterface ui, MainMenu::QuizTopic selectedTopic)
{
    sf::Clock clock;
    sf::Text timeText;
    sf::Font font;
    font.loadFromFile("impact.ttf");
    timeText.setFont(font);
    timeText.setCharacterSize(28);
    timeText.setPosition(window.getSize().x - 250, window.getSize().y - 850);

    int height = window.getSize().y;
    int width = window.getSize().x;
    bool answered = false;
    string selectedAnswer = "";
    int buttonSpacing = 50;
    int buttonYPosition = height / 2 - ((q.answers.size() * buttonSpacing) / 2);
    if (typeid(QuestionType) == typeid(TrueFalseQuestion)) { buttonYPosition -= 50; }

    sf::Clock timer;
    while (!answered && clock.getElapsedTime() < timerTime) {
        sf::Event event;
        sf::Time elapsed = clock.getElapsedTime();
        int remainingTime = static_cast<int>(timerTime.asSeconds() - elapsed.asSeconds());
        timeText.setString("Time remaining: " + to_string(remainingTime) + "s");

        window.clear();
        ui.displayQuestion(window, q, selectedTopic);
        ui.displayAnswerOptions(window, q);
        timeText.setPosition(window.getSize().x - 450, window.getSize().y - 850);
        window.draw(timeText);
        ui.displayGameInfo(window, q, score, currentLevel, questionNumber, NUM_QUESTIONS, selectedTopic);
        ui.displayNavigationButtons(window);
        window.display();

        while (window.pollEvent(event) && !answered) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                int exitButtonX = window.getSize().x - 250;
                int exitButtonY = window.getSize().y - 100;
                int exitButtonWidth = 200;
                int exitButtonHeight = 50;
                if (mousePosition.x >= exitButtonX && mousePosition.x < exitButtonX + exitButtonWidth &&
                    mousePosition.y >= exitButtonY && mousePosition.y < exitButtonY + exitButtonHeight) {
                    window.close();
                }
                for (int j = 0; j < q.answers.size(); j++) {
                    int buttonTop = buttonYPosition + j * buttonSpacing;
                    int buttonBottom = buttonTop + 40;
                    if (event.mouseButton.y >= buttonTop && event.mouseButton.y < buttonBottom) {
                        selectedAnswer = q.answers[j];
                        answered = true;
                        break;
                    }
                }
            }
        }
    }
    return selectedAnswer;
}


template <class QuestionType>
bool UserInterface<QuestionType>::displayFeedback(sf::RenderWindow& window, string userAnswer, QuestionType q)
{
    bool correct = false;
    // Load the gif textures
    sf::Texture correctTexture;
    correctTexture.loadFromFile("correct.gif");
    sf::Texture incorrectTexture;
    incorrectTexture.loadFromFile("incorrect.gif");

    sf::Sprite backgroundSprite;
    //sf::SoundBuffer buffer;
    //buffer.loadFromFile((userAnswer == q.correctAnswer) ? "correct.mp3" : "incorrect.mp3");
    //sf::Sound sound;
    //sound.setBuffer(buffer);

    //sound.setBuffer(buffer);
    if (userAnswer == q.correctAnswer) {
        backgroundSprite.setTexture(correctTexture);
        correct = true;
    }
    else {
        backgroundSprite.setTexture(incorrectTexture);
    }
    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getLocalBounds().width,
        window.getSize().y / backgroundSprite.getLocalBounds().height
    );
    window.draw(backgroundSprite);

    // Create the feedback text
    sf::Font font;
    font.loadFromFile("Trajan Bold.ttf");
    sf::Text feedbackText;
    feedbackText.setFont(font);
    feedbackText.setCharacterSize(24);
    feedbackText.setFillColor((userAnswer == q.correctAnswer) ? sf::Color::Green : sf::Color::Red);
    feedbackText.setString((userAnswer == q.correctAnswer) ? "CORRECT!" : "INCORRECT! The correct answer is: " + q.correctAnswer);

    float maxWidth = window.getSize().x - 200; // assuming 100 pixels padding on either side
    feedbackText.setPosition((maxWidth - feedbackText.getGlobalBounds().width) / 2.f + 100, 100);

    // Scale the text if it is wider than the window
    if (feedbackText.getGlobalBounds().width >= maxWidth) {
        string textString = feedbackText.getString();
        string firstLine, secondLine;
        int index = textString.size() / 2;
        while (textString[index] != ' ') {
            index++;
        }
        firstLine = textString.substr(0, index);
        secondLine = textString.substr(index + 1);
        feedbackText.setString(firstLine + "\n" + secondLine);
    }
    // sound.play();
    window.draw(feedbackText);
    return correct;
}

template <class QuestionType>
void UserInterface<QuestionType>::displayGameInfo(sf::RenderWindow& window, QuestionType question, int score, int level, int questionNumber, int numQuestions, MainMenu::QuizTopic selectedTopic)
{
    sf::Font font;
    font.loadFromFile("impact.ttf");

    int width = window.getSize().x;
    int height = window.getSize().y;

    // Display level number
    sf::Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(28);
    levelText.setString("Level: " + std::to_string(level));
    levelText.setPosition(sf::Vector2f(20, 20));
    window.draw(levelText);

    // Display current score
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(28);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition(sf::Vector2f(width - 220, 20));
    window.draw(scoreText);

    // Display number of questions
    sf::Text questionNumberText;
    questionNumberText.setFont(font);
    questionNumberText.setCharacterSize(28);
    questionNumberText.setString("Question " + std::to_string(questionNumber) + "/" + std::to_string(numQuestions*numLevels));
    questionNumberText.setPosition(sf::Vector2f(width / 2 - 100, 20));
    window.draw(questionNumberText);
}

template<class QuestionType>
void UserInterface<QuestionType>::displayNavigationButtons(sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("impact.ttf");

    int width = window.getSize().x;
    int height = window.getSize().y;

    // Main Menu Button
    sf::RectangleShape mainMenuButton(sf::Vector2f(200, 50));
    mainMenuButton.setFillColor(sf::Color::Black);
    mainMenuButton.setPosition(sf::Vector2f(50, height - 100));

    sf::Text mainMenuText;
    mainMenuText.setFont(font);
    mainMenuText.setCharacterSize(36);
    mainMenuText.setString("Main Menu");
    mainMenuText.setFillColor(sf::Color::White);
    mainMenuText.setPosition(sf::Vector2f(60, height - 95));

    // Exit Button
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color::Black);
    exitButton.setPosition(sf::Vector2f(width - 250, height - 100));

    sf::Text exitText;
    exitText.setFont(font);
    exitText.setCharacterSize(36);
    exitText.setString("Exit");
    exitText.setFillColor(sf::Color::Red);
    exitText.setPosition(sf::Vector2f(width - 220, height - 95));

    // Draw the buttons and text
    window.draw(mainMenuButton);
    window.draw(mainMenuText);
    window.draw(exitButton);
    window.draw(exitText);
}


template class UserInterface<MultipleChoiceQuestion>;
template class UserInterface<TrueFalseQuestion>;