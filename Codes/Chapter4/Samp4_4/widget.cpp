#include "widget.h"
#include "./ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->sliderBlue, SIGNAL(valueChanged(int)), this, SLOT(on_sliderRed_valueChanged(int)));
    connect(ui->sliderGreen, SIGNAL(valueChanged(int)), this, SLOT(on_sliderRed_valueChanged(int)));
    connect(ui->sliderAlpha, SIGNAL(valueChanged(int)), this, SLOT(on_sliderRed_valueChanged(int)));

    ui->sliderRed->setMaximum(255);
    ui->sliderBlue->setMaximum(255);
    ui->sliderGreen->setMaximum(255);
    ui->sliderAlpha->setMaximum(255);

    ui->radioDec->setChecked(true);
    ui->sliderAlpha->setValue(255);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_sliderRed_valueChanged(int value)
{
    // 拖动Red、Green、Blue 颜色滑动条时设置textEdit 的底色
    Q_UNUSED(value);
    QColor color;
    int R = ui->sliderRed->value();
    int G = ui->sliderGreen->value();
    int B = ui->sliderBlue->value();
    int alpha = ui->sliderAlpha->value();

    qDebug() << "R:" << R << ", G: "<< G << ", B: " << B << ", Alpha: " << alpha;
    color.setRgb(R,G,B,alpha); // 使用 QColor 的 setRgb() 函数获得颜色
    QPalette pal = ui->textEdit->palette();
    pal.setColor(QPalette::Base, color); // 设置底色
    ui->textEdit->setPalette(pal);
}


void Widget::on_dial_valueChanged(int value)
{
    // 设置LCD的显示值等于Dial的值
    ui->lcdNumber->display(value);
}


void Widget::on_radioDec_clicked()
{
    // 设置LCD显示十进制数
    ui->lcdNumber->setDigitCount(3); // 设置位数
    ui->lcdNumber->setDecMode();
}


void Widget::on_radioBin_clicked()
{
    // 设置LCD显示二进制数
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->setBinMode();
}


void Widget::on_radioOct_clicked()
{
    // 设置LCD显示8进制数
    ui->lcdNumber->setDigitCount(4);
    ui->lcdNumber->setOctMode();
}


void Widget::on_radioHex_clicked()
{
    // 设置LCD显示十六进制数
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setHexMode();
}

