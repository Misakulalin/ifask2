#include "ifask2.h"
#include<qfile.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QFile qss(":/style/stylesheet.qss");
    QApplication a(argc, argv);
    ifask2 w;
    w.show();
    return a.exec();
}
