#include <QApplication>
#include "mywindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyWindow paint;

    paint.show();

    return a.exec();
}
