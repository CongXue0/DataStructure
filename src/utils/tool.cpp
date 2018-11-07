#include "tool.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDir>

QString Tool::readFileInfo(const QString &path)
{
    QString info;
    QFile file(path);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        info = QLatin1String(file.readAll());
        file.close();
        if (info.length() > 0 && QChar('\n') == info.at(info.length() - 1))
        {
            info = info.mid(0, info.length() - 1);
        }
    }
    return info;
}

void Tool::appendFileInfo(const QString &path, const QString &info)
{
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        if (!info.isEmpty())
        {
            QTextStream in(&file);
            in.setCodec(QTextCodec::codecForName("utf8"));
            in << info;
        }
        file.close();
    }
}

void Tool::writeFileInfo(const QString &path, const QString &info)
{
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        if (!info.isEmpty())
        {
            QTextStream in(&file);
            in.setCodec(QTextCodec::codecForName("utf8"));
            in << info;
        }
        file.close();
    }
}

bool Tool::makePath(const QString &path)
{
    QDir dir;
    if (!dir.exists(path))
    {
        return dir.mkpath(path);
    }
    return true;
}

bool Tool::makeDir(const QString &path)
{
    QDir dir;
    if (!dir.exists(path))
    {
        return dir.mkdir(path);
    }
    return true;
}
