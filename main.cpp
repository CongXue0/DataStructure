#include "widget.h"
#include <QApplication>
#include <time.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(time(NULL));

    Widget w;
    w.show();

    return a.exec();
}
