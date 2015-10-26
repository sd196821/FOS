#include "fos_spd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FOS_SPD w;
    w.show();

    return a.exec();
}
