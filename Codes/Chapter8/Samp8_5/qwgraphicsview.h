#ifndef QWGRAPHICSVIEW_H
#define QWGRAPHICSVIEW_H

#include <QGraphicsView>

class QWGraphicsView : public QGraphicsView
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

public:
    QWGraphicsView(QWidget *parent = nullptr);

signals:
    void mouseMovePoint(QPoint point);

    void mouseClicked(QPoint point);

    void mouseRightClicked(QPoint point);

    void mouseDoubleClick(QPoint point);

    void keyPress(QKeyEvent *event);
    // QWidget interface

};

#endif // QWGRAPHICSVIEW_H
