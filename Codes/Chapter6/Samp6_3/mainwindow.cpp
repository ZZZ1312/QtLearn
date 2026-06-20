#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QCloseEvent>
#include "qformdoc.h"
#include "qformtable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);

    this->setWindowState(Qt::WindowMaximized);

    pixmap = new QPixmap(":/images/images/back.png");
}

MainWindow::~MainWindow()
{
    delete pixmap;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    // 绘制窗口背景图片
    Q_UNUSED(event);
    QPainter painter(this);
    QRect targetRect(
        0,
        ui->toolBar->height(),
        width(),
        height() - ui->toolBar->height() - ui->statusbar->height());

    painter.drawPixmap(targetRect,*pixmap);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    auto ret = QMessageBox::question(this, "关闭程序", "是否确认关闭程序?");
    if (ret == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();

}

void MainWindow::on_actEmbeddedWindget_triggered()
{
    // 创建 QFormDoc 窗体，并在 tabWidget中显示
    QFormDoc *formDoc = new QFormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除
    int cur = ui->tabWidget->addTab(formDoc, QString::asprintf("Doc %d", ui->tabWidget->count() ));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void MainWindow::on_actIndependentWidget_triggered()
{
    QFormDoc *formDoc = new QFormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除
    formDoc->setWindowFilePath("基于QWidget的窗体，无父窗体，关闭时删除");
    formDoc->setWindowFlag(Qt::Window, true);

    formDoc->setWindowOpacity(0.9); // 设置不透明度为0.9，稍微透明
    formDoc->show(); // 在单独的窗口中显示
}


void MainWindow::on_actEmbeddeddMainWindow_triggered()
{
    QFormTable *formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动杀出
    int cur = ui->tabWidget->addTab(formTable, QString::asprintf("Table %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void MainWindow::on_actIndependentMainWindow_triggered()
{
    QFormTable *formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    formTable->setWindowTitle("基于 QMainWindow 的窗口，指定父窗口，关闭时删除");
    formTable->show();
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    // 关闭 Tab
    if (index < 0)
        return;
    QWidget *aForm = ui->tabWidget->widget(index);
    aForm->close();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    bool en = ui->tabWidget->count() > 0; // 再无分页
    ui->tabWidget->setVisible(en);
}