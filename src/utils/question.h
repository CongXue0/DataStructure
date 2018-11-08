#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

class Question
{
public:
    Question();
    Question(QString description, void (*func)(QString, QString &));
    void setDescription(const QString &description);
    QString getDescription();
    void setFunc(void (*func)(QString, QString &));
    void exec(QString input, QString &result);

private:
    QString m_description;
    void (*m_func)(QString, QString &);
};

#endif // QUESTION_H
