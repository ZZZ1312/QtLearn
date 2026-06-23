#include "widget.h"
#include "./ui_widget.h"
#include <QPainter>
#include <QLinearGradient>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // resize(100, 100);
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
    QRect rect((W - side)/2, (H - side) / 2, side, side);
    painter.drawRect(rect); // Viewport 大小
    painter.setViewport(rect); // 设置 Viewport
    painter.setWindow(-100, -100, 200, 200);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置画笔
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    // 线性渐变
    QLinearGradient linearGrad(0, 0, 100, 0);
    linearGrad.setColorAt(0, Qt::yellow);
    linearGrad.setColorAt(1, Qt::green);
    linearGrad.setSpread(QGradient::PadSpread);
    painter.setBrush(linearGrad);

    // 设置复合模式
    // painter.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
    painter.setCompositionMode(QPainter::CompositionMode_Difference);

    for (int i = 0; i < 36; ++i)
    {
        painter.drawEllipse(QPoint(50,0), 50, 50);
        painter.rotate(10);
    }

}

