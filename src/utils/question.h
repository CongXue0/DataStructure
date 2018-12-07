#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

class Question
{
public:
    Question();
    Question(QString description, void (*func)(), int level, QString source);
    void setDescription(const QString &description);
    QString getDescription();
    void setFunc(void (*func)());
    void exec();
    int getLevel();
    QString getSource();

private:
    QString m_description;
    void (*m_func)();
    int m_level;//1-5
    QString m_source;

};

#endif // QUESTION_H
