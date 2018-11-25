#-------------------------------------------------
#
# Project created by QtCreator 2018-11-02T19:09:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataStructure
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    widget.cpp \
    src/utils/tool.cpp \
    src/utils/question.cpp \
    src/utils/questionbank.cpp \
    src/01_LinearList/chapter1_part1.cpp \
    src/utils/json.cpp \
    src/11_LogicThinking/logicthinking_part1.cpp \
    src/12_ClassicAlgorithm/classicalgorithm_part1.cpp \
    src/08_Search/search.cpp \
    src/09_Sorting/sorting.cpp \
    src/09_Sorting/chapter9_part1.cpp \
    src/08_Search/chapter8_part1.cpp \
    src/utils/mydebug.cpp \
    src/02_StackAndQueue/chapter2_part1.cpp \
    src/04_Tree/chapter4_part1.cpp

HEADERS  += widget.h \
    src/utils/tool.h \
    src/utils/question.h \
    src/utils/questionbank.h \
    src/01_LinearList/chapter1_part1.h \
    src/utils/json.h \
    src/01_LinearList/seqlist.h \
    src/01_LinearList/linklist.h \
    src/01_LinearList/doublelinklist.h \
    src/11_LogicThinking/logicthinking_part1.h \
    src/12_ClassicAlgorithm/classicalgorithm_part1.h \
    src/08_Search/search.h \
    src/09_Sorting/sorting.h \
    src/09_Sorting/chapter9_part1.h \
    src/08_Search/chapter8_part1.h \
    src/utils/mydebug.h \
    src/02_StackAndQueue/linkstack.h \
    src/02_StackAndQueue/seqstack.h \
    src/02_StackAndQueue/chapter2_part1.h \
    src/02_StackAndQueue/seqqueue.h \
    src/02_StackAndQueue/linkqueue.h \
    src/04_Tree/chapter4_part1.h \
    src/04_Tree/binarytree.h

FORMS    += widget.ui
