#include "widget.h"
#include "ui_widget.h"
#include <QTextCodec>
#include <QDir>
#include "src/01_LinearList/chapter1_part1.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint | Qt::Dialog);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QDir::setCurrent(QCoreApplication::applicationDirPath());


}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadQuestion()
{
    m_bank.addQuestion(0, Question("", Chapter1_Part1::question1));
}
