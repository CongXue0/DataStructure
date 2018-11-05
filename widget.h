#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "src/utils/questionbank.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void loadQuestion();




    Ui::Widget *ui;

    QuestionBank m_bank;

};

#endif // WIDGET_H
