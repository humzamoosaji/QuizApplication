#include "QuestionBank.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
void QuestionBank::loadQuestions(std::string fileName)
{
    ifstream inputFile(fileName);

    std::string line;
    while (getline(inputFile, line)) {
        MultipleChoiceQuestion question;
        question.question = line;

        int numAnswers = 4;
        for (int i = 0; i < numAnswers; i++) {
            getline(inputFile, line);
            question.answers.push_back(line);
        }

        std::getline(inputFile, line);
        question.correctAnswer = line;

        quizQuestions.push_back(question);
    }
}

MultipleChoiceQuestion QuestionBank::getRandomQuestion()
{
    srand(time(0));
    int randomQuestionIndex = rand() % quizQuestions.size();
    while (usedQuestions.find(randomQuestionIndex) != usedQuestions.end())
    {
        randomQuestionIndex = rand() % quizQuestions.size();
    }
    usedQuestions.insert(randomQuestionIndex);
    return quizQuestions[randomQuestionIndex];
}

vector<MultipleChoiceQuestion> QuestionBank::getQuestions(int numQuestions)
{
    loadQuestions("FootballMCQEasy.txt");
    vector<MultipleChoiceQuestion> questions;
    for (int i = 0; i < numQuestions; i++)
    {
        questions.push_back(QuestionBank::getRandomQuestion());
    }
    return questions;
}
