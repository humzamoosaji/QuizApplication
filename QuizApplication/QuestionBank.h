#pragma once
#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H

#include <string>
#include <unordered_set>
#include <stack>
#include <vector>
#include <set>
#include <fstream>
#include <typeinfo>
#include <string>

using namespace std;

struct MultipleChoiceQuestion
{
    string question;
    vector<string> answers;
    string correctAnswer;
};

struct TrueFalseQuestion
{
    string question;
    vector<string> answers;
    string correctAnswer;
};

template<class QuestionType>
class QuestionBank
{
public:
    vector<QuestionType> getQuestions(int, string);

private:
    vector<QuestionType> quizQuestions;
    unordered_set<int> usedQuestions;
    void loadQuestions(string);
    QuestionType getRandomQuestion();
};

#endif
