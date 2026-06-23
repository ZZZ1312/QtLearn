#include "widget.h"
#include "./ui_widget.h"
#include <QPainter>

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


void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int W = width();
    int H = height();
    int side = qMin(W, H); // 取长和宽的较小值
    QRect rect((W - side) / 2, (H - side) / 2, side, side); // view Port 举行去
    painter.drawRect(rect); // Viewport 的矩形区域
    painter.setViewport(rect);
    painter.setWindow(-100, -100, 200,200); // 设置窗口大小，逻辑坐标
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置画笔
    QPen pen;
    pen.setWidth(1); // 线宽
    pen.setColor(Qt::red); // 划线颜色
    pen.setStyle(Qt::SolidLine); // 线的类型
    painter.setPen(pen);
    for (int i = 0;i < 36; ++i)
    {
        painter.drawEllipse(QPoint(50, 0), 50, 50);
        painter.rotate(10);
    }
}

