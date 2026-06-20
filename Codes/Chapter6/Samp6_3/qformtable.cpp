#include "qformtable.h"
#include "ui_qformtable.h"
#include <QMessageBox>

QFormTable::QFormTable(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QFormTable)
{
    ui->setupUi(this);
}

QFormTable::~QFormTable()
{
    QMessageBox::information(this, "消息", "QFormTable 关闭");
    delete ui;
}
