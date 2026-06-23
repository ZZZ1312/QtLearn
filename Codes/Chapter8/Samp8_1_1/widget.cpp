#include "widget.h"
#include "./ui_widget.h"
#include <QPainter>
#include <QVector>
#include <QPainterPath>
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
    Q_UNUSED(event);
    QPainter painter(this);

    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    int W = this->rect().width();
    int H = this->rect().height();

    // 画弧线
    // QRect rect(W/4, H/4, W/2, H/2);
    // int startAngle = 90 * 16; // 起始90
    // int spanAngle = 90 * 16;
    // painter.drawArc(rect, startAngle, spanAngle);
    // // 画一段弦
    // painter.drawChord(rect, startAngle,spanAngle);

    // 根据给定的点画凸多变型
    // QPoint points[4]= {
    //     QPoint(5*W / 12, H/4),
    //     QPoint(3*W/4, 5 * H / 12),
    //     QPoint(5*W/12, 3* H/4),
    //     QPoint(W/4, 5 * H / 12)
    // };
    // painter.drawConvexPolygon(points, 4);

    // 画矩形
    // QRect targetRect{W/4, H/4, W/2, H/2};
    // painter.drawRect(targetRect);

    // 画椭圆
    // QRect rect(W/4, H/4, W/2, H/3);
    // painter.drawEllipse(rect);

    // 在规定的区域绘制图片
    // QRect rect{W/4, H/4, W/2, H/2};
    // QImage image(":/images/images/Application.ico");
    // painter.drawImage(rect,image);

    // 画直线
    // QLine line(W/4, H/4, W/2, H/2);
    // painter.drawLine(line);

    // 画一批直线
    // QRect rect(W/4, H/4, W/2, H/2);
    // QVector<QLine> lines;
    // lines.append(QLine(rect.topLeft(), rect.bottomRight()));
    // lines.append(QLine(rect.topRight(), rect.bottomLeft()));
    // lines.append(QLine(rect.topLeft(), rect.bottomLeft()));
    // lines.append(QLine(rect.topRight(), rect.bottomRight()));
    // painter.drawLines(lines);

    // 绘制由 QPainterPath 对象定义的路线
    // QRect rect(W/4, H/4, W/2, H/2);
    // QPainterPath path;
    // path.addEllipse(rect);
    // path.addRect(rect);
    // painter.drawPath(path);

    // 绘制扇形
    // QRect rect(W/4, H/4, W/2, H/2);
    // int startAngle = 40 * 16;
    // int spanAngle = 120 * 16;
    // painter.drawPie(rect, startAngle, spanAngle);

    // 绘制 pixmap 图片
    // QRect rect(W/4, H/4, W/2, H/2);
    // QPixmap pixmap(":/images/images/Application.ico");
    // painter.drawPixmap(rect, pixmap);

    // 绘制一个点
    painter.drawPoint(QPoint(W/2, H/2));

    // 画一批点
    QPoint points[] = {
        QPoint(5 * W / 12, H/4),
        QPoint(3 * W / 4, 5 * H/ 12),
        QPoint(2 * W / 4, 5 * H / 12),
    };
    painter.drawPoints(points, 3);

}

