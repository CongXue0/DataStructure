#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H

#include <QObject>
#include "question.h"
#include "tool.h"

class QuestionBank : public QObject
{
    Q_OBJECT
public:
    explicit QuestionBank(QObject *parent = 0);
    void addQuestion(int chapterIndex, Question question);
    int getQuestionCount(int chapterIndex);
    QString getQuestionDescription(int chapterIndex, int questionIndex);
    void execSolution(int chapterIndex, int questionIndex, QString input, QString &result);
signals:

public slots:

private:
    QList<Question> m_list[MAX_CHAPTER_NUM];

};

#endif // QUESTIONBANK_H
