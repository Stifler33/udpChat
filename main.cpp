#include "udpchat.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    udpChat w;
    w.show();
    return a.exec();
}
