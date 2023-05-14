#include "UserInterface.h"
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;

template<class QuestionType>
void UserInterface<QuestionType>::displayQuestion(sf::RenderWindow& window, QuestionType q, MainMenu::QuizTopic selectedTopic)
{
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text questionText;
    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setString(q.question);

    // Set the maximum width of the text to be the width of the window
    float maxWidth = window.getSize().x - 100; // assuming 100 pixels padding on either side
    questionText.setOutlineThickness(2.f);
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

    questionText.setPosition(sf::Vector2f(width / 3, height / 2 - 200));
    window.draw(questionText);
}

template<class QuestionType>
void UserInterface<QuestionType>::displayAnswerOptions(sf::RenderWindow& window, QuestionType q)
{
    sf::Font font;
    font.loadFromFile("arial.ttf");

    int width = window.getSize().x;
    int height = window.getSize().y;

    for (int i = 0; i < q.answers.size(); i++)
    {
        sf::RectangleShape answerButton(sf::Vector2f(400, 40));
        answerButton.setFillColor(sf::Color::Transparent);
        answerButton.setOutlineThickness(0);
        answerButton.setPosition(sf::Vector2f(width / 3, height / 2 + i * 50 - 100));
        window.draw(answerButton);

        sf::Text answerText;
        answerText.setFont(font);
        answerText.setCharacterSize(24);
        answerText.setString(q.answers[i]);
        answerText.setPosition(sf::Vector2f(width / 3, height / 2 + i * 50 - 100));
        window.draw(answerText);
    }
}

template<class QuestionType>
string UserInterface<QuestionType>::getUserAnswer(sf::RenderWindow& window, sf::Time timerTime, QuestionType q, UserInterface ui, MainMenu::QuizTopic selectedTopic)
{
    sf::Clock clock;
    sf::Text timeText;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    timeText.setFont(font);
    timeText.setCharacterSize(24);
    timeText.setPosition(window.getSize().x - 250, window.getSize().y - 850);

    bool answered = false;
    string selectedAnswer = "";
    int buttonYPosition = window.getSize().y / 2 - 100;
    int buttonSpacing = 50;
    sf::Clock timer;
    while (!answered && clock.getElapsedTime() < timerTime) {
        sf::Event event;
        sf::Time elapsed = clock.getElapsedTime();
        int remainingTime = static_cast<int>(timerTime.asSeconds() - elapsed.asSeconds());
        timeText.setString("Time remaining: " + to_string(remainingTime) + "s");

        window.clear();
        ui.displayQuestion(window, q, selectedTopic);
        ui.displayAnswerOptions(window, q);
        timeText.setPosition(window.getSize().x - 250, window.getSize().y - 850);
        window.draw(timeText);
        window.display();

        while (window.pollEvent(event) && !answered) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
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
void UserInterface<QuestionType>::displayFeedback(sf::RenderWindow& window, string userAnswer, QuestionType q)
{
    // Load the gif textures
    sf::Texture correctTexture;
    correctTexture.loadFromFile("correct.gif");
    sf::Texture incorrectTexture;
    incorrectTexture.loadFromFile("incorrect.gif");

    // Create the background sprite
    sf::Sprite backgroundSprite;
    if (userAnswer == q.correctAnswer) {
        backgroundSprite.setTexture(correctTexture);
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
    font.loadFromFile("arial.ttf");
    sf::Text feedbackText;
    feedbackText.setFont(font);
    feedbackText.setCharacterSize(24);
    feedbackText.setFillColor((userAnswer == q.correctAnswer) ? sf::Color::Green : sf::Color::Red);
    feedbackText.setString((userAnswer == q.correctAnswer) ? "CORRECT!" : "INCORRECT! The correct answer is: " + q.correctAnswer);
    feedbackText.setOutlineThickness(2.f);
    feedbackText.setOutlineColor(sf::Color::Black);

    float maxWidth = window.getSize().x - 200; // assuming 100 pixels padding on either side
    feedbackText.setPosition((window.getSize().x - feedbackText.getGlobalBounds().width) / 2.f, 150);

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

    window.draw(feedbackText);
}

template class UserInterface<MultipleChoiceQuestion>;
template class UserInterface<TrueFalseQuestion>;