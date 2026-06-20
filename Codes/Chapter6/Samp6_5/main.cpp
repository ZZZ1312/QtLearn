#include "mainwindow.h"
#include "qdlglogin.h"

#include <QApplication>
#include <QPixmap>
#include <QThread> // 模拟耗时用
#include <QProgressBar>
#include <QTimer>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDlgLogin *dlgLogin = new QDlgLogin();
    if (dlgLogin->exec() == QDialog::Accepted)
    {
        MainWindow w;
        w.show();
        return a.exec();
    }
    else
        return 0;
}