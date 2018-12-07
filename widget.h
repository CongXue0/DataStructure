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
    void loadQuestion();
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void slot_comboBox_chapter_currentIndexChanged(int index);
    void slot_pushButton_exec_clicked();

private:
    Ui::Widget *ui;
    QuestionBank m_bank;

};

#endif // WIDGET_H
