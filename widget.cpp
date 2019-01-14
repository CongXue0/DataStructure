#include "widget.h"
#include "ui_widget.h"
#include <QTextCodec>
#include <QDir>
#include "src/01_LinearList/chapter1_part1.h"
#include "src/utils/json.h"
#include "src/08_Search/chapter8_part1.h"
#include "src/09_Sorting/chapter9_part1.h"
#include "src/02_StackAndQueue/chapter2_part1.h"
#include "src/04_Tree/chapter4_part1.h"
#include "src/06_Graph/chapter6_part1.h"
#include "src/utils/virtualio.h"
#include "src/03_String/chapter3_part1.h"

void Widget::loadQuestion()
{
    m_bank.addQuestion(0, Question("链表demo", Chapter1_Part1::practice_000, 1, "严蔚敏"));
    m_bank.addQuestion(0, Question("双向链表demo", Chapter1_Part1::practice_001, 1, "严蔚敏"));
    m_bank.addQuestion(0, Question("顺序表的逆置", Chapter1_Part1::practice_002, 1, "王道"));
    m_bank.addQuestion(0, Question("删除顺序表中[s,t]之间的元素", Chapter1_Part1::practice_003, 2, "王道"));
    m_bank.addQuestion(0, Question("互换数组区间", Chapter1_Part1::practice_004, 3, "王道"));
    m_bank.addQuestion(0, Question("主元素", Chapter1_Part1::practice_005, 3, "王道"));
    m_bank.addQuestion(0, Question("逆序创建链表", Chapter1_Part1::practice_050, 1, "严蔚敏"));
    m_bank.addQuestion(0, Question("合并顺序表", Chapter1_Part1::practice_051, 1, "严蔚敏"));
    m_bank.addQuestion(0, Question("祖玛", Chapter1_Part1::practice_052, 4, "邓俊辉"));

    m_bank.addQuestion(1, Question("栈与队列demo", Chapter2_Part1::practice_000, 1, "邓俊辉"));
    m_bank.addQuestion(1, Question("进制转换", Chapter2_Part1::practice_001, 2, "邓俊辉"));
    m_bank.addQuestion(1, Question("就近匹配", Chapter2_Part1::practice_002, 2, "邓俊辉"));
    m_bank.addQuestion(1, Question("栈混洗", Chapter2_Part1::practice_003, 2, "邓俊辉"));
    m_bank.addQuestion(1, Question("表达式求值", Chapter2_Part1::practice_004, 3, "扫地僧"));

    m_bank.addQuestion(2, Question("串demo1", Chapter3_Part1::practice_000, 2, "大话"));
    m_bank.addQuestion(2, Question("串demo2", Chapter3_Part1::practice_001, 2, "大话"));
    m_bank.addQuestion(2, Question("串demo3", Chapter3_Part1::practice_002, 2, "大话"));
    m_bank.addQuestion(2, Question("KMP算法", Chapter3_Part1::practice_010, 3, "大话"));

    m_bank.addQuestion(3, Question("二叉树demo", Chapter4_Part1::practice_000, 3, "扫地僧"));
    m_bank.addQuestion(3, Question("线索二叉树demo", Chapter4_Part1::practice_001, 3, "大话"));
    m_bank.addQuestion(3, Question("二叉树层级打印", Chapter4_Part1::practice_002, 3, "无"));
    m_bank.addQuestion(3, Question("平衡二叉树demo", Chapter4_Part1::practice_003, 4, "王道"));

    m_bank.addQuestion(5, Question("邻接矩阵demo", Chapter6_Part1::practice_000, 4, "王道"));
    m_bank.addQuestion(5, Question("邻接表demo", Chapter6_Part1::practice_001, 4, "王道"));
    m_bank.addQuestion(5, Question("单源最短路径", Chapter6_Part1::practice_020, 3, "王道"));
    m_bank.addQuestion(5, Question("Prim算法", Chapter6_Part1::practice_021, 3, "王道"));
    m_bank.addQuestion(5, Question("Kruskal算法", Chapter6_Part1::practice_022, 3, "王道"));
    m_bank.addQuestion(5, Question("Dijkstra算法", Chapter6_Part1::practice_023, 4, "王道"));
    m_bank.addQuestion(5, Question("Floyd算法", Chapter6_Part1::practice_024, 4, "王道"));
    m_bank.addQuestion(5, Question("拓扑排序", Chapter6_Part1::practice_025, 3, "王道"));
    m_bank.addQuestion(5, Question("关键路径", Chapter6_Part1::practice_026, 4, "王道"));

    m_bank.addQuestion(7, Question("哈希表demo", Chapter8_Part1::practice_000, 3, "王道"));
    m_bank.addQuestion(7, Question("红黑树demo", Chapter8_Part1::practice_001, 4, "网络"));

    m_bank.addQuestion(8, Question("排序demo", Chapter9_Part1::practice_000, 1, "王道"));
    m_bank.addQuestion(8, Question("直接插入排序demo", Chapter9_Part1::practice_001, 2, "大话"));
    m_bank.addQuestion(8, Question("希尔排序demo", Chapter9_Part1::practice_002, 2, "大话"));
    m_bank.addQuestion(8, Question("堆排序demo", Chapter9_Part1::practice_003, 3, "大话"));
    m_bank.addQuestion(8, Question("快速排序demo", Chapter9_Part1::practice_004, 3, "大话"));
    m_bank.addQuestion(8, Question("计数排序demo", Chapter9_Part1::practice_005, 3, "大话"));
    m_bank.addQuestion(8, Question("范围查询(Range)", Chapter9_Part1::practice_000, 4, "邓俊辉"));
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint | Qt::Dialog);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    MyDebug::setDebugFlag(true);

    ui->comboBox_chapter->insertItem(0, "01_LinearList");
    ui->comboBox_chapter->insertItem(1, "02_StackAndQueue");
    ui->comboBox_chapter->insertItem(2, "03_String");
    ui->comboBox_chapter->insertItem(3, "04_Tree");
    ui->comboBox_chapter->insertItem(4, "05_GeneralizedList");
    ui->comboBox_chapter->insertItem(5, "06_Graph");
    ui->comboBox_chapter->insertItem(6, "07_DynamicMemory");
    ui->comboBox_chapter->insertItem(7, "08_Search");
    ui->comboBox_chapter->insertItem(8, "09_Sorting");
    ui->comboBox_chapter->insertItem(9, "10_File");
    ui->comboBox_chapter->insertItem(10, "11_LogicThinking");
    ui->comboBox_chapter->insertItem(11, "12_ClassicAlgorithm");

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
    connect(ui->pushButton_exec, SIGNAL(clicked()), this, SLOT(slot_pushButton_exec_clicked()), Qt::QueuedConnection);
}

Widget::~Widget()
{
    delete ui;
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

    MyDebug::clear();
    QString input = ui->textEdit_input->toPlainText();
    VIO::clearInput();
    VIO::setInput(input);
    m_bank.execSolution(ui->comboBox_chapter->currentIndex(), ui->comboBox_question->currentIndex());
    QString result = MyDebug::infoPop();
    ui->textEdit_result->setText(result);
}
