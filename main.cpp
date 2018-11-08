#include "widget.h"
#include <QApplication>
#include <time.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(time(nullptr));

    Widget w;
    w.show();

    return a.exec();
}
