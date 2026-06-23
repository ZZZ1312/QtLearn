#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qwgraphicsview.h"
#include <QTime>
#include <QRandomGenerator>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QColorDialog>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labViewCord = new QLabel("View 坐标: ");
    labViewCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labViewCord);

    labSceneCord = new QLabel("Scene 坐标:");
    labSceneCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labSceneCord);

    labItemCord = new QLabel("Item 坐标: ");
    labItemCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labItemCord);

    labItemInfo = new QLabel("ItemInfo: ");
    labItemInfo->setMinimumWidth(200);
    ui->statusbar->addWidget(labItemInfo);

    view = new QWGraphicsView{};
    setCentralWidget(view);

    scene = new QGraphicsScene(-300, -200, 600, 200);
    view->setScene(scene);
    view->setCursor(Qt::CrossCursor);
    view->setMouseTracking(true);
    view->setDragMode(QGraphicsView::RubberBandDrag);

    connect(view, SIGNAL(mouseMovePoint(QPoint)),
            this, SLOT(on_mouseMovePoint(QPoint)));
    connect(view, SIGNAL(mouseClicked(QPoint)),
            this, SLOT(on_mouseClicked(QPoint)));
    connect(view, SIGNAL(mouseDoubleClick(QPoint)),
            this, SLOT(on_mouseDoubleClicke(QPoint)));
    connect(view, SIGNAL(keyPress(QKeyEvent*)),
            this, SLOT(on_keyPress(QKeyEvent*)));
    connect(view, SIGNAL(mouseRightClicked(QPoint)),
            this, SLOT(on_mouseRightClicked(QPoint)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mouseMovePoint(QPoint point)
{
    // 鼠标移动事件
    labViewCord->setText(QString::asprintf("View 坐标: %d,%d", point.x(), point.y()));
    QPointF pointScene = view->mapToScene(point); // 转换到 scene 坐标
    labSceneCord->setText(QString::asprintf("Scene 坐标: %0.f, %0.f", pointScene.x(), pointScene.y()));
}

void MainWindow::on_mouseRightClicked(QPoint point)
{
    QPointF pointScene = view->mapToScene(point);
    QGraphicsItem *item = scene->itemAt(pointScene, view->transform());
    if (item != nullptr)
    {
        QMenu menuList;
        menuList.addAction("测试菜单项1");
        menuList.addSection("第二个段");
        menuList.addAction("测试菜单项2");
        menuList.exec(QCursor::pos());

    }
}

void MainWindow::on_mouseClicked(QPoint point)
{
    // 鼠标单击
    QPointF pointScene = view->mapToScene(point);
    QGraphicsItem *item = scene->itemAt(pointScene, view->transform());
    if (item != nullptr)
    {
        QPointF pointItem = item->mapFromScene(pointScene);
        labItemCord->setText(QString::asprintf("Item 坐标: %.0f, %.0f", pointItem.x(), pointItem.y()));
        labItemInfo->setText(item->data(ItemDesciption).toString() + ", ItemId=" + item->data(ItemId).toString());
    }
}

void MainWindow::on_mouseDoubleClicke(QPoint point)
{
    // 鼠标双击
    QPointF pointScene = view->mapToScene(point); // 转换到 scene 坐标
    QGraphicsItem *item = nullptr;
    item = scene->itemAt(pointScene, view->transform());
    if (item == nullptr)
        return;
    switch (item->type())
    {
    case QGraphicsRectItem::Type:
    {
        QGraphicsRectItem *theItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
        QColor targetColor = QColorDialog::getColor(theItem->brush().color());
        theItem->setBrush(QBrush(targetColor));
        break;
    }
    case QGraphicsEllipseItem::Type:
    {
        QGraphicsEllipseItem *theItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
        QColor targetColor = QColorDialog::getColor(theItem->brush().color());
        theItem->setBrush(QBrush(targetColor));
        break;
    }
    }
}

void MainWindow::on_keyPress(QKeyEvent *event)
{

}






void MainWindow::on_actItem_Ellipse_triggered()
{
    // 创建椭圆
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(-50,-30,100,60);
    item->setFlags(QGraphicsItem::ItemIsMovable
                  | QGraphicsItem::ItemIsSelectable
                  | QGraphicsItem::ItemIsFocusable);
    item->setBrush(QBrush(Qt::blue));
    item->setZValue(++frontZ);
    int randX = QRandomGenerator::global()->bounded(100);
    int randY = QRandomGenerator::global()->bounded(100);
    item->setPos(-50 + randX, -50 + randY);
    item->setData(ItemId, ++seqNum);
    item->setData(ItemDesciption, "椭圆");

    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}


void MainWindow::on_actZoomIn_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setScale(0.1 + item->scale());
    }
    else
        view->scale(1.1, 1.1);
}


void MainWindow::on_actZoomOut_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setScale(item->scale() - 0.1);
    }
    else
        view->scale(0.9,0.9);
}


void MainWindow::on_actRestore_triggered()
{
    // 取消所有变换
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->resetTransform();
        item->setRotation(0);
        item->setScale(1.0);
    }
    else
        view->resetTransform();
}


void MainWindow::on_actRotateLeft_triggered()
{
    // 逆时针旋转，也就是左旋
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setRotation(-30 + item->rotation());
    }
    else
        view->rotate(-30);
}


void MainWindow::on_actEdit_Front_triggered()
{
    // 前置
    int cnt = scene->selectedItems().count();
    if (cnt > 0)
    {
        // 只处理选中的第一个图形项
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setZValue(++frontZ);
    }
}


void MainWindow::on_actEdit_Back_triggered()
{
    // 后置
    int cnt = scene->selectedItems().count();
    if (cnt > 0)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setZValue(--backZ);
    }
}


void MainWindow::on_actGroup_triggered()
{
    // 组合
    int cnt = scene->selectedItems().count();
    if (cnt > 1)
    {
        QGraphicsItemGroup *group = new QGraphicsItemGroup;
        scene->addItem(group);
        for (int i = 0;i < cnt; ++i)
        {
            QGraphicsItem *item = scene->selectedItems().at(0);
            item->setSelected(false);
            item->clearFocus();
            group->addToGroup(item);
        }
        group->setFlags(QGraphicsItem::ItemIsMovable
                        | QGraphicsItem::ItemIsSelectable
                        | QGraphicsItem::ItemIsFocusable);
        group->setZValue(++frontZ);
        scene->clearSelection();
        group->setSelected(true);
    }
}


void MainWindow::on_actGroupBreak_triggered()
{
    // 打散
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItemGroup *group;
        group = static_cast<QGraphicsItemGroup*>(scene->selectedItems().at(0));
        scene->destroyItemGroup(group);
    }
}


void MainWindow::on_actEdit_Delete_triggered()
{
    // 删除所有选中的图形项
    int cnt = scene->selectedItems().count();
    if (cnt > 0)
    {
        for (int i = 0; i < cnt; ++i)
        {
            QGraphicsItem *item = scene->selectedItems().at(0);
            scene->removeItem(item); // 删除图形项
        }
    }
}
