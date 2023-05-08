#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H

#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

struct MultipleChoiceQuestion
{
    string question;
    vector<string> answers;
    string correctAnswer;
};

class QuestionBank
{
public:
    vector<MultipleChoiceQuestion> getQuestions(int);

private:
    vector<MultipleChoiceQuestion> quizQuestions;
    unordered_set<int> usedQuestions;
    void loadQuestions(string);
    MultipleChoiceQuestion getRandomQuestion();
};

#endif
