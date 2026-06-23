#include "qwgraphicsview.h"
#include <QMouseEvent>

QWGraphicsView::QWGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{}



void QWGraphicsView::mousePressEvent(QMouseEvent *event)
{
        QPoint point = event->pos();
    if (event->button() == Qt::LeftButton)
    {
        emit mouseClicked(point);
    }
    else if (event->button() == Qt::RightButton)
    {
        emit mouseRightClicked(point);
    }
    QGraphicsView::mousePressEvent(event);
}

void QWGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint point = event->pos();
        emit mouseDoubleClick(point);
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}


void QWGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标移动事件
    QPoint point = event->pos();
    emit mouseMovePoint(point);
    QGraphicsView::mouseMoveEvent(event);
}

void QWGraphicsView::keyPressEvent(QKeyEvent *event)
{
    emit keyPress(event);
    QGraphicsView::keyPressEvent(event);
}

