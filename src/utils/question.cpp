#include "question.h"

Question::Question()
{
    m_description = "";
    m_func = nullptr;
}

Question::Question(QString description, void (*func)(QString, QString &))
{
    m_description = description;
    m_func = func;
}

void Question::setDescription(const QString &description)
{
    m_description = description;
}

QString Question::getDescription()
{
    return m_description;
}

void Question::setFunc(void (*func)(QString, QString &))
{
    m_func = func;
}

void Question::exec(QString input, QString &result)
{
    if (m_func != nullptr)
    {
        m_func(input, result);
    }
    else
    {
        result = "";
    }
}
