#include "qwdlgmanual.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWDlgManual w;
    w.show();
    return QCoreApplication::exec();
}
