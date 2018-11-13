#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

class Question
{
public:
    Question();
    Question(QString description, void (*func)(QString, QString &), int level, QString source);
    void setDescription(const QString &description);
    QString getDescription();
    void setFunc(void (*func)(QString, QString &));
    void exec(QString input, QString &result);
    int getLevel();
    QString getSource();

private:
    QString m_description;
    void (*m_func)(QString, QString &);
    int m_level;//1-5
    QString m_source;

};

#endif // QUESTION_H
