#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwgraphicsview.h"
#include <QGraphicsItem>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); 
    labViewCord = new QLabel("View 坐标：");
    labViewCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labViewCord);

    labSceneCord = new QLabel("Scene 坐标:");
    labSceneCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labSceneCord);

    labItemCord = new QLabel("Item 坐标:");
    labItemCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labItemCord);

    labViewSize = new QLabel();
    labSceneRect = new QLabel();
    graphicsView = new QWGraphicsView{};
    graphicsView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(labViewSize);
    layout->addWidget(labSceneRect);
    layout->addWidget(graphicsView);
    ui->centralwidget->setLayout(layout);

    graphicsView->setCursor(Qt::CrossCursor);
    graphicsView->setMouseTracking(true);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);


    connect(graphicsView, SIGNAL(mouseMovePoint(QPoint)),
            this, SLOT(on_mouseMovePoint(QPoint)));
    connect(graphicsView, SIGNAL(mouseClicked(QPoint)),
            this, SLOT(on_mouseClicked(QPoint)));
    iniGraphicsSystem();


    qDebug() << graphicsView->minimumSize();
    qDebug() << graphicsView->minimumSizeHint();

    qDebug() << ui->centralwidget->minimumSizeHint();
    qDebug() << this->minimumSizeHint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mouseMovePoint(QPoint point)
{
    // 鼠标移动事件
    labViewCord->setText(QString::asprintf("View 坐标: %d, %d", point.x(), point.y()));
    QPointF pointScene = graphicsView->mapToScene(point); // 转换到 Scene 坐标
    labSceneCord->setText(QString::asprintf("Scene 坐标: %.0f, %.0f", pointScene.x(), pointScene.y()));
}

void MainWindow::on_mouseClicked(QPoint point)
{
    // 鼠标单击事件
    QPointF pointScene = graphicsView->mapToScene(point); // 转换到 scene 坐标
    QGraphicsItem *item = scene->itemAt(pointScene, graphicsView->transform());;
    if (item != nullptr)
    {
        QPointF pointItem = item->mapFromScene(pointScene); // 图形项局部坐标
        labItemCord->setText(QString::asprintf("Item 坐标: %.0f, %.0f", pointItem.x(), pointItem.y()));
    }
}

void MainWindow::iniGraphicsSystem()
{
    // 构造 QGraphics View 的各项
    QRectF rect(-200, -100, 400, 200);
    scene = new QGraphicsScene(rect); // 逻辑坐标系定义
    graphicsView->setScene(scene);
    // 画一个矩形，大小等于scene
    QGraphicsRectItem *item = new QGraphicsRectItem(rect);
    item->setFlags(QGraphicsItem::ItemIsSelectable
                   |QGraphicsItem::ItemIsFocusable);
    QPen pen;
    pen.setWidth(2);
    item->setPen(pen);
    scene->addItem(item);

    // 画一个位于scene中心的椭圆，测试局部坐标
    QGraphicsEllipseItem *item2 = new QGraphicsEllipseItem(-100, -50, 200, 100);
    QPen pen2;
    pen2.setWidth(6);
    item2->setPen(pen2);
    item2->setPos(0, 0);
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlags(QGraphicsItem::ItemIsMovable
                    | QGraphicsItem::ItemIsSelectable
                    | QGraphicsItem::ItemIsFocusable);
    scene->addItem(item2);

    // 画一个圆，中心位于scene的边缘
    QGraphicsEllipseItem *item3 = new QGraphicsEllipseItem(-50,-50,  100,100);
    item3->setPos(rect.right(), rect.bottom());
    item3->setBrush(QBrush(Qt::red));
    item3->setFlags(QGraphicsItem::ItemIsMovable
                    | QGraphicsItem::ItemIsSelectable
                    | QGraphicsItem::ItemIsFocusable);
    scene->addItem(item3);
    scene->clearSelection();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // 窗口变化大小时的事件
    labViewSize->setText(QString::asprintf("Graphics View 坐标，左上角总是(0, 0)，宽度 = %d, 高度 = %d", graphicsView->width(), graphicsView->height()));
    QRectF rectF = graphicsView->sceneRect(); // scene 的矩形
    labSceneRect->setText(QString::asprintf("QGraphicsView::sceneRect=(Left, Top, Width, Height)=%.0f,%.0f,%.0f,%.0f",
                                            rectF.left(), rectF.top(), rectF.width(), rectF.height()));
}
