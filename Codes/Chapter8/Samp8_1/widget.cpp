#include "widget.h"
#include "./ui_widget.h"
#include <QPainter>
#include <QPixmap>

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
    QPainter painter(this); // 创建 QPainter 对象
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    int w = this->width();
    int h = this->height();


    // 设置画笔
    QPen pen;
    pen.setWidth(3); // 线宽
    pen.setColor(Qt::red); // 划线颜色
    pen.setStyle(Qt::SolidLine); // 线的样式，实线、虚线等
    pen.setCapStyle(Qt::FlatCap); // 线端点样式
    pen.setJoinStyle(Qt::BevelJoin); // 线的连接点样式
    painter.setPen(pen);
    // 设置画刷
    QBrush brush;
    // 1. 单一颜色填充
    // brush.setColor(Qt::yellow); // 画刷颜色
    // brush.setStyle(Qt::SolidPattern); // 画刷填充样式

    // 使用图片进行材质填充
    // QPixmap texturePixmap(":/images/images/eyes.png");
    // QPixmap texturePixmap(":/images/images/dog.png");
    // brush.setStyle(Qt::TexturePattern);
    // brush.setTexture(texturePixmap);

    // 使用垂直线填充
    // brush.setColor(Qt::green);
    // brush.setStyle(Qt::HorPattern);

    // 使用倾斜交叉线填充
    // brush.setColor(Qt::black);
    // brush.setStyle(Qt::DiagCrossPattern);

    // 使用水平网格线填充
    // brush.setColor(Qt::gray);
    // brush.setStyle(Qt::CrossPattern);

    // 径向渐变
    QRadialGradient radialGrad(w/2, h/2, qMax(w/8, h/8), w/2, h/2);
    radialGrad.setColorAt(0, Qt::red);
    radialGrad.setColorAt(0.5, Qt::green);
    radialGrad.setColorAt(1, Qt::blue);
    radialGrad.setSpread(QGradient::ReflectSpread);
    painter.setBrush(radialGrad);

    // 线性渐变
    // QRect rect = this->rect();
    // QLinearGradient linearGrad(rect.left(), rect.top(), rect.right(), rect.top() );
    // linearGrad.setColorAt(0, Qt::blue); // 起点颜色
    // linearGrad.setColorAt(0.5, Qt::green);
    // linearGrad.setColorAt(1, Qt::red);
    // linearGrad.setSpread(QGradient::RepeatSpread); // 展布模式
    // painter.setBrush(linearGrad);

    // QConicalGradient coniGrad(w/2, h/2, 45);
    // coniGrad.setColorAt(0, Qt::yellow);
    // coniGrad.setColorAt(0.5, Qt::blue);
    // coniGrad.setColorAt(1, Qt::green);
    // painter.setBrush(coniGrad);

    painter.drawRect(this->rect());
}
