#include "zombiehordele.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ZombieHordeLE w;
    w.show();

    return a.exec();
}
