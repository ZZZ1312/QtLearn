#include "widget.h"
#include "./ui_widget.h"
#include <QPainter>
#include <QPoint>
#include <QPainterPath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setPalette(QPalette(Qt::white)); // 设置窗口背景为白色
    setAutoFillBackground(true);
    resize(600, 300);// 固定初始化窗口大小
}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // 生成五角星的 5 个顶点坐标，假设原点在五角星中心
    qreal R = 100; // 坐标
    const qreal Pi = 3.14159;
    qreal deg = Pi * 72 / 180;
    QPoint points[5] = {
        QPoint(R, 0),
        QPoint(R * std::cos(deg), -R * std::sin(deg)),
        QPoint(R * std::cos(2 * deg), -R * std::sin(2 * deg)),
        QPoint(R * std::cos(3 * deg), -R * std::sin(3 * deg)),
        QPoint(R * std::cos(4 * deg), -R * std::sin(4 * deg))
    };

    // 设置字体
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);

    // 设置画笔
    QPen penLine;
    penLine.setWidth(2);
    penLine.setColor(Qt::blue);
    penLine.setStyle(Qt::SolidLine);
    penLine.setCapStyle(Qt::FlatCap);
    penLine.setJoinStyle(Qt::BevelJoin);
    painter.setPen(penLine);

    // 设置画刷
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    // 设计绘制五角星的 PainterPath，以便重复使用
    QPainterPath startPath;
    startPath.moveTo(points[0]);
    startPath.lineTo(points[2]);
    startPath.lineTo(points[4]);
    startPath.lineTo(points[1]);
    startPath.lineTo(points[1]);
    startPath.lineTo(points[3]);
    startPath.closeSubpath(); // 闭合路径，最后一个点与第一个点相连

    startPath.addText(points[0], font, "0");
    startPath.addText(points[1], font, "1");
    startPath.addText(points[2], font, "2");
    startPath.addText(points[3], font, "3");
    startPath.addText(points[4], font, "4");

    // 绘图
    painter.save(); // 保存坐标状态
    painter.translate(100, 200); // 平移
    painter.drawPath(startPath); // 画星星
    painter.drawText(0, 0, "S1");
    painter.restore(); // 恢复坐标状态

    painter.translate(300, 120); // 平移
    painter.scale(0.8, 0.8);
    painter.rotate(90); // 顺时针旋转 90 度
    painter.drawPath(startPath); // 画星星
    painter.drawText(0, 0, "S2");

    painter.resetTransform(); // 复位所有变化
    painter.translate(500, 120);
    painter.rotate(-45);
    painter.drawPath(startPath);
    painter.drawText(0, 0 , "S3");

}

