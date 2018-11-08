#include "widget.h"
#include "ui_widget.h"
#include <QTextCodec>
#include <QDir>
#include "src/01_LinearList/chapter1_part1.h"
#include "src/utils/json.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint | Qt::Dialog);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    ui->comboBox_chapter->insertItem(0, "01_LinearList");
    ui->comboBox_chapter->insertItem(1, "02_Stack & Queue");
    ui->comboBox_chapter->insertItem(2, "03_String");
    ui->comboBox_chapter->insertItem(3, "04_Tree");
    ui->comboBox_chapter->insertItem(4, "05_GeneralizedList");
    ui->comboBox_chapter->insertItem(5, "06_Graph");
    ui->comboBox_chapter->insertItem(6, "07_DynamicMemory");
    ui->comboBox_chapter->insertItem(7, "08_Search");
    ui->comboBox_chapter->insertItem(8, "09_Sorting");
    ui->comboBox_chapter->insertItem(9, "10_File");

    loadQuestion();

    int startChapter, startQuestion;
    if (QFile("config.json").exists())
    {
        bool ok;
        QtJson::JsonObject result = QtJson::parse(Tool::readFileInfo("config.json"), ok).toMap();
        if (ok)
        {
            startChapter = result["startChapter"].toInt();
            startQuestion = result["startQuestion"].toInt();
        }
        else
        {
            startChapter = 0;
            startQuestion = 0;
        }
    }
    else
    {
        startChapter = 0;
        startQuestion = 0;
    }
    ui->comboBox_chapter->setCurrentIndex(startChapter);
    slot_comboBox_chapter_currentIndexChanged(startChapter);
    ui->comboBox_question->setCurrentIndex(startQuestion);

    connect(ui->comboBox_chapter, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_comboBox_chapter_currentIndexChanged(int)));
    connect(ui->pushButton_exec, SIGNAL(clicked()), this, SLOT(slot_pushButton_exec_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadQuestion()
{
    m_bank.addQuestion(0, Question("合并顺序表", Chapter1_Part1::practice_000));
    m_bank.addQuestion(0, Question("逆序创建链表", Chapter1_Part1::practice_050));
    m_bank.addQuestion(0, Question("双向链表demo", Chapter1_Part1::practice_100));
}

void Widget::slot_comboBox_chapter_currentIndexChanged(int index)
{
    ui->comboBox_question->clear();
    index = ui->comboBox_chapter->currentIndex();
    int count = m_bank.getQuestionCount(index);
    for (int i = 0; i < count; i++)
    {
        ui->comboBox_question->insertItem(i, QString("%1. ").arg(i) + m_bank.getQuestionDescription(index, i));
    }
}

void Widget::slot_pushButton_exec_clicked()
{
    QtJson::JsonObject obj;
    obj.insert("startChapter", ui->comboBox_chapter->currentIndex());
    obj.insert("startQuestion", ui->comboBox_question->currentIndex());
    QString jsonStr = QtJson::serializeStr(obj);
    if (Tool::readFileInfo("config.json") != jsonStr)
    {
        Tool::writeFileInfo("config.json", jsonStr);
    }

    QString result;
    m_bank.execSolution(ui->comboBox_chapter->currentIndex(), ui->comboBox_question->currentIndex(), ui->textEdit_input->toPlainText(), result);
    ui->textEdit_result->setText(result);
    DEBUG<<"result:"<<result;
}
