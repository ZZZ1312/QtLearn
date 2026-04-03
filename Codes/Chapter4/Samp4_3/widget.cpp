#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnCal_clicked()
{
    // 计算
    int num = ui->spinNum->value();
    double price = ui->doubleSpinPrice->value();
    double total = num * price;
    ui->doubleSpinTotal->setValue(total);
}


void Widget::on_btnDecTrans_clicked()
{
    // 读取十进制数，以其他进制显示
    int value = ui->spinDec->value();
    ui->spinBin->setValue(value);
    ui->spinHex->setValue(value);
}


void Widget::on_btnBinTrans_clicked()
{
    // 读取二进制数，以其他进制显示
    int value = ui->spinBin->value();
    ui->spinDec->setValue(value);
    ui->spinHex->setValue(value);
}


void Widget::on_btnHexTrans_clicked()
{
    // 读取十六进制数，以其他进制显示
    int value = ui->spinHex->value();
    ui->spinDec->setValue(value);
    ui->spinBin->setValue(value);
}

