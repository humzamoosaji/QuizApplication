#include "QuestionBank.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

template<class QuestionType>
void QuestionBank<QuestionType>::loadQuestions(std::string fileName)
{
    ifstream inputFile(fileName);

    std::string line;
    while (getline(inputFile, line)) {
        QuestionType question;
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

template<class QuestionType>
QuestionType QuestionBank<QuestionType>::getRandomQuestion()
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

template<class QuestionType>
vector<QuestionType> QuestionBank<QuestionType>::getQuestions(int numQuestions, string filename)
{
    loadQuestions(filename);
    vector<QuestionType> questions;
    for (int i = 0; i < numQuestions; i++)
    {
        questions.push_back(QuestionBank::getRandomQuestion());
    }
    return questions;
}
