#include "UserInterface.h"
#include <string>
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include "GlobalVariables.h"

using namespace std;

template<class QuestionType>
void UserInterface<QuestionType>::displayQuestion(sf::RenderWindow& window, QuestionType* q, MainMenu::QuizTopic selectedTopic)
{
    sf::Font font;
    font.loadFromFile("Trajan Bold.ttf");

    sf::Text questionText;
    questionText.setFont(font);
    questionText.setCharacterSize(32);
    questionText.setString(q->question);

    float maxWidth = window.getSize().x - 100;
    questionText.setOutlineThickness(5);
    questionText.setOutlineColor(sf::Color::Black);
    questionText.setFillColor(sf::Color::White);

    if (questionText.getGlobalBounds().width >= maxWidth) {
        float scaleFactor = maxWidth / questionText.getGlobalBounds().width;
        questionText.setScale(scaleFactor, scaleFactor);
    }

    int width = window.getSize().x;
    int height = window.getSize().y;

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

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getLocalBounds().width,
        window.getSize().y / backgroundSprite.getLocalBounds().height
    );

    window.draw(backgroundSprite);

    sf::FloatRect textBounds = questionText.getGlobalBounds();
    float textXPosition = (width - textBounds.width) / 2.f;
    questionText.setPosition(textXPosition, height / 2 - 175);

    window.draw(questionText);
}


template<class QuestionType>
void UserInterface<QuestionType>::displayAnswerOptions(sf::RenderWindow& window, QuestionType* q)
{
    sf::Font font;
    font.loadFromFile("Trajan Bold.ttf");

    int width = window.getSize().x;
    int height = window.getSize().y;

    for (int i = 0; i < q->answers.size(); i++)
    {
        sf::Text answerText;
        answerText.setFont(font);
        answerText.setCharacterSize(28);
        answerText.setString(q->answers[i]);
        answerText.setOutlineColor(sf::Color::Black);
        answerText.setOutlineThickness(5);
        answerText.setPosition(sf::Vector2f(width / 3.f, height / 2.f + i * 50.f - 100.f));

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
string UserInterface<QuestionType>::handleUserInteraction(sf::RenderWindow& window, sf::Time timerTime, QuestionType* q, UserInterface<QuestionType>& ui, MainMenu::QuizTopic selectedTopic)
{
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
    int buttonYPosition = height / 2 - ((q->answers.size() * buttonSpacing) / 2);
    
    if (typeid(QuestionType) == typeid(TrueFalseQuestion)) { buttonYPosition -= 50; }
    
    sf::SoundBuffer buffer;
    buffer.loadFromFile("timer.wav");
    
    sf::Sound sound(buffer);
    sound.play();
    sf::Clock clock;

    while (!answered && sound.getStatus() == sf::Music::Playing && sound.getPlayingOffset() < timerTime) {
        sf::Time elapsed = clock.getElapsedTime();
        sf::Event event;
        int remainingTime = timerTime.asSeconds() - elapsed.asSeconds();
        timeText.setString("Time remaining: " + to_string(remainingTime) + "s");

        window.clear();
        ui.displayQuestion(window, q, selectedTopic);
        ui.displayAnswerOptions(window, q);
        timeText.setPosition(window.getSize().x - timeText.getLocalBounds().width - 50, window.getSize().y - 850);
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
                int menuButtonX = 50;
                int ButtonY = window.getSize().y - 100;
                int ButtonWidth = 200;
                int ButtonHeight = 50;
                if (mousePosition.x >= exitButtonX && mousePosition.x < exitButtonX + ButtonWidth &&
                    mousePosition.y >= ButtonY && mousePosition.y < ButtonY + ButtonHeight)
                {
                    window.close();
                }
                for (int j = 0; j < q->answers.size(); j++) {
                    int buttonTop = buttonYPosition + j * buttonSpacing;
                    int buttonBottom = buttonTop + 40;
                    if (event.mouseButton.y >= buttonTop && event.mouseButton.y < buttonBottom) {
                        selectedAnswer = q->answers[j];
                        answered = true;
                        break;
                    }
                }
            }
        }
    }
    return selectedAnswer;
}

template<class QuestionType>
bool UserInterface<QuestionType>::displayFeedback(sf::RenderWindow& window, string userAnswer, QuestionType* q)
{
    bool correct = false;
    sf::Texture correctTexture;
    correctTexture.loadFromFile("correct.gif");
    sf::Texture incorrectTexture;
    incorrectTexture.loadFromFile("incorrect.gif");

    sf::Sprite backgroundSprite;

    sf::SoundBuffer buffer;
    buffer.loadFromFile((userAnswer == q->correctAnswer) ? "correct.wav" : "incorrect.wav");
    if (userAnswer == q->correctAnswer) {
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

    sf::Font font;
    font.loadFromFile("Trajan Bold.ttf");
    sf::Text feedbackText;
    feedbackText.setFont(font);
    feedbackText.setCharacterSize(24);
    feedbackText.setFillColor((userAnswer == q->correctAnswer) ? sf::Color::Green : sf::Color::Red);
    feedbackText.setString((userAnswer == q->correctAnswer) ? "CORRECT!" : "INCORRECT! The correct answer is: " + q->correctAnswer);

    float maxWidth = window.getSize().x - 200; // assuming 100 pixels padding on either side
    feedbackText.setPosition((maxWidth - feedbackText.getGlobalBounds().width) / 2.f + 100, 100);

    // ensure that the text fits onto the window
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
    window.draw(feedbackText);
    sf::Sound sound(buffer);
    window.display();
    sound.play();
    // This loop is necessary for the audio to play :: DO NOT DELETE
    while (sound.getStatus() == sf::Music::Playing) {}
    return correct;
}

template <class QuestionType>
void UserInterface<QuestionType>::displayGameInfo(sf::RenderWindow& window, const QuestionType* question, int score, int level, int questionNumber, int numQuestions, const MainMenu::QuizTopic& selectedTopic)
{
    sf::Font font;
    font.loadFromFile("impact.ttf");

    int width = window.getSize().x;
    int height = window.getSize().y;

    // Display level number
    sf::Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(28);
    levelText.setString("Level: " + to_string(level) + "/" + to_string(numLevels));
    levelText.setPosition(sf::Vector2f(20, 20));
    window.draw(levelText);

    // Display current score
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(28);
    scoreText.setString("Score: " + to_string(score));
    scoreText.setPosition(sf::Vector2f(width - 220, 20));
    window.draw(scoreText);

    // Display number of questions
    sf::Text questionNumberText;
    questionNumberText.setFont(font);
    questionNumberText.setCharacterSize(28);
    questionNumberText.setString("Question " + to_string(questionNumber) + "/" + to_string(numQuestions * 3));
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
    window.draw(exitButton);
    window.draw(exitText);
}

template <class QuestionType>
string UserInterface<QuestionType>::displayEndGameScreen(sf::RenderWindow& window, int score)
{
    sf::Font font;
    font.loadFromFile("impact.ttf");

    sf::Text endGameText;
    endGameText.setFont(font);
    endGameText.setCharacterSize(24);
    string scoreString = to_string(int(round((double(score) / (NUM_QUESTIONS * 3)) * 100)));
    string endGameMessage = "Game Over! You scored: " + scoreString + "%";
    endGameText.setString(endGameMessage);
    endGameText.setPosition(window.getSize().x / 2 - endGameText.getGlobalBounds().width / 2,
        window.getSize().y / 2 - endGameText.getGlobalBounds().height);

    sf::Text mainMenuButtonLabel;
    mainMenuButtonLabel.setFont(font);
    mainMenuButtonLabel.setCharacterSize(18);
    mainMenuButtonLabel.setString("Main Menu");
    mainMenuButtonLabel.setPosition(window.getSize().x / 2 - mainMenuButtonLabel.getGlobalBounds().width / 2,
        window.getSize().y / 2 + mainMenuButtonLabel.getGlobalBounds().height * 2);

    sf::Text exitButtonLabel;
    exitButtonLabel.setFont(font);
    exitButtonLabel.setCharacterSize(18);
    exitButtonLabel.setString("Exit");
    exitButtonLabel.setPosition(window.getSize().x / 2 - exitButtonLabel.getGlobalBounds().width / 2,
        window.getSize().y / 2 + exitButtonLabel.getGlobalBounds().height * 4);

    sf::RectangleShape mainMenuButton;
    mainMenuButton.setSize(sf::Vector2f(mainMenuButtonLabel.getGlobalBounds().width + 10,
        mainMenuButtonLabel.getGlobalBounds().height + 10));
    mainMenuButton.setPosition(window.getSize().x / 2 - mainMenuButton.getGlobalBounds().width / 2,
        window.getSize().y / 2 + mainMenuButtonLabel.getGlobalBounds().height * 2);
    mainMenuButton.setFillColor(sf::Color::Green);

    sf::RectangleShape exitButton;
    exitButton.setSize(sf::Vector2f(exitButtonLabel.getGlobalBounds().width + 10,
        exitButtonLabel.getGlobalBounds().height + 10));
    exitButton.setPosition(window.getSize().x / 2 - exitButton.getGlobalBounds().width / 2,
        window.getSize().y / 2 + exitButtonLabel.getGlobalBounds().height * 4);
    exitButton.setFillColor(sf::Color::Red);

    bool endGameScreenActive = true;
    while (endGameScreenActive)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return "exit";
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mainMenuButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    return "main menu";
                }

                if (exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    window.close();
                    return "exit";
                }
            }
        }

        window.clear();
        window.draw(endGameText);
        window.draw(mainMenuButton);
        window.draw(mainMenuButtonLabel);
        window.draw(exitButton);
        window.draw(exitButtonLabel);
        window.display();
    }

    return "restart";
}



template class UserInterface<MultipleChoiceQuestion>;
template class UserInterface<TrueFalseQuestion>;