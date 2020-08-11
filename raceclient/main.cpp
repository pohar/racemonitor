#include "RaceClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RaceClient w;
    w.show();

    return a.exec();
}
