#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    QString fullPath = QFileDialog::getOpenFileName(nullptr, "选择文件", QDir::currentPath());

    return 0;
}