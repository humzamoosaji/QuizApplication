#include "QuestionBank.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

template<class QuestionType>
void QuestionBank<QuestionType>::loadQuestions(string fileName)
{
    ifstream inputFile(fileName);

    string line;

    while (getline(inputFile, line)) {
        QuestionType question;
        question.question = line;

        int numAnswers = (typeid(QuestionType) == typeid(MultipleChoiceQuestion)) ? 4 : 2;

        for (int i = 0; i < numAnswers; i++) {
            getline(inputFile, line);
            question.answers.push_back(line);
        }

        getline(inputFile, line);
        question.correctAnswer = line;

        quizQuestions.push_back(question);
    }
}

template<class QuestionType>
QuestionType QuestionBank<QuestionType>::getRandomQuestion()
{
    int randomQuestionIndex = rand() % quizQuestions.size();
    while (usedQuestions.find(randomQuestionIndex) != usedQuestions.end())
    {
        randomQuestionIndex = rand() % quizQuestions.size();
    }
    usedQuestions.insert(randomQuestionIndex);
    return quizQuestions[randomQuestionIndex];
}

template<class QuestionType>
vector<QuestionType> QuestionBank<QuestionType>::getQuestions(int numQuestions, std::string filename)
{
    loadQuestions(filename);
    vector<QuestionType> questions;
    for (int i = 0; i < numQuestions; i++)
    {
        questions.push_back(getRandomQuestion());
    }
    return questions;
}

template class QuestionBank<MultipleChoiceQuestion>;
template class QuestionBank<TrueFalseQuestion>;
