#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

class Question
{
public:
    Question();
    Question(QString description, void (*func)(QString &));
    void setDescription(const QString &description);
    QString getDescription();
    void setFunc(void (*func)(QString &));
    void exec(QString &result);

private:
    QString m_description;
    void (*m_func)(QString &);
};

#endif // QUESTION_H
