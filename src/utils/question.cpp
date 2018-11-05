#include "question.h"

Question::Question()
{
    m_description = "";
    m_func = NULL;
}

Question::Question(QString description, void (*func)(QString &))
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

void Question::setFunc(void (*func)(QString &))
{
    m_func = func;
}

void Question::exec(QString &result)
{
    if (m_func != NULL)
    {
        m_func(result);
    }
    else
    {
        result = "";
    }
}
