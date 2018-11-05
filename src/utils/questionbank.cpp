#include "questionbank.h"

QuestionBank::QuestionBank(QObject *parent) : QObject(parent)
{
}

void QuestionBank::addQuestion(int chapterIndex, Question question)
{
    if (chapterIndex < 0)
        chapterIndex = 0;
    if (chapterIndex > MAX_CHAPTER_NUM - 1)
        chapterIndex = MAX_CHAPTER_NUM - 1;
    m_list[chapterIndex].append(question);
}

int QuestionBank::getQuestionCount(int chapterIndex)
{
    if (chapterIndex < 0)
        chapterIndex = 0;
    if (chapterIndex > MAX_CHAPTER_NUM - 1)
        chapterIndex = MAX_CHAPTER_NUM - 1;
    return m_list[chapterIndex].count();
}

QString QuestionBank::getQuestionDescription(int chapterIndex, int questionIndex)
{
    if (chapterIndex < 0)
        chapterIndex = 0;
    if (chapterIndex > MAX_CHAPTER_NUM - 1)
        chapterIndex = MAX_CHAPTER_NUM - 1;
    int count = m_list[chapterIndex].count();
    if (count == 0)
        return "";
    if (questionIndex < 0)
        questionIndex = 0;
    if (questionIndex > count - 1)
        questionIndex = count - 1;
    return m_list[chapterIndex][questionIndex].getDescription();
}

void QuestionBank::execSolution(int chapterIndex, int questionIndex, QString &result)
{
    if (chapterIndex < 0)
        chapterIndex = 0;
    if (chapterIndex > MAX_CHAPTER_NUM - 1)
        chapterIndex = MAX_CHAPTER_NUM - 1;
    int count = m_list[chapterIndex].count();
    if (count == 0)
    {
        result = "";
        return;
    }
    if (questionIndex < 0)
        questionIndex = 0;
    if (questionIndex > count - 1)
        questionIndex = count - 1;
    m_list[chapterIndex][questionIndex].exec(result);
}
